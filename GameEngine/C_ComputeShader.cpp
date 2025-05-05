#include "pch.h"
#include "C_ComputeShader.h"
#include "C_ConstantBuffer.h"

C_ComputeShader::C_ComputeShader()
	: C_Resource(_COMPUTE_SHADER)

	, CP_DX_M_ErrorBlob{}

	, CP_DX_M_ComputeShader{}
	, CP_DX_M_ComputeShaderBlob{}

	, DS_M_MaterialConstant{}

	, SDK_M_GroupCountX(1)
	, SDK_M_GroupCountY(1)
	, SDK_M_GroupCountZ(1)

	, SDK_M_ThreadPerGroupX(16)
	, SDK_M_ThreadPerGroupY(16)
{
	// �ڵ尳��; 2D �� 3D�� ���� ������ ������ �� ����
	E_COLLIDER_TYPE T_ColliderType = C_CollisionManager::SF_Get_Instance()->MF_Get_ColliderType();
	switch (T_ColliderType)
	{
	case _COLLIDER_2D_SIDESCROLL_:
	case _COLLIDER_2D_TOPVEIW:
	case _COLLIDER_2D_ISOMETRICVIEW:
		SDK_M_ThreadPerGroupZ = 1;
		break;
	default:
		SDK_M_ThreadPerGroupZ = 4;
		break;
	}
}

C_ComputeShader::C_ComputeShader(const wstring& _Path, const string& _HLSL_Function, UINT _SDK_RegisterGroupX, UINT _SDK_RegisterGroupY, UINT _SDK_RegisterGroupZ)
	: C_Resource(_COMPUTE_SHADER)

	, CP_DX_M_ErrorBlob{}

	, CP_DX_M_ComputeShader{}
	, CP_DX_M_ComputeShaderBlob{}

	, DS_M_MaterialConstant{}

	, SDK_M_GroupCountX(_SDK_RegisterGroupX)
	, SDK_M_GroupCountY(_SDK_RegisterGroupY)
	, SDK_M_GroupCountZ(_SDK_RegisterGroupZ)

	, SDK_M_ThreadPerGroupX(16)
	, SDK_M_ThreadPerGroupY(16)
{
	// �ڵ尳��; 2D �� 3D�� ���� ������ ������ �� ����
	E_COLLIDER_TYPE T_ColliderType = C_CollisionManager::SF_Get_Instance()->MF_Get_ColliderType();
	switch (T_ColliderType)
	{
	case _COLLIDER_2D_SIDESCROLL_:
	case _COLLIDER_2D_TOPVEIW:
	case _COLLIDER_2D_ISOMETRICVIEW:
		SDK_M_ThreadPerGroupZ = 1;
		break;
	default:
		SDK_M_ThreadPerGroupZ = 4;
		break;
	}
	MF_Create_ComputeShader(_Path, _HLSL_Function);
}

C_ComputeShader::~C_ComputeShader()
{
}

void C_ComputeShader::MF_Bind_ComputeShader()
{
}

void C_ComputeShader::MF_UnBind_ComputeShader()
{
}

void C_ComputeShader::MF_Create_ComputeShader(const wstring& _Path, const string& _HLSL_Function)
{
	wstring T_ShaderFilePath = C_PathManager::SF_Get_Instance()->MF_Get_ResourcePath_s() + _Path;

#ifdef _DEBUG	// �ڵ尳��; ������, ���� �� �ʱ�ȭ 2ȸ -> ���� �� �ʱ�ȭ
	UINT Flag = D3DCOMPILE_DEBUG;
#else
	UINT Flag = 0;
#endif

	if (FAILED(D3DCompileFromFile(T_ShaderFilePath.c_str()
		, nullptr
		, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _HLSL_Function.c_str()
		, "cs_5_0"			// cs_5_0; Compute Shader, Shader Model 5.0
		, Flag
		, 0
		, CP_DX_M_ComputeShaderBlob.GetAddressOf()
		, CP_DX_M_ErrorBlob.GetAddressOf())))
	{
		// ������ �����ϸ� �޼��� �ڽ��� ������ ���г��� ����
		if (nullptr != CP_DX_M_ErrorBlob)
		{
			// ErrorBlob ���ڿ� ��������
			char* T_Char_s_Ansi = (char*)CP_DX_M_ErrorBlob->GetBufferPointer();
			string T_ErrorMassage_Ansi = T_Char_s_Ansi;

			// ���ڿ� ��ȯ: ANSI -> WideLiteral
			wstring T_ErrorMassage = { T_ErrorMassage_Ansi.begin(), T_ErrorMassage_Ansi.end() };
			const wchar_t* T_ErrorLiteralTitle = T_ErrorMassage.c_str();

			T_ErrorMassage += L"in C_ComputeShader::MF_Create_ComputeShader(), D3DCompileFromFile() Failed";
			const wchar_t* T_ErrorLiteralMassage = T_ErrorMassage.c_str();

			// �޽��� �˾�
			POPUP(T_ErrorLiteralTitle, T_ErrorLiteralMassage)
		}
		else
		{
			POPUP(L"D3DCompileFromFile() Failed", L"in C_ComputeShader::MF_Create_ComputeShader(), D3DCompileFromFile() Failed")
		}
	}
	
	if (FAILED(C_Device::SF_Get_Instance()->MF_Get_Device()->CreateComputeShader(CP_DX_M_ComputeShaderBlob->GetBufferPointer()
		, CP_DX_M_ComputeShaderBlob->GetBufferSize()
		, nullptr
		, CP_DX_M_ComputeShader.GetAddressOf())))
	{
		POPUP(L"CreateComputeShader() Failed", L"in C_ComputeShader::MF_Create_ComputeShader(), CreateComputeShader() Failed")

	}
}

void C_ComputeShader::MF_Dispatch()
{
	MF_Bind_ComputeShader();

	MF_Calculate_GroupXYZ();

	// ������� ������ۿ� ���� �� CS ���ε�
	static C_ConstantBuffer* P_T_ConstantBuffer = C_Device::SF_Get_Instance()->MF_Get_ConstantBuffer(E_CONSTANTBUFFER_TYPE::_CONSTANTBUFFER_MATERIAL);
	P_T_ConstantBuffer->MF_Set_ConstantBufferByData(&DS_M_MaterialConstant, sizeof(DS_MaterialConstant));
	P_T_ConstantBuffer->MF_Bind_ConstantBufferToComputeShaderOnly();

	// ��ǻƮ ���̴� ���ε� �� ����
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->CSSetShader(CP_DX_M_ComputeShader.Get(), nullptr, 0);
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->Dispatch(SDK_M_GroupCountX, SDK_M_GroupCountY, SDK_M_GroupCountZ);
	
	// ���ҽ� �� ���̴� Ŭ����
	MF_UnBind_ComputeShader();
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->CSSetShader(nullptr, nullptr, 0);
}

void C_ComputeShader::MF_Calculate_GroupXYZ()
{
}