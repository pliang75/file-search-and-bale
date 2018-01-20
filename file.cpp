

#include "file.h"
#include "entrance.h"
#include "ui_file.h"

#include <QMessageBox>
#include <QFile>

file::file(QWidget *parent) :
    ui(new Ui::file)
{
    ui->setupUi(this);
    _parent=parent;
    inf=new infwrong(this);
    excel = NULL;
    wrong_1 = new WrongDialog_1(this);
    wrong_2 = new WrongDialog_2(this);
}

file::~file()
{
    delete ui;
    delete excel;
}

void file::on_check_clicked()
{
    check();
    ifopen();
}

void file::on_map_clicked()
{
    creatmap();

}

void file::on_zip_clicked()
{
    creatzip();
    QMessageBox::information(this,tr("提示"),tr("sucess"));
}

void file::on_finding_clicked()
{
    finding();
}

void file::on_quick_clicked()
{
    creatquick();
    QMessageBox::information(this,tr("提示"),tr("sucess"));
}

void file::creatquick()
{
    QSettings settings("TestSetting.ini", QSettings::IniFormat);
    abb=settings.value("GPS/gpsBaud").toString();
    qDebug()<<abb;
    acc=abb+"/图册";
    QFile file(abb+"/快照文件列表.txt");
    file.open(QFile::WriteOnly  | QIODevice::Truncate | QIODevice::Text);
    QTextStream out(&file);
    chakan(acc, out);
    file.close();
}

void file::finding()
{
    QString directory = QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this,tr("get path"),QDir::currentPath()));
    abb=directory;
    QSettings settings("TestSetting.ini", QSettings::IniFormat);
    settings.beginGroup("GPS");
    settings.setValue("gpsBaud",abb);
    settings.endGroup();
    if(!directory.isEmpty())
    {
        if(ui->comboBox->findText(directory)==-1)
        {
            ui->comboBox->addItem(directory);
        }
        ui->comboBox->setCurrentIndex(ui->comboBox->findText(directory));
    }
}

void file::chakan(QString path,QTextStream& out){
  QDir dir(path);
  foreach(QFileInfo mfi ,dir.entryInfoList())
  {
    if(mfi.isFile()&&mfi.suffix()=="txt")
    {
        qDebug()<< mfi.fileName()<<mfi.filePath()<<'\n';
        out<<mfi.fileName()<<"-"<<mfi.filePath()<<'\n';
    }else
    {
        if(mfi.fileName()=="." || mfi.fileName() == "..")continue;
        chakan(mfi.absoluteFilePath(),out);
    }
  }
}

void file::check()
{
    int b=0;
    int c=0;
    QFile file(abb+"/快照文件列表.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Truncate| QIODevice::Text)) {
        //qDebug()<<"Can't open the file!"<<endl;
     }
    QFile ffile("D:/错误命名.txt");
    ffile.open(QFile::WriteOnly  | QIODevice::Truncate| QIODevice::Text);
    QTextStream out(&ffile);
    while(!file.atEnd()) {
        QTextCodec *codec=QTextCodec::codecForName("GB2312");
        //qDebug()<<codec->toUnicode(file.readLine());
        QString str(codec->toUnicode(file.readLine()));
        QString sstr=str.left(str.indexOf('.'));
        QStringList strlist=sstr.split("_");
        int a=strlist.size();
        if(a<3)
        {
            out<<str;
            c=c+1;
        }else {
            b=b+1;
        }
        //qDebug()<< sstr;
    }
    file.close();
    ffile.close();
    //qDebug()<<b;
    if(c>0)
    {
        QMessageBox::information(this,tr("提示"),tr("存在错误命名文件"));
    }else
    {
        QMessageBox::information(this,tr("提示"),tr("没有错误命名文件"));
        ffile.remove();
    }
}

