#include "pack.h"

Pack::Pack()
{

}

bool Pack::copyFile(QString &fileName, QString &newFileName)
{
    if(!QFile(fileName).exists())
        return false;
    return file.copy(fileName, newFileName);
}
