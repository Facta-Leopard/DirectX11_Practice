#pragma once
#include "solution.h"

class C_InputManager :
    public C_Singleton< C_InputManager>
{
    SINGLE(C_InputManager);

protected:
    vector<DS_KeyInfo>          STL_M_DS_KeyInfo;      // vector<DS_KeyInfo>
    DS_MouseInfo                M_DS_MouseInfo;        // DS_MouseInfo
    
public:
    // √ ±‚»≠
    void MF_Initialize();

    void MF_Update();

    // KeyInfo Getter
    DS_KeyInfo MF_GetMouseInfo(E_KEY_TYPE _KeyType)
    {
        return STL_M_DS_KeyInfo[_KeyType];
    }

    // MouseInfo Getter
    DS_MouseInfo MF_GetMouseInfo()
    {
        return M_DS_MouseInfo;
    }
};

