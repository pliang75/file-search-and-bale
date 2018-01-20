#ifndef FLIETWO_H
#define FLIETWO_H

#include <QMainWindow>
#include "file.h"

namespace Ui {
class flietwo;
}

class flietwo : public QMainWindow
{
    Q_OBJECT

public:
    explicit flietwo(QWidget *parent = 0);

    ~flietwo();

    void mapping();

private slots:
    void on_rreturn_clicked();

    void on_zip_clicked();

    void on_map_clicked();

    void on_quick_2_clicked();

private:
    Ui::flietwo *ui;
    QObject *_parent;
    file *ff;
};

#endif // FLIETWO_H
