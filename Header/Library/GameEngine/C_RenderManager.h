#pragma once
#include "C_Singleton.h"
#include "define.h"

class C_RenderManager :
    public C_Singleton< C_RenderManager>
{
    SINGLE(C_RenderManager)

protected:
    // ���� �߰� ���� ����

public:
    void MF_Initialize();

    void MF_Update();


    // ����, Object �����Լ� ���� 



    void MF_Render();

};

