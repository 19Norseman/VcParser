/*copyright ccervo
*/
#include "mainwindow.h"

#include <fstream>
#include <string>


#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>

#include <thread>
#include <chrono>

#include "streamreader.h"
#include "contentline.h"
#include "property.h"
#include "attribute.h"
#include "value.h"
#include "vcard.h"
using namespace std;

QVector < Vcard *> vectorOfVcards;
QVector < Vcard *> vectorOfDupes;

//We've read all Vcards
//Now we need to find possible duplicates and merge them
void MergeDupes (MainWindow *ptrToMainWindow) {
    QVector<ContentLine*>* ptrToToContentLines;
    QVector<ContentLine*>* ptrToFromContentLines;
    Vcard *ptrToToVcard;
    Vcard *ptrToFromVcard;
    QString ToName;
    QString FromName;
    int indexOfToVcard;
    int indexOfFromVcard;
    int mergeFromIndex;
    int mergeToIndex;
    int indexOfFromCL;
    QString mergeToPropText;
    QString mergeFromPropText;
    QString mergeToValueText;
    QString mergeFromValueText;
    ContentLine *ptrToLineToMerge;
    ContentLine *ptrToLinePresent;
    int insertIndex;
    Q_UNUSED(ptrToLinePresent);
    int mergeCount;
    bool shouldMerge=false;//indicates From Content line should be merged into To Vcard
    bool wasDupe;//indicates From Vcard is duplicate, has same N_, as To Vcard
    int propCardinality[NUMBEROFPROPERTYDEFINNITIONS];
    propertynumber propertyNumber;
    versionnumber ToVcardVersion;
    versionnumber FromVcardVersion;
    p_cardinality ToVcardCardinality;
    //loop over all vcards looking for dupes
    //Select a To Vcard from vector of all Vcards read and then find any dupes in From vcards
    for (indexOfToVcard=0;indexOfToVcard<vectorOfVcards.length();indexOfToVcard++) {
        ptrToToVcard=vectorOfVcards.at(indexOfToVcard);
        //initialize the property cardinalities for the ToVcard
        //Build table of all properties and set cardinality of all to zero
        for (int i=0;i<NUMBEROFPROPERTYDEFINNITIONS;i++) {
            propCardinality[i]=0;
        }
        ptrToToContentLines=ptrToToVcard->GetPtrToContentLines();
        //Now loop over all ToContentLines and up date cardinality for this vcard
        for (int i=0;i<ptrToToContentLines->length();i++) {
            //Get property name of To vcard property
            QString ToVcardPropName=QString(ptrToToContentLines->at(i)->GetProperty()->GetPropertyText());
            //Convert name to number/index
            propertyNumber=(propertynumber)ptrToMainWindow->getPropertyHashValue(ToVcardPropName,ToVcardVersion);
            //adjust cardinality
            propCardinality[propertyNumber]++;
        }
        //assign the value of the N property content line of ToVcard to ToName
        //Force version of ToVcard to VERSION 4.
        //TOTO: Strip any properties not allowed in version 4
        for (int indexOfToCL=0;indexOfToCL<ptrToToContentLines->length();indexOfToCL++) {
            //We are merging duplicates force To Vcard version to Version 4
            if (QString(ptrToToContentLines->at(indexOfToCL)->GetProperty()->GetPropertyText())==QString(VERSION_NAME)) {
                int versionLength=strlen(VERSION2DOT1_NAME);
                char newVersion[versionLength+3];
                newVersion[0]=0;
                strncat(newVersion,VERSION2DOT1_NAME,versionLength);
                strncat(newVersion,"\r\n",3);
                ptrToToContentLines->at(indexOfToCL)->GetValue()->SetValueText(newVersion);
                ptrToToVcard->SetVersion(v_2dot1);
           }
            //We are forcing vcard version to version 4
            // We have to strip all properties not allowed in version 4
                for (int definitionIndex=0;definitionIndex<NUMBEROFPROPERTYDEFINNITIONS;definitionIndex++) {
                    //PropertyDefinition *propdef=ptrToMainWindow->getPtrToPropertyDefinition(definitionIndex);
                   QString propertyName=QString(ptrToMainWindow->getPtrToPropertyDefinition(definitionIndex)->getName().toStdString().c_str());
                   //If the property name of this content line matches the propertyName of the definition AND
                   // if the definition sas noneallowed,strip it.
                    if (propertyName==QString(ptrToToContentLines->at(indexOfToCL)->GetProperty()->GetPropertyText()))
                    {
                        if (ptrToMainWindow->getPtrToPropertyDefinition(definitionIndex)->getPropertyCardinality(ptrToToVcard->GetVersion())==
                            p_noneallowed)
                        {
                              delete(ptrToToContentLines->at(indexOfToCL));
                              ptrToToContentLines->remove(indexOfToCL);

                        }
                }

                }

            if (QString(ptrToToContentLines->at(indexOfToCL)->GetProperty()->GetPropertyText())==QString(N_NAME)) {
                ToName=QString(ptrToToContentLines->at(indexOfToCL)->GetValue()->GetValueText());
           }
        }
        //Select a FromVcard to see if its a duplicate of ToVcard
        //We call it a duplicate if N_ value of FromVcard equals N_ value of ToVcard
        for (indexOfFromVcard=indexOfToVcard+1;indexOfFromVcard<vectorOfVcards.length();indexOfFromVcard++) {
            ptrToFromVcard=vectorOfVcards.at(indexOfFromVcard);
            ToVcardVersion=ptrToToVcard->GetVersion();
            FromVcardVersion=ptrToFromVcard->GetVersion();
            //TODO: remove
            if (FromVcardVersion==v_3) {
                int foo=0;
                Q_UNUSED(foo);
            }
            ptrToFromContentLines=ptrToFromVcard->GetPtrToContentLines();
            int foobar=1;//inserted for debugging
            Q_UNUSED(foobar);
            //Get the value of N_property ContentLine of FromVcard
            // if it matches property value of the N content line of ToVcard, its a duplicate
            //loop matchin N_ values
            for (indexOfFromCL=0;indexOfFromCL<ptrToFromContentLines->length();indexOfFromCL++) {
                if (ptrToFromContentLines->at(indexOfFromCL)->GetProperty()->GetGroupText()!=nullptr) {
                    int foobar=1;
                    Q_UNUSED(foobar);
                }
                    if (QString(ptrToFromContentLines->at(indexOfFromCL)->GetProperty()->GetPropertyText())==QString(N_NAME)) {
                    FromName=QString(ptrToFromContentLines->at(indexOfFromCL)->GetValue()->GetValueText());
                    wasDupe=false;
                    mergeCount=0;
                    //Before comparing names we strip all trailing ";"
                    // this handles case where some writers format name as last;first;gender;title;
                    // even when gender and title are blanks
                    //First strip ToName
                    for (int i=ToName.length()-3;i>=0;i--) {
                        if (ToName.at(i)==';') {
                            ToName.remove(i,1);
                        } else {
                            break;
                        }
                    }
                    //Then strip From Name
                    for (int i=FromName.length()-3;i>=0;i--) {
                        if (FromName.at(i)==';') {
                            FromName.remove(i,1);
                        } else {
                            break;
                        }
                    }
                    //Are ToName and FromName equal
                    if (ToName==FromName) {
                        wasDupe=true;
                        //This FromVcard is considereed a duplicate of this ToVcard
                        //Merge vcard at indexOfFromCard into vcard at indexOfToCard
                        //If the ptrToFromContentLines ContentLine has a ContentLine that is not in the ptrToToContentLines
                        // 1) Merge it into the ptrToToContentLines ContentLines Vector
                        // 2) remove it from the ptrToFromContentLines ContentLines vector
                        // 3) a) If we merged a ContentLine replace the ContentLines vector in ToVcard with
                        //        ContentLines vector from FromVcard
                        //    b) remove the ContentLines vector from FromVcard (avoids double delete)
                        //    c) delete FromVcard from Vcard vector (avoids double delete)

                        //loop over all Content lines in FromVcard looking for property value not in content lines of ToVcard
                        for ( mergeFromIndex=0;mergeFromIndex<ptrToFromContentLines->length()-1;mergeFromIndex++) {
                            shouldMerge=true;//assume we fill merge from ContentLine into To ContentLines
                             //loop over all to ContentLines checking for match with from
                            for (mergeToIndex=0;mergeToIndex<ptrToToContentLines->length()-1;mergeToIndex++) {
                                mergeToPropText=QString(ptrToToContentLines->at(mergeToIndex)->GetProperty()->GetPropertyText());
                                mergeFromPropText=QString(ptrToFromContentLines->at(mergeFromIndex)->GetProperty()->GetPropertyText());
                                if (mergeFromIndex==0) {
                                    insertIndex=ptrToToContentLines->length()-1;
                                }
                                ptrToLineToMerge=ptrToFromContentLines->at(mergeFromIndex);
                                ptrToLinePresent=ptrToToContentLines->at(mergeToIndex);
                                Q_UNUSED(ptrToLinePresent);
                                if (ptrToToContentLines->at(mergeToIndex)->GetValue()!=nullptr) {
                                    mergeToValueText=ptrToToContentLines->at(mergeToIndex)->GetValue()->GetValueText();
                                }
                                if (ptrToFromContentLines->at(mergeFromIndex)->GetValue()!=nullptr) {
                                    mergeFromValueText=ptrToFromContentLines->at(mergeFromIndex)->GetValue()->GetValueText();
                                }
                                    propertyNumber=(propertynumber)ptrToMainWindow->getPropertyHashValue(mergeToPropText,ToVcardVersion);

                                    ToVcardCardinality=
                                            ptrToMainWindow->getPtrToPropertyDefinition(propertyNumber)->
                                            getPropertyCardinality(ToVcardVersion);
                                    //For ContentLines to require merging Properties must be equal
                                    if (mergeToPropText==mergeFromPropText) {
                                        //properties are equal.
                                        // if values are not equal we merge
                                        if (mergeToValueText==mergeFromValueText) {
                                            //values are equal we don't need to merge
                                            shouldMerge=false;
                                            break;
                                        } else {
                                            insertIndex=mergeToIndex;
                                            //Properties are equal and values are not equal we need to merge lines
                                            //If required cardinality of property is none, or exactly one we can't merge
                                            if ((ToVcardCardinality==p_oneormoremay)||(ToVcardCardinality==p_oneormoremust)) {
                                                //Properties match, values are different and required cardinalithy
                                                // is not none or exactly one
                                                // we need to merge
                                                continue;
                                            } else {
                                                //Properties match, values are different, but cardinality is none or exactly one
                                                // we can't merge
                                                shouldMerge=false;
                                                break;
                                            }
                                        }
                                    } else {
                                        //Properties are not equal
                                        //Its possible the property from FromVcard is not in ToVcard
                                        // If shouldMerge is true when we fall out of loop that's the case
                                        // and we merge it
                                        continue;
                                    }

                            }//Loop over all To property lines checking for match with from
                            //Should we merge contentline from FromVcard?
                            if (shouldMerge) {
                                  // Maybe
                                 // If property is not allowed in ToVcard version we can't merge it
                                    for (int definitionIndex=0;definitionIndex<NUMBEROFPROPERTYDEFINNITIONS;definitionIndex++) {
                                        //PropertyDefinition *propdef=ptrToMainWindow->getPtrToPropertyDefinition(definitionIndex);
                                       QString propertyName=QString(ptrToMainWindow->getPtrToPropertyDefinition(definitionIndex)->
                                                                    getName().toStdString().c_str());
                                       //If the property name of this content line in FromVcard matches the propertyName of the definition AND
                                       // if the definition is not allowed for ToVcard, don't merge
                                        if (propertyName==QString(ptrToFromContentLines->at(mergeFromIndex)->GetProperty()->GetPropertyText())
                                                &&(ptrToMainWindow->getPtrToPropertyDefinition(definitionIndex)->getPropertyCardinality(ptrToToVcard->
                                                   GetVersion())==p_noneallowed))
                                        {
                                            //Indeicae we can't merge it
                                            shouldMerge=false;
                                        }
                                    }
                                    //Again, should we merge contentline from FromVcard?
                                    if (shouldMerge) {
                                        //Yes. Add the ContentLine to ToVcard
                                        mergeCount++;
                                        ptrToToContentLines->insert(insertIndex,ptrToLineToMerge);
                                        //remove it from ptrToFromContentLines, but don't delete it. it will be deleted when merged vcard is deleted
                                        ptrToFromContentLines->remove(mergeFromIndex);
\
                                    }
                            }
                            int foo=1;
                            Q_UNUSED(foo);
                }//Loop over all contentlines in fromContentlines
            }//end of if N_ of ToVcard matches N_ of FromVcard
         }//end of if property is N_
        int bad=1;
        Q_UNUSED(bad;)
      }//over all From content lines looking for match N
      if (wasDupe==true) {
        //save the dupicate vcard
        vectorOfDupes.append(vectorOfVcards.at(indexOfFromVcard));
        //remove it from the vector of vcards
        vectorOfVcards.remove(indexOfFromVcard--);
      }
    }//FromvCard
    }//end of loop looking for dupes of To vcard
}


