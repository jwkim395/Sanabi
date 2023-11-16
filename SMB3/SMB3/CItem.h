#pragma once
#include "CPlatform.h"
class CItem :
    public CPlatform
{
private:
    int itemNum; // 1 > coin, 2 > ¹ö¼¸
public:
    int getItemNum() { return itemNum; }

    CItem(int);
    ~CItem();
};

