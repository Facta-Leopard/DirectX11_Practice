#pragma once

#include <Windows.h>
#include "framework.h"

#include <wrl/client.h>
using namespace Microsoft::WRL;

// �޸� ���� ��������
#include <memory>
using namespace std;

// DirectX ���̺귯�� ��ũ
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>
#include <DirectXMath.h>
using namespace DirectX;
using namespace DirectX::PackedVector;

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")

// ��İ���
#include "SimpleMath.h"
using namespace DirectX::SimpleMath;

// DirectxTex ���̺귯�� ��ũ
#include <DirectxTex/DirectXTex.h>
#include <DirectxTex/DirectXTex.inl>

#ifndef _DEBUG
#pragma comment(lib, "DirectxTex/DirectXTex.lib")
#else
#pragma comment(lib, "DirectxTex/DirectXTex_debug.lib")
#endif

// FMOD
#include <FMOD/fmod.h>
#include <FMOD/fmod.hpp>
#include <FMOD/fmod_codec.h>

#ifdef _DEBUG
#pragma comment(lib, "FMOD/fmodL64_vc.lib")
#else
#pragma comment(lib, "FMOD/fmod64_vc.lib")
#endif

// STL
#include <vector>
#include <list>
#include <map>
#include <string>
using namespace std;

// �� �� ����� ����
#include "define.h"

#include "enum.h"
#include "globalVariable.h"
#include "globalFunction.h"

#include "C_Singleton.h"