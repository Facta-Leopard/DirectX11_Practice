#pragma once
#include "C_Singleton.h"
#include "global.h"

class C_TimeManager :
    public C_Singleton<C_TimeManager>
{
    SINGLE(C_TimeManager);

protected:
    // 측정용
    // 측정은 정밀도가 높은 LARGE_INTEGER를 쓰는 것이였군
    LARGE_INTEGER       M_CurrentFrequency;              // LARGE_INTEGER; UNION; 64Bit Interger
    LARGE_INTEGER       M_TotalFrequencyBefore;          // LARGE_INTEGER; UNION; 64Bit Interger
    LARGE_INTEGER       M_TotalFrequencyCurrent;         // LARGE_INTEGER; UNION; 64Bit Interger


    // 계산용
    // 계산은 현재 64비트 기준으로는 최적화가 덜 되어서 오버헤드가 더 심할 수 있어서 기존 32비트를 쓰는 것이였나..
    float               M_EngineTime;               // float
    float               M_EngineDeltaTime;          // float

    float               M_DeltaTime;                // float

    float               M_OneSecondTime;            // float

    // FPS
    UINT                M_FPS;                      // UINT

public:
    HRESULT MF_Initialize();

    void MF_Update();


    inline float MF_Get_EngineTime()                 // Getter; M_EngineTime
    {
        return M_EngineTime;
    }

    inline float MF_Get_EngineDeltaTime()            // Getter; M_EngineDeltaTime
    {
        return M_EngineDeltaTime;
    }

    inline float MF_Get_TotalPlayTime()              // Getter; M_OneSecondTime
    {
        return M_OneSecondTime;
    }

    inline float MF_Get_DeltaTime()                  // Getter; M_DeltaTime
    {
        return M_DeltaTime;
    }

    inline float MF_Get_OneSecondTime()              // Getter; M_OneSecondTime
    {
        return M_OneSecondTime;
    }

    inline UINT MF_Get_FPS()                         // Getter; M_FPS
    {
        return M_FPS;
    }
};

