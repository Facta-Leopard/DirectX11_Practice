#pragma once
#include "C_Singleton.h"

class C_RenderManager :
    public C_Singleton< C_RenderManager>
{
    SINGLE(C_RenderManager)

private:
    // ���� �߰� ���� ����

public:
    HRESULT MF_Initialize();

    void MF_Update();


    // ����, Object �����Լ� ���� 



    void MF_Render();

};

