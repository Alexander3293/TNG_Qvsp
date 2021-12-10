#ifndef CREATEPROJECT_H
#define CREATEPROJECT_H

#include <QDialog>
#include "ui_createproject.h"
#include <QFileDialog>
#include <QDate>
#include <QTime>
#include <QScrollBar>
#include <QPixmap>
#include <QPushButton>

//#include <QDebug>

namespace Ui {
class CreateProject;
}

class CreateProject : public QDialog
{
    Q_OBJECT

public:
    explicit CreateProject(QWidget *parent = 0);
    ~CreateProject();

    QString getPath() const;
    void setPath(const QString &value);

    QString getName() const;
    void setName(const QString &value);

private slots:
    void on_pushButtonPath_clicked();

    void on_pushButtonCancel_clicked();

    void on_textEditPath_textChanged();

    void on_textEditName_textChanged();

    void on_pushButton_2_clicked();

private:
    Ui::CreateProject *ui;
    QString path_;
    QString name_;
    void resizeTextEditName();
    void resizeTextEditPath();

signals:
    void create(QString name, QString path);

};

#endif // CREATEPROJECT_H
