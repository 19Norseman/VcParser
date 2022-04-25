
#include <fstream>
#include <cstring>

#include <QApplication>

#include <mainwindow.h>
#include "vcard.h"
#include "property.h"
#include "attribute.h"
#include "propertydefinition.h"
#include "value.h"

Vcard::Vcard(QApplication *applicationptr,MainWindow *mainwindowptr,ifstream *streamptr)
{
    vcardVersion=v_2dot1;
    ptrToApplication=applicationptr;
    ptrToMainWindow=mainwindowptr;
    ptrToIfstream=streamptr;
    ptrToStreamReader=new StreamReader(ptrToApplication,ptrToMainWindow,ptrToIfstream);
}

Vcard::~Vcard() {
    delete(ptrToStreamReader);
    for (int i=0;i<vectorOfContentLinePtrs.length();i++) {
        delete (vectorOfContentLinePtrs.at(i));
    }
}

StreamReader *Vcard::GetPtrToStreamReader(void) {
    return ptrToStreamReader;
}


versionnumber Vcard::GetVersion(void) {
    return vcardVersion;
}
void Vcard::SetVersion(versionnumber cardVersion) {
    vcardVersion=cardVersion;
}



QVector< ContentLine*>* Vcard::GetPtrToContentLines() {
    return &vectorOfContentLinePtrs;
}

void Vcard::SetContentLines(QVector < ContentLine*> *newptr) {
    //Todo: Should we delete content lines before deleting?
    vectorOfContentLinePtrs.clear();
    if (newptr!=nullptr) {
        for (int i=0;i<newptr->length();i++)
        {
           vectorOfContentLinePtrs.append(newptr->at(i));
        }
    }
   }


