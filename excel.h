#ifndef EXCEL_H
#define EXCEL_H

#include <QAxObject>
#include <QString>
#include <QList>
#include <QVector>
#include <QVariant>
#include <QPair>
#include <QMap>

struct ExcelInform{
    QString snInform;       //零件编号
    QString nameInform;     //名称
    QString infom;          //加工类型
    QString typeInform;     //机架高度
};

class Excel
{
public:
    Excel();
    ~Excel();

    void readExcel(QString &filePath);
    bool isLackCol();
    bool isError();
    void isSnError();
    void getArrRow();
    void getExcelInform();
    QVariant readAll();
    void castVariant2ListListVariant(const QVariant &var, QList<QList<QVariant> > &res);
    QString getSaveFileName();

    //返回私有数据
    QString getErrorInform();
    QVector<QPair<int, int>> getErrorVector();
    QMap<int, QString> getErrorSn();
    QList<ExcelInform> getM_data();

private:
    QAxObject* excel;
    QAxObject* workbooks;
    QAxObject* workbook;
    QAxObject* worksheets;
    ExcelInform m_excelInform;          //excel每行中的必要信息
    QList<ExcelInform> m_data;          //储存excel的内容
    int arrRow[5];                      //储存必要的行数
    int nCols, nRows;                   //总行列数
//    QPair<int, int> errorNumber;
    QString errorInform;                        //错误信息，缺少编号等主要信息
    QVector<QPair<int, int>> errVector;         //编号等为空的行列数
    QMap<int, QString> errSN;                   //有问题的编号所在的行数和编号字符串
};

#endif // EXCEL_H
