#pragma once
#include "CPlatform.h"
class CItem :
    public CPlatform
{
private:
    int itemNum; // 1 > coin, 2 > ¹ö¼¸
    class CMovement* m_Movement;
    bool isMoving;
    float overing;
    float velo;
    int onBlock;
public:
    int getItemNum() { return itemNum; }
    bool getIsMoving() { return isMoving; }
    void setIsMoving(bool _move) { isMoving = _move; }

    virtual void tick(float _DT) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;



    CItem(int);
    ~CItem();
};