ItemResult Vcard::VCardReader(void) {
    ItemResult result;
    int loop=1;
    int contentLineIndex=0;//initialize the number of contentlines in the vcard
    for (int i=0;i<NUMBEROFPROPERTYDEFINNITIONS;i++) {
        propertyCardinalityForCard[i]=0;
    }
    //read one Vcard from stream by readint content lines until we get an error or an END:VCARD
    while (loop) {
        ptrToApplication->processEvents();
        //Create a new empty content line
        vectorOfContentLinePtrs.append( new ContentLine(ptrToMainWindow,ptrToStreamReader, none));
        //Read and set the content of the content line stored stored in the vector;
        result=vectorOfContentLinePtrs.at(contentLineIndex)->ContentLineReader();
        //Did we read a valid content line
        if ((result.GetResult()==failure)||(result.GetResult()==emptyresult)||(result.GetResult()==successEOF)) {
            break;//No return failure or empty
        } else {
            //Check cardinality of properties for this content line
            //Get a pointer to property of this contentLine
            Property *ptrToproperty=vectorOfContentLinePtrs.at(contentLineIndex)->GetProperty();
            //Get a pointer to the text of the property of this contantLIne
            char * propertyText=ptrToproperty->GetPropertyText();
            //Convert the propertyText to a property number
            propertynumber propertyN=(propertynumber)ptrToMainWindow->getPropertyHashValue(propertyText,GetVersion());
            //get num ber of content lines in this card
            int countOfContentLines=vectorOfContentLinePtrs.length();
            Q_UNUSED(countOfContentLines);
            //get a pointer to the Attributes for this contentLine
            Attribute * ptrToAttribute=vectorOfContentLinePtrs.at(contentLineIndex)->GetAttribute();
            //get the count of attributes for this contentLine
            int countOfAttributes=0;
            a_cardinality attributeCardinality=a_noneallowed;
            //If there are attributes for this content line, get the count of attributes
            if (ptrToAttribute!=nullptr )
                countOfAttributes=ptrToAttribute->GetAttributeCount();
            Value *ptrToValue=vectorOfContentLinePtrs.at(contentLineIndex)->GetValue();
            //if there are values for this content line get valuesse \r\n;
            char *valueText=(char *)"\r\n";
            if (ptrToValue!=nullptr) {
                valueText=ptrToValue->GetValueText();
            }
            //create an array to handle store values;
            char trimmedValue[strlen(valueText)];
            //copy values
            strncpy(trimmedValue,valueText,strlen(valueText)-2);//trim off the trailing /r/n
            trimmedValue[strlen(valueText)-2]=0;
            switch (propertyN) {
                //When property is end_p check all content lines for property cardinality
                // this handles case where cardinality >0 is required but has not been met
                case end_p:
                    {
                        propertyCardinalityForCard[end_p]++;
                        //set intial result to success
                        //We have an END:VCARD so break out of loop reading content lines
                        loop=0;
                    }
                    break;
            case begin_p:                
                ptrToMainWindow->incrementVcardCount();
                ptrToMainWindow->getVcardLineEdit()->setText(to_string(ptrToMainWindow->getVcardCount()).c_str());
                goto common;

            case version_p:
                SetVersion((versionnumber)ptrToMainWindow->getVersionHashValue(QString(trimmedValue)));
                goto common;
            case n_p:
            {
                //If there is a value, regularize it
                int nameSize=sizeof(trimmedValue)/sizeof(trimmedValue[0]);
                if ( nameSize!=0) {
                    //First force trim it and force to lower case
                    QString name=QString(trimmedValue).simplified().toLower();
                    //Then force initial caps
                    for (int i=0;i<name.length();i++) {
                        if (i==0) {
                            name[i]=name.at(i).toUpper();
                        }
                        if ((name.at(i)==';') && (i+1<name.length())) {
                            name[i+1]=name.at(i+1).toUpper();
                        } else {
                            if ((name.at(i)==' ') && (i+1<name.length())) {
                                name[i+1]=name.at(i+1).toUpper();
                            }
                        }
                    }
                    //then set it as value text
                    if (ptrToValue!=nullptr) {
                        name.append("\r\n");
                        ptrToValue->SetValueText((char *)name.toStdString().c_str());
                    }
                }
                goto common;
            }
            case fn_p:
            {
                //If there is a value, regularize it
                int fullNameSize=sizeof(trimmedValue)/sizeof(trimmedValue[0]);
                if ( fullNameSize!=0) {
                    //First trim it and force to lower case
                    QString fullName=QString(trimmedValue).simplified().toLower();
                    //Then force initial caps
                    for (int i=0;i<fullName.length();i++) {
                        if (i==0) {
                            fullName[i]=fullName.at(i).toUpper();
                        }
                        if ((fullName.at(i)==' ') && (i+1<fullName.length())) {
                            fullName[i+1]=fullName.at(i+1).toUpper();
                        }
                    }
                    //then set it as value text
                    if (ptrToValue!=nullptr) {
                        fullName.append("\r\n");
                        ptrToValue->SetValueText((char *)fullName.toStdString().c_str());
                    }
                }
                goto common;
            }
            case email_p:
            {
                //If there is a value, regularize it
                int emailSize=sizeof(trimmedValue)/sizeof(trimmedValue[0]);
                if (emailSize!=0) {
                    //First force trim it and force to lower case
                    QString emailAddr=QString(trimmedValue).simplified().toLower();
                   //then set it as value text
                    if (ptrToValue!=nullptr) {
                        emailAddr.append("\r\n");
                        ptrToValue->SetValueText((char *)emailAddr.toStdString().c_str());
                    }
                }
                goto common;
            }

            case tel_p:
            {
                //If there is a value, regularize it
                int fullTelSize=sizeof(trimmedValue)/sizeof(trimmedValue[0]);
                QString tellNum;
                if ( fullTelSize!=0) {
                    //First trim it and force to lower case
                    tellNum=QString(trimmedValue).simplified().toLower();
                    //Then strip all but numerics
                    for (int i=tellNum.length()-1;i>=0;i--) {
                        if (!tellNum.at(i).isNumber()) {
                            tellNum.remove(i,1);
                        }                        }
                    }
                int tellNumLength=tellNum.length();
                    //then insert hyphens for readability
                switch (tellNumLength) {
                case 3:
                    tellNum.insert(1,'-');
                    break;
                case 4:
                    tellNum.insert(2,'-');
                    break;
                case 5:
                    tellNum.insert(1,'-');
                    tellNum.insert(4,'-');
                    break;
                case 6:
                    tellNum.insert(2,'-');
                    tellNum.insert(5,'-');
                    break;
                case 7:
                    tellNum.insert(3,'-');
                    break;
                case 8:
                    tellNum.insert(1,'-');
                    tellNum.insert(5,'-');
                    break;
                case 9:
                    tellNum.insert(2,'-');
                    tellNum.insert(6,'-');
                    break;
                case 10:
                    tellNum.insert(tellNum.length()-4,'-');
                    tellNum.insert(tellNum.length()-8,'-');
                    break;

                default:
                    if (tellNumLength>10) {
                        tellNum.insert(tellNum.length()-4,'-');
                        tellNum.insert(tellNum.length()-8,'-');
                        tellNum.insert(tellNum.length()-12,'-');
                    }
                    break;
                }


                    if (ptrToValue!=nullptr) {
                        tellNum=tellNum+"\r\n";
                        ptrToValue->SetValueText((char *)tellNum.toStdString().c_str());
                    }
                }
                goto common;

common:
             default:
                    {
                        const char *ptrTOExpermentalProperty=strstr(vectorOfContentLinePtrs.at(contentLineIndex)->GetProperty()->GetPropertyText(),EXPERIMENTALPROPERTY);
                        //If this property is an experimental property and stripping is requested,
                        // strip it.
                        if ((ptrTOExpermentalProperty!=nullptr) &&
                                (ptrTOExpermentalProperty)==vectorOfContentLinePtrs.at(contentLineIndex)->GetProperty()->GetPropertyText()
                                && (ptrToMainWindow->getStripXState()))
                        {
                            delete(vectorOfContentLinePtrs.at(contentLineIndex));
                            vectorOfContentLinePtrs.remove(contentLineIndex--);
                        }

                        char *errorMessage=ptrToMainWindow->messageBuffer;
                        const char *propertyName=ptrToMainWindow->getPtrToPropertyDefinition(propertyN)->getName().toStdString().c_str();
                        propertyCardinalityForCard[propertyN]++;
                        sprintf(errorMessage,VCARD_ATTRIBUTE_CARDINALITY_ERROR,ptrToMainWindow->getVcardCount(),propertyName,propertyCardinalityForCard[propertyN]);
                        attributeCardinality=ptrToMainWindow->getPtrToPropertyDefinition(propertyN)->getAttributeCardinality(GetVersion());
                        switch (attributeCardinality) {
                        case a_noneallowed:
                            if (countOfAttributes!=0) {
                                result.SetResult(failure_cardinality,errorMessage);
                            }
                            break;
                        case a_exactlyonemust:
                            if (countOfAttributes!=1) {
                                result.SetResult(failure_cardinality,errorMessage);
                            }
                            break;
                        case a_exactlyonemay:
                            if (countOfAttributes>1) {
                                result.SetResult(failure_cardinality,errorMessage);
                            }
                            break;
                        case a_oneormoremust:
                            if (countOfAttributes<1) {
                                result.SetResult(failure_cardinality,errorMessage);
                            }
                            break;
                        case a_oneormoremay:
                            break;
                        }
                       break;
                    }
            }

            contentLineIndex++;
        }
        continue;//Keep going;
    }
    if ((result.GetResult()==successEol) || (result.GetResult()==successEOF))
        result=CheckCardinality(result);
    return result;
}

