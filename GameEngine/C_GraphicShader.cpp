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

	, E_M_RasterizerState(_RASTERIZER_CULL_BACK)		// 뒷면 컬링을 기본값으로 하였음

	, CP_DX_M_PixelShader{}
	, CP_DX_M_PixelShaderBlob{}

	, E_M_DepthStencilState{}
	, E_M_BlendState(_BLEND_DEFAULT)					// 안 섞는 것을 기본값으로 하였음

	, E_M_DomainState(_DOMAIN_QPAQUE)					// 불투명 값을 기본값으로 하였음
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
	ComPtr<ID3D11RasterizerState> CP_DX_T_RasterizerState = C_Device::SF_Get_Instance()->MF_Get_RasterizerState(E_M_RasterizerState);				// 유의! ID3D11RasterizerState는 추상화에 따른 인터페이스이므로 직접 대입이 안됨!; 그러므로, ComPtr<ID3D11RasterizerState>값 반환을 받는 형식으로 함
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->RSSetState(CP_DX_T_RasterizerState.Get());

	//// PS: Pixel Shader
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->PSSetShader(CP_DX_M_PixelShader.Get(), nullptr, 0);

	//// OM: Output Merger
	ComPtr<ID3D11DepthStencilState> CP_DX_T_DepthStencilState = C_Device::SF_Get_Instance()->MF_Get_DepthStencilState(E_M_DepthStencilState);		// 유의! ID3D11DepthStencilState는 추상화에 따른 인터페이스이므로 직접 대입이 안됨!; 그러므로, ComPtr<ID3D11DepthStencilState>값 반환을 받는 형식으로 함
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->OMSetDepthStencilState(CP_DX_T_DepthStencilState.Get(), 0);

	ComPtr<ID3D11BlendState> CP_DX_T_BlendState = C_Device::SF_Get_Instance()->MF_Get_BlendState(E_M_BlendState);									// 유의! ID3D11BlendState는 추상화에 따른 인터페이스이므로 직접 대입이 안됨!; 그러므로, ComPtr<ID3D11BlendState>값 반환을 받는 형식으로 함
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->OMSetBlendState(CP_DX_T_BlendState.Get(), nullptr, 0xffffffff);
}

