#pragma once
#include "C_Singleton.h"
#include "define.h"

class C_RenderManager :
    public C_Singleton< C_RenderManager>
{
    SINGLE(C_RenderManager)

protected:
    // 향후 추가 구현 예정

public:
    void MF_Initialize();

    void MF_Update();


    // 향후, Object 관련함수 생성 



    void MF_Render();

};