ItemResult Vcard::CheckCardinality(ItemResult inputresult) {
     itemErrorLevel inputlevel=inputresult.GetLevel();
    if (inputresult.GetResult()!=successEOF) {
        for (int definitionIndex=0;definitionIndex<NUMBEROFPROPERTYDEFINNITIONS;definitionIndex++) {
            char *errorMessage=ptrToMainWindow->messageBuffer;
            //PropertyDefinition *propdef=ptrToMainWindow->getPtrToPropertyDefinition(definitionIndex);
            const char *propertyName=ptrToMainWindow->getPtrToPropertyDefinition(definitionIndex)->getName().toStdString().c_str();
            sprintf(errorMessage,VCARD_PROPERTY_CARDINALITY_ERROR,ptrToMainWindow->getVcardCount(),propertyName,propertyCardinalityForCard[definitionIndex]);
            switch(ptrToMainWindow->getPtrToPropertyDefinition(definitionIndex)->getPropertyCardinality(GetVersion()))
            {
                case p_noneallowed:
                if (propertyCardinalityForCard[definitionIndex]!=0) {
                    //TODO: made non-fatal possible restore
                    inputresult.SetResult(failure_cardinality,errorMessage);
                    definitionIndex=NUMBEROFPROPERTYDEFINNITIONS;
                }
                break;
                case p_exactlyonemust:
                if (propertyCardinalityForCard[definitionIndex]!=1) {
                    inputresult.SetResult(failure_cardinality,errorMessage,levelfatal);
                    definitionIndex=NUMBEROFPROPERTYDEFINNITIONS;
                }
#if 0
                    //TODO: Changed handling of property to teate these as unknowb
                    if ((strcmp(propertyName,"TZ"))&&(strcmp(propertyName,"FN")))
                    {
                        if (propertyCardinalityForCard[definitionIndex]!=1) {
                            inputresult.SetResult(failure_cardinality,errorMessage,levelfatal);
                            definitionIndex=NUMBEROFPROPERTYDEFINNITIONS;
                        }
                    } else {
                        break;
                    }
#endif
                    break;
                case p_exactlyonemay:
                if (propertyCardinalityForCard[definitionIndex]>1) {
                    inputresult.SetResult(failure_cardinality,errorMessage);
                    definitionIndex=NUMBEROFPROPERTYDEFINNITIONS;
                }
                    break;
                case p_oneormoremust:
                if (propertyCardinalityForCard[definitionIndex]==0) {
                    inputresult.SetResult(failure_cardinality,errorMessage,levelfatal);
                    definitionIndex=NUMBEROFPROPERTYDEFINNITIONS;
                }
                    break;
                case p_oneormoremay:
                    break;
                default:
                        break;
            }
        }
        if (inputlevel==levelfatal) {
            //SetResult(itemError code,const char *what="",itemErrorLevel level=levelwarning);
           inputresult.SetResult(inputresult.GetResult(),inputresult.GetWhat(),inputlevel);
        }
    }
    return inputresult;
}
