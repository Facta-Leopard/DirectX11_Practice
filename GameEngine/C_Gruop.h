#pragma once
#include "C_Entity.h"
#include "C_Object.h"

class C_Group :
    public C_Entity
{
public:
    C_Group();

    // Group 클래스 자체를 복사할 필요가 없을 것 같아서 제거

public:
    ~C_Group();

protected:
    E_GROUP_NUMBER                      M_Index;                    // E_GROUP_NUMBER; 분류를 위한 그룹

    // Object를 관리하기 위한 Member Variable
    vector<C_Object*>                   STL_M_AllObject;            // vector<C_Object*>; 성능이점을 갖기위한 구조
    vector<C_Object*>                   STL_M_ParentObject;         // vector<C_Object*>; 최상위 부모만 관리함으로써, Transform 계산 등의 기준점을 갖기 위함


public:
    void MF_Prepare();

    void MF_Step();

    // STL_M_AllObject 관련
    inline void MF_InsertObjectIntoAllObject(C_Object* _Object)
    {
        STL_M_AllObject.push_back(_Object);
    }

    inline vector<C_Object*> MF_GetAllObjectFromGroup()                     // Getter
    {
        return STL_M_AllObject;
    }

    void MF_EraseObjectFromAllObject(C_Object* _Object);                    // Just Unlist, Not Delete

    // STL_M_ParentObject 관련
    void MF_AddObjectToParentObject(C_Object* _Object);                     // 오브젝트를 부모 오브젝트에 넣기 

    inline vector<C_Object*> MF_GetParentObjectFromGroup()                  // Getter
    {
        return STL_M_ParentObject;
    }
};