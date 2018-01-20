#include "flietwo.h"
#include "entrance.h"
#include "ui_flietwo.h"

flietwo::flietwo(QWidget *parent) :
    ui(new Ui::flietwo)
{
    ui->setupUi(this);
    _parent=parent;
    ff = new file(this);
}

flietwo::~flietwo()
{
    delete ui;
}

void flietwo::on_rreturn_clicked()
{
    this->hide();
    (( entrance *)_parent)->show();
}

void flietwo::on_zip_clicked()
{
    ff->creatzip();
    qDebug()<<"111";
}

void flietwo::on_map_clicked()
{
    mapping();
}

void flietwo::mapping()
{
    QMap<QString,QString> map;
    map = ff->creatmap();
    qDebug()<<map.count();
    QMap<QString,QString>::iterator it;
        for ( it = map.begin(); it != map.end(); ++it )
            {
                qDebug()<<it.key()<<it.value();
            }
}

void flietwo::on_quick_2_clicked()
{

}
