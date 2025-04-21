#include "pch.h"
#include "C_GraphicShader.h"

C_GraphicShader::C_GraphicShader()
	: C_Resource(_GRAPHIC_SHADER)

	, CP_DX_M_ErrorBlob{}

	, CP_DX_M_InputLayout{}
	, DX_M_PrimitiveTopology{}

	, CP_DX_M_VertexShader{}
	, CP_DX_M_VertexShaderBlob{}

	, CP_DX_M_GeometryShader{}
	, CP_DX_M_GeometryShaderBlob{}

	, E_M_RasterizerState(_RASTERIZER_CULL_BACK)		// �޸� �ø��� �⺻������ �Ͽ���

	, CP_DX_M_PixelShader{}
	, CP_DX_M_PixelShaderBlob{}

	, E_M_DepthStencilState{}
	, E_M_BlendState(_BLEND_DEFAULT)					// �� ���� ���� �⺻������ �Ͽ���

	, E_M_DomainState(_DOMAIN_QPAQUE)					// ������ ���� �⺻������ �Ͽ���
{
}

C_GraphicShader::~C_GraphicShader()
{
}

void C_GraphicShader::MF_Bind_GraphicShader()
{
	// Graphic Pipeline
	//// IA: Input Assembler
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->IASetInputLayout(CP_DX_M_InputLayout.Get());
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->IASetPrimitiveTopology(DX_M_PrimitiveTopology);

	//// VS: Vertex Shader
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->VSSetShader(CP_DX_M_VertexShader.Get(), nullptr, 0);

	//// GS: Geometry Shader(optional)
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->GSSetShader(CP_DX_M_GeometryShader.Get(), nullptr, 0);

	//// RS: Rasterizer Stage
	ComPtr<ID3D11RasterizerState> CP_DX_T_RasterizerState = C_Device::SF_Get_Instance()->MF_Get_RasterizerState(E_M_RasterizerState);				// ����! ID3D11RasterizerState�� �߻�ȭ�� ���� �������̽��̹Ƿ� ���� ������ �ȵ�!; �׷��Ƿ�, ComPtr<ID3D11RasterizerState>�� ��ȯ�� �޴� �������� ��
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->RSSetState(CP_DX_T_RasterizerState.Get());

	//// PS: Pixel Shader
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->PSSetShader(CP_DX_M_PixelShader.Get(), nullptr, 0);

	//// OM: Output Merger
	ComPtr<ID3D11DepthStencilState> CP_DX_T_DepthStencilState = C_Device::SF_Get_Instance()->MF_Get_DepthStencilState(E_M_DepthStencilState);		// ����! ID3D11DepthStencilState�� �߻�ȭ�� ���� �������̽��̹Ƿ� ���� ������ �ȵ�!; �׷��Ƿ�, ComPtr<ID3D11DepthStencilState>�� ��ȯ�� �޴� �������� ��
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->OMSetDepthStencilState(CP_DX_T_DepthStencilState.Get(), 0);

	ComPtr<ID3D11BlendState> CP_DX_T_BlendState = C_Device::SF_Get_Instance()->MF_Get_BlendState(E_M_BlendState);									// ����! ID3D11BlendState�� �߻�ȭ�� ���� �������̽��̹Ƿ� ���� ������ �ȵ�!; �׷��Ƿ�, ComPtr<ID3D11BlendState>�� ��ȯ�� �޴� �������� ��
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->OMSetBlendState(CP_DX_T_BlendState.Get(), nullptr, 0xffffffff);
}

