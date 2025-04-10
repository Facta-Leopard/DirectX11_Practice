#pragma once
#include "C_Component.h"

#include "enum.h"

class C_ScriptComponent :
    public C_Component
{
public:
    C_ScriptComponent(E_SCRIPT_TYPE _ScrptType);

protected:
    C_ScriptComponent(const C_ScriptComponent& _Origin);

public:
    ~C_ScriptComponent();

protected:
    E_SCRIPT_TYPE               M_ScrptType;                // E_SCRIPT_TYPE

public:
    virtual C_ScriptComponent* MF_Clone() = 0;              // Clone Function; Virtual

    virtual void MF_ComponentTick() final {}                // ��ӹ��� �۵��Լ� �߻�ȭ �������̵� �Ҵ� ����

    virtual void MF_ComponentTickAfter() override {}        // ��ӹ��� �۵��Լ� �߻�ȭ �������̵� �Ҵ� ����

    virtual void MF_ScriptTick() = 0;                       // ��ӹ޴� Ŭ������ �۵��Լ� �ۼ��� �����ϱ� ���ؼ� �߻�ȭ ����

public:
    E_SCRIPT_TYPE MF_Get_ScriptType()                       // Getter; ����! C_Object�� Template Function�� ���������Ƿ�, ������ ����!
    {
        return M_ScrptType;
    }
};

