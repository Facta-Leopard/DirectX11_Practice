#pragma once
#include "component.h"

class C_Collider2D
    : public C_Component
{
public:
    C_Collider2D();

protected:
    C_Collider2D(const C_Collider2D& _Origin);

public:
    ~C_Collider2D();

protected:
    Vector3                         M_ColliderScale;                              // Vector3; 유의! 충돌체 크기로 축 값이 0.f가 들어가는 경우가 안 생기도록 디버깅 때 방어코드 작성 필수!
    Vector3                         Mat_M_CollisionPosition;                      // Vector3; 캐싱 목적의 멤버 변수


    bool                            M_IsCollision;                                // bool

    Vector3                         M_OverLapCount;                               // Vector3



public:
    CLONE(C_Collider2D)

    virtual void MF_Prepare() override;

    virtual void MF_ComponentTick() override;

    virtual void MF_ComponentTickAfter() override;

public:

};

