#pragma once
#include "C_Entity.h"

#include "define.h"

class C_Component;

class C_Object :
    public C_Entity
{
protected:
    C_Object();
    C_Object(const C_Object& _Origin);
    
    ~C_Object();

protected:
    // ȿ������ ���� Heap���� ����
    C_Component*         M_Components[_COMPONENT_END];              // C_Component

public:
    CLONE(C_Object)



};

