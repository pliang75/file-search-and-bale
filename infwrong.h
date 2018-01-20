#ifndef INFWRONG_H
#define INFWRONG_H

#include <QDialog>
#include <Qtcore>
#include <QFileDialog>
#include <QString>

namespace Ui {
class infwrong;
}

class infwrong : public QDialog
{
    Q_OBJECT

public:
    explicit infwrong(QWidget *parent = 0);
    ~infwrong();

    void wwrong();

private:
    Ui::infwrong *ui;

};

#endif // INFWRONG_H
