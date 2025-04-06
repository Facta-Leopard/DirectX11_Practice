#pragma once
#include "C_Entity.h"
#include "C_Object.h"

class C_Group :
    public C_Entity
{
public:
    C_Group();

    // Group Ŭ���� ��ü�� ������ �ʿ䰡 ���� �� ���Ƽ� ����

public:
    ~C_Group();

protected:
    E_GROUP_NUMBER                      M_Index;                    // E_GROUP_NUMBER; �з��� ���� �׷�

    // Object�� �����ϱ� ���� Member Variable
    vector<C_Object*>                   STL_M_AllObject;            // vector<C_Object*>; ���������� �������� ����
    vector<C_Object*>                   STL_M_ParentObject;         // vector<C_Object*>; �ֻ��� �θ� ���������ν�, Transform ��� ���� �������� ���� ����


public:
    void MF_Prepare();

    void MF_Step();

    // STL_M_AllObject ����
    inline void MF_InsertObjectIntoAllObject(C_Object* _Object)
    {
        STL_M_AllObject.push_back(_Object);
    }

    inline vector<C_Object*> MF_GetAllObjectFromGroup()                     // Getter
    {
        return STL_M_AllObject;
    }

    void MF_EraseObjectFromAllObject(C_Object* _Object);                    // Just Unlist, Not Delete

    // STL_M_ParentObject ����
    void MF_AddObjectToParentObject(C_Object* _Object);                     // ������Ʈ�� �θ� ������Ʈ�� �ֱ� 

    inline vector<C_Object*> MF_GetParentObjectFromGroup()                  // Getter
    {
        return STL_M_ParentObject;
    }
};