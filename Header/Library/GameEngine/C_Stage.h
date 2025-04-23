#pragma once
#include "C_Entity.h"
#include "C_Group.h"

class C_Stage :
    public C_Entity
{
public:
    C_Stage(E_STAGE_NUMBER _StageNumber);          // �������� �з��� �����̹Ƿ�, ������ �����ϴ� �ɷ�

    // Stage�� ������ ���� ������? ��������� ���ǰ� �ʿ��ϸ� �� �� ����� ������ ����

public:
    ~C_Stage();

protected:
    const E_STAGE_NUMBER            L_E_M_StageNumber;                // E_STAGE_NUMBER; Stage ����
    E_STAGE_STATE                   E_M_StageState;                   // E_STAGE_STATE; Play, Pause, Stop

    E_COLLIDER_TYPE                 E_M_ColliderType;                 // E_COLLIDER_TYPE; ����! �浹�ý��� ���� ���̵���ο� ����, �浹��� ����� ���� �߻��� ���� ������ ���� ���� �뵵��

    C_Group* P_M_Group_s[_GROUP_END];          // C_Group;

public:
    virtual C_Stage* MF_Clone() override final { return nullptr; }                      // ����, �� ���� ���� �� ���Ƽ� ��� ����; ���Կ����ڸ� ���� ���� ����

public:
    void MF_Prepare();                                                                  // �ʱ�ȭ �Լ�

    void MF_Step();                                                                     // Group �� ��� Object�� Tick() ����

    void MF_StepAfter();                                                                // Group �� ��� Object�� TickAfter() ����


public:
    inline E_STAGE_NUMBER MF_Get_StageNumber()                                          // Getter; ó�� ������� �� �������� �κ��̹Ƿ�, Setter�� ���� �������� ����
    {
        return L_E_M_StageNumber;
    }

    inline E_STAGE_STATE MF_Get_StageState()                                            // Getter
    {
        return E_M_StageState;
    }

    inline E_COLLIDER_TYPE MF_Get_ColliderType()                                        // Getter
    {
        return E_M_ColliderType;
    }

    inline C_Group* MF_Get_Group_s(E_GROUP_INDEX _GroupIndex)                            // Getter
    {
        return P_M_Group_s[_GroupIndex];
    }

public:
    inline void MF_Set_StageState(E_STAGE_STATE _StageState)                            // Setter
    {
        E_M_StageState = _StageState;
    }

    inline C_Group* MF_Set_Group_s(E_GROUP_INDEX _GroupType, C_Group* _Group)     // Setter; ����Ģ�� ����� �ʵ��� ����� ����
    {
        if (nullptr == _Group)      // ����ڵ�
        {
            POPUP_DEBUG(L"nullptr == _Group", L"in C_Group* MF_Set_Group(), nullptr == _Group")
        }
        P_M_Group_s[_GroupType] = _Group;
    }

public:
    inline void MF_Detach_Group_s()                                                      // Detach; �Ҹ��� ���� ���� ����� ��ȯ���� ������ �Լ�
    {
        for (int i = 0; i < (int)_GROUP_END; ++i)
        {
            if (nullptr == P_M_Group_s[(E_GROUP_INDEX)i])				// ����ڵ�
            {
                continue;
            }
            P_M_Group_s[(E_GROUP_INDEX)i]->STL_P_M_AllObject.clear();
        }
    }


};

