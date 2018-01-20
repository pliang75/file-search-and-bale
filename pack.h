#ifndef PACK_H
#define PACK_H

#include <QFile>

class Pack
{
public:
    Pack();
    bool copyFile(QString &fileName, QString &newFileName);
private:
    QFile file;
};

#endif // PACK_H
