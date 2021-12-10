#ifndef CHECKBOXINCOMBOWIDGET_H
#define CHECKBOXINCOMBOWIDGET_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class CheckBoxInComboWidget;
}

class CheckBoxInComboWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CheckBoxInComboWidget(QWidget *parent = 0);
    void addItem(const QString& name, int index);
    ~CheckBoxInComboWidget();
    QVector<bool> getVectIsChangedValues() const;

public slots:
    void setVecIsChangedValues(const QVector<bool> vecIsChangedValues);

private slots:
    void slot_changed(const QModelIndex&, const QModelIndex&);

private:
    Ui::CheckBoxInComboWidget *ui;
    QStandardItemModel* model_;
    std::vector<QStandardItem*> checkBoxItems_;
    QVector<bool> vecIsChangedValues_;
};

#endif // CHECKBOXINCOMBOWIDGET_H
