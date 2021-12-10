#include "checkboxincombowidget.h"
#include "ui_checkboxincombowidget.h"

CheckBoxInComboWidget::CheckBoxInComboWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckBoxInComboWidget),
    model_(new QStandardItemModel)
{
    ui->setupUi(this);
    connect(model_, SIGNAL(dataChanged (const QModelIndex&, const QModelIndex&)),
            this, SLOT(slot_changed(const QModelIndex&, const QModelIndex&)));
    ui->comboBox->setModel(model_);
    ui->comboBox->addItem("(выберите)");
}

auto initAndAddInModule = [](QStandardItemModel* model, const QString &name, int index){
    QStandardItem* itemCheckBox = new QStandardItem;

    itemCheckBox->setText(name);
    itemCheckBox->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    itemCheckBox->setData(Qt::Unchecked, Qt::CheckStateRole);
    model->insertRow(index, itemCheckBox);
    return itemCheckBox;
};

void CheckBoxInComboWidget::addItem(const QString &name, int index)
{
   QStandardItem* itemCheckBox = initAndAddInModule(model_, name, index);
   checkBoxItems_.push_back(itemCheckBox);
   vecIsChangedValues_.push_back(false);
}

CheckBoxInComboWidget::~CheckBoxInComboWidget()
{
    for(auto it = checkBoxItems_.cbegin(); it < checkBoxItems_.cend(); it++)
        delete *it;
    checkBoxItems_.clear();
    delete ui;
}

void CheckBoxInComboWidget::slot_changed(const QModelIndex& topLeft, const QModelIndex& bottomRight)
{
    Q_UNUSED(bottomRight);

    QStandardItem* item = checkBoxItems_[topLeft.row()];
    if(item->checkState() == Qt::Unchecked)
        vecIsChangedValues_[topLeft.row()] = false;
    else if(item->checkState() == Qt::Checked)
        vecIsChangedValues_[topLeft.row()] = true;

}

void CheckBoxInComboWidget::setVecIsChangedValues(const QVector<bool> vecIsChangedValues)
{
    vecIsChangedValues_ = vecIsChangedValues;

    auto setItemState = [](QStandardItem* item, bool state){
        if(state)
            item->setCheckState(Qt::Checked);
        else
            item->setCheckState(Qt::Unchecked); };

    for(int numMod = 0; numMod < vecIsChangedValues_.size(); numMod++)
        setItemState(checkBoxItems_[numMod], vecIsChangedValues_[numMod]);
}

QVector<bool> CheckBoxInComboWidget::getVectIsChangedValues() const
{
    return vecIsChangedValues_;
}
