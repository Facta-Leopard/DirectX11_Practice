#pragma once
#include "component.h"

#include "C_StageManager.h"

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
    XMVECTOR                      XM_VEC3_M_ColliderScale;                                 // Vector3; ����! �浹ü ũ��� �� ���� 0.f�� ���� ��찡 �� ���⵵�� ����� �� ����ڵ� �ۼ� �ʼ�!

    XMMATRIX                      XM_MAT_M_CollisionXMMATRIX;                              // Matrix; ����! ������� ���� ������ ��� ����;

    XMVECTOR                      XM_VEC3_M_CollisionDirection_s[_DIRECTION_END];          // Vector3; ����! ������� ���� ������ ��� ����; C_Transform�� ���⺤�͸� ĳ����

    bool                          M_IsDependent;                                           // bool; ������Ʈ���� ������ ����

    int                           M_OverLapCount;                                          // int; ����! UINT�� �������� ������ ī��Ʈ ���ҽ� ������ �Ǽ� �����÷ο� �� �� �ֱ� �����̸�, ����ڵ带 �ִ� ���� ������ �Լ�ȣ��� ���� ������� ���Ұ� ���� ������ ���Ǿ� int�� ��

    // ����, �˸� ���� �κ��� ��ũ��Ʈ ���۽� ���� �ؾ��� ��

public:
    CLONE(C_Collider2D)

    virtual void MF_Prepare() override;

    virtual void MF_ComponentTick() override;

    virtual void MF_ComponentTickAfter() override;

public:
    inline XMVECTOR MF_Get_ColliderScale()
    {
        return XM_VEC3_M_ColliderScale;
    }

    inline XMMATRIX MF_Get_ColliderXMMATRIX()
    {
        return XM_MAT_M_CollisionXMMATRIX;
    }

    inline XMVECTOR MF_Get_XMVECTOR3FromCollisionXMMATRIX()
    {
        E_COLLIDER_TYPE T_ColliderType = C_StageManager::SF_Get_Instance()->MF_Get_CurrentStage()->MF_Get_ColliderType();

        XMVECTOR _XM_VEC3_Scale, _XM_VEC3_Rotation, XM_VEC3_T_Position;
        XMMatrixDecompose(&_XM_VEC3_Scale, &_XM_VEC3_Rotation, & XM_VEC3_T_Position, XM_MAT_M_CollisionXMMATRIX);

        switch (T_ColliderType)
        {
        case _COLLIDER_2D_TOPVEIW:
        case _COLLIDER_2D_ISOMETRICVIEW:
            XM_VEC3_T_Position = XMVectorSetY(XM_VEC3_T_Position, 0.f);
            return XM_VEC3_T_Position; // Vector3(Vec3_T_Position.x, 0.f, Vec3_T_Position.z);
            
            break;
        default:
            XM_VEC3_T_Position = XMVectorSetZ(XM_VEC3_T_Position, 0.f);
            return XM_VEC3_T_Position; // Vector3(Vec3_T_Position.x, Vec3_T_Position.y, 0.f);

            break;
        }
    }

    inline bool MF_Get_IsDependent()
    {
        return M_IsDependent;
    }

    inline int MF_Get_OverlapCount()
    {
        return M_OverLapCount;
    }

public:


    void MF_Set_ColliderScale(XMVECTOR _XM_VEC3_ColliderScale);

    inline void MF_Set_ColliderXMMATRIX(XMMATRIX _ColliderXMMATRIX)
    {
        XM_MAT_M_CollisionXMMATRIX = _ColliderXMMATRIX;
    }

    inline void MF_Set_IsDependent(bool _IsDependent)
    {
        M_IsDependent = _IsDependent;
    }

    inline void MF_Set_IsDependentOn()
    {
        M_IsDependent = true;
    }

    inline void MF_Set_IsDependentOff()
    {
        M_IsDependent = false;
    }

    inline void MF_Set_OverlapCount(int _OverlapCount)
    {
        M_OverLapCount = _OverlapCount;
    }

    inline void MF_Set_Add_OverlapCount()
    {
        ++M_OverLapCount;
    }

        

    // �ڵ尳������ ���� ��ȿȭ
    //inline void MF_Set_Subtrct_OverlapCount()
    //{
    //    --M_OverLapCount;
    //}

public:
    void MF_On_OverlapBegin(C_Collider2D* _Collider2D);

    void MF_On_OverlapIng(C_Collider2D* _Collider2D);

    void MF_On_OverlapEnd(C_Collider2D* _Collider2D);

    // �ݹ�� ����Լ�; ����, ��ũ��Ʈ ������ �Լ����� .cpp�� ������ �� �ֵ��� �� ��
    void MF_Nofify_OverlapBegin(C_Collider2D* _Collider2D);                      // ��ũ��Ʈ ������ ���� �ۼ��ʿ�

    void MF_Nofify_OverlapIng(C_Collider2D* _Collider2D);                        // ��ũ��Ʈ ������ ���� �ۼ��ʿ�

    void MF_NofifyOverlapEnd(C_Collider2D* _Collider2D);                         // ��ũ��Ʈ ������ ���� �ۼ��ʿ�
    
};

