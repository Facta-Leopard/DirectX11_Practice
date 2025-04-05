#pragma once
#include "C_Singleton.h"
#include "define.h"

class C_TimeManager :
    public C_Singleton<C_TimeManager>
{
    SINGLE(C_TimeManager);

protected:
    // ������
    // ������ ���е��� ���� LARGE_INTEGER�� ���� ���̿���
    LARGE_INTEGER       M_CurrentFrequency;              // LARGE_INTEGER; UNION; 64Bit Interger
    LARGE_INTEGER       M_TotalFrequencyBefore;          // LARGE_INTEGER; UNION; 64Bit Interger
    LARGE_INTEGER       M_TotalFrequencyCurrent;         // LARGE_INTEGER; UNION; 64Bit Interger


    // ����
    // ����� ���� 64��Ʈ �������δ� ����ȭ�� �� �Ǿ ������尡 �� ���� �� �־ ���� 32��Ʈ�� ���� ���̿���..
    float               M_EngineTime;               // float
    float               M_EngineDeltaTime;          // float

    float               M_DeltaTime;                // float

    float               M_OneSecondTime;            // float

    // FPS
    UINT                M_FPS;                      // UINT

public:
    void MF_Initialize();

    void MF_Update();


    inline float MF_GetEngineTime()                 // Getter; M_EngineTime
    {
        return M_EngineTime;
    }

    inline float MF_GetEngineDeltaTime()            // Getter; M_EngineDeltaTime
    {
        return M_EngineDeltaTime;
    }

    inline float MF_GetTotalPlayTime()              // Getter; M_OneSecondTime
    {
        return M_OneSecondTime;
    }

    inline float MF_GetDeltaTime()                  // Getter; M_DeltaTime
    {
        return M_DeltaTime;
    }

    inline float MF_GetOneSecondTime()              // Getter; M_OneSecondTime
    {
        return M_OneSecondTime;
    }

    inline UINT MF_GetFPS()                         // Getter; M_FPS
    {
        return M_FPS;
    }
};

