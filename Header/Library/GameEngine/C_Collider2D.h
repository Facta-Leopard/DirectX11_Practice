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
    Vector2                         Vec2_M_ColliderScale2D;                       // Vector2; ����! �浹ü ũ��� �� ���� 0.f�� ���� ��찡 �� ���⵵�� ����� �� ����ڵ� �ۼ� �ʼ�!
    Vector3                         Vec3_M_ColliderScale3D;                       // Vector3; ĳ�� ������ ��� ����; ����! �Լ�ȣ���� ������带 ���̱� ����

    Matrix                          Mat_M_CollisionPosition;                      // Vector3; ĳ�� ������ ��� ����; ����! �Լ�ȣ���� ������带 ���̱� ����

    bool                            M_IsCollision;                                // bool

    int                             M_OverLapCount;                               // int; ����! UINT�� �������� ������ ī��Ʈ ���ҽ� ������ �Ǽ� �����÷ο� �� �� �ֱ� �����̸�, ����ڵ带 �ִ� ���� ������ �Լ�ȣ��� ���� ������� ���Ұ� ���� ������ ���Ǿ� int�� ��

    // ����, �˸� ���� �κ��� ��ũ��Ʈ ���۽� ���� �ؾ��� ��

public:
    CLONE(C_Collider2D)

    virtual void MF_Prepare() override;

    virtual void MF_ComponentTick() override;

    virtual void MF_ComponentTickAfter() override;

public:
    inline Vector2 MF_Get_ColliderScale2D()
    {
        return Vec2_M_ColliderScale2D;
    }

    inline void MF_Set_ColliderScale2D(Vector2 _ColliderScale2D)
    {
        Vec2_M_ColliderScale2D = _ColliderScale2D;
    }

    inline Vector3 MF_Get_ColliderScale3D()
    {
        return Vec3_M_ColliderScale3D;
    }

    inline void MF_Set_ColliderScale3D(Vector3 _ColliderScale3D)
    {
        Vec3_M_ColliderScale3D = _ColliderScale3D;
    }

    inline Matrix MF_Get_ColliderPosition()
    {
        return Mat_M_CollisionPosition;
    }

    inline void MF_Set_ColliderPosition(Matrix _ColliderPosition)
    {
        Mat_M_CollisionPosition = _ColliderPosition;
    }

    inline bool MF_Get_IsCollision()
    {
        return M_IsCollision;
    }

    inline void MF_Set_IsCollision(bool _IsCollision)
    {
        M_IsCollision = _IsCollision;
    }

    inline void MF_Set_IsCollisionOn()
    {
        M_IsCollision = true;
    }

    inline void MF_Set_IsCollisionOff()
    {
        M_IsCollision = false;
    }

    inline int MF_Get_OverlapCount()
    {
        return M_OverLapCount;
    }

    inline void MF_Set_OverlapCount(int _OverlapCount)
    {
        M_OverLapCount = _OverlapCount;
    }

    inline void MF_Set_Add_OverlapCount()
    {
        ++M_OverLapCount;
    }

    inline void MF_Set_Subtrct_OverlapCount()
    {
        --M_OverLapCount;
    }
    
public:
    void MF_On_OverlapBegin(C_Collider2D _Collider2D);

    void MF_On_OverlapIng(C_Collider2D _Collider2D);

    void MF_On_OverlapEnd(C_Collider2D _Collider2D);

    // �ݹ�� ����Լ�
    void MF_Nofify_OverlapBegin(C_Collider2D _Collider2D);

    void MF_Nofify_OverlapIng(C_Collider2D _Collider2D);

    void MF_NofifyOverlapEnd(C_Collider2D _Collider2D);

};