void C_GraphicShader::MF_Create_VertexShader(const wstring& _Path, const string& _HLSL_Function)
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
		, "vs_5_0"			// vs_5_0; Vertex Shader, Shader Model 5.0
		, Flag
		, 0
		, CP_DX_M_VertexShaderBlob.GetAddressOf()
		, CP_DX_M_ErrorBlob.GetAddressOf())))
	{
		// ������ �����ϸ� �޼��� �ڽ��� ������ ���г��� ����
		if (nullptr != CP_DX_M_ErrorBlob)
		{
			// ErrorBlob ���ڿ� ��������
			char* T_Char_s_Ansi = (char*)CP_DX_M_ErrorBlob->GetBufferPointer();
			string T_ErrorMassage_Ansi = T_Char_s_Ansi;
			
			// ���ڿ� ��ȯ: ANSI -> WideLiteral
			wstring T_ErrorMassage = {T_ErrorMassage_Ansi.begin(), T_ErrorMassage_Ansi.end()};
			const wchar_t* T_ErrorLiteralTitle= T_ErrorMassage.c_str();

			T_ErrorMassage += L"in C_GraphicShader::MF_Create_VertexShader(), D3DCompileFromFile() Failed";
			const wchar_t* T_ErrorLiteralMassage = T_ErrorMassage.c_str();

			// �޽��� �˾�
			POPUP(T_ErrorLiteralTitle, T_ErrorLiteralMassage)
		}
		else
		{
			POPUP(L"D3DCompileFromFile() Failed", L"in C_GraphicShader::MF_Create_VertexShader(), D3DCompileFromFile() Failed")
		}
	}

	if (FAILED(C_Device::SF_Get_Instance()->MF_Get_Device()->CreateVertexShader(CP_DX_M_VertexShaderBlob->GetBufferPointer()
		, CP_DX_M_VertexShaderBlob->GetBufferSize()
		, nullptr
		, CP_DX_M_VertexShader.GetAddressOf())))
	{
		POPUP(L"CreateVertexShader() Failed", L"in C_GraphicShader::MF_Create_VertexShader(), CreateVertexShader() Failed")
	}


	// Input Layout �� ���� ����; ����! HLSL�� IMGUI�� ����Ǵ� Semantic�� ���⿡ �ٰ��ؼ� �ٲ� ��!
	D3D11_INPUT_ELEMENT_DESC DX_T_InputLayoutDesc[3] = {};

	// GPU�� ����Ǵ� SemanticName; ����! ANSI��!
	DX_T_InputLayoutDesc[0].SemanticName = "SEMANTIC_POSITION";				// HLSL���� �� �ڷ��� Semantic
	// ���� �̸��� ���� ��� �����ϴ� �ε���
	DX_T_InputLayoutDesc[0].SemanticIndex = 0;								// �ν��Ͻ̿� ���� �ѹ����� ������ �� ���̱⵵ ��
	// ������ ����(����): DXGI_FORMAT_R32G32B32_FLOAT -> Vector3, DXGI_FORMAT_R32G32_FLOAT -> Vector2)), DXGI_FORMAT_R8G8B8A8_UNORM -> RGBA, DXGI_FORMAT_R32_UINT -> UINT
	DX_T_InputLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;			// Vector3	
	// �����Ͱ� ��� �ִ� ���� ���� ��ȣ
	DX_T_InputLayoutDesc[0].InputSlot = 0;									// ���� ���۸� ����ϹǷ� 0���� ����
	// SemanticName�� Offset ��ġ(����Ʈ ����)
	DX_T_InputLayoutDesc[0].AlignedByteOffset = 0;							// SEMANTIC_POSITION�� ����ü ���ο��� �� ��°�� ��ġ�ϴ���(��, ��ġ�� ����Ʈ ����)
	// ���ؼ���: D3D11_INPUT_PER_VERTEX_DATA -> ��������, D3D11_INPUT_PER_INSTANCE_DATA -> �ν��Ͻ� ����
	DX_T_InputLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;	// D3D11_INPUT_PER_VERTEX_DATA -> �������� �ٲ��
	// �������� ������ ���� �� �� ������ ���� ���� ; 0�� ���, �׳� ��� ���� ���� ���ٴ� �ǹ�
	DX_T_InputLayoutDesc[0].InstanceDataStepRate = 0;						// �׳� ��� ���� ���� ����

	// GPU�� ����Ǵ� SemanticName; ����! ANSI��!
	DX_T_InputLayoutDesc[0].SemanticName = "SEMANTIC_UV";					// HLSL���� �� �ڷ��� Semantic
	// ���� �̸��� ���� ��� �����ϴ� �ε���
	DX_T_InputLayoutDesc[0].SemanticIndex = 0;								// �ν��Ͻ̿� ���� �ѹ����� ������ �� ���̱⵵ ��
	// ������ ����(����): DXGI_FORMAT_R32G32B32_FLOAT -> Vector3, DXGI_FORMAT_R32G32_FLOAT -> Vector2)), DXGI_FORMAT_R8G8B8A8_UNORM -> RGBA, DXGI_FORMAT_R32_UINT -> UINT
	DX_T_InputLayoutDesc[0].Format = DXGI_FORMAT_R32G32_FLOAT;				// Vector2	
	// �����Ͱ� ��� �ִ� ���� ���� ��ȣ
	DX_T_InputLayoutDesc[0].InputSlot = 0;									// ���� ���۸� ����ϹǷ� 0���� ����
	// SemanticName�� Offset ��ġ(����Ʈ ����)
	DX_T_InputLayoutDesc[0].AlignedByteOffset = 12;							// SEMANTIC_UV�� ����ü ���ο��� �� ��°�� ��ġ�ϴ���(��, ��ġ�� ����Ʈ ����)
	// ���ؼ���: D3D11_INPUT_PER_VERTEX_DATA -> ��������, D3D11_INPUT_PER_INSTANCE_DATA -> �ν��Ͻ� ����
	DX_T_InputLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;	// D3D11_INPUT_PER_VERTEX_DATA -> �������� �ٲ��
	// �������� ������ ���� �� �� ������ ���� ���� ; 0�� ���, �׳� ��� ���� ���� ���ٴ� �ǹ�
	DX_T_InputLayoutDesc[0].InstanceDataStepRate = 0;						// �׳� ��� ���� ���� ����

	// GPU�� ����Ǵ� SemanticName; ����! ANSI��!
	DX_T_InputLayoutDesc[0].SemanticName = "SEMANTIC_COLOR";				// HLSL���� �� �ڷ��� Semantic
	// ���� �̸��� ���� ��� �����ϴ� �ε���
	DX_T_InputLayoutDesc[0].SemanticIndex = 0;								// �ν��Ͻ̿� ���� �ѹ����� ������ �� ���̱⵵ ��
	// ������ ����(����): DXGI_FORMAT_R32G32B32_FLOAT -> Vector3, DXGI_FORMAT_R32G32_FLOAT -> Vector2)), DXGI_FORMAT_R8G8B8A8_UNORM -> RGBA, DXGI_FORMAT_R32_UINT -> UINT
	DX_T_InputLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;		// Vector4
	// �����Ͱ� ��� �ִ� ���� ���� ��ȣ
	DX_T_InputLayoutDesc[0].InputSlot = 0;									// ���� ���۸� ����ϹǷ� 0���� ����
	// SemanticName�� Offset ��ġ(����Ʈ ����)
	DX_T_InputLayoutDesc[0].AlignedByteOffset = 28;							// SEMANTIC_COLOR�� ����ü ���ο��� �� ��°�� ��ġ�ϴ���(��, ��ġ�� ����Ʈ ����)
	// ���ؼ���: D3D11_INPUT_PER_VERTEX_DATA -> ��������, D3D11_INPUT_PER_INSTANCE_DATA -> �ν��Ͻ� ����
	DX_T_InputLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;	// D3D11_INPUT_PER_VERTEX_DATA -> �������� �ٲ��
	// �������� ������ ���� �� �� ������ ���� ���� ; 0�� ���, �׳� ��� ���� ���� ���ٴ� �ǹ�
	DX_T_InputLayoutDesc[0].InstanceDataStepRate = 0;						// �׳� ��� ���� ���� ����

	if (FAILED(C_Device::SF_Get_Instance()->MF_Get_Device()->CreateInputLayout(DX_T_InputLayoutDesc, 3
		, CP_DX_M_VertexShaderBlob->GetBufferPointer()
		, CP_DX_M_VertexShaderBlob->GetBufferSize()
		, CP_DX_M_InputLayout.GetAddressOf())))
	{
		POPUP(L"CreateInputLayout() Failed", L"in C_GraphicShader::MF_Create_VertexShader(), CreateInputLayout() Failed")
	}
}

