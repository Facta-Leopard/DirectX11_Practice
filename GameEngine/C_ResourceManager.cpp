#include "pch.h"
#include "C_ResourceManager.h"

#include "DirectxTex/DirectXTex.h"
#include "DirectxTex/DirectXTex.inl"

#include "C_Mesh.h"

C_ResourceManager::C_ResourceManager()
	: STL_M_ImageSet{}
{
	// .rsc 파일이 저장되어 있는 기본 위치 설정
	wchar_t wchar_T_Path_s[255] = {};
	wstring wstring_BasicPath = {};
	GetCurrentDirectory(255, wchar_T_Path_s);
	wcscat_s(wchar_T_Path_s, 255, L"\\Resource\\");
	wstring_M_BasicPath = wchar_T_Path_s;

	CreateDirectoryW(wstring_M_BasicPath.c_str(), nullptr);

	// 코드개선: 기본적으로 지정되는 파일명(확장자 포함)
	wstring_M_BasicImageFileName = L"CompressedImage.rsc";

	// 파일이 없는 경우, CompressedImage.rsc 파일을 생성
	FILE* SDK_T_File = nullptr;
	wstring wstring_T_Path = wstring_M_BasicPath + wstring_M_BasicImageFileName;

	_wfopen_s(&SDK_T_File, wstring_T_Path.c_str(), L"rb");

	// 향후, 조건문 부분을 _wfopen_s 반환값으로 하면 오버헤드가 더 적을 것 같긴한데, 10시간째 씨름중이라 나중에 다시 생각해보자
	if (nullptr == SDK_T_File)
	{
		_wfopen_s(&SDK_T_File, wstring_T_Path.c_str(), L"wb");
		size_t T_Zero = 0;
		fwrite(&T_Zero, sizeof(size_t), 1, SDK_T_File);
		fclose(SDK_T_File);
		POPUP(L"The .rsc File Does Not Exist", (L"A temporary file named `" + wstring_M_BasicImageFileName+ L"` has been created at `" + wstring_M_BasicPath).c_str())
	}

	// 기존에 저장된 내용 로드
	MF_Load_All();
}

C_ResourceManager::~C_ResourceManager()
{
	// STL 컨테이너 메모리 해제
	DELETEALL_STL_MAP(STL_M_Stage)

	// MAP 구조인 STL 내부 값이 shared_ptr 이므로, delete를 사용한 매크로가 아닌 .clear()를 사용
	STL_M_Resoure.clear();
	DELETEALL_STL_MAP(STL_M_ImageSet)
}

// Basic
// 초기화 함수
HRESULT C_ResourceManager::MF_Initialize()
{
	if (FAILED(MF_Create_MeshResource()))
	{
		POPUP(L"MF_Create_MeshResource() Failed", L"in C_ResourceManager::MF_Initialize(), MF_Create_MeshResource() Failed")
		return E_FAIL;
	}

	if (FAILED(MF_Create_TextureResource()))
	{
		POPUP(L"MF_Create_TextureResource() Failed", L"in C_ResourceManager::MF_Initialize(), MF_Create_TextureResource() Failed")
		return E_FAIL;
	}

	if (FAILED(MF_Create_SpriteResource()))
	{
		POPUP(L"MF_Create_SpriteResource() Failed", L"in C_ResourceManager::MF_Initialize(), MF_Create_SpriteResource() Failed")
		return E_FAIL;
	}

	if (FAILED(MF_Create_FlipBookResource()))
	{
		POPUP(L"MF_Create_FlipBookResource() Failed", L"in C_ResourceManager::MF_Initialize(), MF_Create_FlipBookResource() Failed")
		return E_FAIL;
	}

	if (FAILED(MF_Create_SoundResource()))
	{
		POPUP(L"MF_Create_SoundResource() Failed", L"in C_ResourceManager::MF_Initialize(), MF_Create_SoundResource() Failed")
		return E_FAIL;
	}

	if (FAILED(MF_Create_PrefabResource()))
	{
		POPUP(L"MF_Create_PrefabResource() Failed", L"in C_ResourceManager::MF_Initialize(), MF_Create_PrefabResource() Failed")
		return E_FAIL;
	}

	if (FAILED(MF_Create_GraphicShaderResource()))
	{
		POPUP(L"MF_Create_GraphicShaderResource() Failed", L"in C_ResourceManager::MF_Initialize(), MF_Create_GraphicShaderResource() Failed")
		return E_FAIL;
	}

	if (FAILED(MF_Create_ComputeShaderResource()))
	{
		POPUP(L"MF_Create_ComputeShaderResource() Failed", L"in C_ResourceManager::MF_Initialize(), MF_Create_ComputeShaderResource() Failed")
		return E_FAIL;
	}

	return S_OK;
}

