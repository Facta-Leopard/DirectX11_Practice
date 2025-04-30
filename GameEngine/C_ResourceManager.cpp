#include "pch.h"
#include "C_ResourceManager.h"

#include "DirectxTex/DirectXTex.h"
#include "DirectxTex/DirectXTex.inl"

#include "C_Mesh.h"

C_ResourceManager::C_ResourceManager()
	: STL_M_ImageSet{}
{
	// .rsc ������ ����Ǿ� �ִ� �⺻ ��ġ ����
	wchar_t wchar_T_Path_s[255] = {};
	wstring wstring_BasicPath = {};
	GetCurrentDirectory(255, wchar_T_Path_s);
	wcscat_s(wchar_T_Path_s, 255, L"\\Resource\\");
	wstring_M_BasicPath = wchar_T_Path_s;

	CreateDirectoryW(wstring_M_BasicPath.c_str(), nullptr);

	// �ڵ尳��: �⺻������ �����Ǵ� ���ϸ�(Ȯ���� ����)
	wstring_M_BasicImageFileName = L"CompressedImage.rsc";

	// ������ ���� ���, CompressedImage.rsc ������ ����
	FILE* SDK_T_File = nullptr;
	wstring wstring_T_Path = wstring_M_BasicPath + wstring_M_BasicImageFileName;

	_wfopen_s(&SDK_T_File, wstring_T_Path.c_str(), L"rb");

	// ����, ���ǹ� �κ��� _wfopen_s ��ȯ������ �ϸ� ������尡 �� ���� �� �����ѵ�, 10�ð�° �������̶� ���߿� �ٽ� �����غ���
	if (nullptr == SDK_T_File)
	{
		_wfopen_s(&SDK_T_File, wstring_T_Path.c_str(), L"wb");
		size_t T_Zero = 0;
		fwrite(&T_Zero, sizeof(size_t), 1, SDK_T_File);
		fclose(SDK_T_File);
		POPUP(L"The .rsc File Does Not Exist", (L"A temporary file named `" + wstring_M_BasicImageFileName+ L"` has been created at `" + wstring_M_BasicPath).c_str())
	}

	// ������ ����� ���� �ε�
	MF_Load_All();
}

C_ResourceManager::~C_ResourceManager()
{
	// STL �����̳� �޸� ����
	DELETEALL_STL_MAP(STL_M_Stage)

	// MAP ������ STL ���� ���� shared_ptr �̹Ƿ�, delete�� ����� ��ũ�ΰ� �ƴ� .clear()�� ���
	STL_M_Resoure.clear();
	DELETEALL_STL_MAP(STL_M_ImageSet)
}

// Basic
// �ʱ�ȭ �Լ�
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

//// �޽� ���� �Լ�
HRESULT C_ResourceManager::MF_Create_MeshResource(UINT _SDK_Slice)
{
	MF_Create_PointMeshResource();

	MF_Create_RectangleMeshResource();

	MF_Create_CircleMeshResource(_SDK_Slice);
}

