#pragma once
#include "C_Singleton.h"

// 내가 만든 FL_IMAGER_PACKER 코드 사용
// https://github.com/Facta-Leopard/FL_IMAGE_PACKER
class C_ResourceManager :
    public C_Singleton<C_ResourceManager>
{
    SINGLE(C_ResourceManager)

protected:
    map<wstring, C_Stage*>              STL_M_Stage;            // map<wstring, C_Stage*>; 스테이지를 저장할 STL 컨테이너

    map<wstring, C_Resource*>           STL_M_Resoure;          // map<wstring, C_Resource*>; 리소스를 저장할 STL컨테이너
    
    map<wstring, FL_DS_ImageSet*>		STL_M_ImageSet;			// map<wstring, FL_DS_ImageSet*>; 데이터를 저장할 STL 컨테이너
    wstring						    	wstring_BasicPath;		// wstring; 기본적인 디렉토리 주소; 실행 디렉토리 + (\Resource) 디렉토리 주소 설정

public:
    HRESULT MF_Initialize();

    // Resource 관련
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

