#ifndef ENTRANCE_H
#define ENTRANCE_H

#include <QMainWindow>
#include "file.h"
#include "flietwo.h"

namespace Ui {
class entrance;
}

class entrance : public QMainWindow
{
    Q_OBJECT

public:
    explicit entrance(QWidget *parent = 0);
    ~entrance();

private slots:

    void on_aentrance_clicked();

    void on_bentrance_clicked();

private:
    Ui::entrance *ui;
    file * af;
    flietwo * bf;
};

#endif // ENTRANCE_H
