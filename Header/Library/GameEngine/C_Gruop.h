#pragma once
#include "C_Entity.h"

#include "C_Object.h"

#include "global.h"

class C_Group :
    public C_Entity
{
public:
    C_Group();

    // Group Ŭ���� ��ü�� ������ �ʿ䰡 ���� �� ���Ƽ� ����

public:
    ~C_Group();

protected:
    E_GROUP_TYPE                        M_Index;                    // E_GROUP_NUMBER; �з��� ���� �׷�

    // Object�� �����ϱ� ���� Member Variable
    vector<C_Object*>                   STL_M_AllObject;            // vector<C_Object*>; ���������� �������� ����, MF_Render()�� ������ ����ϱ� ����
    vector<C_Object*>                   STL_M_ParentObject;         // vector<C_Object*>; �ֻ��� �θ� ���������ν�, Transform ��� ���� �������� ���� ����


public:
    void MF_Prepare();                                              // Group �� ��� �θ� ������Ʈ �ʱ�ȭ

    void MF_Tick();                                                 // Group �� ��� �θ� ������Ʈ Tick() ����

    void MF_TickAfter();                                            // Group �� ��� �θ� ������Ʈ Tick��������() ����


    // STL_M_AllObject ����
    inline void MF_InsertObjectIntoAllObject(C_Object* _Object)
    {
        STL_M_AllObject.push_back(_Object);
    }

    inline vector<C_Object*> MF_Get_AllObjectFromGroup()                     // Getter
    {
        return STL_M_AllObject;
    }

    // STL_M_ParentObject ����
    inline vector<C_Object*> MF_Get_ParentObjectFromGroup()                   // Getter
    {
        return STL_M_ParentObject;
    }

    // STL_M_AllObject ����
    void MF_Detach_ObjectFromAllObject(C_Object* _Object);                    // Detach; ���� ����! ���� �迭 �������� ���� ����!

    // STL_M_ParentObject ����
    void MF_Attach_ObjectToParentObject(C_Object* _Object);                   // Attach; 
};