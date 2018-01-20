#include "wrongdialog_2.h"
#include "ui_wrongdialog_2.h"

WrongDialog_2::WrongDialog_2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WrongDialog_2)
{
    ui->setupUi(this);
}

void WrongDialog_2::showErrorSN()
{
    ui->textEdit->clear();
    int iRow = 0;
    QString str;
    for(auto i = errorSN.begin(); i != errorSN.end(); ++i)
    {
        iRow = i.key();
        str = i.value();
        QString string = "the row is " + QString::number(iRow) + " and the value is " + str;
        ui->textEdit->append(string);
    }

    ui->textEdit->append(tr("Please check out and OK to continue!"));
}

void WrongDialog_2::setErrorSN(QMap<int, QString> &err)
{
    this->errorSN = err;
}

void WrongDialog_2::setExcelData(QList<ExcelInform> &data)
{
    this->excelData = data;
}

WrongDialog_2::~WrongDialog_2()
{
    delete ui;
}

void WrongDialog_2::on_pushButton_clicked()
{
    this->hide();
}

void WrongDialog_2::on_pushButton_2_clicked()
{
    this->hide();
}
