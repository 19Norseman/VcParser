#include <QApplication>
#include <QCursor>

#include "streamreader.h"
#include "mainwindow.h"

StreamReader::StreamReader(QApplication *app,MainWindow *mainWindow,ifstream *input)
{
     ptrToApplication=app;
     ptrToInput=input;
     ptrToMainWindow=mainWindow;
     ptrToInputTextEdit=ptrToMainWindow->getInputEditText();
     ptrToInputOctalTextEdit= ptrToMainWindow->getInputOctalEditText();
     ptrToParsedTextEdit= ptrToMainWindow->getOutputEditText();
     //initialize previous character array
     encoding=none;
     base64count=0;
     InitPrevious();
     folding=0;
     isEOL=0;
}

StreamReader::~StreamReader() {

}
//Echo a chacter to the input Window
//NOTE: 8 bit characters are echod as [xxx] to avoid issues with character encoding
void StreamReader::EchoInput(char inputchar) {
    if (ptrToMainWindow->getInputDisplayState()) {
        ForceEchoInput(inputchar);
    }
}


//Echo a chacter to the input Window
//NOTE: 8 bit characters are echod as [xxx] to avoid issues with character encoding
void StreamReader::ForceEchoInput(char inputchar) {
    char safeString[7];
    QTextCursor myCursor=ptrToInputTextEdit->textCursor();
    myCursor.movePosition(QTextCursor::End);
    ptrToInputTextEdit->setTextCursor(myCursor);
    if (inputchar>=0) {
        QString echo=QString(QChar(inputchar));
        ptrToInputTextEdit->insertPlainText(echo);
    } else {
        convertToSafeString(inputchar,safeString);
        QString echo=QString(safeString);
        ptrToInputTextEdit->insertPlainText(echo);
    }
}


//Echo a chacter to the octal display window if display octal is enabled
//NOTE: characters are echoed as [xxx]
void StreamReader::EchoInputAsOctal(char inputchar) {
    if (ptrToMainWindow->getOctalDisplayState()) {
        char safeString[7];
        QTextCursor myCursor=ptrToInputOctalTextEdit->textCursor();
        myCursor.movePosition(QTextCursor::End);
        ptrToInputOctalTextEdit->setTextCursor(myCursor);

        convertToSafeString(inputchar,safeString);
        QString echo=QString(safeString);
        ptrToInputOctalTextEdit->insertPlainText(echo);
    }
}

//Echo a chacter to the parsed display window if displayparsed data is enabled
//NOTE: characters are echoed as [xxx]

void StreamReader::EchoParsed(char inputchar) {
    if (ptrToMainWindow->getParsedDisplayState()) {
        char safeString[7];
        QTextCursor myCursor=ptrToParsedTextEdit->textCursor();
        myCursor.movePosition(QTextCursor::End);
        ptrToParsedTextEdit->setTextCursor(myCursor);
        if (inputchar>=0) {
            QString echo=QString(QChar(inputchar));
            ptrToParsedTextEdit->insertPlainText(echo);
        } else {
            convertToSafeString(inputchar,safeString);
            QString echo=QString(safeString);
            ptrToParsedTextEdit->insertPlainText(echo);
        }
    }
}

void StreamReader::convertToSafeString(char input, char *output) {
    //Convert input char to octal string
    char octals[7];
    snprintf(&octals[0],6,"[%3.3o]",(unsigned char)input);
    for (int i=0;i<6;i++) {
        output[i]=octals[i];
    }

}


char StreamReader::ReadOne() {
    try {
        //set input char to 0, EOF. Terminate input string
        base64Touple[0]=0;
        inputChars[0]=0;
        inputChars[1]=0;
        folding=0;
        isEOL=0;
        //If the input stream is valid read 1 char from inout
        if (*ptrToInput) {
            ptrToInput->read(inputChars,1);
            //If char read is \r Don't echo. It causes a paragraph break and is visually misleading
           if (inputChars[0]!=CARRIAGE_RETURN) {
                   EchoInput(inputChars[0]);
            }
            EchoInputAsOctal(inputChars[0]);
            //Accummulate characters in previous array so that we can handle folding
            //Is array full?
            if (previousIndex==PREVIOUS_END) {
            //yes, discard oldest character
                strncpy(&previous[0], &previous[1], PREVIOUS_LENGTH-1);
                previousIndex--;
            }
            //Append newest character
            previous[previousIndex++]=inputChars[0];
        }
        //We have a character we need to determine if its part of a possible folding sequence
        // or an eol.
        if (inputChars[0]==NEW_LINE) {
            //Yes. Did caller specify data isencoded?
            //We have 3 cases to consider: base64, quoted printable and no encoding
            //Handle folding for current encoding
            switch(encoding) {
                case base64:
                // fall through
                case none:
                    {
                       //Caller says data is not encoded or is base64 encoded
                       //Handle normal line folding or not folding
                       //Have we started a folding sequence?
                       //Store the input char in the sequence
                       //A folding sequence is /r/n followed by space or horizontal tab
                       //peek ahead to get the 3rd character of a possible folding sequence
                        char peekedChar=ptrToInput->peek();
                        //Now check for /r/n/(white space)
                        if ((previous[previousIndex-2]==CARRIAGE_RETURN) &&
                            (previous[previousIndex-1]==NEW_LINE) &&
                            ((peekedChar==SPACE) || (peekedChar==HORIZONTAL_TAB) )
                           )
                        {
                            //We have the sequence. Its not an EOL
                            folding=1;
                            isEOL=0;
                        } else
                        {
                            //We don't have the sequence it is an EOL
                            folding=0;
                            isEOL=1;
                        }
                    }
                    break;
                case quotedprintable:
                    {
                        //Caller has specified data is quotedprintable encoded
                        //Is this the 3rd character of the sequence?
                        if (previousIndex==PREVIOUS_END) {
                            //Yes we have 3 characters of a possible quotedprintable folding sequence
                            //Is it in fact a quotedprintable folding sequence?
                            int cmpResult=strcmp(previous,QUOTED_PRINTABLE_FOLDING_SEQUENCE);
                            if (!cmpResult) {
                                //Yes, it is a quotedprintable folding sequence
                                // =\r\n
                                folding=1;
                                isEOL=0;
                            } else {
                                //No, its not the quoted printable folding sequence.
                                //Is it the end of line sequence
                                if (previous[1]=='\r')
                                {
                                    //Yes its an EOL
                                    folding=0;
                                    isEOL=1;
                                }
                            }
                        }
                      }
                    break;
            }//End switch on encoding
        }
        //The previous messy if's should have handled all \r\n sequences
        // a bare \r or \n is not an eol sequence
        ptrToApplication->processEvents();
    } catch(std::exception &e) {
        const char *message=e.what();
        Q_UNUSED(message);
        throw e;
    }
    return inputChars[0];
}

char StreamReader::Peekone() {
    if (*ptrToInput) {
        return (char)ptrToInput->peek();
     } else
    {
        return (char)0;
    }

}


void StreamReader::InitPrevious() {
    for (int i=0;i<PREVIOUS_LENGTH;i++) {
        previous[i]=0;
    }
    previousIndex=0;
}

int StreamReader::IsEOL(void) {
    return isEOL;
}

void StreamReader::SetEncoding(encodingType type) {
    encoding=type;
    base64count=0;
    return ;
}

void StreamReader::SetBase64Count(int count) {
    base64count=count;
}

encodingType StreamReader::IfEncoding() {
    return encoding;
}



