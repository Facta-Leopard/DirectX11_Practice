// LNK2005 ���� ������

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


//// RVO ����
Vector3 SF_Get_ScaleVector3FromMatrix(const Matrix& _Matrix)
{
	return Vector3(
		sqrtf((_Matrix._11 * _Matrix._11) + (_Matrix._21 * _Matrix._21) + (_Matrix._31 * _Matrix._31)),
		sqrtf((_Matrix._12 * _Matrix._12) + (_Matrix._22 * _Matrix._22) + (_Matrix._32 * _Matrix._32)),
		sqrtf((_Matrix._13 * _Matrix._13) + (_Matrix._23 * _Matrix._13) + (_Matrix._33 * _Matrix._33))
	);
}


// ��Ʈ�������� ���⺤�� �̾Ƴ���
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


//// ��Ʈ���� �����ϸ� ����
//// ������ ������ �ͼ����� �ʴ�.
void GF_Set_ScaleToMatrix(Matrix& _Matrix, const Vector3& V_Scale)
{
	// X�� ���� ���� (Right)
	_Matrix._11 *= V_Scale.x;
	_Matrix._12 *= V_Scale.x;
	_Matrix._13 *= V_Scale.x;

	// Y�� ���� ���� (Up)
	_Matrix._21 *= V_Scale.y;
	_Matrix._22 *= V_Scale.y;
	_Matrix._23 *= V_Scale.y;

	// Z�� ���� ���� (Look)
	_Matrix._31 *= V_Scale.z;
	_Matrix._32 *= V_Scale.z;
	_Matrix._33 *= V_Scale.z;

	// ����! _41, _42, _43�� ��ġ ���� ������ �־ �ǵ帮�� ������� ���ϱ� ���� ����
}


// ���ڿ� ��ȯ���� �Լ�
//// wstring -> string ��ȯ�Լ�
string GF_ConvertWStringToString_WinAPI(const wstring& _wstring)
{
	// ��ȯ�� �ʿ��� ���ڿ� ���� ���
	int string_T_Size = WideCharToMultiByte(CP_UTF8, 0, _wstring.c_str(), -1, nullptr, 0, nullptr, nullptr);

	// ���ڿ� ������ŭ string ���� ����
	string string_T(string_T_Size, 0);

	// ��ȯ
	WideCharToMultiByte(CP_UTF8, 0, _wstring.c_str(), -1, &string_T[0], string_T_Size, nullptr, nullptr);

	return string_T;
}

//// string -> wsting ��ȯ�Լ�
wstring GF_ConvertStringToWString_WinAPI(const string& _string)
{
	// ��ȯ�� �ʿ��� ���ڿ� ���� ���
	int wstring_T_Size = MultiByteToWideChar(CP_UTF8, 0, _string.c_str(), -1, nullptr, 0);

	// ���ڿ� ������ŭ wstring ���� ����
	wstring wstring_T(wstring_T_Size, 0);

	// ��ȯ
	MultiByteToWideChar(CP_UTF8, 0, _string.c_str(), -1, &wstring_T[0], wstring_T_Size);

	return wstring_T;
}