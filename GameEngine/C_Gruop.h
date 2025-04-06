#pragma once
#include "C_Entity.h"
#include "C_Object.h"

class C_Gruop :
    public C_Entity
{
public:
    C_Gruop();

protected:
    C_Gruop(const C_Gruop& _Origin);

public:
    ~C_Gruop();

protected:
    E_GROUP_NUMBER                      M_Index;                    // E_GROUP_NUMBER; �з��� ���� �׷�

    // Object�� �����ϱ� ���� Member Variable
    vector<C_Object*>                   STL_M_ParentObject;         // vector<C_Object*>; �ֻ��� �θ� ���������ν�, Transform ��� ���� �������� ���� ����
    vector<C_Object*>                   STL_M_AllObject;            // vector<C_Object*>; ���������� �������� ����

public:
    CLONE(C_Gruop)

public:
    void MF_Prepare();
};