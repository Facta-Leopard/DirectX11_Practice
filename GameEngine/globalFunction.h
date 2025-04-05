#pragma once

#include "pch.h"

// inline에 대한 잘못된 인식을 개선했음
// inline은 .cpp없이도 링킹할 수 있게 하는 것과 컴파일러 최적화의 두 종류가 있었음
// 이 함수는 .cpp 없이 쓸 수 있도록 하는 inline 함수
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