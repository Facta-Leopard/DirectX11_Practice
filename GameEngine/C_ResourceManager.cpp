#include "pch.h"
#include "C_ResourceManager.h"

#include "DirectxTex/DirectXTex.h"
#include "DirectxTex/DirectXTex.inl"

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
	DELETEALL_STL_MAP(STL_M_Resoure)
	DELETEALL_STL_MAP(STL_M_ImageSet)
}

// Basic

HRESULT C_ResourceManager::MF_Initialize()
{
	return E_NOTIMPL;
}

HRESULT C_ResourceManager::MF_Create_MeshResource()
{
	return E_NOTIMPL;
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

// Attach & Detach
// 붙히고 떼고 하는 것은 디버그 모드에서만 되도록 조정
#ifdef _DEBUG

HRESULT C_ResourceManager::MF_Attach_Resource(const wstring& _wstringName, C_Resource* _Resource)
{
	return E_NOTIMPL;
}

HRESULT C_ResourceManager::MF_Attach_Resource(const string& _stringName, C_Resource* _Resource)
{
	// UTF-8 -> UNICODE로 변환
	wstring _wstringName = GF_ConvertStringToWString_WinAPI(_stringName);

	return MF_Attach_Resource(_wstringName, _Resource);
}



HRESULT C_ResourceManager::MF_Attach_ImageToImageSet(const wstring& _wstringName, FL_DS_ImageSet* _ImageSet)
{
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
			STL_M_ImageSet[_wstringName] = _ImageSet;
		}
		else
		{
			return E_FAIL;
		}
	}
	else
	{
		STL_M_ImageSet.insert(make_pair(_wstringName, _ImageSet));
	}
	return S_OK;
}

HRESULT C_ResourceManager::MF_Attach_ImageToImageSet(const string& _stringName, FL_DS_ImageSet* _ImageSet)
{
	// UTF-8 -> UNICODE로 변환
	wstring _wstringName = GF_ConvertStringToWString_WinAPI(_stringName);

	return MF_Attach_ImageToImageSet(_wstringName, _ImageSet);
}

HRESULT C_ResourceManager::MF_Detach_Resource(const wstring& _wstringName)
{
	return E_NOTIMPL;
}

HRESULT C_ResourceManager::MF_Detach_Resource(const string& _stringName)
{
	// UTF-8 -> UNICODE로 변환
	wstring _wstringName = GF_ConvertStringToWString_WinAPI(_stringName);

	return MF_Detach_Resource(_wstringName);
}

HRESULT C_ResourceManager::MF_Detach_ImageToImageSet(const wstring& _wstringName)
{
	return E_NOTIMPL;
}

HRESULT C_ResourceManager::MF_Detach_ImageToImageSet(const string& _stringName)
{
	// UTF-8 -> UNICODE로 변환
	wstring _wstringName = GF_ConvertStringToWString_WinAPI(_stringName);

	return MF_Detach_ImageToImageSet(_wstringName);
}
#endif // _DEBUG

// Save
// 저장하는 것은 디버그 모드에서만 되도록 조정
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