////// �� �޽� ���� �Լ�
HRESULT C_ResourceManager::MF_Create_PointMeshResource()
{
	// PointMesh; ���޽�
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

////// �׸� �޽� ���� �Լ�
HRESULT C_ResourceManager::MF_Create_RectangleMeshResource()
{
	// RectangleMesh; �׸�޽�
	shared_ptr<C_Mesh> SP_T_RectangleMesh = make_shared<C_Mesh>();
	SP_T_RectangleMesh->MF_Set_Name(L"RectangleMesh");

	//// �� ����ü �迭 ����
	////// 0��° �� �� �ʱ�ȭ
	DS_Vertex DS_T_RectangleVertex_s[4] = {};
	DS_T_RectangleVertex_s[0].SDK_XM_FLOAT3_Position = { -0.5f, 0.5f, 0.f };
	DS_T_RectangleVertex_s[0].SDK_XM_FLOAT2_PositionUV = { 0.f, 0.f };
	DS_T_RectangleVertex_s[0].SDK_XM_FLOAT4_Color = { 1.f, 0.f, 0.f, 1.f };

	////// 1��° �� �� �ʱ�ȭ
	DS_T_RectangleVertex_s[1].SDK_XM_FLOAT3_Position = { 0.5f, 0.5f, 0.f };
	DS_T_RectangleVertex_s[1].SDK_XM_FLOAT2_PositionUV = { 1.f, 0.f };
	DS_T_RectangleVertex_s[1].SDK_XM_FLOAT4_Color = { 0.f, 1.f, 0.f, 1.f };

	////// 2��° �� �� �ʱ�ȭ
	DS_T_RectangleVertex_s[2].SDK_XM_FLOAT3_Position = { 0.5f, -0.5f, 0.f };
	DS_T_RectangleVertex_s[2].SDK_XM_FLOAT2_PositionUV = { 1.f, 1.f };
	DS_T_RectangleVertex_s[2].SDK_XM_FLOAT4_Color = { 0.f, 0.f, 1.f, 1.f };

	////// 3��° �� �� �ʱ�ȭ
	DS_T_RectangleVertex_s[3].SDK_XM_FLOAT3_Position = { -0.5f, -0.5f, 0.f };
	DS_T_RectangleVertex_s[3].SDK_XM_FLOAT2_PositionUV = { 0.f, 1.f };
	DS_T_RectangleVertex_s[3].SDK_XM_FLOAT4_Color = { 1.f, 0.f, 1.f, 1.f };

	//// Index: Topology ����
	//// ����! �ﰢ�� �������� 2���� ������ ����̹Ƿ�, �Ʒ��� ���� ������
	UINT SDK_T_RectangleTopologyIndex[6] = { 0, 1, 2, 0, 2, 3 };

	//// ����! �� ����ü�� �Ʒ����� ����׿����� ��Ȱ���ϹǷ�, �׷��� �ε����� 6����(�ﰢ�� 0-1-2, �ﰢ�� 0-2-3)!
	HRESULT SDK_HRESULT_RectangleMeshBuffer = SP_T_RectangleMesh->MF_Create_Buffer(DS_T_RectangleVertex_s, 4, SDK_T_RectangleTopologyIndex, 6);
	HRESULT SDK_HRESULT_RectangleMeshAttach = MF_Attach_Resource(SP_T_RectangleMesh->MF_Get_Name(), SP_T_RectangleMesh);

	if (FAILED(SDK_HRESULT_RectangleMeshBuffer) || FAILED(SDK_HRESULT_RectangleMeshAttach))
	{
		POPUP_DEBUG(L"RectangleMesh Failed ", L"in C_ResourceManager::MF_Create_RectangleMeshResource(), RectangleMesh Failed")
		return E_FAIL;
	}

	// RectangleMesh_Debug; ������ �׸�޽�
	shared_ptr<C_Mesh> SP_T_RectangleMesh_Debug = make_shared<C_Mesh>();
	SP_T_RectangleMesh_Debug->MF_Set_Name(L"RectangleMesh_Debug");

	//// Index: Topology ����
	////// ����! �ﰢ�� �������� 2���� �ƴ� �簢�� ���������� ������ ����̹Ƿ�, �Ʒ��� ���� ������
	UINT SDK_T_RectangleTopologyIndex_Debug[5] = { 0, 1, 2, 3, 0 };

	//// ����! �� ����ü�� ������ ���� �� ����ü�� ��Ȱ���ϹǷ�, �׷��� �ε����� 5����(�簢�� 0-1-2-3-0)!
	HRESULT SDK_HRESULT_RectangleMeshBuffer_Debug = SP_T_RectangleMesh_Debug->MF_Create_Buffer(DS_T_RectangleVertex_s, 4, SDK_T_RectangleTopologyIndex_Debug, 5);
	HRESULT SDK_HRESULT_RectangleMeshAttach_Debug = MF_Attach_Resource(SP_T_RectangleMesh_Debug->MF_Get_Name(), SP_T_RectangleMesh_Debug);

	if (FAILED(SDK_HRESULT_RectangleMeshBuffer_Debug) || FAILED(SDK_HRESULT_RectangleMeshAttach_Debug))
	{
		POPUP_DEBUG(L"RectangleMesh_Debug Failed ", L"in C_ResourceManager::MF_Create_RectangleMeshResource(), RectangleMesh_Debug Failed")
		return E_FAIL;
	}

	return S_OK;
}

////// �� �޽� ���� �Լ�
HRESULT C_ResourceManager::MF_Create_CircleMeshResource(UINT _SDK_Slice)
{
	// CircleMesh; �� �޽�
	shared_ptr<C_Mesh> SP_T_CircleMesh = make_shared<C_Mesh>();
	SP_T_CircleMesh->MF_Set_Name(L"CircleMesh");

	//// ���� ǥ���� �� �޽� STL �����̳� ����
	vector<DS_Vertex> STL_DS_T_CircleVertex;

	////// �� �߽� ���� ����
	DS_Vertex DS_T_CircleCenter;
	DS_T_CircleCenter.SDK_XM_FLOAT3_Position = { 0.f, 0.f, 0.f };
	DS_T_CircleCenter.SDK_XM_FLOAT2_PositionUV = { 0.5f, 0.5f };
	DS_T_CircleCenter.SDK_XM_FLOAT4_Color = { 1.f, 1.f, 1.f, 1.f };

	////// �� �߽��� �� �޽� STL �����̳ʿ� ����
	STL_DS_T_CircleVertex.push_back(DS_T_CircleCenter);

	float T_Radius = 0.5f;
	float T_Angle = 0.f;

	////// �� �ܰ��� ������ ���� ��� �� ����
	////// ����׿뿡�� �Ȱ��� ���
	for (UINT i = 0; i < _SDK_Slice + 1; ++i)
	{
		DS_T_CircleCenter.SDK_XM_FLOAT3_Position = { T_Radius * cosf(T_Angle), T_Radius * sinf(T_Angle), 0.f };
		DS_T_CircleCenter.SDK_XM_FLOAT2_PositionUV = { DS_T_CircleCenter.SDK_XM_FLOAT3_Position.x + 0.5f, 1.f - (DS_T_CircleCenter.SDK_XM_FLOAT3_Position.y + 0.5f) };
		STL_DS_T_CircleVertex.push_back(DS_T_CircleCenter);

		// ���� ��, float���� �ٲ��� ������ ������ �������� �ٲ� 0�̵Ǵ� �һ�簡 �߻�����
		// �ǿ����� �� �ϳ��� �Ǽ����� ����������, �Ǽ������� ���� ���� ������ ĳ�����ؼ� �����ִ� ���� ����,
		T_Angle += XM_2PI / (float)_SDK_Slice;
	}

	//// ���� ǥ���ϴµ� �� �ε���
	vector<UINT> STL_SDK_T_CircleIndex;

	////// �� �ε��� ��� �� ����
	////// �ﰢ�� ���������� �������� ���� ���� ���
	////// ����׿뿡�� �Ȱ��� ���
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

	// CircleMesh_Debug; ����� �� �޽�
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

// ã�� �Լ�
// ����� ���� �ڷ��� �߿��� �̹��� ã��
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

	// ����
	return MF_FindImageSetFromVectorData(wstring_T_Name);
}

// Attach & Detach
HRESULT C_ResourceManager::MF_Attach_Resource(const wstring& _wstringName, shared_ptr<C_Resource> _SP_Resource)
{
	return E_NOTIMPL;
}

HRESULT C_ResourceManager::MF_Attach_Resource(const string& _stringName, shared_ptr<C_Resource> _SP_Resource)
{
	// UTF-8 -> UNICODE�� ��ȯ
	const wstring _wstringName = GF_ConvertStringToWString_WinAPI(_stringName);

	return MF_Attach_Resource(_wstringName, _SP_Resource);
}

HRESULT C_ResourceManager::MF_Attach_ImageToImageSet(const wstring& _wstringName)
{
	// ����, �ش� ������ �ִ��� Ȯ��
	if (nullptr != MF_FindImageSetFromVectorData(_wstringName))
	{
		// �̹� �����ϸ� �޽��� �ڽ� ����� ����ڿ��� Ȯ��
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
	
	// ��ũ��ġ�̹��� ����ü �ӽû���
	ScratchImage T_ScretchImage = {};

	// �̹��������� ��ũ��ġ �̹����� ��ȯ
	if (FAILED(MF_Convert_FileToScratchImage(_wstringName, T_ScretchImage)))
	{
		POPUP(L"MF_Convert_FileToScratchImage() Failed", L"in C_ResourceManager::MF_Attach_ImageToImageSet(), MF_Convert_FileToScratchImage() Failed")
		return E_FAIL;
	}

	// �ӽ� ��Ÿ������
	FL_DS_ImageSet T_ImageSet = {};
	// ��ũ��ġ �̹����� �̹�����Ʈ�� ��ȯ
	if (FAILED(MF_Convert_ScratchImageToCPUImage(T_ScretchImage, T_ImageSet)))
	{
		POPUP(L"MF_Convert_ScratchImageToCPUImage() Failed", L"in C_ResourceManager::MF_Attach_ImageToImageSet(), MF_Convert_ScratchImageToCPUImage() Failed")
		return E_FAIL;
	}
	FL_DS_ImageSet* P_T_ImageSet = &T_ImageSet;

	map<wstring, FL_DS_ImageSet*>::iterator T_Iterator = STL_M_ImageSet.find(_wstringName);
	if (T_Iterator != STL_M_ImageSet.end())
	{
		// �̹� �����ϸ� �޽��� �ڽ� ����� ����ڿ��� Ȯ��
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
	// UTF-8 -> UNICODE�� ��ȯ
	const wstring _wstringName = GF_ConvertStringToWString_WinAPI(_stringName);

	return MF_Attach_ImageToImageSet(_wstringName);
}

// ��ȯ�� �Լ�
//// ���� ���Ͽ��� ��ũ��ġ�̹����� ��ȯ
HRESULT C_ResourceManager::MF_Convert_FileToScratchImage(const wstring& _wstringName, ScratchImage& _ScratchImage)
{
	// ������ �ӽÿ� ����ü �ʱ�ȭ
	FL_DS_ImageSet T_ImageSet = {};

	// �ӽÿ� ����ü�� �̹������ҽ� ���� ��Ÿ������; ����! Scratch�� ��Ÿ�����Ϳ� �򰥸��� �� ��!

	// �̹����� �J��� ��� ���� wchar ���ڿ� �ʱ�ȭ
	wchar_t wchar_T_Path_s[255] = {};

	wstring wstring_T_Path = {};

	// �ּ� �� ���ϸ� �ҷ�����
	wstring_T_Path = wstring_M_BasicPath + _wstringName;

	// ����, WIC���� �ٸ� ������ �߰��� ��� �� �κ� �������
	wchar_t wchar_T_Extension[16] = {};
	_wsplitpath_s(wstring_T_Path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, wchar_T_Extension, 16);
	wstring wstring_T_Extension = wchar_T_Extension;

	// Ȯ���ڿ� ����, �̹��� Ÿ�� �κ��� �߸� �Է����� ��찡 �����ǵ��� ��� ����
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

//// ���� ���Ͽ��� ��ũ��ġ�̹����� ��ȯ(string ��)
HRESULT C_ResourceManager::MF_Convert_FileToScratchImage(const string& _stringName, ScratchImage& _ScratchImage)
{
	// wstring���� ��ȯ
	const wstring _wstringName = GF_ConvertStringToWString_WinAPI(_stringName);

	return MF_Convert_FileToScratchImage(_wstringName, _ScratchImage);
}

//// ��ũ��ġ �̹����� �̹�����Ʈ�� ��ȯ
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

	// ���� �޸� ���� ����; ����! ������ �����ϴ� ������ ������!
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

	// �ڲ� �̺κ� �Ǽ��ϴ� ��; ����! STL �����̳ʴ� �⺻������ ���� ����ϱ� ���������� ���� ���縦 ���Ѿ� ��!
	_ImageSet.M_CPUImage = std::move(T_CPU_Image);

	return S_OK;
}

//// �̹�����Ʈ�� ��ũ��ġ �̹����� ��ȯ
HRESULT C_ResourceManager::MF_Convert_CPUImageToScratchImage(const FL_DS_CPU_Image& _Source_CPU_Image, ScratchImage& _Out_ScratchImage_Out)
{
	if (FAILED(_Out_ScratchImage_Out.Initialize(_Source_CPU_Image.M_MetaData)))		// ����ڵ�
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
// �����ϴ� ���� ����� ��忡���� �ǵ��� ����
// ��, �������� ������ ������ �� �� �ֵ��� ��; ����, �������� �ۼ��� ���
#ifdef _DEBUG
void C_ResourceManager::MF_Save_All()
{
	// ������ �������!
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
	// ����, ����ȭ �� �б� ������, �޸� ���� ������ ������ �����Ͼ�ϴ� ���� ���� �͵� ����غ���

	FILE* SDK_T_File = nullptr;

	// �ڵ� ����; ���ϸ� ��������
	// �ӽ� ��κ��� ����
	// ������带 �������� �����ϱ� ����, ȯ������� �ƴ� ���� �ӽú��� ���� �� ������� ��
	wstring wstring_T_Path = wstring_M_BasicPath + wstring_M_BasicImageFileName;

	// ���� ����
	_wfopen_s(&SDK_T_File, wstring_T_Path.c_str(), L"wb");

	// ����, ���ǹ� �κ��� _wfopen_s ��ȯ������ �ϸ� ������尡 �� ���� �� �����ѵ�, 10�ð�° �������̶� ���߿� �ٽ� �����غ���
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

		// FL_DS_ResourceImageDesc�� ����ȵǴ� ������ ����
		const FL_DS_ResourceImageDesc& DS_T_Desc = T_ImageSet->M_Desc;

		fwrite(&DS_T_CpuImage.M_MetaData, sizeof(TexMetadata), 1, SDK_T_File);

		const size_t T_EntryCount = DS_T_CpuImage.STL_M_Entry.size();
		fwrite(&T_EntryCount, sizeof(size_t), 1, SDK_T_File);
		fwrite(DS_T_CpuImage.STL_M_Entry.data(), sizeof(FL_DS_ImageEntry), T_EntryCount, SDK_T_File);

		const size_t T_PixelSize = DS_T_CpuImage.M_PixelBlob.size();
		fwrite(&T_PixelSize, sizeof(size_t), 1, SDK_T_File);
		fwrite(DS_T_CpuImage.M_PixelBlob.data(), 1, T_PixelSize, SDK_T_File);

		// FL_DS_ResourceImageDesc�� ����ȵǴ� ������ ����
		fwrite(&DS_T_Desc, sizeof(FL_DS_ResourceImageDesc), 1, SDK_T_File);
	}

	fclose(SDK_T_File);
	return S_OK;
}
#endif // _DEBUG

// Load
void C_ResourceManager::MF_Load_All()
{
	// �ε�� ��������!
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
	// ����, ����ȭ �� �б� ������, �޸� ���� ������ ������ �����Ͼ�ϴ� ���� ���� �͵� ����غ���

	FILE* SDK_T_File = nullptr;

	// �ڵ� ����; ���ϸ� ��������
	// �ӽ� ��κ��� ����
	// ������带 �������� �����ϱ� ����, ȯ������� �ƴ� ���� �ӽú��� ���� �� ������� ��
	wstring wstring_T_Path = wstring_M_BasicPath + wstring_M_BasicImageFileName;

	_wfopen_s(&SDK_T_File, wstring_T_Path.c_str(), L"rb");

	// ����, ���ǹ� �κ��� _wfopen_s ��ȯ������ �ϸ� ������尡 �� ���� �� �����ѵ�, 10�ð�° �������̶� ���߿� �ٽ� �����غ���
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

		// �ڵ尳��: �޸𸮸� Ȯ�� (�ʱ�ȭ ����); �ʿ���� �ʱ�ȭ �۾��� ���� ������� ����
		wstring T_Key;
		T_Key.resize(T_KeyLength);

		fread(&T_Key[0], sizeof(wchar_t), T_KeyLength, SDK_T_File);

		auto* T_ImageSet = new FL_DS_ImageSet();

		// �������� ����, Save ���¿� ���� ������ ���̴� ���� ����
		FL_DS_CPU_Image& DS_T_CpuImage = T_ImageSet->M_CPUImage;

		// FL_DS_ResourceImageDesc�� ����ȵǴ� ������ ����
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

		// FL_DS_ResourceImageDesc�� ����ȵǴ� ������ ����
		fread(&DS_T_Desc, sizeof(FL_DS_ResourceImageDesc), 1, SDK_T_File);

		STL_M_ImageSet.insert({ T_Key, T_ImageSet });
	}

	// ���� �ݱ�
	fclose(SDK_T_File);
	return S_OK;
}