void C_GraphicShader::MF_Create_GeometryShader(const wstring& _Path, const string& _HLSL_Function)
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
		, "gs_5_0"			// gs_5_0; Geometry Shader, Shader Model 5.0
		, Flag, 0
		, CP_DX_M_GeometryShaderBlob.GetAddressOf()
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

			T_ErrorMassage += L"in C_GraphicShader::MF_Create_GeometryShader(), D3DCompileFromFile() Failed";
			const wchar_t* T_ErrorLiteralMassage = T_ErrorMassage.c_str();

			// �޽��� �˾�
			POPUP(T_ErrorLiteralTitle, T_ErrorLiteralMassage)
		}
		else
		{
			POPUP(L"D3DCompileFromFile() Failed", L"in C_GraphicShader::MF_Create_GeometryShader(), D3DCompileFromFile() Failed")
		}
	}

	if (FAILED(C_Device::SF_Get_Instance()->MF_Get_Device()->CreateGeometryShader(CP_DX_M_GeometryShaderBlob->GetBufferPointer()
		, CP_DX_M_GeometryShaderBlob->GetBufferSize()
		, nullptr
		, CP_DX_M_GeometryShader.GetAddressOf())))
	{
		POPUP(L"CreateGeometryShader() Failed", L"in C_GraphicShader::MF_Create_GeometryShader(), CreateGeometryShader() Failed")

	}
}

