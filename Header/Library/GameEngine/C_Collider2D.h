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
    Vector3                         M_ColliderScale;                              // Vector3; ����! �浹ü ũ��� �� ���� 0.f�� ���� ��찡 �� ���⵵�� ����� �� ����ڵ� �ۼ� �ʼ�!
    Vector3                         Mat_M_CollisionPosition;                      // Vector3; ĳ�� ������ ��� ����


    bool                            M_IsCollision;                                // bool

    Vector3                         M_OverLapCount;                               // Vector3



public:
    CLONE(C_Collider2D)

    virtual void MF_Prepare() override;

    virtual void MF_ComponentTick() override;

    virtual void MF_ComponentTickAfter() override;

public:

};