//// 메쉬 생성 함수
HRESULT C_ResourceManager::MF_Create_MeshResource(UINT _SDK_Slice)
{
	MF_Create_PointMeshResource();

	MF_Create_RectangleMeshResource();

	MF_Create_CircleMeshResource(_SDK_Slice);
}

////// 점 메쉬 생성 함수
HRESULT C_ResourceManager::MF_Create_PointMeshResource()
{
	// PointMesh; 점메쉬
	shared_ptr<C_Mesh> SP_T_PointMesh = make_shared<C_Mesh>();
	SP_T_PointMesh->MF_Set_Name(L"PointMesh");

	DS_Vertex DS_T_PointVertex;
	DS_T_PointVertex.SDK_XM_FLOAT3_Position = { 0.f, 0.f, 0.f };
	DS_T_PointVertex.SDK_XM_FLOAT2_PositionUV = { 0.f, 0.f };
	DS_T_PointVertex.SDK_XM_FLOAT4_Color = { 1.f, 1.f, 1.f, 1.f };

	UINT SDK_T_Index = 0;

	HRESULT SDK_HRESULT_PointMeshBuffer = SP_T_PointMesh->MF_Create_Buffer(&DS_T_PointVertex, 1, &SDK_T_Index, 1);
	HRESULT SDK_HRESULT_PointMeshAttach = MF_Attach_Resource(SP_T_PointMesh->MF_Get_Name(), SP_T_PointMesh);
	if (FAILED(SDK_HRESULT_PointMeshBuffer) || FAILED(SDK_HRESULT_PointMeshAttach))
	{
		POPUP_DEBUG(L"PointMesh Failed ", L"in C_ResourceManager::MF_Create_PointMeshResource(), PointMesh Failed")
		return E_FAIL;
	}

	return S_OK;
}

////// 네모 메쉬 생성 함수
HRESULT C_ResourceManager::MF_Create_RectangleMeshResource()
{
	// RectangleMesh; 네모메쉬
	shared_ptr<C_Mesh> SP_T_RectangleMesh = make_shared<C_Mesh>();
	SP_T_RectangleMesh->MF_Set_Name(L"RectangleMesh");

	//// 점 구조체 배열 선언
	////// 0번째 점 값 초기화
	DS_Vertex DS_T_RectangleVertex_s[4] = {};
	DS_T_RectangleVertex_s[0].SDK_XM_FLOAT3_Position = { -0.5f, 0.5f, 0.f };
	DS_T_RectangleVertex_s[0].SDK_XM_FLOAT2_PositionUV = { 0.f, 0.f };
	DS_T_RectangleVertex_s[0].SDK_XM_FLOAT4_Color = { 1.f, 0.f, 0.f, 1.f };

	////// 1번째 점 값 초기화
	DS_T_RectangleVertex_s[1].SDK_XM_FLOAT3_Position = { 0.5f, 0.5f, 0.f };
	DS_T_RectangleVertex_s[1].SDK_XM_FLOAT2_PositionUV = { 1.f, 0.f };
	DS_T_RectangleVertex_s[1].SDK_XM_FLOAT4_Color = { 0.f, 1.f, 0.f, 1.f };

	////// 2번째 점 값 초기화
	DS_T_RectangleVertex_s[2].SDK_XM_FLOAT3_Position = { 0.5f, -0.5f, 0.f };
	DS_T_RectangleVertex_s[2].SDK_XM_FLOAT2_PositionUV = { 1.f, 1.f };
	DS_T_RectangleVertex_s[2].SDK_XM_FLOAT4_Color = { 0.f, 0.f, 1.f, 1.f };

	////// 3번째 점 값 초기화
	DS_T_RectangleVertex_s[3].SDK_XM_FLOAT3_Position = { -0.5f, -0.5f, 0.f };
	DS_T_RectangleVertex_s[3].SDK_XM_FLOAT2_PositionUV = { 0.f, 1.f };
	DS_T_RectangleVertex_s[3].SDK_XM_FLOAT4_Color = { 1.f, 0.f, 1.f, 1.f };

	//// Index: Topology 순서
	//// 유의! 삼각형 토폴로지 2개를 붙히는 방식이므로, 아래와 같이 설정함
	UINT SDK_T_RectangleTopologyIndex[6] = { 0, 1, 2, 0, 2, 3 };

	//// 유의! 점 구조체는 아래에서 디버그용으로 재활용하므로, 그래서 인덱스는 6개임(삼각형 0-1-2, 삼각형 0-2-3)!
	HRESULT SDK_HRESULT_RectangleMeshBuffer = SP_T_RectangleMesh->MF_Create_Buffer(DS_T_RectangleVertex_s, 4, SDK_T_RectangleTopologyIndex, 6);
	HRESULT SDK_HRESULT_RectangleMeshAttach = MF_Attach_Resource(SP_T_RectangleMesh->MF_Get_Name(), SP_T_RectangleMesh);

	if (FAILED(SDK_HRESULT_RectangleMeshBuffer) || FAILED(SDK_HRESULT_RectangleMeshAttach))
	{
		POPUP_DEBUG(L"RectangleMesh Failed ", L"in C_ResourceManager::MF_Create_RectangleMeshResource(), RectangleMesh Failed")
		return E_FAIL;
	}

	// RectangleMesh_Debug; 디버깅용 네모메쉬
	shared_ptr<C_Mesh> SP_T_RectangleMesh_Debug = make_shared<C_Mesh>();
	SP_T_RectangleMesh_Debug->MF_Set_Name(L"RectangleMesh_Debug");

	//// Index: Topology 순서
	////// 유의! 삼각형 토폴로지 2개가 아닌 사각형 토폴로지를 붙히는 방식이므로, 아래와 같이 설정함
	UINT SDK_T_RectangleTopologyIndex_Debug[5] = { 0, 1, 2, 3, 0 };

	//// 유의! 점 구조체는 위에서 만든 점 구조체를 재활용하므로, 그래서 인덱스는 5개임(사각형 0-1-2-3-0)!
	HRESULT SDK_HRESULT_RectangleMeshBuffer_Debug = SP_T_RectangleMesh_Debug->MF_Create_Buffer(DS_T_RectangleVertex_s, 4, SDK_T_RectangleTopologyIndex_Debug, 5);
	HRESULT SDK_HRESULT_RectangleMeshAttach_Debug = MF_Attach_Resource(SP_T_RectangleMesh_Debug->MF_Get_Name(), SP_T_RectangleMesh_Debug);

	if (FAILED(SDK_HRESULT_RectangleMeshBuffer_Debug) || FAILED(SDK_HRESULT_RectangleMeshAttach_Debug))
	{
		POPUP_DEBUG(L"RectangleMesh_Debug Failed ", L"in C_ResourceManager::MF_Create_RectangleMeshResource(), RectangleMesh_Debug Failed")
		return E_FAIL;
	}

	return S_OK;
}

