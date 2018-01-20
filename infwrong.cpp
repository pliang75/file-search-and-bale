#include "infwrong.h"
#include "ui_infwrong.h"

infwrong::infwrong(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::infwrong)
{
    ui->setupUi(this);
}
infwrong::~infwrong()
{
    delete ui;
}

void infwrong::wwrong()
{
    ui->listWidget->clear();
    QStringList strlist;
    qDebug()<<"mmp";
    QFile ffile("D:/错误命名.txt");
    ffile.open(QFile::ReadOnly | QIODevice::Truncate| QIODevice::Text);
    while(!ffile.atEnd()) {
        QTextCodec *codec=QTextCodec::codecForName("GB2312");
        strlist<<QString (codec->toUnicode(ffile.readLine()));
    }
    ui->listWidget->addItems(strlist);
    ffile.close();
}
