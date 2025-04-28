#pragma once
#include "C_Singleton.h"

class C_Stage;

class C_Resource;

struct FL_DS_ImageSet;

// ���� ���� FL_IMAGER_PACKER �ڵ� ���
// https://github.com/Facta-Leopard/FL_IMAGE_PACKER
class C_ResourceManager :
    public C_Singleton<C_ResourceManager>
{
    SINGLE(C_ResourceManager)

protected:
    map<wstring, C_Stage*>              STL_M_Stage;                            // map<wstring, C_Stage*>; ���������� ������ STL �����̳�

    map<wstring, C_Resource*>           STL_M_Resoure;                          // map<wstring, C_Resource*>; ���ҽ��� ������ STL�����̳�
    
    map<wstring, FL_DS_ImageSet*>		STL_M_ImageSet;			                // map<wstring, FL_DS_ImageSet*>; �����͸� ������ STL �����̳�; ����, �߰� ����
    wstring						    	wstring_M_BasicPath;	            	// wstring; �⺻���� ���丮 �ּ�; ���� ���丮 + (\Resource) ���丮 �ּ� ����
    wstring								wstring_M_BasicFileName;	        	// wstring; �⺻���� ���ϸ�; �ʿ�� �����Ͽ� ��밡��
    wstring								wstring_M_BasicResourceFileName;		// wstring; �⺻���� ���ϸ�; �ʿ�� �����Ͽ� ��밡��
    wstring								wstring_M_BasicImageFileName;		    // wstring; �⺻���� ���ϸ�; �ʿ�� �����Ͽ� ��밡��

public:
    HRESULT MF_Initialize();

    // Resource ����
    HRESULT MF_Create_MeshResource();
    
    HRESULT MF_Create_TextureResource();

    HRESULT MF_Create_SpriteResource();

    HRESULT MF_Create_FlipBookResource();

    HRESULT MF_Create_SoundResource();

    HRESULT MF_Create_PrefabResource();

    HRESULT MF_Create_GraphicShaderResource();
    
    HRESULT MF_Create_ComputeShaderResource();

public:
// ������ ���� �ϴ� ���� ����� ��忡���� �ǵ��� ����
#ifdef _DEBUG
    HRESULT MF_Attach_Resource(const wstring& _wstringName, C_Resource* _Resource);

    HRESULT MF_Attach_Resource(const string& _stringName, C_Resource* _Resource);

    HRESULT MF_Attach_ImageToImageSet(const wstring& _wstringName, FL_DS_ImageSet* _ImageSet);

    HRESULT MF_Attach_ImageToImageSet(const string& _stringName, FL_DS_ImageSet* _ImageSet);

    HRESULT MF_Detach_Resource(const wstring& _wstringName);

    HRESULT MF_Detach_Resource(const string& _stringName);

    HRESULT MF_Detach_ImageToImageSet(const wstring& _wstringName);

    HRESULT MF_Detach_ImageToImageSet(const string& _stringName);
#endif // _DEBUG

public:


public:
// �����ϴ� ���� ����� ��忡���� �ǵ��� ����
#ifdef _DEBUG
    void MF_Save_All();

    HRESULT MF_Save_ResourceAllAsFile();

    HRESULT MF_Save_ImageAllAsFile();
#endif // _DEBUG

public:
    void MF_Load_All();

    HRESULT MF_Load_StageAllFromFile();

    HRESULT MF_Load_ResourceAllFromFile();

    HRESULT MF_Load_ImageAllFromFile();

};

