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
    const E_RESOURCE_TYPE   M_E_ResouceType;        // E_RESOURCE_TYPE
    
    // ���� ī��Ʈ�� ���� ������ ��������� �ڵ忡�� �����ϰ�, ����Ʈ �����͸� ����ϵ��� ����

    wstring                 M_PathKey;              // wstring ��ο� Ű�� ���ÿ� ����ϱ� ����

public:
    // Ŭ�� �Լ� �߻�ȭ
    virtual C_Resource* MF_Clone() = 0;

    // M_E_ResouceType Getter
    E_RESOURCE_TYPE MF_GetResourceType()
    {
        return M_E_ResouceType;
    }

    // M_PathKey Getter
    wstring MF_GetPathKey()
    {
        return M_PathKey;
    }

    // M_PathKey Setter
    wstring MF_SetPathKey(const wstring& _PathKey)
    {
        M_PathKey = _PathKey;
    }

    // ����, Save �� Load�� ���� ����
    // HRESULT MF_Save(const wstring& _PathKey);
    // HRESULT MF_Load(const wstring& _PathKey);
};