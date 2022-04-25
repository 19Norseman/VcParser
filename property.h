#ifndef PROPERTY_H
#define PROPERTY_H

#include <QPlainTextEdit>

#include "manifestconstants.h"
#include "itemresult.h"

class MainWindow;
class StreamReader;

class Property
{
public:
    Property(MainWindow *wPtr,StreamReader *rPtr, encodingType encode);
    ~Property();
    ItemResult PropertyReader();
    char *GetPropertyText(void);
    char *GetGroupText(void);
private:
    void PropertyWriter(char s);
    char currentChar;
    encodingType encoding;
    States state;
    MainWindow *ptrToMainWindow;
    StreamReader *ptrToStreamReader;
    int propertyTextLength;
    int propertyTextIndex;
    char *ptrToPropertyText;
    int groupTextLength;
    int groupTextIndex;
    char *ptrToGroupText;

};

#endif // PROPERTY_H
