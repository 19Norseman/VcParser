#include "mainwindow.h"
#include "property.h"
#include "attribute.h"
#include "value.h"
#include "contentline.h"

ContentLine::ContentLine(MainWindow *wPtr,StreamReader *rPtr, encodingType encode) {
    ptrToMainWindow=wPtr;
    ptrToStreamReader=rPtr;
    state=Blank;
    ptrToValue=nullptr;
    ptrToAttribute=nullptr;
    ptrToProperty=nullptr;
    encoding=encode;
}
ContentLine::~ContentLine() {
    if (ptrToValue!=nullptr) {
        delete(ptrToValue);
        ptrToProperty=nullptr;
    }
    if (ptrToAttribute!=nullptr) {
        delete(ptrToAttribute);
        ptrToAttribute=nullptr;
    }
    if (ptrToProperty!=nullptr) {
        delete(ptrToProperty);
        ptrToProperty=nullptr;
    }
    return;

}
ItemResult ContentLine::ContentLineReader() {
    ItemResult result;
    char lookAhead;
    int loop=1;
    state=Blank;
    while (loop) {
        switch (state) {
            //Not started. skip whitespace and blank lines
            case Blank:
                lookAhead=ptrToStreamReader->Peekone();
                switch (lookAhead) {
                 case CARRIAGE_RETURN:
                    ptrToStreamReader->ReadOne();
                    break;
                 case NEW_LINE:
                    ptrToStreamReader->ReadOne();
                    break;
                 case SPACE:
                    ptrToStreamReader->ReadOne();
                    break;
                 case HORIZONTAL_TAB:
                    ptrToStreamReader->ReadOne();
                    break;
                 case (char)ENEDOFFILE:
                    loop=0;
                    if (state==Blank) {
                        state=done;
                       result.SetResult(successEOF,CONTENTLINE_EOF,levelfatal);
                    } else {
                        result.SetResult(emptyresult,CONTENTLINE_EOF,levelfatal);
                    }
                    break;
                default:
                    //If peek shows none white space switch to state to  notBlank
                    // By BNF a non blank line must start with property, have 0 or more attributes and one value
                    state=notBlank;
                    ptrToProperty=new Property(ptrToMainWindow,ptrToStreamReader,encoding);
                    break;
                }
                break;
             //Not Blank read the property
             case notBlank:
                //We have a none blank line
                // By BNF property must start with group or name, have 0 or more attributes and exactly 1 value
                result=ptrToProperty->PropertyReader();
                switch (result.GetResult()) {
                    //if we failed to find property return failure
                    case emptyresult:
                        loop=0;
                        break;
                    case failure:
                        loop=0;
                        break;
                    //if we have attributes read them
                    case successHasAttributes:
                        //Create and attribute object and read the attribute
                        ptrToAttribute=new Attribute(ptrToMainWindow,ptrToStreamReader,encoding);
                        state=hasAttribute;
                        break;
                    //if we have a value read it
                    case successHasValue:
                        //Create a value object and read it.
                        ptrToValue=new Value(ptrToMainWindow,ptrToStreamReader,encoding);
                        state=hasValue;
                        break;
                    //Any other result is a failure
                    default:
                        loop=0;
                        result.SetResult(ptrToProperty->PropertyReader().GetResult(),ptrToProperty->PropertyReader().GetWhat());
                        break;
                }
                break;
            case hasAttribute:
                //read all the attibutes
                result=ptrToAttribute->AttributeReader();
                switch(result.GetResult()) {
                    //If we failed to read attribute report failure
                    case failure:
                        break;
                    case successHasValue:
                        {
                            //Does attribute specify encoding?
                            char *ptrToAttributeText=ptrToAttribute->GetAttributeText();
                            if (strstr(ptrToAttributeText,BASE64NAME)!=nullptr) {
                                encoding=base64;
                            } else {
                                if (strstr(ptrToAttributeText,QUOTEDPRINTABLENAME)!=nullptr) {
                                    encoding=quotedprintable;
                                } else {
                                    encoding=none;
                                }
                            }
                            //Create a value object and read it.
                            ptrToValue=new Value(ptrToMainWindow,ptrToStreamReader,encoding);
                            state=hasValue;
                            }
                            break;
                        case noerror:
                                break;
                        default:
                                break;
                    }
                    break;
            case hasValue:
                result=ptrToValue->ValueReader();
                switch(result.GetResult()) {
                    case failure:
                    loop=0;
                    break;
                case successEol:
                    loop=0;
                     break;
                default:
                    loop=0;
                    break;
                }
               break;
            case done:
                loop=0;
                break;
            default:
            break;
    }
    }
    return result;
}
Value *ContentLine::GetValue() {
    return ptrToValue;
}
Attribute *ContentLine::GetAttribute() {
    return ptrToAttribute;
}
Property *ContentLine::GetProperty() {
    return ptrToProperty;
}
