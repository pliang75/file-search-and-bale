#ifndef WRONGDIALOG_2_H
#define WRONGDIALOG_2_H

#include "excel.h"

#include <QDialog>
#include <QMap>
#include <QString>
#include <QList>

namespace Ui {
class WrongDialog_2;
}

class WrongDialog_2 : public QDialog
{
    Q_OBJECT

public:
    explicit WrongDialog_2(QWidget *parent = 0);
    void showErrorSN();
    void setErrorSN(QMap<int, QString> &err);

    void setExcelData(QList<ExcelInform> &data);
    ~WrongDialog_2();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::WrongDialog_2 *ui;
    QMap<int, QString> errorSN;
    QList<ExcelInform> excelData;
};

#endif // WRONGDIALOG_2_H
