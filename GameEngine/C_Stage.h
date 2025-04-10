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
    const E_STAGE_NUMBER            L_M_StageNumber;                // E_STAGE_NUMBER; Stage ����
    E_STAGE_STATE                   M_StageState;                   // E_STAGE_STATE; Play, Pause, Stop
    C_Group*                        P_M_Group_s[_GROUP_END];        // C_Group;

public:
    virtual C_Stage* MF_Clone() override final { return nullptr; }                      // ����, �� ���� ���� �� ���Ƽ� ��� ����; ���Կ����ڸ� ���� ���� ����

public:
    void MF_Prepare();                                                                  // �ʱ�ȭ �Լ�

    void MF_Step();                                                                     // Group �� ��� Object�� Tick() ����

    void MF_StepAfter();                                                                // Group �� ��� Object�� TickAfter() ����

    void DetachGroups();                                                                // �Ҹ��� ���� ���� ����� ��ȯ���� ������ �Լ�


    inline E_STAGE_NUMBER MF_Get_StageNumber()                                          // Getter; ó�� ������� �� �������� �κ��̹Ƿ�, Setter�� ���� �������� ����
    {
        return L_M_StageNumber;
    }

    inline E_STAGE_STATE MF_Get_StageState()                                            // Getter
    {
        return M_StageState;
    }

    inline void MF_Set_StageStage(E_STAGE_STATE _StageState)                            // Setter
    {
        M_StageState = _StageState;
    }


    inline C_Group* MF_Get_Groups()                                                     // Getter
    {
        return P_M_Group_s[_GROUP_END - 1];                                             // ����, _GROUP_END - 1 �κ� �ٽ� �����غ� ��; Index�� ��� �б� ���� �����
    }

    inline C_Group* MF_Set_GroupInGroups(C_Group* _Group, E_GROUP_TYPE _GroupType)      // Setter; ����Ģ�� ����� �ʵ��� ����� ����
    {
        for (size_t i = 0; i < _GROUP_END; i++)
        {
            if (_GroupType == i)
            {
                P_M_Group_s[i] = _Group;
            }
        }
    }

};