////// 원 메쉬 생성 함수
HRESULT C_ResourceManager::MF_Create_CircleMeshResource(UINT _SDK_Slice)
{
	// CircleMesh; 원 메쉬
	shared_ptr<C_Mesh> SP_T_CircleMesh = make_shared<C_Mesh>();
	SP_T_CircleMesh->MF_Set_Name(L"CircleMesh");

	//// 원을 표시할 원 메쉬 STL 컨테이너 생성
	vector<DS_Vertex> STL_DS_T_CircleVertex;

	////// 원 중심 별도 생성
	DS_Vertex DS_T_CircleCenter;
	DS_T_CircleCenter.SDK_XM_FLOAT3_Position = { 0.f, 0.f, 0.f };
	DS_T_CircleCenter.SDK_XM_FLOAT2_PositionUV = { 0.5f, 0.5f };
	DS_T_CircleCenter.SDK_XM_FLOAT4_Color = { 1.f, 1.f, 1.f, 1.f };

	////// 원 중심을 원 메쉬 STL 컨테이너에 삽입
	STL_DS_T_CircleVertex.push_back(DS_T_CircleCenter);

	float T_Radius = 0.5f;
	float T_Angle = 0.f;

	////// 원 외곽을 구성할 정점 계산 및 삽입
	////// 디버그용에도 똑같이 사용
	for (UINT i = 0; i < _SDK_Slice + 1; ++i)
	{
		DS_T_CircleCenter.SDK_XM_FLOAT3_Position = { T_Radius * cosf(T_Angle), T_Radius * sinf(T_Angle), 0.f };
		DS_T_CircleCenter.SDK_XM_FLOAT2_PositionUV = { DS_T_CircleCenter.SDK_XM_FLOAT3_Position.x + 0.5f, 1.f - (DS_T_CircleCenter.SDK_XM_FLOAT3_Position.y + 0.5f) };
		STL_DS_T_CircleVertex.push_back(DS_T_CircleCenter);

		// 나눌 때, float으로 바꾸지 않으면 정수형 연산으로 바뀌어서 0이되는 불상사가 발생가능
		// 피연산자 중 하나만 실수여도 가능하지만, 실수방지를 위해 전부 강제로 캐스팅해서 맞춰주는 것이 좋다,
		T_Angle += XM_2PI / (float)_SDK_Slice;
	}

	//// 원을 표시하는데 쓸 인덱스
	vector<UINT> STL_SDK_T_CircleIndex;

	////// 원 인덱스 계산 및 삽입
	////// 삼각형 토폴로지를 연속으로 놓는 형식 사용
	////// 디버그용에도 똑같이 사용
	for (UINT i = 0; i < _SDK_Slice; ++i)
	{
		STL_SDK_T_CircleIndex.push_back(0);
		STL_SDK_T_CircleIndex.push_back(i + 2);
		STL_SDK_T_CircleIndex.push_back(i + 1);
	}

	HRESULT SDK_HRESULT_T_CircleMeshBuffer = SP_T_CircleMesh->MF_Create_Buffer(STL_DS_T_CircleVertex.data(), (UINT)STL_DS_T_CircleVertex.size(), STL_SDK_T_CircleIndex.data(), (UINT)STL_SDK_T_CircleIndex.size());
	HRESULT SDK_HRESULT_T_CircleMeshAttach = MF_Attach_Resource(SP_T_CircleMesh->MF_Get_Name(), SP_T_CircleMesh);

	if (FAILED(SDK_HRESULT_T_CircleMeshBuffer) || FAILED(SDK_HRESULT_T_CircleMeshAttach))
	{
		POPUP_DEBUG(L"CircleMesh Failed ", L"in C_ResourceManager::MF_Create_CircleMeshResource(), CircleMesh Failed")
		return E_FAIL;
	}

	// CircleMesh_Debug; 디버그 원 메쉬
	shared_ptr<C_Mesh> SP_T_CircleMesh_Debug = make_shared<C_Mesh>();
	SP_T_CircleMesh->MF_Set_Name(L"CircleMesh_Debug");

	HRESULT SDK_HRESULT_T_CircleMeshBuffer_Debug = SP_T_CircleMesh_Debug->MF_Create_Buffer(STL_DS_T_CircleVertex.data(), (UINT)STL_DS_T_CircleVertex.size(), STL_SDK_T_CircleIndex.data(), (UINT)STL_SDK_T_CircleIndex.size());
	HRESULT SDK_HRESULT_T_CircleMeshAttach_Debug = MF_Attach_Resource(SP_T_CircleMesh_Debug->MF_Get_Name(), SP_T_CircleMesh_Debug);

	if (FAILED(SDK_HRESULT_T_CircleMeshBuffer_Debug) || FAILED(SDK_HRESULT_T_CircleMeshAttach_Debug))
	{
		POPUP_DEBUG(L"CircleMesh_Debug Failed ", L"in C_ResourceManager::MF_Create_CircleMeshResource(), CircleMesh_Debug Failed")
		return E_FAIL;
	}

	STL_DS_T_CircleVertex.clear();
	STL_SDK_T_CircleIndex.clear();

	return S_OK;
}