void *VcardToCharString(Vcard *ptrToVcard,bool tofile)
{
    char *bufferPtr=nullptr;
  try {
        int bufferLength=0;
        int bufferIndex=0;
        QVector < ContentLine*> *ptrToVectorofContentLinePtrs;
        ptrToVectorofContentLinePtrs=ptrToVcard->GetPtrToContentLines();
        if (ptrToVectorofContentLinePtrs->length()>0) {
            bufferPtr=(char *)malloc(1);
            bufferLength=1;

            //Write all the content lines
            for (int contentLineIndex=0;contentLineIndex<ptrToVectorofContentLinePtrs->length();contentLineIndex++)
            {
                //Get the group and copy it to buffer
                Property *ptrToProperty=ptrToVectorofContentLinePtrs->at(contentLineIndex)->GetProperty();
                if (ptrToProperty!=nullptr) {
                    const char *ptrToGroupText=(const char *)ptrToProperty->GetGroupText();
                    if (ptrToGroupText!=nullptr) {
                        int groupLength=(int)strlen(ptrToGroupText);
                        bufferLength+=groupLength;
                        bufferPtr=(char *)realloc((void*)bufferPtr,(size_t)bufferLength);
                        for (int i=0;i<groupLength;i++) {
                            bufferPtr[bufferIndex++]=ptrToGroupText[i];
                        }
                    }
                }

               //Get the property name and copy it to buffer
               ptrToProperty=ptrToVectorofContentLinePtrs->at(contentLineIndex)->GetProperty();
               if (ptrToProperty!=nullptr) {
                   const char *ptrToPropertyText=(const char *)ptrToProperty->GetPropertyText();
                   if (ptrToPropertyText!=nullptr) {
                       int propertyLength=(int)strlen(ptrToPropertyText);
                       bufferLength+=propertyLength;
                       bufferPtr=(char *)realloc((void*)bufferPtr,(size_t)bufferLength);
                       for (int i=0;i<propertyLength;i++) {
                           bufferPtr[bufferIndex++]=ptrToPropertyText[i];
                       }
                   }
               }
               //Copy start of attribute and get the attribute text to buffer
               Attribute *ptrToAttribute=ptrToVectorofContentLinePtrs->at(contentLineIndex)->GetAttribute();
               if (ptrToAttribute!=nullptr) {
                   const char *ptrToAttributeText=(const char *)ptrToAttribute->GetAttributeText();
                   if (ptrToAttributeText!=nullptr) {
                       int attributeLength=(int)strlen(ptrToAttributeText)+1;
                       bufferLength+=attributeLength;
                       bufferPtr=(char *)realloc((void *)bufferPtr,(size_t)bufferLength);
                       bufferPtr[bufferIndex++]=STARTOFATTRIBUTE;
                       for (int i=0;i<attributeLength-1;i++) {
                           bufferPtr[bufferIndex++]=ptrToAttributeText[i];
                       }
                   }
               }
               //Copy start of value, get the value to buffer
               Value *ptrToValue=ptrToVectorofContentLinePtrs->at(contentLineIndex)->GetValue();
               if (ptrToValue!=nullptr) {
                   const char *ptrToValueText=(const char *)ptrToValue->GetValueText();
                    if (ptrToValueText!=nullptr) {
                       int valueLength=(int)strlen(ptrToValueText)+1;
                       bufferLength+=valueLength;
                       bufferPtr=(char *)realloc((void*)bufferPtr,(size_t)bufferLength);
                       bufferPtr[bufferIndex++]=STARTOFVALUE;
                       for (int i=0;i<valueLength-1;i++) {
                           if ((ptrToValueText[i]!=CARRIAGE_RETURN) || (tofile==true)) {
                               bufferPtr[bufferIndex++]=ptrToValueText[i];
                           }
                       }
                   }
               }

            }
            bufferPtr[bufferIndex++]=0;
        }
    } catch (exception &e) {
        throw e;
    }
    return bufferPtr;
}
void ForceEchoVcard(Vcard * ptrToVcard) {
    try {
            void *vcharsPtr=VcardToCharString(ptrToVcard,false);
            char *ptrToChars=(char *)vcharsPtr;
            if (vcharsPtr!=nullptr) {
                for (int i=0;i<(int)strlen(ptrToChars);i++) {
                    ptrToVcard->GetPtrToStreamReader()->ForceEchoInput(ptrToChars[i]);
                }
            }
    } catch (exception &e) {
        throw e;
    }
    return;
}

