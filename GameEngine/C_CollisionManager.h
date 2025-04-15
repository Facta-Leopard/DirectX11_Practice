#pragma once
#include "C_Singleton.h"
#include "global.h"

class C_CollisionManager :
    public C_Singleton<C_CollisionManager>
{
    SINGLE(C_CollisionManager)

protected:
    DWORD                                           SDK_M_Group_s[_GROUP_END];                      // DWORD ; ���� �ڵ� ������ �޸� ����(Pragma Pack(1)�� �ʼ��� �ϰ� �ϰ�, �̿� ���� SIMD ������ ����� �� �����Ƿ�, ������ ���Ͽ� ����ü�� ����Ͽ� �ذ��ϰ��� ��

    unordered_map<ULONGLONG,bool>                   STL_M_SDKIsCollision;                           // unordered_map<ULARGE_INTEGER,bool>; �ʹ� ��Ŷ�� ���ϴ� ����̸�, ���� Ȯ�强���� ����Ͽ� ������ map���ٴ� �� ��ȸ�� ��ȸ�� �� ���� ������ ����ǹǷ� STL ����

    // ĳ�̿� ��� ����
    UINT                                            SDK_M_BucketSize;                               // UINT; unordered_map �ӵ� ������ ���� ĳ�̿�; �ʱⰪ�� 4095�� �ϰ� ������ 65535; ����, �� �κ��� Ȯ�强�� ����ؼ� �� ���� �浹ü�� ������ ���, ���ؽø� ���̱� ���� ���� 1048575�� �ϴ� ���� ���� �� ����(Ŀ�Ƿ���ũ ���� 300ms ����)

    E_COLLIDER_TYPE                                 E_M_ColliderType;                               // E_COLLIDER_TYPE; �浹��� ������带 ���̱� ���� ĳ�̿�

    Vector3                                         Vec3_M_ColliderPositionA;                       // Vector3; �浹��� ������带 ���̱� ���� ĳ�̿�
    Vector3                                         Vec3_M_ColliderPositionB;                       // Vector3; �浹��� ������带 ���̱� ���� ĳ�̿�
    Vector3                                         Vec3_M_ColliderDistanceEachOther;               // Vector3; �浹��� ������带 ���̱� ���� ĳ�̿�; �� �浹ü�� �ִ� ����

    Vector2                                         Vec2_M_ColliderPositionA;                       // Vector2; �浹��� ������带 ���̱� ���� ĳ�̿�; MF_Check_DistanceBetweenCenters() ����
    Vector2                                         Vec2_M_ColliderPositionB;                       // Vector2; �浹��� ������带 ���̱� ���� ĳ�̿�; MF_Check_DistanceBetweenCenters() ����

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

    bool MF_Check_DistanceBetweenCenters(C_Collider2D* _ColliderA, C_Collider2D* _ColliderB);                // ����, �����ε��ϴ� ���� ������ �����غ���

    bool MF_Check_SAT();
};