HRESULT C_ResourceManager::MF_Create_TextureResource()
{
	return E_NOTIMPL;
}

HRESULT C_ResourceManager::MF_Create_SpriteResource()
{
	return E_NOTIMPL;
}

HRESULT C_ResourceManager::MF_Create_FlipBookResource()
{
	return E_NOTIMPL;
}

HRESULT C_ResourceManager::MF_Create_SoundResource()
{
	return E_NOTIMPL;
}

HRESULT C_ResourceManager::MF_Create_PrefabResource()
{
	return E_NOTIMPL;
}

HRESULT C_ResourceManager::MF_Create_GraphicShaderResource()
{
	return E_NOTIMPL;
}

HRESULT C_ResourceManager::MF_Create_ComputeShaderResource()
{
	return E_NOTIMPL;
}

// 찾기 함수
// 저장된 벡터 자료형 중에서 이미지 찾기
FL_DS_ImageSet* C_ResourceManager::MF_FindImageSetFromVectorData(const wstring& _wstringName)
{
	map<wstring, FL_DS_ImageSet*>::iterator T_Iterator = STL_M_ImageSet.find(_wstringName);

	if (STL_M_ImageSet.end() != T_Iterator)
	{
		return (*T_Iterator).second;
	}
	else
	{
		return nullptr;
	}
}

FL_DS_ImageSet* C_ResourceManager::MF_FindImageSetFromVectorData(const string& _stringName)
{
	const wstring wstring_T_Name = GF_ConvertStringToWString_WinAPI(_stringName);

	// 래핑
	return MF_FindImageSetFromVectorData(wstring_T_Name);
}

// Attach & Detach
HRESULT C_ResourceManager::MF_Attach_Resource(const wstring& _wstringName, shared_ptr<C_Resource> _SP_Resource)
{
	return E_NOTIMPL;
}

