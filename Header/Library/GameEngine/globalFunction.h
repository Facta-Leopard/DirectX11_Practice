#pragma once

#include "pch.h"

// inline�� ���� �߸��� �ν��� ��������
// inline�� .cpp���̵� ��ŷ�� �� �ְ� �ϴ� �Ͱ� �����Ϸ� ����ȭ�� �� ������ �־���
// �� �Լ��� .cpp ���� �� �� �ֵ��� �ϴ� inline �Լ�
inline bool GF_Toggle(bool _input)
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