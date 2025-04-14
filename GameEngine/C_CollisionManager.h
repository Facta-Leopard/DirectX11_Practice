#pragma once
#include "C_Singleton.h"
#include "global.h"

class C_CollisionManager :
    public C_Singleton<C_CollisionManager>
{
    SINGLE(C_CollisionManager)

protected:
    USHORT                                      SDK_M_Group_s[_GROUP_END];                     // USHORT; 기존 코드 형식은 메모리 정렬(Pragma Pack(1)을 필수로 하게 하고, 이에 따른 SIMD 적용이 어려울 수 있으므로, 윈도우 유니온 구조체를 사용하여 해결하고자 함
    unordered_map<POINTS,bool>                  STL_M_SDKIsCollision;                          // unordered_map<POINTS,bool>; 초반 버킷을 정하는 방식이며, 향후 확장성까지 고려하여 기존의 map보다는 더 순회며 조회가 더 빠를 것으로 예상되므로 STL 변경

public:
    HRESULT MF_Initialize();

    void MF_Update();



public:
    void MF_Check_SameGroup(USHORT _GroupA, USHORT _GroupB);

    void MF_Check_OverlapGroup(E_GROUP_INDEX _GroupIndexA, E_GROUP_INDEX _GroupIndexB);

    void MF_Check_SAT(C_Collider2D _ColliderA, C_Collider2D _ColliderB);
};

