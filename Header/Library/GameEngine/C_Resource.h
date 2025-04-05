#pragma once

#include "solution.h"

#include "C_Entity.h"


class C_Resource :
    public C_Entity
{
protected:
    // Resource Type은 생성시 정의되어야 하므로, 이에 대한 부분 무조껀 정의하도록 함
    C_Resource(E_RESOURCE_TYPE _ResourceType);

    // C_Entity 클래스에서 virtual 선언해서 안 붙혀도 virtual 상관없음
    ~C_Resource();

protected:
    const E_RESOURCE_TYPE   M_E_ResouceType;            // E_RESOURCE_TYPE
    
    // 참조 카운트를 통한 스스로 삭제기능은 코드에서 제거하고, 스마트 포인터를 사용하도록 수정

    wstring                 M_PathKey;                  // wstring 경로와 키를 동시에 사용하기 위함

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

    // 향후, Save 및 Load는 별도 구성
    // HRESULT MF_Save(const wstring& _PathKey);
    // HRESULT MF_Load(const wstring& _PathKey);
};