QMap<QString,QString> file::creatmap()
{
    QMap<QString,QString> mmap;
    QFile file(abb+"/快照文件列表.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Truncate| QIODevice::Text);
    while(!file.atEnd()) {
        QTextCodec *codec=QTextCodec::codecForName("GB2312");
        QString str(codec->toUnicode(file.readLine()));
        QStringList strlist=str.split("-");
        QString string=strlist.at(1).left(strlist.at(1).length()-1);
        QString sstr=strlist.at(0).left(str.indexOf('.'));
        QStringList sstrlist=sstr.split("_");
        QString ssstr=sstrlist.at(0)+"_"+sstrlist.at(1);
        mmap.insert(ssstr,string);
    }
    file.close();
    return mmap;
}

void file::ifseven()
{
    QFileInfo fi(abb+"/快照文件列表.txt");
    if(fi.isFile())
    {
        QDateTime mmm=fi.lastModified();
        int y=QDateTime::currentDateTime().toString("yy").toInt()-mmm.toString("yy").toInt();
        int M=QDateTime::currentDateTime().toString("MM").toInt()-mmm.toString("MM").toInt();
        int d=QDateTime::currentDateTime().toString("dd").toInt()-mmm.toString("dd").toInt();
        int total=y*365+M*30+d;
        if(total>7)
          {
             QMessageBox::warning(this,tr("警告"),tr("快照文件已已过期，需重新更新"));
          }
    }
}

void file:: creatzip()
{
    JlCompress::compressDir("D:/图册.zip","D:/图册");
}


void file::ifopen()
{
    QFileInfo fi("D:/错误命名.txt");
    if(fi.isFile())
    {
        inf->show();
        inf->wwrong();
    }
}

void file::on_rreturn_clicked()
{
    this->hide();
    (( entrance *)_parent)->show();
}

//excel 相关
void file::on_finding_2_clicked()
{
    QString &directory=QFileDialog::getOpenFileName(this,tr("Import file")
    ,qApp->applicationDirPath(),tr("Excel Files (*.xlsx & *.xls)"));
    if(!directory.isEmpty())
    {
        if(ui->comboBox_2->findText(directory)==-1)
        {
            ui->comboBox_2->addItem(directory);
        }
        ui->comboBox_2->setCurrentIndex(ui->comboBox_2->findText(directory));
    }
}

void file::on_quick_2_clicked()
{
    QString excelFile = ui->comboBox_2->currentText();
    qDebug()<<excelFile;

    if(excelFile.isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("there is no Excel file!"));
        return ;
    }

    if(excel != NULL)
        excel = NULL;
    excel = new Excel();

    excel->readExcel(excelFile);
    excel->getArrRow();
    if(excel->isLackCol())
    {
        QString str = excel->getErrorInform();
        str = "lack" + str;
        QMessageBox::information(this, tr("Error"), tr(str.toLatin1()));
        return ;
    }

    if(excel->isError())
    {
        wrong_1->setErrorInformVector(excel->getErrorVector());
        wrong_1->shouTheErroeInform();
        wrong_1->show();
        return ;
    }

    excel->isSnError();
    wrong_2->setErrorSN(excel->getErrorSn());
    wrong_2->showErrorSN();
    wrong_2->show();
    return ;
}

void file::on_pushButton_clicked()
{
    if(excel == NULL)
    {
        QMessageBox::information(this, tr("Error"), tr("First check out Excel"));
        return ;
    }

    QString directory = QDir::toNativeSeparators(
                QFileDialog::getExistingDirectory(this,tr("the path for save"),QDir::currentPath()));
    if(directory.isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("Please select File Directory"));
        return ;
    }
    qDebug()<<"directory first debug:"<<directory;
    excel->getExcelInform();
    QList<ExcelInform> excelData = excel->getM_data();
    QString snInform,insertInform;
    QString fileName, newFileName;
    QFile file;
    QDir temp;
    QMap<QString,QString> map = creatmap();

    qDebug()<<"复制test";
    for(int i = 0; i < excelData.size(); ++i)
    {
        qDebug()<<"excelData loop test";
        qDebug()<<excelData.at(i).typeInform;
        if(!excelData.at(i).typeInform.isEmpty())
        {
            qDebug()<<"非空";
            //非空，需要在pdf中加入信息生成新的pdf
        }
        else
        {
            snInform = excelData.at(i).snInform;
            insertInform = excelData.at(i).infom;
            qDebug()<<"snInform = "<<snInform;
            qDebug()<<"inform = "<<insertInform;

            auto mapItera = map.find(snInform);
            fileName = mapItera.value();

            QFile fileOld(fileName);
            QFileInfo fileOldInfo(fileOld.fileName());
            QString str =fileOldInfo.fileName();

            newFileName = directory + "\\" + insertInform;


            if(!temp.exists(newFileName))
                temp.mkdir(newFileName);

            newFileName = newFileName + "\\" + str;
            file.copy(fileName, newFileName);
        }
    }
}
