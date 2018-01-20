#include "excel.h"

#include <string.h>

#include <QDebug>
#include <QStringList>

Excel::Excel()
{
    excel = new QAxObject("Excel.Application");
    excel->setProperty("Visible", false);
    workbooks = excel->querySubObject("WorkBooks");
    workbook = nullptr;
    worksheets = nullptr;

    memset(arrRow, 0, sizeof(arrRow));
}

Excel::~Excel()
{
    delete excel;
    delete workbook;
    delete workbooks;
    delete worksheets;
}

void Excel::readExcel(QString &filePath)
{
    workbooks->dynamicCall("Open (const QString&)",filePath);
    workbook=excel->querySubObject("ActiveWorkBook");
    worksheets = workbook->querySubObject("WorkSheets(int)", 1);
    //得到一个表

    QAxObject* usedrange=worksheets->querySubObject("UsedRange");
    QAxObject* rows=usedrange->querySubObject("Rows");
    QAxObject* columns=usedrange->querySubObject("Columns");

    nCols=columns->property("Count").toInt();       //列数
    nRows=rows->property("Count").toInt();          //行数
    qDebug()<< "cols=" <<nCols << " rows="<< nRows;
}

bool Excel::isLackCol()
{
//    QString errorInform = "";
    for(int i = 0; i <= 3; ++i)
    {
        if(arrRow[i] == 0)
        {
            if(i == 0)
                errorInform += " component sn";
            else if(i == 1)
                errorInform += " component name";
            else if(i == 2)
                errorInform += " processing information";
            else if(i == 3)
                errorInform += " processing types";
        }
    }
    if("" != errorInform)
        return true;
    else
        return false;
}

//错误返回turn
//判断是否需要的信息为空
bool Excel::isError()
{
    QAxObject* cell;
    QString cellStr;

    QPair<int, int> errorNumber;
    for(int j = 0; j < 3; ++j)
    {
        for(int i = arrRow[4]; i <= nRows; ++i)
        {
            cell = worksheets->querySubObject("Cells(int,int)", i, arrRow[j]);
            cellStr = cell->dynamicCall("Value2()").toString();
            //储存无零件编号，名称，加工类型的行列数组；
            //暂无储存的数据结构
            if("" == cellStr)
            {
                errorNumber.first = i;
                errorNumber.second = arrRow[j];
                errVector.append(errorNumber);
            }
        }
    }

    //判断结构非空，则缺少数据
    if(!errVector.empty())
        return true;

    else
        return false;
}

void Excel::isSnError()
{
    //单独一个方法
    QString productionSN;
    QAxObject* cell;
    QStringList list;
    for(int i = arrRow[4] + 1; i < nRows; ++i)
    {
        cell = worksheets->querySubObject("Cells(int,int)", i, arrRow[0]);
        productionSN = cell->dynamicCall("Value2()").toString();
        list = productionSN.split("_");
        //分隔后，少于2个
        if(list.size() != 2)
        {
            errSN.insert(i, productionSN);
            //少于则编号有问题，记录下来
            //不用返回turn
        }
    }
}


void Excel::getArrRow()
{
    QString cellStr;
    QAxObject* cell;

    for(int i = 1; i <= nRows; ++i)
    {
        for(int j = 1; j <= nCols; ++j)
        {
            cell = worksheets->querySubObject("Cells(int,int)", i, j);
            cellStr = cell->dynamicCall("Value2()").toString();
            qDebug()<< "i= "<<i << "j=  "<<j <<" cellStr" <<cellStr;
            if("零件编号" == cellStr)
            {
                arrRow[0] = j;
                arrRow[4] = i;
            }
            else if("名称" == cellStr)
                arrRow[1] = j;
            else if("加工类型" == cellStr)
                arrRow[2] = j;
            else if("机架高度" == cellStr)
                arrRow[3] = j;
            else
                continue;
        }
    }

    for(int i = 0; i < 5; ++i)
        qDebug()<<i <<"arrRow[i] "<<arrRow[i];
    delete cell;
}

void Excel::getExcelInform()
{
    QAxObject* excelCont;

    //获取有用信息
    for(int i = arrRow[4] + 1; i <= nRows; ++i)
    {
       excelCont = worksheets->querySubObject("Cells(int,int)", i, arrRow[0]);
       m_excelInform.snInform = excelCont->dynamicCall("Value2()").toString();
       excelCont = worksheets->querySubObject("Cells(int,int)", i, arrRow[1]);
       m_excelInform.nameInform = excelCont->dynamicCall("Value2()").toString();
       excelCont = worksheets->querySubObject("Cells(int,int)", i, arrRow[2]);
       m_excelInform.infom = excelCont->dynamicCall("Value2()").toString();
       excelCont = worksheets->querySubObject("Cells(int,int)", i, arrRow[3]);
       m_excelInform.typeInform = excelCont->dynamicCall("Value2()").toString();
       m_data.append(m_excelInform);
    }

    for(int i = 0; i < m_data.length(); ++i)
    {
        qDebug()<<m_data[i].snInform;
    }

    workbook->dynamicCall("Close (Boolean)",false);
    excel->dynamicCall("Quit (void)");

    delete excelCont;
}


QVariant Excel::readAll()
{
    QVariant var;
    if(worksheets != NULL && !worksheets->isNull())
    {
        QAxObject *usedRange = worksheets->querySubObject("UsedRange");
        if(NULL == usedRange || usedRange->isNull())
        {
            return var;
        }
        var = usedRange->dynamicCall("Value");
        delete usedRange;
    }
    return var;
}

void Excel::castVariant2ListListVariant(const QVariant &var, QList<QList<QVariant> > &res)
{
    QVariantList varRows = var.toList();
    if(varRows.isEmpty())
    {
        return;
    }
    const int rowCount = varRows.size();
    QVariantList rowData;
    for(int i=0;i<rowCount;++i)
    {
        rowData = varRows[i].toList();
        res.push_back(rowData);
    }
}

QString Excel::getErrorInform()
{
    return this->errorInform;
}

QVector<QPair<int, int> > Excel::getErrorVector()
{
    return this->errVector;
}

QMap<int, QString> Excel::getErrorSn()
{
    return errSN;
}

QList<ExcelInform> Excel::getM_data()
{
    return m_data;
}
