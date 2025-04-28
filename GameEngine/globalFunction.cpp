// LNK2005 에러 방지용

#include "pch.h"

#include "globalFunction.h"
bool GF_Toggle(bool _input)
{
	if (_input)
	{
		return false;
	}
	else
	{
		return true;
	}
}


//// RVO 버전
Vector3 SF_Get_ScaleVector3FromMatrix(const Matrix& _Matrix)
{
	return Vector3(
		sqrtf((_Matrix._11 * _Matrix._11) + (_Matrix._21 * _Matrix._21) + (_Matrix._31 * _Matrix._31)),
		sqrtf((_Matrix._12 * _Matrix._12) + (_Matrix._22 * _Matrix._22) + (_Matrix._32 * _Matrix._32)),
		sqrtf((_Matrix._13 * _Matrix._13) + (_Matrix._23 * _Matrix._13) + (_Matrix._33 * _Matrix._33))
	);
}


// 매트릭스에서 방향벡터 뽑아내기
Vector3 GF_Get_DirectionVector3FromMatrix(const Matrix& _Matrix, E_DIRECTION_TYPE _DIRECTIONTYPE)
{
	switch (_DIRECTIONTYPE)
	{
	case _DIRECTION_RIGHT:
		return (Vector3)(_Matrix._11, _Matrix._12, _Matrix._13);
		break;
	case _DIRECTION_UP:
		return (Vector3)(_Matrix._21, _Matrix._22, _Matrix._23);
		break;
	case _DIRECTION_FRONT:
		return (Vector3)(_Matrix._31, _Matrix._32, _Matrix._33);
		break;
	default:
		return (Vector3)(_Matrix._31, _Matrix._32, _Matrix._33);
		break;
	}
}


//// 매트릭스 스케일만 조정
//// 참조는 아직도 익숙하지 않다.
void GF_Set_ScaleToMatrix(Matrix& _Matrix, const Vector3& V_Scale)
{
	// X축 방향 벡터 (Right)
	_Matrix._11 *= V_Scale.x;
	_Matrix._12 *= V_Scale.x;
	_Matrix._13 *= V_Scale.x;

	// Y축 방향 벡터 (Up)
	_Matrix._21 *= V_Scale.y;
	_Matrix._22 *= V_Scale.y;
	_Matrix._23 *= V_Scale.y;

	// Z축 방향 벡터 (Look)
	_Matrix._31 *= V_Scale.z;
	_Matrix._32 *= V_Scale.z;
	_Matrix._33 *= V_Scale.z;

	// 유의! _41, _42, _43은 위치 값과 관련이 있어서 건드리면 대형사고 나니까 절대 조심
}


// 문자열 변환관련 함수
//// wstring -> string 변환함수
string GF_ConvertWStringToString_WinAPI(const wstring& _wstring)
{
	// 변환에 필요한 문자열 개수 계산
	int string_T_Size = WideCharToMultiByte(CP_UTF8, 0, _wstring.c_str(), -1, nullptr, 0, nullptr, nullptr);

	// 문자열 개수만큼 string 버퍼 생성
	string string_T(string_T_Size, 0);

	// 변환
	WideCharToMultiByte(CP_UTF8, 0, _wstring.c_str(), -1, &string_T[0], string_T_Size, nullptr, nullptr);

	return string_T;
}

//// string -> wsting 변환함수
wstring GF_ConvertStringToWString_WinAPI(const string& _string)
{
	// 변환에 필요한 문자열 개수 계산
	int wstring_T_Size = MultiByteToWideChar(CP_UTF8, 0, _string.c_str(), -1, nullptr, 0);

	// 문자열 개수만큼 wstring 버퍼 생성
	wstring wstring_T(wstring_T_Size, 0);

	// 변환
	MultiByteToWideChar(CP_UTF8, 0, _string.c_str(), -1, &wstring_T[0], wstring_T_Size);

	return wstring_T;
}