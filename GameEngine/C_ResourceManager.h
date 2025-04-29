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
    inline wstring MF_Get_BasicPath()
    {
        return wstring_M_BasicPath;
    }

    inline wstring MF_Get_BasicFileName()
    {
        return wstring_M_BasicFileName;
    }

    inline wstring MF_Get_BasicResourceFileName()
    {
        return wstring_M_BasicResourceFileName;
    }

    inline wstring MF_Get_BasicImageFileName()
    {
        return wstring_M_BasicImageFileName;
    }

public:
    inline void MF_Set_BasicPath(const wstring& _wsting)
    {
        wstring_M_BasicPath = _wsting;
    }

    inline void MF_Set_BasicFileName(const wstring& _wsting)
    {
        wstring_M_BasicFileName = _wsting;
    }

    inline void MF_Set_BasicResourceFileName(const wstring& _wsting)
    {
        wstring_M_BasicResourceFileName = _wsting;
    }

    inline void MF_Set_BasicImageFileName(const wstring& _wsting)
    {
        wstring_M_BasicImageFileName = _wsting;
    }

public:
// ����� ���� �ڷ��� �߿��� �̹��� ã��
    FL_DS_ImageSet* MF_FindImageSetFromVectorData(const wstring& _wstringName);

    FL_DS_ImageSet* MF_FindImageSetFromVectorData(const string& _stringName);

public:
// ������ ���� ����� ��忡���� �ǵ��� ����
#ifdef _DEBUG
    HRESULT MF_Attach_Resource(const wstring& _wstringName);

    HRESULT MF_Attach_Resource(const string& _stringName);

    HRESULT MF_Attach_ImageToImageSet(const wstring& _wstringName);

    HRESULT MF_Attach_ImageToImageSet(const string& _stringName);
#endif // _DEBUG

public:
// ��ȯ�� �Լ�
//// ���� ���Ͽ��� ��ũ��ġ�̹����� ��ȯ
    HRESULT MF_Convert_FileToScratchImage(const wstring& _wstringName, ScratchImage& _ScratchImage);

    HRESULT MF_Convert_FileToScratchImage(const string& _stringName, ScratchImage& _ScratchImage);

//// ��ũ��ġ �̹����� �̹�����Ʈ�� ��ȯ
    HRESULT MF_Convert_ScratchImageToCPUImage(const ScratchImage& _ScratchImage, FL_DS_ImageSet& _ImageSet);

//// �̹�����Ʈ�� ��ũ��ġ �̹����� ��ȯ
    HRESULT MF_Convery_CPUImageToScratchImage(const FL_DS_CPU_Image& _Source_CPU_Image, ScratchImage& _Out_ScratchImage_Out);

public:
// �����ϴ� ���� ����� ��忡���� �ǵ��� ����
// ��, �������� ������ ������ �� �� �ֵ��� ��; ����, �������� �ۼ��� ���
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

