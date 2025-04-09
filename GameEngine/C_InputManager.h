#pragma once

#include "C_Singleton.h"

#include "global.h"

class C_InputManager :
    public C_Singleton< C_InputManager>
{
    SINGLE(C_InputManager);

protected:
    vector<DS_KeyInfo>          STL_M_DS_KeyInfo;      // vector<DS_KeyInfo>
    DS_MouseInfo                M_DS_MouseInfo;        // DS_MouseInfo
    
public:
    void MF_Initialize();

    void MF_Update();


    inline DS_KeyInfo MF_Get_MouseInfo(E_KEY_TYPE _KeyType)    // Getter; STL_M_DS_KeyInfo
    {
        return STL_M_DS_KeyInfo[_KeyType];
    }

    inline DS_MouseInfo MF_Get_MouseInfo()                     // Getter; M_DS_MouseInfo
    {
        return M_DS_MouseInfo;
    }
};

