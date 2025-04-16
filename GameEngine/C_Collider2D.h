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
    Vector3                         Vec3_M_ColliderScale;                               // Vector3; ����! �浹ü ũ��� �� ���� 0.f�� ���� ��찡 �� ���⵵�� ����� �� ����ڵ� �ۼ� �ʼ�!

    Matrix                          MAT_M_CollisionMatrix;                               // Matrix; ����! ������� ���� ������ ��� ����;

    Vector3                         Vec3_M_CollisionDirection_s[_DIRECTION_END];      // Vector3; ����! ������� ���� ������ ��� ����; C_Transform�� ���⺤�͸� ĳ����

    bool                            M_IsDependent;                                      // bool; ������Ʈ���� ������ ����

    int                             M_OverLapCount;                                     // int; ����! UINT�� �������� ������ ī��Ʈ ���ҽ� ������ �Ǽ� �����÷ο� �� �� �ֱ� �����̸�, ����ڵ带 �ִ� ���� ������ �Լ�ȣ��� ���� ������� ���Ұ� ���� ������ ���Ǿ� int�� ��

    // ����, �˸� ���� �κ��� ��ũ��Ʈ ���۽� ���� �ؾ��� ��

public:
    CLONE(C_Collider2D)

    virtual void MF_Prepare() override;

    virtual void MF_ComponentTick() override;

    virtual void MF_ComponentTickAfter() override;

public:
    inline Vector3 MF_Get_ColliderScale()
    {
        return Vec3_M_ColliderScale;
    }

    inline void MF_Set_ColliderScale(Vector3 _ColliderScale)
    {
        Vec3_M_ColliderScale = _ColliderScale;

        E_COLLIDER_TYPE T_ColliderType = C_StageManager::SF_Get_Instance()->MF_Get_CurrentStage()->MF_Get_ColliderType();

        switch (T_ColliderType)
        {

        case _COLLIDER_2D_TOPVEIW:
        case _COLLIDER_2D_ISOMETRICVIEW:

            Vec3_M_ColliderScale = (Vector3)(_ColliderScale.x, 0.f, _ColliderScale.z);

            break;
        default:

            Vec3_M_ColliderScale = (Vector3)(_ColliderScale.x, _ColliderScale.y, 0.f);

            break;
        }
    }

    inline Matrix MF_Get_ColliderMatrix()
    {
        return MAT_M_CollisionMatrix;
    }

    inline Vector3 MF_Get_Vector3FromCollisionMatrix()
    {
        E_COLLIDER_TYPE T_ColliderType = C_StageManager::SF_Get_Instance()->MF_Get_CurrentStage()->MF_Get_ColliderType();

        Vector3 Vec3_T_Position = MAT_M_CollisionMatrix.Translation();

        // ������ ���ڸ����� ����.. �������µ� �� �������ž�
        switch (T_ColliderType)
        {
        case _COLLIDER_2D_TOPVEIW:
        case _COLLIDER_2D_ISOMETRICVIEW:
            Vec3_T_Position.y = 0.f;
            return Vec3_T_Position; // Vector3(Vec3_T_Position.x, 0.f, Vec3_T_Position.z);
            
            break;
        default:
            Vec3_T_Position.z = 0.f;
            return Vec3_T_Position; // Vector3(Vec3_T_Position.x, Vec3_T_Position.y, 0.f);

            break;
        }
    }

    inline void MF_Set_ColliderPosition(Matrix _ColliderMatrix)
    {
        MAT_M_CollisionMatrix = _ColliderMatrix;
    }

    inline bool MF_Get_IsDependent()
    {
        return M_IsDependent;
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

