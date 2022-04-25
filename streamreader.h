#ifndef STREAMREADER_H
#define STREAMREADER_H
#include <fstream>

#include <QPlainTextEdit>

#include "manifestconstants.h"


class MainWindow;
class Qapplication;

using namespace std;

class StreamReader
{
public:
    StreamReader(QApplication *app,MainWindow *mainWindow,ifstream *input);
    ~StreamReader();
    void SetEncoding(encodingType encoding);
    void SetBase64Count(int count);
    int IsEOL(void);
    char ReadOne();
    char Peekone();
    void EchoInput(char inputchar);
    void ForceEchoInput(char inputchar);
    void EchoInputAsOctal(char inputchar);
    void EchoParsed(char inputchar);

private:
    void convertToSafeString(char input, char *output);
    encodingType IfEncoding();
    void InitPrevious();
    QApplication *ptrToApplication;
    MainWindow * ptrToMainWindow;
    ifstream * ptrToInput;
    QPlainTextEdit *ptrToInputTextEdit;
    QPlainTextEdit *ptrToInputOctalTextEdit;
    QPlainTextEdit *ptrToParsedTextEdit;
    encodingType encoding;
    char base64Touple[5];
    int base64count;
    char inputChars[2];
    int previousIndex;
    char previous[PREVIOUS_LENGTH];
    int folding;
    int isEOL;

};

#endif // STREAMREADER_H
