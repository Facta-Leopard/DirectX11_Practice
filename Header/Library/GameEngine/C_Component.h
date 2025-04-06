#pragma once

#include "C_Entity.h"

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
    C_Object*                       P_M_OwnerObject;                // C_Object*; ������Ʈ�� ���� ��ü ����� �˷��ִ� ����

    const E_COMPONENT_TYPE          L_M_ComponentType;              // const E_COMPONENT_TYPE; ������ ���� Ÿ������ ������ �� ���������� �ϱ� ����

public:
    // �߻� �Լ� ������ Ŭ�������� ��ӹް� ����, �ٽ� �߻�Ŭ������ �������� �� override�� ������ ����!
    virtual C_Component* MF_Clone() override = 0;                   // Clone Function; Virtual

public:
    // ����, Ŭ������ �ڵ�����ȯ �߰�����



};

