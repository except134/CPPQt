#ifndef PARSETEXT_H
#define PARSETEXT_H

#include <QString>

class ParseText
{
public:
    ParseText();
    bool Change(QString);
    QString GetText();
    QString InsertSymbol(QString example);

private:
    QString text;
    QString preText;
    qint32 pos;
};

#endif // PARSETEXT_H