//Write Vcard
//Write parsed vcard to output file
int WriteVcard(Vcard * ptrToVcard,ofstream *outputStream) {
    int result=0;
    try {
        void *vcardChars=VcardToCharString( ptrToVcard,true);
        char *ptrToChars=(char *)vcardChars;
        if (vcardChars!=nullptr) {
                outputStream->write(ptrToChars,strlen(ptrToChars));
                free(vcardChars);
       }

    } catch (exception &e) {
        throw e;
        result=-1;
    }

    return result;
}

//Pause Vcard reading
void pause(QApplication *ptrToApplication,MainWindow *ptrToMainWindow,ifstream * ptrToInputStream, ofstream * ptrToOutputStream) {
   do  {
       ptrToApplication->processEvents();
       ptrToMainWindow->getInputLabel()->setVisible(true);
       ptrToMainWindow->getInputEditText()->setVisible(true);
       if (ptrToMainWindow->getOctalDisplayState()) {
           ptrToMainWindow->getInputOctalLabel()->setVisible(true);
           ptrToMainWindow->getInputOctalEditText()->setVisible(true);
       } else {
           ptrToMainWindow->getInputOctalLabel()->setVisible(false);
           ptrToMainWindow->getInputOctalEditText()->setVisible(false);
       }
       if (ptrToMainWindow->getParsedDisplayState()) {
           ptrToMainWindow->getOutputLabel()->setVisible(true);
           ptrToMainWindow->getOutputEditText()->setVisible(true);
       } else {
           ptrToMainWindow->getOutputLabel()->setVisible(false);
           ptrToMainWindow->getOutputEditText()->setVisible(false);
       }
       ptrToMainWindow->blinkStartButton();
//Todo: remove       ptrToMainWindow->blinkContinueButton();
       ptrToApplication->processEvents();
       std::this_thread::sleep_for(std::chrono::milliseconds(200));
       //TODO: Not sure if this is clean
       //This only works if pause is called
       //If application is run without stop on vcard
       // it hangs for ever;
       if (ptrToMainWindow->getIsClosed()) {
           if ((ptrToInputStream!=nullptr)&&(ptrToInputStream->is_open())) {
               ptrToInputStream->close();
           }
           if ((ptrToOutputStream!=nullptr)&&(ptrToOutputStream->is_open())) {
               ptrToOutputStream->close();
           }
           ptrToApplication->exit(0);
           exit(0);
       }
    } while ((!ptrToMainWindow->getStartButtonState()));
//Todo: remove } while ((!ptrToMainWindow->getStartButtonState())(!ptrToMainWind&&ow->getContinueButtonState()));
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    ifstream inputStream;
    ofstream outputStream;
    QMessageBox messageBox;
//    StreamReader *ptrToStreamReader=nullptr;
    Vcard *ptrToVcard=nullptr;
    ItemResult result;
    QString inputName="";
    QString outputName="";
    QString outputPathName="";
    inputName=QFileDialog::getOpenFileName(nullptr,INPUT_FILE_DIALOG_TITLE,FILE_SEARCH_PATH,VCF_FILE_WILD_CARD);
    if (inputName.isNull()) {
        messageBox.setText(MB_MAIN_CLOSED_MESSAGE);
        messageBox.exec();
        return -1;
    } else {
        inputStream.open(inputName.toStdString().c_str(),ios_base::in);
        if (!inputStream.is_open()) {
            return -1;
        }
    }
    w.show();
    //Works but very slow. QPlainTextEdit is slow
    // Add ability to stop enable or disable input echo, octal input echo, output echo
    // Add checks for valid vcard -> BEGIN,END,FN,VERSION
    // Add ability to handle multiple VCARDS
    int loop1=1;
    int loop2=1;
    pause(&a,&w,&inputStream,&outputStream);
    if (w.getOutputState()) {
        if (w.getOneFileState()) {
            //Get name of file to write output Vcard file to
            outputName=QFileDialog::getSaveFileName(nullptr,OUTPUT_FILE_DIALOG_TITLE,FILE_SEARCH_PATH);
        } else {
            //Get path to directory to write Vcard files to.
            outputPathName=outputName=QFileDialog::getExistingDirectory(nullptr,OUTPUT_DIRECTORY_DIALOG_TITLE,FILE_SEARCH_PATH);
        }
    }
    //Loop until error on eof
    while (loop2) {
        //loop reading one card
        while (loop1) {
            a.processEvents();
            a.processEvents();
            //Create a new vcard object
            ptrToVcard= new Vcard(&a,&w,&inputStream);
            //Read vcard definition from input stream
            result=ptrToVcard->VCardReader();
            /*    noerror,
            emptyresult,
            successHasAttributes,
            successHasValue,
            successEol,
            successEOF,
            failure_cardinality,
            failure
            */
            switch(result.GetResult()) {
            //Did we successfully read vcard
            case successEol: {
                //Yes drop out of read vcard loop
                loop1=0;
                vectorOfVcards.append(ptrToVcard);
            }
                break;
            case successEOF:
                loop1=0;
                loop2=0;
                break;
            case failure_cardinality:
            case failure: {
                //Yes, we had an error reading vcard
                // format a message to display and display it
                // in message box
                string vcardmessage=MAIN_VCARD_ERROR;
                const char *resultWhat=result.GetWhat();
                vcardmessage+=resultWhat;
                messageBox.setText(vcardmessage.c_str());
                messageBox.exec();
                //Was the error a fatal error?
                if ((result.GetLevel()==levelfatal)) {
                    ForceEchoVcard( ptrToVcard);
                    pause(&a,&w,&inputStream,&outputStream);
                    //Yes, drop out of reading input stream
                    loop1=0;
                    loop2=0;
                    //TODO: add code to echo bad vcard
                } else {
                    //No, error wasn't fatal.
                    //Pause to allow user interaction
                    pause(&a,&w,&inputStream,&outputStream);
                    //None fatal error,  write vcard and continue
                    //Drop out of reading this vcard
                    loop1=0;
                    vectorOfVcards.append(ptrToVcard);
                }
            }
                break;
            case emptyresult: {
                string message=MAIN_DONE;
                message+=result.GetWhat();
                messageBox.setText(message.c_str());
                messageBox.exec();
                loop1=0;
                loop2=0;
            }
               break;
            case successHasAttributes:
                break;
            case successHasValue:
                break;
            case noerror:
               break;

            }
            continue;
        }
        //Todo: Not sure if this clean
        if (w.getIsClosed()) {
            if (inputStream.is_open()) {
               inputStream.close();
            }
            if (outputStream.is_open()) {
                outputStream.close();
            }

            a.exit(0);
            exit(0);
        }
        if (w.getStopState()!=0) {
            pause(&a,&w,&inputStream,&outputStream);
        }
        loop1=1;
        if ((result.GetResult()==failure) ||(result.GetResult()==emptyresult)) {
            break;
        }
        w.getInputEditText()->clear();
        w.getInputOctalEditText()->clear();
        w.getOutputEditText()->clear();
     }
    if (w.getMergeState()) {
        MergeDupes(&w);
    }
    //Should we write vcards to output file?
    if (w.getOutputState()) {
        //Do we want all output in one file?
        if (!w.getOneFileState()) {
            //No, write Vcards to individual files
            for (int i=0;i<vectorOfVcards.length();i++) {
                outputName="";
                for (int j=0;j<vectorOfVcards[i]->GetPtrToContentLines()->length();j++) {
                    if (vectorOfVcards[i]->GetPtrToContentLines()->at(j)->GetProperty()!=nullptr) {
                        if (QString(vectorOfVcards[i]->GetPtrToContentLines()->at(j)->GetProperty()->GetPropertyText())==N_NAME) {
                            //Got n_name property
                            if (vectorOfVcards[i]->GetPtrToContentLines()->at(j)->GetValue()!=nullptr) {
                                outputName=vectorOfVcards[i]->GetPtrToContentLines()->at(j)->GetValue()->GetValueText();
                                for (int k=0;k<outputName.length();k++) {
                                    if (!outputName.at(k).isLetterOrNumber()) {
                                       outputName[k]=' ';
                                    }
                                }
                                outputName=outputName.simplified();
                                for (int k=0;k<outputName.length();k++) {
                                    if (outputName.at(k)==' ') {
                                       outputName[k]='_';
                                    }
                                }
                                outputName=outputPathName+"/"+outputName+"_"+QString(to_string(i).c_str())+".vcf";
                                break;
                            }
                            break;
                        }
                    }
                }
                if (outputName!=QString("")) {
                outputStream.open((const char*)outputName.toStdString().c_str(),ios_base::out);
                WriteVcard(vectorOfVcards.at(i),&outputStream);
                outputStream.close();
                }
            }
        } else {
            //Yes, we write all output Vcards in one file
            if (outputName!=QString("")) {
                outputStream.open((const char*)outputName.toStdString().c_str(),ios_base::out);
                for (int i=0;i<vectorOfVcards.length();i++) {
                    WriteVcard(vectorOfVcards.at(i),&outputStream);
                }
                outputStream.close();
            }

        }
    }
    //Delete all the vcards we read
    for (int j=vectorOfVcards.length()-1;j>=0;j--) {
        delete(vectorOfVcards[j]);
        vectorOfVcards.remove(j);
    }
    for (int i=vectorOfDupes.length()-1;i>=0;i--) {
        delete(vectorOfDupes[i]);
        vectorOfDupes.remove(i);
    }
    messageBox.setText(MB_MAIN_EOF_MESSAGE);
    messageBox.exec();
    a.processEvents();
    a.exit(0);
    if (inputStream.is_open()) {
        inputStream.close();
    }
    if (outputStream.is_open()) {
        outputStream.close();
    }
    return 0;
    }
