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
    E_COLLIDER_TYPE                                 E_M_ColliderType;                               // E_COLLIDER_TYPE; �浹��� ������带 ���̱� ���� ĳ�̿�

    static Vector3                                  Vec3_S_ColliderPositionA;                       // Vector3; �浹��� ������带 ���̱� ���� ĳ�̿�
    static Vector3                                  Vec3_S_ColliderPositionB;                       // Vector3; �浹��� ������带 ���̱� ���� ĳ�̿�

    static Vector3                                  Vec3_S_ColliderDistanceEachOther;               // Vector3; �浹��� ������带 ���̱� ���� ĳ�̿�

    static Vector3                                  Vec3_S_ColliderRadiusA;                         // Vector3; �浹��� ������带 ���̱� ���� ĳ�̿�
    static Vector3                                  Vec3_S_ColliderRadiusB;                         // Vector3; �浹��� ������带 ���̱� ���� ĳ�̿�

    static Vector3                                  Vec3_S_ColliderScaleA;                         // Vector3; �浹��� ������带 ���̱� ���� ĳ�̿�
    static Vector3                                  Vec3_S_ColliderScaleB;                         // Vector3; �浹��� ������带 ���̱� ���� ĳ�̿�

    static Vector3                                  Vec3_S_ColliderDirection_sA[_DIRECTION_END];   // Vector3; �浹��� ������带 ���̱� ���� ĳ�̿�
    static Vector3                                  Vec3_S_ColliderDirection_sB[_DIRECTION_END];   // Vector3; �浹��� ������带 ���̱� ���� ĳ�̿�

    static E_COLLIDER_TYPE                          E_S_ColliderType;                              // E_COLLIDER_TYPE; �浹��� ������带 ���̱� ���� ĳ�̿�

    static int                                      S_AxisCount;                                   // int; �浹��� ������带 ���̱� ���� ĳ�̿�

public:
    HRESULT MF_Initialize();

    void MF_Update();

public:
    void MF_Check_SameGroup(USHORT _GroupA, USHORT _GroupB);

    void MF_Check_OverlapGroup(E_GROUP_INDEX _GroupIndexA, E_GROUP_INDEX _GroupIndexB);

    bool MF_Check_DistanceBetweenCenters(C_Collider2D* _ColliderA, C_Collider2D* _ColliderB);                // ����, �����ε��ϴ� ���� ������ �����غ���

    bool MF_Check_SAT();
};

