#pragma once
#include "C_Singleton.h"

// ���� ���� FL_IMAGER_PACKER �ڵ� ���
// https://github.com/Facta-Leopard/FL_IMAGE_PACKER
class C_ResourceManager :
    public C_Singleton<C_ResourceManager>
{
    SINGLE(C_ResourceManager)

protected:
    map<wstring, C_Stage*>              STL_M_Stage;            // map<wstring, C_Stage*>; ���������� ������ STL �����̳�

    map<wstring, C_Resource*>           STL_M_Resoure;          // map<wstring, C_Resource*>; ���ҽ��� ������ STL�����̳�
    
    map<wstring, FL_DS_ImageSet*>		STL_M_ImageSet;			// map<wstring, FL_DS_ImageSet*>; �����͸� ������ STL �����̳�
    wstring						    	wstring_BasicPath;		// wstring; �⺻���� ���丮 �ּ�; ���� ���丮 + (\Resource) ���丮 �ּ� ����

public:
    HRESULT MF_Initialize();

    // Resource ����
    void MF_Create_MeshResource();
    
    void MF_Create_TextureResource();

    void MF_Create_SpriteResource();

    void MF_Create_FlipBookResource();

    void MF_Create_SoundResource();

    void MF_Create_PrefabResource();

    void MF_Create_GraphicShaderResource();
    
    void MF_Create_ComputeShaderResource();

public:
    void MF_Attach_Resource(const )




};

