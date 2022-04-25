#include "value.h"
#include "mainwindow.h"
#include "itemresult.h"

Value::Value(MainWindow *wPtr,StreamReader *rPtr, encodingType encode)
{
    ptrToMainWindow=wPtr;
    ptrToStreamReader=rPtr;
    state=Blank;
    ptrToStreamReader->SetEncoding(encode);
    try {
        ptrToValueText=(char *)calloc(TEXTCHUNKSIZE,sizeof(char));
        valueTextLength=TEXTCHUNKSIZE;
        valueTextIndex=0;
    } catch (const std::exception& e) {
        throw e;
    }

}

Value::~Value() {
    if (ptrToValueText!=nullptr) {
        free(ptrToValueText);
        ptrToValueText=nullptr;
    }
}

ItemResult Value::ValueReader() {
    ItemResult result;
    const char *valueLabel=VALUE_LABEL;
    for (int i=0;i<(int)strlen(valueLabel);i++) {
        ptrToStreamReader->EchoParsed(valueLabel[i]);
    }
     //Read until EOF or EOL
    //EOL us valid end of value
    //EOF is error
    int loop=1;
    while (loop) {
        //Read an input character
        currentChar=ptrToStreamReader->ReadOne();
        switch (currentChar) {
        //If we detect EOF before EOL return failure
        case 0:
            loop=0;
            result.SetResult(failure,VALUE_EOF_ERROR);
            break;
        case ENDOFVALUE:
            //Display input character
            ptrToStreamReader->EchoParsed(currentChar);
            //Store the current character
            ValueWriter(currentChar);
            if (ptrToStreamReader->IsEOL()) {
                loop=0;
                if (state==notBlank) {
                    result.SetResult(successEol,VALUE_READ_SUCCESS);
                } else {
                    //By BNF value may not be blank
                    result.SetResult(failure,VALUE_BLANK_ERROR);
                }
            }
            break;

        default:
            //Store input character in value
            //Display input character
            state=notBlank;
            ptrToStreamReader->EchoParsed(currentChar);
             //Store the current character
            ValueWriter(currentChar);
            break;

        }
    }
    return result;
}

void Value::ValueWriter(char s) {
    //If the Value text buffer is full allocate another chunk, copy old buffer to new buffer and delete old
     if ((valueTextIndex>=valueTextLength)) {
         try {
             //allocate a new buffer chunk size bigger and copy data to new buffer;
             char *dstPtr=nullptr;
             dstPtr=(char *)calloc(valueTextLength+TEXTCHUNKSIZE,sizeof(char));
             for (int i=0;i<valueTextLength;i++) {
               dstPtr[i]=ptrToValueText[i];
             }
             valueTextLength=valueTextLength+TEXTCHUNKSIZE;
             free(ptrToValueText);
             ptrToValueText=dstPtr;
         }  catch (const std::exception& e) {
             throw e;
         }
     }
     ptrToValueText[valueTextIndex++]=s;
 }

char * Value::GetValueText(void) {
    return ptrToValueText;
}

void Value::ClearValueText(void) {
    valueTextIndex=0;
    ptrToValueText[valueTextIndex]=0;
}

void Value::SetValueText(char * text) {
    ClearValueText();
    for  (int i=0;i<(int)strlen(text);i++) {
        ValueWriter(text[i]);
    }
    ValueWriter(0);
}
