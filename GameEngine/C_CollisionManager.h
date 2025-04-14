#pragma once
#include "C_Singleton.h"
#include "global.h"

class C_CollisionManager :
    public C_Singleton<C_CollisionManager>
{
    SINGLE(C_CollisionManager)

protected:
    USHORT                                      SDK_M_Group_s[_GROUP_END];                     // USHORT; ���� �ڵ� ������ �޸� ����(Pragma Pack(1)�� �ʼ��� �ϰ� �ϰ�, �̿� ���� SIMD ������ ����� �� �����Ƿ�, ������ ���Ͽ� ����ü�� ����Ͽ� �ذ��ϰ��� ��
    unordered_map<POINTS,bool>                  STL_M_SDKIsCollision;                          // unordered_map<POINTS,bool>; �ʹ� ��Ŷ�� ���ϴ� ����̸�, ���� Ȯ�强���� ����Ͽ� ������ map���ٴ� �� ��ȸ�� ��ȸ�� �� ���� ������ ����ǹǷ� STL ����

public:
    HRESULT MF_Initialize();

    void MF_Update();



public:
    void MF_Check_SameGroup(USHORT _GroupA, USHORT _GroupB);

    void MF_Check_OverlapGroup(E_GROUP_INDEX _GroupIndexA, E_GROUP_INDEX _GroupIndexB);

    void MF_Check_SAT(C_Collider2D _ColliderA, C_Collider2D _ColliderB);
};