HRESULT C_ResourceManager::MF_Attach_Resource(const string& _stringName, shared_ptr<C_Resource> _SP_Resource)
{
	// UTF-8 -> UNICODE로 변환
	const wstring _wstringName = GF_ConvertStringToWString_WinAPI(_stringName);

	return MF_Attach_Resource(_wstringName, _SP_Resource);
}

HRESULT C_ResourceManager::MF_Attach_ImageToImageSet(const wstring& _wstringName)
{
	// 먼저, 해당 내용이 있는지 확인
	if (nullptr != MF_FindImageSetFromVectorData(_wstringName))
	{
		// 이미 존재하면 메시지 박스 띄워서 사용자에게 확인
		int T_MessageResult = MessageBoxW(
			nullptr,
			(_wstringName + L" Is Used").c_str(),
			(L"Do You Want to OverWrite" + _wstringName + L"?").c_str(),
			MB_YESNO | MB_ICONQUESTION);

		if (T_MessageResult != IDYES)
		{
			return E_FAIL;
		}
	}
	
	// 스크래치이미지 구조체 임시생성
	ScratchImage T_ScretchImage = {};

	// 이미지파일을 스크래치 이미지로 변환
	if (FAILED(MF_Convert_FileToScratchImage(_wstringName, T_ScretchImage)))
	{
		POPUP(L"MF_Convert_FileToScratchImage() Failed", L"in C_ResourceManager::MF_Attach_ImageToImageSet(), MF_Convert_FileToScratchImage() Failed")
		return E_FAIL;
	}

	// 임시 메타데이터
	FL_DS_ImageSet T_ImageSet = {};
	// 스크래치 이미지를 이미지세트로 변환
	if (FAILED(MF_Convert_ScratchImageToCPUImage(T_ScretchImage, T_ImageSet)))
	{
		POPUP(L"MF_Convert_ScratchImageToCPUImage() Failed", L"in C_ResourceManager::MF_Attach_ImageToImageSet(), MF_Convert_ScratchImageToCPUImage() Failed")
		return E_FAIL;
	}
	FL_DS_ImageSet* P_T_ImageSet = &T_ImageSet;

	map<wstring, FL_DS_ImageSet*>::iterator T_Iterator = STL_M_ImageSet.find(_wstringName);
	if (T_Iterator != STL_M_ImageSet.end())
	{
		// 이미 존재하면 메시지 박스 띄워서 사용자에게 확인
		int T_MessageResult = MessageBoxW(
			nullptr,
			(_wstringName + L" Is Used").c_str(),
			(L"Do You Want to OverWrite" + _wstringName + L"?").c_str(),
			MB_YESNO | MB_ICONQUESTION
		);

		if (T_MessageResult == IDYES)
		{
			delete T_Iterator->second;
			STL_M_ImageSet[_wstringName] = P_T_ImageSet;
		}
		else
		{
			return E_FAIL;
		}
	}
	else
	{
		STL_M_ImageSet.insert(make_pair(_wstringName, P_T_ImageSet));
	}
	return S_OK;
}

HRESULT C_ResourceManager::MF_Attach_ImageToImageSet(const string& _stringName)
{
	// UTF-8 -> UNICODE로 변환
	const wstring _wstringName = GF_ConvertStringToWString_WinAPI(_stringName);

	return MF_Attach_ImageToImageSet(_wstringName);
}

// 변환용 함수
//// 실제 파일에서 스크래치이미지로 변환
HRESULT C_ResourceManager::MF_Convert_FileToScratchImage(const wstring& _wstringName, ScratchImage& _ScratchImage)
{
	// 저장할 임시용 구조체 초기화
	FL_DS_ImageSet T_ImageSet = {};

	// 임시용 구조체에 이미지리소스 관련 메타데이터; 유의! Scratch용 메타데이터와 헷갈리지 말 것!

	// 이미지를 긇어올 경로 관련 wchar 문자영 초기화
	wchar_t wchar_T_Path_s[255] = {};

	wstring wstring_T_Path = {};

	// 주소 및 파일명 불러오기
	wstring_T_Path = wstring_M_BasicPath + _wstringName;

	// 향후, WIC말고 다른 포맷을 추가할 경우 이 부분 개선고려
	wchar_t wchar_T_Extension[16] = {};
	_wsplitpath_s(wstring_T_Path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, wchar_T_Extension, 16);
	wstring wstring_T_Extension = wchar_T_Extension;

	// 확장자에 따라, 이미지 타입 부분을 잘못 입력했을 경우가 수정되도록 기능 개선
	if ((wstring_T_Extension == L".png") || (wstring_T_Extension == L".PNG"))
	{
		T_ImageSet.M_Desc.E_ImageType = _IMAGETYPE_PNG;
	}
	else if ((wstring_T_Extension == L".jpg") || (wstring_T_Extension == L".JPG"))
	{
		T_ImageSet.M_Desc.E_ImageType = _IMAGETYPE_JPG;
	}
	else if ((wstring_T_Extension == L".jpeg") || (wstring_T_Extension == L".JPEG"))
	{
		T_ImageSet.M_Desc.E_ImageType = _IMAGETYPE_JPEG;
	}
	else if ((wstring_T_Extension == L".bmp") || (wstring_T_Extension == L".BMP"))
	{
		T_ImageSet.M_Desc.E_ImageType = _IMAGETYPE_BMP;
	}
	else
	{
		POPUP(L"FileType Is Not WIC", L"FileType Is Not WIC");
		return E_FAIL;
	}
	if (FAILED(LoadFromWICFile(wstring_T_Path.c_str(), WIC_FLAGS_NONE, nullptr, _ScratchImage)))
	{
		POPUP(L"LoadFromWICFile Failed", L"File Extension Is Not WIC");
		return E_FAIL;
	}
	return S_OK;
}

