#include "filecopyer.h"
//FileCopyer::FileCopyer()
//{
//    meas_file = "";
//}

void FileCopyer::startThread(QString fileName)
{
    meas_file = fileName;

    single_segd_rev2_files* segd_;

//    qDebug() << "fileName" << meas_file;
//    qDebug() << "fileName" << meas_file.mid(0, meas_file.lastIndexOf("/"));
    QString dir_meas_file = meas_file.mid(0, meas_file.lastIndexOf("/")+1);
    Measurement* meas_ = new Measurement(meas_file);
    //QTime time_between =meas_->getTimeStop() - meas_->getTimeStart();
//    int count_measures = QTime(0,0,0).msecsTo(meas_->getTimeStop()) - QTime(0,0,0).msecsTo(meas_->getTimeStart());
//    qDebug() << "raznost msec" << count_measures;
//    qDebug() << "Time Start" << meas_->getTimeStart();
//    qDebug() << "Time Stop" << meas_->getTimeStop();

//    qDebug() << "num Dwnholes" << meas_->getNumDnHoleModules();
//    qDebug() << "num Upholes" << meas_->getNumUpHoleModules();
//    QDate date_tmp = meas_->getDate();
//    QTime time_tmp = meas_->getTime();

    uint device_downHoles = 0;       //Количество подземных модулей
    uint device_UpHoles = 0;
    uint device_tbf  = 1;
    uint device_sync = 1;

    device_downHoles = meas_->getNumDnHoleModules() * 3;
//    device_UpHoles = meas_->getNumUpHoleModules();
    device_UpHoles = 4; //max 4 device          /* TODO */
    /* Обработка SGD файлов в один файл */
    int number_files = 0;

    QDir dir(dir_meas_file);
    QStringList lis_file;

    head_rev2_1 header_sgd_rev2_1;

    /* Начинаем проверять наличие файлов и объединять их */
    do{
        lis_file.clear();
        dir.setNameFilters(QStringList(QString::number(number_files) + "*.sgd"));
        lis_file = dir.entryList(QDir::Files, QDir::Name);
        //qDebug() << lis_file.count();
        if(lis_file.isEmpty())
            continue;
        segd_ = new single_segd_rev2_files();
        segd_->setFileName(dir_meas_file+QString::number(number_files)+"_meas_.sgd");

        QStringList lis_file_tmp;

        /* Проверим на наличие данных в файлах измерений и запишем в QStringList lis_file_tmp*/
        bool statusFileData = false;
        for (const auto& filName : qAsConst(lis_file) )
        {
            statusFileData = segd_->checkData(dir_meas_file+filName);
            //qDebug() << filName << statusFileData;

            if(filName.contains("DownnHole_device")){
                if(statusFileData == false)
                    device_downHoles -= 1;
                else
                    lis_file_tmp.append(filName);
            }
            else if(filName.contains("UpHole_device")){
                if(statusFileData == false)
                    device_UpHoles -= 1;

                else{
                    //qDebug() << "name files UpHole" << filName;
                    lis_file_tmp.append(filName);
                }
            }
            else if(filName.contains("Sync_device")){

                if(statusFileData == false)
                    device_sync = 0;
                else
                    lis_file_tmp.append(filName);
            }
            else if(filName.contains("TBF")){

                if(statusFileData == false)
                    device_tbf = 0;
                else
                    lis_file_tmp.append(filName);
            }
        }

        /* Определяем количество устройств по названию файлов */
        uint8_t cnt_chnl_sets = 0;
        if(device_downHoles) cnt_chnl_sets++;
        if(device_UpHoles) cnt_chnl_sets++;
        if(device_sync) cnt_chnl_sets++;
        if(device_tbf) cnt_chnl_sets++;

        /* Запись всех файлов осуществляется при наличии хотя бы 1 подземного модуля,
         * поэтому отсчет данные времени будут взяты из него */

        segd_->getHeaderDataRev2_1(dir_meas_file + lis_file_tmp.at(0), header_sgd_rev2_1);

        segd_->setData(&header_sgd_rev2_1.gen_head_1.yr, &header_sgd_rev2_1.gen_head_1.dy);
        segd_->setTime(&header_sgd_rev2_1.gen_head_1.h, &header_sgd_rev2_1.gen_head_1.mi, &header_sgd_rev2_1.gen_head_1.se);
        segd_->setCounterByte(0);
        segd_->setFileNumber(1);
        segd_->setRecordLenght(1);   //not used for rev 3.1
        segd_->setChannelSets(cnt_chnl_sets);    //Количество используемых каналов (sync, tbf...)
        segd_->write_general_header();
        segd_->write_general_header_blk2();

        if(header_sgd_rev2_1.trace_length_ms > 131070){
            //qDebug() << "trace length" << header_sgd_rev2_1.trace_length_ms;
            header_sgd_rev2_1.trace_length_ms = 131070;
        }
        /* Заполняю Header конечного файла */
        if(device_downHoles){
            /* Down Holes */
            segd_->setChannelSetNumber(1);
            segd_->setChannelSetStartTime(0);
            segd_->setChannelSetEndTime(header_sgd_rev2_1.trace_length_ms/2);       //length data
            segd_->setDataLength(0); //length data
            segd_->setNumberOfChannels(device_downHoles);
            segd_->setChannelType((quint8)CHANNELSETS_TYPE_SEIS);
            segd_->setChannelGainControlMethod((quint8)CHANNELSETS_GAINMODE_FIXED);
            segd_->setAliasFilterSlope((quint16)1);
            segd_->write_header();
        }
        if(device_UpHoles){
            /*Up Hole */
            segd_->setChannelSetNumber(3);
            segd_->setChannelSetStartTime(0);
            segd_->setChannelSetEndTime(header_sgd_rev2_1.trace_length_ms/2);       //length data
            segd_->setDataLength(0); //length data
            segd_->setNumberOfChannels(device_UpHoles);
            segd_->setChannelType((quint8)CHANNELSETS_TYPE_UPHOLE);
            segd_->setChannelGainControlMethod((quint8)CHANNELSETS_GAINMODE_FIXED);
            segd_->setAliasFilterSlope((quint16)1);
            segd_->write_header();
        }
        if(device_sync) {
            /* Sync */
            segd_->setChannelSetNumber(4);
            segd_->setChannelSetEndTime(header_sgd_rev2_1.trace_length_ms/2);       //length data
            segd_->setDataLength(0); //length data
            segd_->setNumberOfChannels(device_sync);
            segd_->setChannelType((quint8)CHANNELSETS_TYPE_OTHER);
            segd_->setChannelGainControlMethod((quint8)CHANNELSETS_GAINMODE_FIXED);
            segd_->setAliasFilterSlope((quint16)1);
            segd_->write_header();
        }
        if(device_tbf){
            /* TBF */
            segd_->setChannelSetNumber(2);
            segd_->setChannelSetStartTime(0);
            segd_->setChannelSetEndTime(header_sgd_rev2_1.trace_length_ms/2);       //length data
            segd_->setDataLength(0); //length data
            segd_->setNumberOfChannels(device_tbf);
            segd_->setChannelType((quint8)CHANNELSETS_TYPE_TIMEBREAK);
            segd_->setChannelGainControlMethod((quint8)CHANNELSETS_GAINMODE_FIXED);
            segd_->setAliasFilterSlope((quint16)1);
            segd_->write_header();
        }
        segd_->write_extended_header();
        segd_->setDataLength(header_sgd_rev2_1.trace_length_ms);

        /* test */
        for (int i=0; i<lis_file_tmp.count(); i++) {
          //qDebug() << "2" << lis_file_tmp.at(i);
           segd_->openFile_test(dir_meas_file +lis_file_tmp.at(i));
        }

        number_files++;
        delete  segd_;

    }while (!lis_file.isEmpty());

    QApplication::beep();

    emit resultReady(true);
}


