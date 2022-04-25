#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H


#include <QPlainTextEdit>

#include "manifestconstants.h"
#include "itemresult.h"

class MainWindow;
class StreamReader;


class Attribute
{
public:
    Attribute(MainWindow *wPtr,StreamReader *rPtr, encodingType encode);
    ~Attribute();
    ItemResult AttributeReader();
    char *GetAttributeText(void);
    int GetAttributeCount(void);
private:
    void AttributeWriter(char s);
    char currentChar;
    encodingType encoding;
    States state;
    MainWindow *ptrToMainWindow;
    StreamReader *ptrToStreamReader;
    int attributeTextLength;
    int attributeTextIndex;
    char *ptrToAttributeText;
    int countOfAttributes;

};
#endif // ATTRIBUTE_H
