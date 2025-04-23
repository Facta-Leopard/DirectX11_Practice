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
    XMVECTOR                      XM_VEC3_M_ColliderScale;                                 // Vector3; 유의! 충돌체 크기로 축 값이 0.f가 들어가는 경우가 안 생기도록 디버깅 때 방어코드 작성 필수!

    XMMATRIX                      XM_MAT_M_CollisionXMMATRIX;                              // Matrix; 유의! 오버헤드 감소 목적의 멤버 변수;

    XMVECTOR                      XM_VEC3_M_CollisionDirection_s[_DIRECTION_END];          // Vector3; 유의! 오버헤드 감소 목적의 멤버 변수; C_Transform의 방향벡터를 캐싱함

    bool                          M_IsDependent;                                           // bool; 오브젝트와의 의존성 관련

    int                           M_OverLapCount;                                          // int; 유의! UINT로 하지않은 이유는 카운트 감소시 음수가 되서 오버플로우 될 수 있기 때문이며, 방어코드를 넣는 것이 도리어 함수호출로 인한 오버헤드 감소거 심할 것으로 사료되어 int로 씀

    // 향후, 알림 관련 부분은 스크립트 제작시 같이 해야할 듯

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

        

    // 코드개선으로 인한 무효화
    //inline void MF_Set_Subtrct_OverlapCount()
    //{
    //    --M_OverLapCount;
    //}

public:
    void MF_On_OverlapBegin(C_Collider2D* _Collider2D);

    void MF_On_OverlapIng(C_Collider2D* _Collider2D);

    void MF_On_OverlapEnd(C_Collider2D* _Collider2D);

    // 콜백용 모듈함수; 향후, 스크립트 구성시 함수내용 .cpp에 적용할 수 있도록 할 것
    void MF_Nofify_OverlapBegin(C_Collider2D* _Collider2D);                      // 스크립트 구성시 마저 작성필요

    void MF_Nofify_OverlapIng(C_Collider2D* _Collider2D);                        // 스크립트 구성시 마저 작성필요

    void MF_NofifyOverlapEnd(C_Collider2D* _Collider2D);                         // 스크립트 구성시 마저 작성필요
    
};

