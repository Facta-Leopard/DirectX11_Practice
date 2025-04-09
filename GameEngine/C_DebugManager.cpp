#include "pch.h"
#include "C_DebugManager.h"

#include "C_TimeManager.h"

C_DebugManager::C_DebugManager()
	: M_IsDebugSrcreen(true)
{

}

C_DebugManager::~C_DebugManager()
{

}

HRESULT C_DebugManager::MF_Initialize()
{
	return E_NOTIMPL;
}

void C_DebugManager::MF_Update()
{
	MF_DebugRender();
}

void C_DebugManager::MF_DebugRender()
{



}