void C_GraphicShader::MF_Create_VertexShader(const wstring& _Path, const string& _HLSL_Function)
{
	wstring T_ShaderFilePath = C_PathManager::SF_Get_Instance()->MF_Get_ResourcePath_s() + _Path;

#ifdef _DEBUG	// 코드개선; 디버깅시, 선언 및 초기화 2회 -> 선언 및 초기화
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
		// 컴파일 실패하면 메세지 박스에 컴파일 실패내용 띄우기
		if (nullptr != CP_DX_M_ErrorBlob)
		{
			// ErrorBlob 문자열 꺼내오기
			char* T_Char_s_Ansi = (char*)CP_DX_M_ErrorBlob->GetBufferPointer();
			string T_ErrorMassage_Ansi = T_Char_s_Ansi;
			
			// 문자열 변환: ANSI -> WideLiteral
			wstring T_ErrorMassage = {T_ErrorMassage_Ansi.begin(), T_ErrorMassage_Ansi.end()};
			const wchar_t* T_ErrorLiteralTitle= T_ErrorMassage.c_str();

			T_ErrorMassage += L"in C_GraphicShader::MF_Create_VertexShader(), D3DCompileFromFile() Failed";
			const wchar_t* T_ErrorLiteralMassage = T_ErrorMassage.c_str();

			// 메시지 팝업
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


	// Input Layout 도 같이 생성; 유의! HLSL과 IMGUI에 연결되는 Semantic도 여기에 근거해서 바꿀 것!
	D3D11_INPUT_ELEMENT_DESC DX_T_InputLayoutDesc[3] = {};

	// GPU로 연결되는 SemanticName; 유의! ANSI임!
	DX_T_InputLayoutDesc[0].SemanticName = "SEMANTIC_POSITION";				// HLSL에서 쓸 자료형 Semantic
	// 동일 이름이 있을 경우 구분하는 인덱스
	DX_T_InputLayoutDesc[0].SemanticIndex = 0;								// 인스턴싱에 따른 넘버링을 구분할 때 쓰이기도 함
	// 데이터 포맷(형식): DXGI_FORMAT_R32G32B32_FLOAT -> Vector3, DXGI_FORMAT_R32G32_FLOAT -> Vector2)), DXGI_FORMAT_R8G8B8A8_UNORM -> RGBA, DXGI_FORMAT_R32_UINT -> UINT
	DX_T_InputLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;			// Vector3	
	// 데이터가 들어 있는 버퍼 슬롯 번호
	DX_T_InputLayoutDesc[0].InputSlot = 0;									// 단일 버퍼만 사용하므로 0으로 통일
	// SemanticName의 Offset 위치(바이트 단위)
	DX_T_InputLayoutDesc[0].AlignedByteOffset = 0;							// SEMANTIC_POSITION이 구조체 내부에서 몇 번째에 위치하는지(단, 위치는 바이트 기준)
	// 기준설정: D3D11_INPUT_PER_VERTEX_DATA -> 정점기준, D3D11_INPUT_PER_INSTANCE_DATA -> 인스턴싱 기준
	DX_T_InputLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;	// D3D11_INPUT_PER_VERTEX_DATA -> 정점마다 바뀌도록
	// 기준으로 설정된 것을 몇 개 단위로 쓸지 설정 ; 0일 경우, 그냥 계속 값은 값을 쓴다는 의미
	DX_T_InputLayoutDesc[0].InstanceDataStepRate = 0;						// 그냥 계속 값은 값을 쓴다

	// GPU로 연결되는 SemanticName; 유의! ANSI임!
	DX_T_InputLayoutDesc[0].SemanticName = "SEMANTIC_UV";					// HLSL에서 쓸 자료형 Semantic
	// 동일 이름이 있을 경우 구분하는 인덱스
	DX_T_InputLayoutDesc[0].SemanticIndex = 0;								// 인스턴싱에 따른 넘버링을 구분할 때 쓰이기도 함
	// 데이터 포맷(형식): DXGI_FORMAT_R32G32B32_FLOAT -> Vector3, DXGI_FORMAT_R32G32_FLOAT -> Vector2)), DXGI_FORMAT_R8G8B8A8_UNORM -> RGBA, DXGI_FORMAT_R32_UINT -> UINT
	DX_T_InputLayoutDesc[0].Format = DXGI_FORMAT_R32G32_FLOAT;				// Vector2	
	// 데이터가 들어 있는 버퍼 슬롯 번호
	DX_T_InputLayoutDesc[0].InputSlot = 0;									// 단일 버퍼만 사용하므로 0으로 통일
	// SemanticName의 Offset 위치(바이트 단위)
	DX_T_InputLayoutDesc[0].AlignedByteOffset = 12;							// SEMANTIC_UV이 구조체 내부에서 몇 번째에 위치하는지(단, 위치는 바이트 기준)
	// 기준설정: D3D11_INPUT_PER_VERTEX_DATA -> 정점기준, D3D11_INPUT_PER_INSTANCE_DATA -> 인스턴싱 기준
	DX_T_InputLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;	// D3D11_INPUT_PER_VERTEX_DATA -> 정점마다 바뀌도록
	// 기준으로 설정된 것을 몇 개 단위로 쓸지 설정 ; 0일 경우, 그냥 계속 값은 값을 쓴다는 의미
	DX_T_InputLayoutDesc[0].InstanceDataStepRate = 0;						// 그냥 계속 값은 값을 쓴다

	// GPU로 연결되는 SemanticName; 유의! ANSI임!
	DX_T_InputLayoutDesc[0].SemanticName = "SEMANTIC_COLOR";				// HLSL에서 쓸 자료형 Semantic
	// 동일 이름이 있을 경우 구분하는 인덱스
	DX_T_InputLayoutDesc[0].SemanticIndex = 0;								// 인스턴싱에 따른 넘버링을 구분할 때 쓰이기도 함
	// 데이터 포맷(형식): DXGI_FORMAT_R32G32B32_FLOAT -> Vector3, DXGI_FORMAT_R32G32_FLOAT -> Vector2)), DXGI_FORMAT_R8G8B8A8_UNORM -> RGBA, DXGI_FORMAT_R32_UINT -> UINT
	DX_T_InputLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;		// Vector4
	// 데이터가 들어 있는 버퍼 슬롯 번호
	DX_T_InputLayoutDesc[0].InputSlot = 0;									// 단일 버퍼만 사용하므로 0으로 통일
	// SemanticName의 Offset 위치(바이트 단위)
	DX_T_InputLayoutDesc[0].AlignedByteOffset = 28;							// SEMANTIC_COLOR이 구조체 내부에서 몇 번째에 위치하는지(단, 위치는 바이트 기준)
	// 기준설정: D3D11_INPUT_PER_VERTEX_DATA -> 정점기준, D3D11_INPUT_PER_INSTANCE_DATA -> 인스턴싱 기준
	DX_T_InputLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;	// D3D11_INPUT_PER_VERTEX_DATA -> 정점마다 바뀌도록
	// 기준으로 설정된 것을 몇 개 단위로 쓸지 설정 ; 0일 경우, 그냥 계속 값은 값을 쓴다는 의미
	DX_T_InputLayoutDesc[0].InstanceDataStepRate = 0;						// 그냥 계속 값은 값을 쓴다

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

#ifdef _DEBUG	// 코드개선; 디버깅시, 선언 및 초기화 2회 -> 선언 및 초기화
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
		// 컴파일 실패하면 메세지 박스에 컴파일 실패내용 띄우기
		if (nullptr != CP_DX_M_ErrorBlob)
		{
			// ErrorBlob 문자열 꺼내오기
			char* T_Char_s_Ansi = (char*)CP_DX_M_ErrorBlob->GetBufferPointer();
			string T_ErrorMassage_Ansi = T_Char_s_Ansi;

			// 문자열 변환: ANSI -> WideLiteral
			wstring T_ErrorMassage = { T_ErrorMassage_Ansi.begin(), T_ErrorMassage_Ansi.end() };
			const wchar_t* T_ErrorLiteralTitle = T_ErrorMassage.c_str();

			T_ErrorMassage += L"in C_GraphicShader::MF_Create_GeometryShader(), D3DCompileFromFile() Failed";
			const wchar_t* T_ErrorLiteralMassage = T_ErrorMassage.c_str();

			// 메시지 팝업
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
		// 컴파일 실패하면 메세지 박스에 컴파일 실패내용 띄우기
		if (nullptr != CP_DX_M_ErrorBlob)
		{
			// ErrorBlob 문자열 꺼내오기
			char* T_Char_s_Ansi = (char*)CP_DX_M_ErrorBlob->GetBufferPointer();
			string T_ErrorMassage_Ansi = T_Char_s_Ansi;

			// 문자열 변환: ANSI -> WideLiteral
			wstring T_ErrorMassage = { T_ErrorMassage_Ansi.begin(), T_ErrorMassage_Ansi.end() };
			const wchar_t* T_ErrorLiteralTitle = T_ErrorMassage.c_str();

			T_ErrorMassage += L"in C_GraphicShader::MF_Create_PixelShader(), D3DCompileFromFile() Failed";
			const wchar_t* T_ErrorLiteralMassage = T_ErrorMassage.c_str();

			// 메시지 팝업
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
