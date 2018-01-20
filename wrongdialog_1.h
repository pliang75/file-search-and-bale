#ifndef WRONGDIALOG_1_H
#define WRONGDIALOG_1_H

#include <QDialog>
#include <QVector>
#include <QPair>

namespace Ui {
class WrongDialog_1;
}

class WrongDialog_1 : public QDialog
{
    Q_OBJECT

public:
    explicit WrongDialog_1(QWidget *parent = 0);
    void shouTheErroeInform();
    void setErrorInformVector(QVector<QPair<int, int>> &vec);
    ~WrongDialog_1();

private:
    Ui::WrongDialog_1 *ui;
    QVector<QPair<int, int>> errorInformVector;
};

#endif // WRONGDIALOG_1_H