//// 실제 파일에서 스크래치이미지로 변환(string 용)
HRESULT C_ResourceManager::MF_Convert_FileToScratchImage(const string& _stringName, ScratchImage& _ScratchImage)
{
	// wstring으로 변환
	const wstring _wstringName = GF_ConvertStringToWString_WinAPI(_stringName);

	return MF_Convert_FileToScratchImage(_wstringName, _ScratchImage);
}

//// 스크래치 이미지를 이미지세트로 변환
HRESULT C_ResourceManager::MF_Convert_ScratchImageToCPUImage(const ScratchImage& _ScratchImage, FL_DS_ImageSet& _ImageSet)
{
	FL_DS_CPU_Image T_CPU_Image = _ImageSet.M_CPUImage;
	const Image* P_ImageArray = _ScratchImage.GetImages();
	size_t Count = _ScratchImage.GetImageCount();
	const uint8_t* P_PixelsBase = _ScratchImage.GetPixels();
	size_t TotalSize = _ScratchImage.GetPixelsSize();

	if ((nullptr == P_ImageArray) || (nullptr == P_PixelsBase) || (0 == Count) || (0 == TotalSize))
	{
		POPUP_DEBUG(L"struct Image Is Empty", L"in C_ResourceManager::MF_Convert_ScratchImageToCPUImage(), struct Image Is Empty")
		return E_FAIL;
	}

	T_CPU_Image.M_MetaData = _ScratchImage.GetMetadata();
	T_CPU_Image.M_PixelBlob.resize(TotalSize);

	// 실제 메모리 버퍼 복사; 유의! 통으로 복사하는 버릇을 들이자!
	memcpy(T_CPU_Image.M_PixelBlob.data(), P_PixelsBase, TotalSize);

	T_CPU_Image.STL_M_Entry.clear();
	for (size_t i = 0; i < Count; ++i)
	{
		const Image& T_Image = P_ImageArray[i];
		FL_DS_ImageEntry Entry = {};
		Entry.SDK_M_Width = T_Image.width;
		Entry.SDK_M_Height = T_Image.height;
		Entry.DX_M_ImageFormat = T_Image.format;
		Entry.SDK_M_RowPitch = T_Image.rowPitch;
		Entry.SDK_M_SlicePitch = T_Image.slicePitch;
		Entry.SDK_M_OffsetInBlob = static_cast<size_t>(T_Image.pixels - P_PixelsBase);

		T_CPU_Image.STL_M_Entry.push_back(Entry);
	}

	// 자꾸 이부분 실수하는 듯; 유의! STL 컨테이너는 기본적으로 얉은 복사니까 강제적으로 깊은 복사를 시켜야 함!
	_ImageSet.M_CPUImage = std::move(T_CPU_Image);

	return S_OK;
}

//// 이미지세트를 스크래치 이미지로 변환
HRESULT C_ResourceManager::MF_Convert_CPUImageToScratchImage(const FL_DS_CPU_Image& _Source_CPU_Image, ScratchImage& _Out_ScratchImage_Out)
{
	if (FAILED(_Out_ScratchImage_Out.Initialize(_Source_CPU_Image.M_MetaData)))		// 방어코드
	{
		POPUP_DEBUG(L"_Out_ScratchImage_Out.Initialize() Failed", L"in C_ResourceManager::MF_Convert_CPUImageToScratchImage(), _Out_ScratchImage_Out.Initialize() Failed")

		return E_FAIL;
	}

	const Image* P_ImageArray = _Out_ScratchImage_Out.GetImages();
	size_t Count = _Out_ScratchImage_Out.GetImageCount();
	uint8_t* P_PixelsBase = _Out_ScratchImage_Out.GetPixels();
	size_t TotalSize = _Out_ScratchImage_Out.GetPixelsSize();

	if ((nullptr == P_ImageArray) || (nullptr == P_PixelsBase) || (_Source_CPU_Image.STL_M_Entry.size() != Count))
	{
		POPUP_DEBUG(L"struct Image Is Empty", L"in C_ResourceManager::MF_Convert_CPUImageToScratchImage(), struct Image Is Empty")

		return E_FAIL;
	}

	if (TotalSize > _Source_CPU_Image.M_PixelBlob.size())
	{
		POPUP_DEBUG(L"struct Image Is Empty", L"in C_ResourceManager::MF_Convert_CPUImageToScratchImage(), struct Image Is Empty")
		return E_FAIL;
	}

	memcpy(P_PixelsBase, _Source_CPU_Image.M_PixelBlob.data(), TotalSize);

	return S_OK;
}

