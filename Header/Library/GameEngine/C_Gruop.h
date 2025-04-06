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
    E_GROUP_NUMBER                      M_Index;                    // E_GROUP_NUMBER; 분류를 위한 그룹

    // Object를 관리하기 위한 Member Variable
    vector<C_Object*>                   STL_M_ParentObject;         // vector<C_Object*>; 최상위 부모만 관리함으로써, Transform 계산 등의 기준점을 갖기 위함
    vector<C_Object*>                   STL_M_AllObject;            // vector<C_Object*>; 성능이점을 갖기위한 구조

public:
    CLONE(C_Gruop)

public:
    void MF_Prepare();
};