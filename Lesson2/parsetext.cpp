#include "parsetext.h"

#define MIN(a, b) (a < b) ? a : b

ParseText::ParseText() : text(""), preText(""), pos(0)
{
}

bool ParseText::Change(QString istr)
{
   qint32 length = MIN(MIN(text.length(), istr.length()), pos);
   preText = "";

   for (qint32 i = 0; i < length; i++) {
       if (text[i] != istr[i]) {
           pos = i;
           break;
       }
   }

   const QChar *arStr = istr.constData();
   qint32 ppos = 0, lastp = -1; // курсор на начало символа, с которого будет осуществлять происк
                                // метку #@
   bool chg = false; // есть изменения текста?

   for (qint32 fnd = istr.indexOf("#@", pos); // поиск первого примера в тексте
        fnd != -1 && lastp != pos; // -1 - означает, что в строке нет (больше) примеров
        fnd = istr.indexOf("#@", pos))
   {
       preText.insert(preText.length(), &arStr[ppos], fnd); // копируем текст до примера
       lastp = pos;
       pos = fnd;
       int r = istr.indexOf('$', fnd);//если есть равенство, то пример завершен
       int space = istr.indexOf(' ', fnd);
       if ((r < space || space == -1) && r != -1) // проверяем, что равно для текущего примера, а не следующего
       {
           QString exampl = "";
           exampl.insert(0, &arStr[fnd + 2], r - fnd - 2);
           QString rez = InsertSymbol(exampl);
           preText += rez;
           pos = r + 1;
           chg = true;
       }
       preText.insert(preText.length(), &arStr[pos], istr.length() - pos); // дописываем оставшийся текст
   }

   return chg;
}

QString ParseText::GetText()
{
    text = preText;
    return text;
}

QString ParseText::InsertSymbol(QString example)
{
    QString str = example;
    if(str == "rub")
        return "₽";
    if(str == "copy")
        return "©";
    if(str == "euro")
        return "€";
    if(str == "prom")
        return "‰";

    return str;
}

