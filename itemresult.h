#ifndef ITEMRESULT_H
#define ITEMRESULT_H
#include "manifestconstants.h"

class ItemResult
{
public:
    ItemResult();
    ~ItemResult();
    void SetResult(itemError code,const char *what="",itemErrorLevel level=levelwarning);
    itemError GetResult();
    const char *GetWhat();
    itemErrorLevel GetLevel();
private:
itemError resultCode;
const char *message;
itemErrorLevel errorLevel;
};

#endif // ITEMRESULT_H
