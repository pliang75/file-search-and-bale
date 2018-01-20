#ifndef FILE_H
#define FILE_H

#include "excel.h"
#include "wrongdialog_1.h"
#include "wrongdialog_2.h"

#include <QMainWindow>
#include <Qtcore>
#include <QFileDialog>
#include <QString>
#include<QMessageBox>
#include <QMap>
#include<quazip/JlCompress.h>
#include"infwrong.h"



namespace Ui {
class file;
}

class file : public QMainWindow
{
    Q_OBJECT

public:
    explicit file(QWidget *parent = 0);
    ~file();

    void check();

    void creatzip();

    void ifseven();

    void creatquick();

    void finding();

    void ifopen();

    void chakan(QString path,QTextStream& out);

    QMap<QString,QString> creatmap();

private slots:

    void on_finding_clicked();

    void on_quick_clicked();

    void on_check_clicked();

    void on_map_clicked();

    void on_zip_clicked();

    void on_rreturn_clicked();

    void on_finding_2_clicked();

    void on_quick_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::file *ui;
    QString abb;
    QString acc;
    QObject *_parent;

    //excel
    Excel *excel;
    WrongDialog_1 *wrong_1;
    WrongDialog_2 *wrong_2;

    infwrong * inf;
};

#endif // FILE_H