// Save
// 저장하는 것은 디버그 모드에서만 되도록 조정
// 단, 스테이지 저장은 별개로 할 수 있도록 함; 향후, 스테이지 작성시 사용
#ifdef _DEBUG
void C_ResourceManager::MF_Save_All()
{
	// 저장은 순서대로!
	if (FAILED(MF_Save_ResourceAllAsFile()))
	{
		POPUP_DEBUG(L"MF_Save_ResourceAllAsFile() Failed", L"in C_ResourceManager::MF_Save_All(), MF_Save_ResourceAllAsFile() Failed")
	}

	if (FAILED(MF_Save_ImageAllAsFile()))
	{
		POPUP_DEBUG(L"MF_Save_ImageAllAsFile() Failed", L"in C_ResourceManager::MF_Save_All(), MF_Save_ImageAllAsFile() Failed")
	}
}

HRESULT C_ResourceManager::MF_Save_ResourceAllAsFile()
{
	return E_NOTIMPL;
}

HRESULT C_ResourceManager::MF_Save_ImageAllAsFile()
{
	// 향후, 난독화 및 분기 등으로, 메모리 덤프 등으로 리버스 엔지니어링하는 것을 막는 것도 고려해보자

	FILE* SDK_T_File = nullptr;

	// 코드 개선; 파일명 지정가능
	// 임시 경로변수 생성
	// 오버헤드를 극한으로 감소하기 위해, 환원방식이 아닌 스택 임시변수 선언 및 버리기로 함
	wstring wstring_T_Path = wstring_M_BasicPath + wstring_M_BasicImageFileName;

	// 파일 열기
	_wfopen_s(&SDK_T_File, wstring_T_Path.c_str(), L"wb");

	// 향후, 조건문 부분을 _wfopen_s 반환값으로 하면 오버헤드가 더 적을 것 같긴한데, 10시간째 씨름중이라 나중에 다시 생각해보자
	if (nullptr == SDK_T_File)
	{
		MessageBox(nullptr, L"_wfopen_s() Failed", L"_wfopen_s() Must Check", MB_OK | MB_ICONINFORMATION);
		return E_FAIL;
	}

	size_t T_MapSize = STL_M_ImageSet.size();
	fwrite(&T_MapSize, sizeof(size_t), 1, SDK_T_File);

	for (const auto& pair : STL_M_ImageSet)
	{
		const wstring& T_Key = pair.first;
		const size_t T_KeyLength = T_Key.length();

		fwrite(&T_KeyLength, sizeof(size_t), 1, SDK_T_File);
		fwrite(T_Key.c_str(), sizeof(wchar_t), T_KeyLength, SDK_T_File);

		const FL_DS_ImageSet* T_ImageSet = pair.second;

		const FL_DS_CPU_Image& DS_T_CpuImage = T_ImageSet->M_CPUImage;

		// FL_DS_ResourceImageDesc이 저장안되는 논리버그 수정
		const FL_DS_ResourceImageDesc& DS_T_Desc = T_ImageSet->M_Desc;

		fwrite(&DS_T_CpuImage.M_MetaData, sizeof(TexMetadata), 1, SDK_T_File);

		const size_t T_EntryCount = DS_T_CpuImage.STL_M_Entry.size();
		fwrite(&T_EntryCount, sizeof(size_t), 1, SDK_T_File);
		fwrite(DS_T_CpuImage.STL_M_Entry.data(), sizeof(FL_DS_ImageEntry), T_EntryCount, SDK_T_File);

		const size_t T_PixelSize = DS_T_CpuImage.M_PixelBlob.size();
		fwrite(&T_PixelSize, sizeof(size_t), 1, SDK_T_File);
		fwrite(DS_T_CpuImage.M_PixelBlob.data(), 1, T_PixelSize, SDK_T_File);

		// FL_DS_ResourceImageDesc이 저장안되는 논리버그 수정
		fwrite(&DS_T_Desc, sizeof(FL_DS_ResourceImageDesc), 1, SDK_T_File);
	}

	fclose(SDK_T_File);
	return S_OK;
}
#endif // _DEBUG