void C_GraphicShader::MF_Create_PixelShader(const wstring& _Path, const string& _HLSL_Function)
{
	wstring T_ShaderFilePath = C_PathManager::SF_Get_Instance()->MF_Get_ResourcePath_s() + _Path;

	UINT Flag = 0;

#ifdef _DEBUG
	Flag = D3DCOMPILE_DEBUG;
#endif

	if (FAILED(D3DCompileFromFile(T_ShaderFilePath.c_str()
		, nullptr
		, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _HLSL_Function.c_str()
		, "ps_5_0"			// ps_5_0; Pixel Shader, Shader Model 5.0
		, Flag
		, 0
		, CP_DX_M_PixelShaderBlob.GetAddressOf()
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

			T_ErrorMassage += L"in C_GraphicShader::MF_Create_PixelShader(), D3DCompileFromFile() Failed";
			const wchar_t* T_ErrorLiteralMassage = T_ErrorMassage.c_str();

			// �޽��� �˾�
			POPUP(T_ErrorLiteralTitle, T_ErrorLiteralMassage)
		}
		else
		{
			POPUP(L"D3DCompileFromFile() Failed", L"in C_GraphicShader::MF_Create_PixelShader(), D3DCompileFromFile() Failed")
		}
	}

	if (FAILED(C_Device::SF_Get_Instance()->MF_Get_Device()->CreatePixelShader(CP_DX_M_PixelShaderBlob->GetBufferPointer()
		, CP_DX_M_PixelShaderBlob->GetBufferSize()
		, nullptr
		, CP_DX_M_PixelShader.GetAddressOf())))
	{
		POPUP(L"CreatePixelShader() Failed", L"in C_GraphicShader::MF_Create_PixelShader(), CreatePixelShader() Failed")
	}
}
