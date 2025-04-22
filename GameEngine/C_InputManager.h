#pragma once

#include "C_Singleton.h"

#include "global.h"

class C_InputManager :
    public C_Singleton< C_InputManager>
{
    SINGLE(C_InputManager);

private:
    vector<DS_KeyInfo>          STL_M_DS_KeyInfo;      // vector<DS_KeyInfo>
    DS_MouseInfo                M_DS_MouseInfo;        // DS_MouseInfo
    
public:
    HRESULT MF_Initialize();                                    // 초기화 함수

    void MF_Update();

public:
    inline DS_KeyInfo MF_Get_MouseInfo(E_KEY_TYPE _KeyType)     // Getter; STL_M_DS_KeyInfo
    {
        return STL_M_DS_KeyInfo[_KeyType];
    }

    inline DS_MouseInfo MF_Get_MouseInfo()                      // Getter; M_DS_MouseInfo
    {
        return M_DS_MouseInfo;
    }
};

