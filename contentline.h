#ifndef CONTENTLINE_H
#define CONTENTLINE_H


#include <QPlainTextEdit>

#include "manifestconstants.h"
#include "itemresult.h"

class MainWindow;
class StreamReader;
class Value;
class Attribute;
class Property;

class ContentLine
{
public:
    ContentLine(MainWindow *wPtr,StreamReader *rPtr, encodingType encode);
    ~ContentLine();
    ItemResult ContentLineReader();
    Value *GetValue();
    Attribute *GetAttribute();
    Property *GetProperty();
private:
    char currentChar;
    encodingType encoding;
    States state;
    MainWindow *ptrToMainWindow;
    StreamReader *ptrToStreamReader;
    Value *ptrToValue;
    Attribute *ptrToAttribute;
    Property *ptrToProperty;

};

#endif // CONTENTLINE_H
