#ifndef VCARD_H
#define VCARD_H

#include <QVector>

#include "manifestconstants.h"
#include "itemresult.h"
#include "streamreader.h"
#include "contentline.h"

using namespace std;

class QApplication;
class MainWindow;
class fstream;


class Vcard
{
public:
    Vcard(QApplication *applicationptr,MainWindow *mainwindowptr,ifstream *streamptr);
    ~Vcard();
    ItemResult VCardReader(void);
    versionnumber GetVersion(void);
    void SetVersion(versionnumber cardVersion);
    QVector< ContentLine*>* GetPtrToContentLines();
    void SetContentLines(QVector < ContentLine*> *newptr);
    ItemResult CheckCardinality(ItemResult inputresult);
    StreamReader *GetPtrToStreamReader(void);
private:
  QApplication *ptrToApplication;
  MainWindow *ptrToMainWindow;
  ifstream *ptrToIfstream;
  StreamReader *ptrToStreamReader;
  QVector < ContentLine*> vectorOfContentLinePtrs;
  int propertyCardinalityForCard[NUMBEROFPROPERTYDEFINNITIONS];  
  versionnumber vcardVersion;
};

#endif // VCARD_H
