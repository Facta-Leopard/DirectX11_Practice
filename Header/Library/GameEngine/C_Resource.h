#pragma once

#include "solution.h"

#include "C_Entity.h"


class C_Resource :
    public C_Entity
{
protected:
    // Resource Type�� ������ ���ǵǾ�� �ϹǷ�, �̿� ���� �κ� ������ �����ϵ��� ��
    C_Resource(E_RESOURCE_TYPE _ResourceType);

    // C_Entity Ŭ�������� virtual �����ؼ� �� ������ virtual �������
    ~C_Resource();

protected:
    const E_RESOURCE_TYPE   M_E_ResouceType;            // E_RESOURCE_TYPE
    
    // ���� ī��Ʈ�� ���� ������ ��������� �ڵ忡�� �����ϰ�, ����Ʈ �����͸� ����ϵ��� ����

    wstring                 M_PathKey;                  // wstring ��ο� Ű�� ���ÿ� ����ϱ� ����

public:
    virtual C_Resource* MF_Clone() = 0;                 // Clone Function; Virtual


    inline E_RESOURCE_TYPE MF_GetResourceType()                // Getter; M_E_ResouceType
    {
        return M_E_ResouceType;
    }

    inline wstring MF_GetPathKey()                             // Getter; M_PathKey
    {
        return M_PathKey;
    }

    inline wstring MF_SetPathKey(const wstring& _PathKey)      // Setter
    {
        M_PathKey = _PathKey;
    }

    // ����, Save �� Load�� ���� ����
    // HRESULT MF_Save(const wstring& _PathKey);
    // HRESULT MF_Load(const wstring& _PathKey);
};