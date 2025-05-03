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
    map<wstring, C_Stage*>                        STL_M_Stage;                          // map<wstring, C_Stage*>; 스테이지를 저장할 STL 컨테이너

    map<wstring, shared_ptr<C_Resource>>          STL_SP_M_Resource;                    // map<wstring, C_Resource*>; 리소스를 저장할 STL컨테이너
    
    map<wstring, FL_DS_ImageSet*>		          STL_M_ImageSet;			            // map<wstring, FL_DS_ImageSet*>; 데이터를 저장할 STL 컨테이너; 향후, 추가 개선
    wstring						    	          wstring_M_BasicPath;	            	// wstring; 기본적인 디렉토리 주소; 실행 디렉토리 + (\Resource) 디렉토리 주소 설정
    wstring								          wstring_M_BasicFileName;	        	// wstring; 기본적인 파일명; 필요시 수정하여 사용가능
    wstring								          wstring_M_BasicResourceFileName;		// wstring; 기본적인 파일명; 필요시 수정하여 사용가능
    wstring						                  wstring_M_BasicImageFileName;		    // wstring; 기본적인 파일명; 필요시 수정하여 사용가능

public:
    HRESULT MF_Initialize();

    // Resource 관련
    //// 메쉬 생성관련
    HRESULT MF_Create_MeshResource(UINT _SDK_Slice = 30);

    ////// 점 메쉬 생성
    HRESULT MF_Create_PointMeshResource();

    ////// 네모 메쉬 생성(디버그 포함)
    HRESULT MF_Create_RectangleMeshResource();

    ////// 원 메쉬 생성(디버그 포함)
    HRESULT MF_Create_CircleMeshResource(UINT _SDK_Slice);

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
    // shared_ptr 스마트 포인터를 사용한 C_Resource로 모든 리소스 관리
    HRESULT MF_Attach_Resource(const wstring& _wstringName, shared_ptr<C_Resource> _SP_Resource);

    // shared_ptr 스마트 포인터를 사용한 C_Resource로 모든 리소스 관리(string 용)
    HRESULT MF_Attach_Resource(const string& _stringName, shared_ptr<C_Resource> _SP_Resource);

    HRESULT MF_Attach_ImageToImageSet(const wstring& _wstringName);

    HRESULT MF_Attach_ImageToImageSet(const string& _stringName);

public:
    // 리소스가 저장된 STL 컨테이너에서 리소스 찾기
    shared_ptr<C_Resource> MF_FindResourceFromSTL(const wstring& _wstringName);

    shared_ptr<C_Resource> MF_FindResourceFromSTL(const string& _stringName);

    // 이미지가 저장된 STL 컨테이너에서 이미지 찾기
    FL_DS_ImageSet* MF_FindImageSetFromSTL(const wstring& _wstringName);

    FL_DS_ImageSet* MF_FindImageSetFromSTL(const string& _stringName);

public:
    // 변환용 함수
    //// 실제 파일에서 스크래치이미지로 변환
    HRESULT MF_Convert_FileToScratchImage(const wstring& _wstringName, ScratchImage& _ScratchImage);

    //// 실제 파일에서 스크래치이미지로 변환(string 용)
    HRESULT MF_Convert_FileToScratchImage(const string& _stringName, ScratchImage& _ScratchImage);

    //// 스크래치 이미지를 이미지세트로 변환
    HRESULT MF_Convert_ScratchImageToCPUImage(const ScratchImage& _ScratchImage, FL_DS_ImageSet& _ImageSet);

    //// 이미지세트를 스크래치 이미지로 변환
    HRESULT MF_Convert_CPUImageToScratchImage(const FL_DS_CPU_Image& _Source_CPU_Image, ScratchImage& _Out_ScratchImage_Out);

public:
    // 저장하는 것은 디버그 모드에서만 되도록 조정
    // 단, 스테이지 저장은 별개로 할 수 있도록 함; 향후, 스테이지 작성시 사용
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

