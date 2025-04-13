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
    Vector2                         Vec2_M_ColliderScale2D;                       // Vector2; 유의! 충돌체 크기로 축 값이 0.f가 들어가는 경우가 안 생기도록 디버깅 때 방어코드 작성 필수!
    Vector3                         Vec3_M_ColliderScale3D;                       // Vector3; 캐싱 목적의 멤버 변수; 유의! 함수호출의 오버헤드를 줄이기 위함

    Matrix                          Mat_M_CollisionPosition;                      // Vector3; 캐싱 목적의 멤버 변수; 유의! 함수호출의 오버헤드를 줄이기 위함

    bool                            M_IsCollision;                                // bool

    int                             M_OverLapCount;                               // int; 유의! UINT로 하지않은 이유는 카운트 감소시 음수가 되서 오버플로우 될 수 있기 때문이며, 방어코드를 넣는 것이 도리어 함수호출로 인한 오버헤드 감소거 심할 것으로 사료되어 int로 씀

    // 향후, 알림 관련 부분은 스크립트 제작시 같이 해야할 듯

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

    // 콜백용 모듈함수
    void MF_Nofify_OverlapBegin(C_Collider2D _Collider2D);

    void MF_Nofify_OverlapIng(C_Collider2D _Collider2D);

    void MF_NofifyOverlapEnd(C_Collider2D _Collider2D);

};

