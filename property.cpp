#include <cstring>
#include <cstdlib>
#include "property.h"

#include "manifestconstants.h"
#include "property.h"
#include "mainwindow.h"



using namespace std;

Property::Property(MainWindow *wPtr,StreamReader *rPtr, encodingType encode)
{
try {   ptrToMainWindow=wPtr;
    ptrToStreamReader=rPtr;
    state=Blank;
    ptrToStreamReader->SetEncoding(encode);

        ptrToPropertyText=(char *)calloc(TEXTCHUNKSIZE,sizeof(char));
        propertyTextLength=TEXTCHUNKSIZE;
        propertyTextIndex=0;
        groupTextLength=0;
        groupTextIndex=0;
        ptrToGroupText=nullptr;

    } catch (const std::exception& e) {
        throw e;
    }

}

Property::~Property() {
    if (ptrToPropertyText!=nullptr) {
        free(ptrToPropertyText);
        ptrToPropertyText=nullptr;
    }
    if (ptrToGroupText!=nullptr) {
        free(ptrToGroupText);
        ptrToGroupText=nullptr;
    }
}

ItemResult Property::PropertyReader() {
    ItemResult result;
    //Read until EOF or EOL or end of item
    //EOL us valid end of value
    //EOF is error
    //You can have a value without attributes
    //  Some Properties require an attribute
    //BEGIN:VCARD
    //VERSION:xx.xx
    //END:VCARD
    //Attribute and value parsing is specific to property
    int loop=1;
    while (loop) {
        //Read an input character
        currentChar=ptrToStreamReader->ReadOne();
        switch (currentChar) {
            //If we detect EOF or EOL before ENDOFPROPERTY
            //or ENDOFPROPERTIES its an error
            case ENEDOFFILE:
                loop=0;
                if (state==notBlank) {
                    result.SetResult(failure,PROPERTY_EOF_ERROR);
                } else {
                   loop=0;
                   result.SetResult(successEOF,PROPERTY_EOF_SUCCESS);
               }
                break;
            //Is this a  start of ATTRIBUTE?
            case STARTOFATTRIBUTE:
                //Yes, this start of ATTRIBUTE.
                //PropertyWriter(currentChar);
                loop=0;
                result.SetResult(successHasAttributes);
                break;
           //Is this value?
            case STARTOFVALUE:
               //Yes, this the start of value
                //PropertyWriter(currentChar);
                loop=0;
                if (state==notBlank) {
                    result.SetResult(successHasValue);
                } else {
                    result.SetResult(failure,PROPERTY_NO_VALUE_ERROR);
                }
                break;
           //Is this the end an EOL/New line?
           case NEW_LINE:
                //Display input character
                PropertyWriter(currentChar);
                if (ptrToStreamReader->IsEOL()) {
                    //Yes, return EOL there are no attributes or values
                    loop=0;
                    if (state==notBlank) {
                        result.SetResult(failure,PROPERTY_NO_END_ERROR);
                    } else {
                        result.SetResult(failure,PROPERTY_BLANK_ERROR);//TODO: Not sure this is correct. It could occur if you have a group but no property name.
                    }
                }
                 break;
            default:
                //Store input character in Property
                PropertyWriter(currentChar);
                state=notBlank;
               break;
            }
         }
        //Convert property name to uppercase
        // Spec says its case insensitive we convert uppercase for consistency
        switch (result.GetResult()) {
            case successHasAttributes:
            case successHasValue:
            case successEol:
            try {
                    //If we have a none null property we need to process it.
                    //First we upper case the entite string
                    //Then if the property includes a group prefix we move the group prefix to group and
                    //  remove it from property.
                    //Finally if they are non-blank we echo the group and property
                    if (ptrToPropertyText!=nullptr) {
                        //Upper case it
                        for (int i=0;i<propertyTextLength;i++) {
                           ptrToPropertyText[i]=toupper(ptrToPropertyText[i]);
                        }
                        //No process group prefix if it exists
                        char * ptrToEndOfGroup=strchr(ptrToPropertyText,GROUP_TERMINATOR);
                        //Do we have a group prefix on the property?
                        if (ptrToEndOfGroup!=nullptr) {
                            //Yes, allocate pace for it. Copy it from property to group. Remove it from property
                            size_t charSize=sizeof (char);
                            int groupSize=(ptrToEndOfGroup-ptrToPropertyText)+2;
                            int copySize=(ptrToEndOfGroup-ptrToPropertyText)+1;
                            ptrToGroupText=(char *)calloc(groupSize,charSize);
                            //copy it
                            strncpy ( ptrToGroupText, ptrToPropertyText, copySize );
                            char *startRemove=ptrToPropertyText;
                            char *endRemove=ptrToEndOfGroup+1;
                            //remove it
                            for (int removeIndex=0;removeIndex<=(endRemove-startRemove);removeIndex++) {
                                startRemove[removeIndex]=endRemove[removeIndex];
                            }
                            //Echo the Group
                            const char *groupLabel=GROUP_LABEL;
                            for (int i=0;i<(int)strlen(groupLabel);i++) {
                                ptrToStreamReader->EchoParsed(groupLabel[i]);
                            }
                            for (int j=0;j<(int)strlen(ptrToGroupText);j++) {
                                ptrToStreamReader->EchoParsed(ptrToGroupText[j]);
                            }

                        }
                        //Echo the property
                        const char *propertyLabel=PROPERTY_LABEL;
                        for (int i=0;i<(int)strlen(propertyLabel);i++) {
                            ptrToStreamReader->EchoParsed(propertyLabel[i]);
                        }
                        for (int j=0;j<(int)strlen(ptrToPropertyText);j++) {
                            ptrToStreamReader->EchoParsed(ptrToPropertyText[j]);
                        }
                    }
                } catch(exception& e) {
                        throw e;
                }
                 break;
            default:
                break;
            }
    return result;
}

//Store Property in buffer
void Property::PropertyWriter(char s) {
    //If the Property text buffer is full allocate another chunk, copy old buffer to new buffer and delete old
     if ((propertyTextIndex>=propertyTextLength)) {
         try {
             //allocate a new buffer chunk size bigger and copy data to new buffer;
             char *dstPtr=(char *)calloc(propertyTextLength+TEXTCHUNKSIZE,sizeof(char));
             for (int i=0;i<propertyTextLength;i++) {
               dstPtr[i]=ptrToPropertyText[i];
             }
            propertyTextLength=propertyTextLength+TEXTCHUNKSIZE;
             free(ptrToPropertyText);
             ptrToPropertyText=dstPtr;
         }  catch (const std::exception& e) {
             throw e;
         }
     }
     ptrToPropertyText[propertyTextIndex++]=s;
    return;
}

char *Property::GetPropertyText(void) {
    return ptrToPropertyText;
}

char *Property::GetGroupText(void) {
    return ptrToGroupText;
}

