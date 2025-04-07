#pragma once

#include "C_Entity.h"

#include "enum.h"
#include "component.h"

class C_Object;

class C_Component :
    public C_Entity
{
public:
    C_Component(E_COMPONENT_TYPE _E_COMPONENT);

protected:

    C_Component(const C_Component& _Origin);

public:
    virtual ~C_Component();

protected:
    const E_COMPONENT_TYPE          L_M_ComponentType;              // const E_COMPONENT_TYPE; ������ ���� Ÿ������ ������ �� ���������� �ϱ� ����

    C_Object*                       P_M_OwnerObject;                // C_Object*; ������Ʈ�� ���� ��ü ����� �˷��ִ� ����

public:
    // �߻� �Լ� ������ Ŭ�������� ��ӹް� ����, �ٽ� �߻�Ŭ������ �������� �� override�� ������ ����!
    virtual C_Component* MF_Clone() override = 0;                   // Clone Function; Virtual

    virtual void MF_ComponentTick() = 0;                            // ��ӹ޴� Ŭ������ �۵��Լ� �ۼ��� �����ϱ� ���ؼ� �߻�ȭ ����

    virtual void MF_ComponentTickAfter() = 0;                       // ��ӹ޴� Ŭ������ �۵��Լ� �ۼ��� �����ϱ� ���ؼ� �߻�ȭ ����

    virtual C_Component* MF_GetMyself()                             // Return This Point By Vitual and Polymorph; �������� �̿��� �ڱ��ڽ� ��ȯ�Լ�
    {
        if (_COMPONENT_SCRIPT == this->L_M_ComponentType)           // ����ڵ�
        {
            POPUP_DEBUG(L"Return This Is Script Component", L"in C_Component::GetMyself, _COMPONENT_SCRIPT == this->L_M_ComponentType")
        }
        if (_COMPONENT_RENDER == this->L_M_ComponentType)           // ����ڵ�
        {
            POPUP_DEBUG(L"Return This Is Script Component", L"in C_Component::GetMyself, _COMPONENT_RENDER == this->L_M_ComponentType")
        }
        return this; 
    }

    virtual void MF_Prepare() = 0;                                  // ��ӹ޴� Ŭ������ �۵��Լ� �ۼ��� �����ϱ� ���ؼ� �߻�ȭ ����

public:
    inline E_COMPONENT_TYPE MF_GetComponentType()                   // Getter
    {
        return L_M_ComponentType;
    }

    // ����, Ŭ������ �ڵ�����ȯ �߰�����



};