// Load
void C_ResourceManager::MF_Load_All()
{
	// 로드는 역순으로!
	if (FAILED(MF_Load_ImageAllFromFile()))
	{
		POPUP_DEBUG(L"MF_Load_ImageAllFromFile() Failed", L"in C_ResourceManager::MF_Load_All(), MF_Load_ImageAllFromFile() Failed")
	}

	if (FAILED(MF_Load_ResourceAllFromFile()))
	{
		POPUP_DEBUG(L"MF_Load_ResourceAllFromFile() Failed", L"in C_ResourceManager::MF_Load_All(), MF_Load_ResourceAllFromFile() Failed")
	}

	if (FAILED(MF_Load_StageAllFromFile()))
	{
		POPUP_DEBUG(L"MF_Load_StageAllFromFile() Failed", L"in C_ResourceManager::MF_Load_All(), MF_Load_StageAllFromFile() Failed")
	}
}

HRESULT C_ResourceManager::MF_Load_StageAllFromFile()
{
	return E_NOTIMPL;
}

HRESULT C_ResourceManager::MF_Load_ResourceAllFromFile()
{
	return E_NOTIMPL;
}

HRESULT C_ResourceManager::MF_Load_ImageAllFromFile()
{
	// 향후, 난독화 및 분기 등으로, 메모리 덤프 등으로 리버스 엔지니어링하는 것을 막는 것도 고려해보자

	FILE* SDK_T_File = nullptr;

	// 코드 개선; 파일명 지정가능
	// 임시 경로변수 생성
	// 오버헤드를 극한으로 감소하기 위해, 환원방식이 아닌 스택 임시변수 선언 및 버리기로 함
	wstring wstring_T_Path = wstring_M_BasicPath + wstring_M_BasicImageFileName;

	_wfopen_s(&SDK_T_File, wstring_T_Path.c_str(), L"rb");

	// 향후, 조건문 부분을 _wfopen_s 반환값으로 하면 오버헤드가 더 적을 것 같긴한데, 10시간째 씨름중이라 나중에 다시 생각해보자
	if (nullptr == SDK_T_File)
	{
		MessageBox(nullptr, L"_wfopen_s() Failed", L"_wfopen_s() Must Check", MB_OK | MB_ICONINFORMATION);

		return E_FAIL;
	}

	size_t T_MapSize = 0;
	fread(&T_MapSize, sizeof(size_t), 1, SDK_T_File);

	for (size_t i = 0; i < T_MapSize; ++i)
	{
		size_t T_KeyLength = 0;
		fread(&T_KeyLength, sizeof(size_t), 1, SDK_T_File);

		// 코드개선: 메모리만 확보 (초기화 없음); 필요없는 초기화 작업을 없애 오버헤드 감소
		wstring T_Key;
		T_Key.resize(T_KeyLength);

		fread(&T_Key[0], sizeof(wchar_t), T_KeyLength, SDK_T_File);

		auto* T_ImageSet = new FL_DS_ImageSet();

		// 가독성을 위해, Save 형태와 같이 역참조 줄이는 형식 적용
		FL_DS_CPU_Image& DS_T_CpuImage = T_ImageSet->M_CPUImage;

		// FL_DS_ResourceImageDesc이 저장안되는 논리버그 수정
		FL_DS_ResourceImageDesc& DS_T_Desc = T_ImageSet->M_Desc;

		fread(&DS_T_CpuImage.M_MetaData, sizeof(TexMetadata), 1, SDK_T_File);

		size_t T_EntryCount = 0;
		fread(&T_EntryCount, sizeof(size_t), 1, SDK_T_File);
		DS_T_CpuImage.STL_M_Entry.resize(T_EntryCount);
		fread(DS_T_CpuImage.STL_M_Entry.data(), sizeof(FL_DS_ImageEntry), T_EntryCount, SDK_T_File);

		size_t T_PixelSize = 0;
		fread(&T_PixelSize, sizeof(size_t), 1, SDK_T_File);
		DS_T_CpuImage.M_PixelBlob.resize(T_PixelSize);
		fread(DS_T_CpuImage.M_PixelBlob.data(), 1, T_PixelSize, SDK_T_File);

		// FL_DS_ResourceImageDesc이 저장안되는 논리버그 수정
		fread(&DS_T_Desc, sizeof(FL_DS_ResourceImageDesc), 1, SDK_T_File);

		STL_M_ImageSet.insert({ T_Key, T_ImageSet });
	}

	// 파일 닫기
	fclose(SDK_T_File);
	return S_OK;
}
