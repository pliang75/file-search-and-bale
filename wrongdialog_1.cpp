#include "wrongdialog_1.h"
#include "ui_wrongdialog_1.h"

#include <QString>
#include <QDebug>

WrongDialog_1::WrongDialog_1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WrongDialog_1)
{
    ui->setupUi(this);
}

void WrongDialog_1::shouTheErroeInform()
{
    ui->textEdit->clear();
    QString str;
    int iRow, jRow;
    for(int i = 0; i < errorInformVector.size(); ++i)
    {
        iRow = errorInformVector.at(i).first;
        jRow = errorInformVector.at(i).second;
        qDebug()<<iRow << jRow;
        str = "The Row is " + QString::number(iRow) + ",The Column is " + QString::number(jRow);
        ui->textEdit->append(str);
    }
}

void WrongDialog_1::setErrorInformVector(QVector<QPair<int, int> > &vec)
{
    errorInformVector = vec;
}

WrongDialog_1::~WrongDialog_1()
{
    delete ui;
}
