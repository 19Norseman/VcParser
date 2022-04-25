#include "manifestconstants.h"
#include "itemresult.h"
#include "attribute.h"
#include "mainwindow.h"



Attribute::Attribute(MainWindow *wPtr,StreamReader *rPtr, encodingType encode)
{
    ptrToMainWindow=wPtr;
    ptrToStreamReader=rPtr;
    state=Blank;
    countOfAttributes=1;//The fact that we are trying to read an attribute means parser thinks there is at least 1
    ptrToStreamReader->SetEncoding(encode);
    try {
        ptrToAttributeText=(char *)calloc(TEXTCHUNKSIZE,sizeof(char));
        attributeTextLength=TEXTCHUNKSIZE;
        attributeTextIndex=0;
    } catch (const std::exception& e) {
        throw e;
    }

}

Attribute::~Attribute() {
    if (ptrToAttributeText!=nullptr) {
        free(ptrToAttributeText);
        ptrToAttributeText=nullptr;
    }
}

int Attribute::GetAttributeCount() {
    return countOfAttributes;
}

ItemResult Attribute::AttributeReader() {
    ItemResult result;
    const char *attributeLabel=ATTRIBUTE_LABEL;
    for (int i=0;i<(int)strlen(attributeLabel);i++) {
        ptrToStreamReader->EchoParsed(attributeLabel[i]);
    }
    //Read until EOF or EOL
    //EOL us valid end of value
    //EOF is error
    int loop=1;
    while (loop) {
        //Read an input character
        currentChar=ptrToStreamReader->ReadOne();
        switch (currentChar) {
        //If we detect EOF or EOL before ENDOFATTRIBUTES its an error
            case 0:
                result.SetResult(failure,ATTRIBUTE_EOF_ERROR);
                loop=0;
                break;

            //Is this the start of a new ATTRIBUTE?
            case STARTOFATTRIBUTE:
                //Yes, this is start of attribute and there may be more
                // continue reading and storing attributes
                //Display input character
                 ptrToStreamReader->EchoParsed(currentChar);
                //Store input character in Attribute
                 //TODO: for some reason this was commented out
                AttributeWriter(currentChar);
                countOfAttributes++;
                break;

           //Is this the start of VALUE?
           case STARTOFVALUE:
               //Yes, this is the start of VALUE.
                //Display input character
                ptrToStreamReader->EchoParsed(currentChar);
                 //Store input character in Attribute
//                AttributeWriter(currentChar);
                loop=0;
                result.SetResult(successHasValue,ATTRIBUTE_SUCCESS);
                break;
           //Is this the end of all attributes for this property and an EOL?
           case NEW_LINE:
                if (ptrToStreamReader->IsEOL()) {
                    //Display input character
                    ptrToStreamReader->EchoParsed(currentChar);
                    //Store input character in Attribute
                    AttributeWriter(currentChar);
                    //Yes, return failure, there must be a value
                    loop=0;
                    result.SetResult(failure,ATTRIBUTE_NO_VALUE_ERROR);
                }
            break;
           default:
                state=notBlank;
                //Display input character
                ptrToStreamReader->EchoParsed(currentChar);
                //Store input character in Attribute
                AttributeWriter(currentChar);
                break;
       }
    }
    //Convert attributes to uppercase
    // Spec says its case insensitive we convert uppercase for consistency
    switch (result.GetResult()) {
        case successHasValue:
            if (ptrToAttributeText!=nullptr) {
                for (int i=0;i<attributeTextLength;i++)
                   ptrToAttributeText[i]=toupper(ptrToAttributeText[i]);
            }
             break;
        default:
            break;
        }

    return result;
}

//Store attribute in buffer
void Attribute::AttributeWriter(char s) {
    //If the attribute text buffer is full allocate another chunk, copy old buffer to new buffer and delete old
     if ((attributeTextIndex>=attributeTextLength)) {
         try {
             //allocate a new buffer chunk size bigger and copy data to new buffer;
             char *dstPtr=(char *)calloc(attributeTextLength+TEXTCHUNKSIZE,sizeof(char));
             for (int i=0;i<attributeTextLength;i++) {
               dstPtr[i]=ptrToAttributeText[i];
             }
             attributeTextLength=attributeTextLength+TEXTCHUNKSIZE;
             free(ptrToAttributeText);
             ptrToAttributeText=dstPtr;
         }  catch (const std::exception& e) {
             throw e;
         }
     }
     ptrToAttributeText[attributeTextIndex++]=s;
    return;
}

char *Attribute::GetAttributeText(void) {
    return ptrToAttributeText;
}
