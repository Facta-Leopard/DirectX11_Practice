#pragma once
#include "C_Component.h"

#include "global.h"

class C_StateComponent :
    public C_Component
{
public:
    C_StateComponent();

    // ����, �ʿ�� ���� ������ ���� �κ� ������

public:
    ~C_StateComponent();

protected:
    // ��������;
    bool                    M_IsDelete;                     // bool; ������ �������; ���� �ð��� ������ �Ǹ� �������� ������ ��
    float                   M_TimeLeftToDelete;             // float; ����������� ���� �ð�; 0�� ��� �۵����� �ʴ� ������ ����

    // �׾����� ���� �� ������ �ð�
    bool                    M_IsDie;                        // bool; �׾�����; ����, �׾������� �ٷ� ���� �����ӿ��� �������� ���� �ƴ� �����̸� �ֱ� ����
    float                   M_TimeLeftToDie;                // float; �ױ���� ���� �ð�; 0�� ��� �۵����� �ʴ� ������ ����

    // ����, Ȯ�强�� ���� �����̻� ��Ҹ� ������ ���� ���ϰ�, �߰��� Getter�� Setter ���� �Լ��� ���Խ�Ű�� �͵� ���� ��; �ϴ��� if + else if ������ ���������, ���� �÷��� ������� �ϴ� �͵� ����غ���

public:
    virtual void MF_Prepare() override;

    virtual void MF_ComponentTick() override;                           // Broad Phase; ���º������ ���� �ð� ���; ����! ���ڰ� �߰��� ���, ����κ� �߰��� ��! ����, Ȯ�强�� ���� ���ǹ� �߰��� ������ ��

    virtual void MF_ComponentTickAfter() override;                      // Narrow Phase; ���� �ð��� ���� ���� ����; ����! ���ڰ� �߰��� ���, ����κ� �߰��� ��! ����, Ȯ�强�� ���� ���ǹ� �߰��� ������ ��

public:
    inline bool MF_Get_IsDelete()                                       // Getter
    {
        return M_IsDelete;
    }

    inline bool MF_Get_IsDie()                                          // Getter
    {
        return M_IsDie;
    }

public:
    inline void MF_Set_IsDelete(bool _Bool)                             // Setter
    {
        M_IsDelete = _Bool;
    }

    inline void MF_Set_TimeLeftToDelete(float _RemainTime)              // Setter
    {
        M_TimeLeftToDelete = _RemainTime;
    }

    inline void MF_Set_IsDie(bool _Bool)                                // Setter
    {
        M_IsDie = _Bool;
    }

    inline void MF_Set_TimeLeftToDie(float _RemainTime)                 // Setter
    {
        M_TimeLeftToDie = _RemainTime;
    }

protected:
    void MF_Count_TimeLeft();                                           // ����! ���ڰ� �߰��� ���, ����κ� �߰��� ��! ����, Ȯ�强�� ���� ���ǹ� �߰��� ������ ��

    void MF_Check_State();                                              // ����! ���ڰ� �߰��� ���, ����κ� �߰��� ��! ����, Ȯ�强�� ���� ���ǹ� �߰��� ������ ��

};

