#pragma once
#include "C_Singleton.h"
#include "global.h"

class C_CollisionManager :
    public C_Singleton<C_CollisionManager>
{
    SINGLE(C_CollisionManager)

protected:
    DWORD                                           SDK_M_Group_s[_GROUP_END];                      // DWORD ; 기존 코드 형식은 메모리 정렬(Pragma Pack(1)을 필수로 하게 하고, 이에 따른 SIMD 적용이 어려울 수 있으므로, 윈도우 유니온 구조체를 사용하여 해결하고자 함

    unordered_map<ULONGLONG,bool>                   STL_M_SDKIsCollision;                           // unordered_map<ULARGE_INTEGER,bool>; 초반 버킷을 정하는 방식이며, 향후 확장성까지 고려하여 기존의 map보다는 더 순회며 조회가 더 빠를 것으로 예상되므로 STL 변경

    // 캐싱용 멤버 변수
    UINT                                            SDK_M_BucketSize;                               // UINT; unordered_map 속도 증가를 위한 캐싱용; 초기값은 4095로 하고 다음은 65535; 향후, 이 부분은 확장성을 고려해서 더 많은 충돌체를 생각할 경우, 리해시를 줄이기 위한 값인 1048575로 하는 것이 좋을 것 같음(커피레이크 기준 300ms 추정)

    E_COLLIDER_TYPE                                 E_M_ColliderType;                               // E_COLLIDER_TYPE; 충돌계산 오버헤드를 줄이기 위한 캐싱용

    Vector3                                         Vec3_M_ColliderPositionA;                       // Vector3; 충돌계산 오버헤드를 줄이기 위한 캐싱용
    Vector3                                         Vec3_M_ColliderPositionB;                       // Vector3; 충돌계산 오버헤드를 줄이기 위한 캐싱용
    Vector3                                         Vec3_M_ColliderDistanceEachOther;               // Vector3; 충돌계산 오버헤드를 줄이기 위한 캐싱용; 두 충돌체를 있는 벡터

    Vector2                                         Vec2_M_ColliderPositionA;                       // Vector2; 충돌계산 오버헤드를 줄이기 위한 캐싱용; MF_Check_DistanceBetweenCenters() 전용
    Vector2                                         Vec2_M_ColliderPositionB;                       // Vector2; 충돌계산 오버헤드를 줄이기 위한 캐싱용; MF_Check_DistanceBetweenCenters() 전용

public:
    HRESULT MF_Initialize();

    void MF_Update();

public:
    inline UINT MF_Get_BucketSize()
    {
        return SDK_M_BucketSize;
    }

    inline void MF_Set_MF_Get_BucketSize(UINT _BucketSize)
    {
        SDK_M_BucketSize = _BucketSize;

    }

public:
    void MF_Check_SameGroup(USHORT _GroupA, USHORT _GroupB);

    void MF_Check_OverlapGroup(E_GROUP_INDEX _GroupIndexA, E_GROUP_INDEX _GroupIndexB);

    bool MF_Check_DistanceBetweenCenters(C_Collider2D* _ColliderA, C_Collider2D* _ColliderB);                // 향후, 오버로딩하는 것이 좋을지 생각해보자

    bool MF_Check_SAT();
};

