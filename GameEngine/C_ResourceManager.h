#pragma once
#include "C_Singleton.h"

class C_Stage;

class C_Resource;

struct FL_DS_ImageSet;

// 내가 만든 FL_IMAGER_PACKER 코드 사용
// https://github.com/Facta-Leopard/FL_IMAGE_PACKER
class C_ResourceManager :
    public C_Singleton<C_ResourceManager>
{
    SINGLE(C_ResourceManager)

protected:
    map<wstring, C_Stage*>              STL_M_Stage;                            // map<wstring, C_Stage*>; 스테이지를 저장할 STL 컨테이너

    map<wstring, C_Resource*>           STL_M_Resoure;                          // map<wstring, C_Resource*>; 리소스를 저장할 STL컨테이너
    
    map<wstring, FL_DS_ImageSet*>		STL_M_ImageSet;			                // map<wstring, FL_DS_ImageSet*>; 데이터를 저장할 STL 컨테이너; 향후, 추가 개선
    wstring						    	wstring_M_BasicPath;	            	// wstring; 기본적인 디렉토리 주소; 실행 디렉토리 + (\Resource) 디렉토리 주소 설정
    wstring								wstring_M_BasicFileName;	        	// wstring; 기본적인 파일명; 필요시 수정하여 사용가능
    wstring								wstring_M_BasicResourceFileName;		// wstring; 기본적인 파일명; 필요시 수정하여 사용가능
    wstring								wstring_M_BasicImageFileName;		    // wstring; 기본적인 파일명; 필요시 수정하여 사용가능

public:
    HRESULT MF_Initialize();

    // Resource 관련
    HRESULT MF_Create_MeshResource();
    
    HRESULT MF_Create_TextureResource();

    HRESULT MF_Create_SpriteResource();

    HRESULT MF_Create_FlipBookResource();

    HRESULT MF_Create_SoundResource();

    HRESULT MF_Create_PrefabResource();

    HRESULT MF_Create_GraphicShaderResource();
    
    HRESULT MF_Create_ComputeShaderResource();

public:
// 붙히고 떼고 하는 것은 디버그 모드에서만 되도록 조정
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
// 저장하는 것은 디버그 모드에서만 되도록 조정
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

