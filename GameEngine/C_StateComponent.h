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
    // ��������
    bool                    M_IsDelete;                     // bool; ������ �������
    float                   M_TimeLeftToDelete;             // float; ����������� ���� �ð�

    // �׾����� ���� �� ������ �ð�
    bool                    M_IsDie;                        // bool; �׾�����; ����, �׾������� �ٷ� ���� �����ӿ��� �������� ���� �ƴ� �����̸� �ֱ� ����
    float                   M_TimeLeftToDie;                // float; �ױ���� ���� �ð�

    // ����, Ȯ�强�� ���� �����̻� ��Ҹ� ������ ���� ��

public:
    virtual void MF_Prepare() override;

    virtual void MF_ScriptTick() override;


};

