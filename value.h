#ifndef VALUE_H
#define VALUE_H

#include <QPlainTextEdit>

#include "manifestconstants.h"
#include "itemresult.h"

class MainWindow;
class StreamReader;

class Value
{
public:
    Value(MainWindow *wPtr,StreamReader *rPtr, encodingType encode);
    ~Value();
    ItemResult ValueReader();
    char * GetValueText(void);
    void ClearValueText(void);
    void SetValueText(char * text);
private:
    void ValueWriter(char s);
    char currentChar;
    encodingType encoding;
    States state;
    MainWindow *ptrToMainWindow;
    StreamReader *ptrToStreamReader;
    int valueTextLength;
    int valueTextIndex;
    char *ptrToValueText;

};

#endif // VALUE_H
