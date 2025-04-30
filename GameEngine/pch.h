// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가

#include "global.h"

#include "define.h"

// 메모리 참조 해제관련
#include <memory>
using namespace std;

// DirectX 라이브러리 링크
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>
#include <DirectXMath.h>
using namespace DirectX;
using namespace DirectX::PackedVector;

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")

// STL
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <string>
using namespace std;


// 행렬관련
#include "../GameEngine/SimpleMath.h"
using namespace DirectX::SimpleMath;

// DirectxTex 라이브러리 링크
#include <DirectxTex/DirectXTex.h>
#include <DirectxTex/DirectXTex.inl>

#ifndef _DEBUG
#pragma comment(lib, "DirectxTex/DirectXTex.lib")
#else
#pragma comment(lib, "DirectxTex/DirectXTex_debug.lib")
#endif

// 관리자
#include "C_InputManager.h"
#include "C_PathManager.h"
#include "C_TimeManager.h"
#include "C_ResourceManager.h"
#include "C_CollisionManager.h"
#include "C_StageManager.h"
#include "C_RenderManager.h"
#ifdef _DEBUG
#include "C_DebugManager.h"
#endif // DEBUG
#include "C_TaskManager.h"

// Resourece
#include "struct.h"

#include "C_Entity.h"

#include "C_Object.h"

#include "component.h"

#include "C_Device.h"

#include "C_GameEngine.h"

#endif //PCH_H
