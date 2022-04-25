#include "itemresult.h"

ItemResult::ItemResult()
{
    resultCode=noerror;
    message="";
}

ItemResult::~ItemResult()
{

}

itemError ItemResult::ItemResult::GetResult()
{
    return resultCode;
}

const char* ItemResult::ItemResult::GetWhat()
{
  return message;
}

void ItemResult::SetResult(itemError code,const char *what,itemErrorLevel level) {
    resultCode=code;
    message=what;
    errorLevel=level;
}

itemErrorLevel ItemResult::GetLevel() {
    return errorLevel;
}
