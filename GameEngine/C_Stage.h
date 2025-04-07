#pragma once
#include "C_Entity.h"
#include "C_Gruop.h"

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
    C_Group*                        P_M_Group_s[_GROUP_END];        // C_Group*;

public:
    virtual C_Stage* MF_Clone() override final { return nullptr; }                      // ����, �� ���� ���� �� ���Ƽ� ��� ����; ���Կ����ڸ� ���� ���� ����

public:
    void MF_Prepare();                                                                  // �ʱ�ȭ �Լ�

    void MF_Step();                                                                     // Group �� ��� Object�� Tick() ����

    void MF_StepAfter();                                                                // Group �� ��� Object�� TickAfter() ����

    void DetachGroups();                                                                // �Ҹ��� ���� ���� ����� ��ȯ���� ������ �Լ�


    inline E_STAGE_NUMBER MF_GetStageNumber()                                           // Getter; ó�� ������� �� �������� �κ��̹Ƿ�, Setter�� ���� �������� ����
    {
        return L_M_StageNumber;
    }

    inline E_STAGE_STATE MF_GetStageState()                                             // Getter
    {
        return M_StageState;
    }

    inline void MF_SetStageStage(E_STAGE_STATE _StageState)                             // Setter
    {
        M_StageState = _StageState;
    }


    inline C_Group* MF_GetGroups()                                                      // Getter
    {
        return P_M_Group_s[_GROUP_END - 1];                                             // Index�� ��� �б� ���� �����
    }

    inline C_Group* MF_SetGroupInGroups(C_Group* _Group, E_GROUP_TYPE _GroupType)       // Setter; ����Ģ�� ����� �ʵ��� ����� ����
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

