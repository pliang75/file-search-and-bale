#include "entrance.h"
#include "ui_entrance.h"

entrance::entrance(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::entrance)
{
    ui->setupUi(this);
    af=new file(this);
    bf=new flietwo(this);
    af->ifseven();
}

entrance::~entrance()
{
    delete ui;
}

void entrance::on_aentrance_clicked()
{
    this->hide();
    af->show();
}

void entrance::on_bentrance_clicked()
{
    this->hide();
    bf->show();
}
