#include "pch.h"
#include "C_StageManager.h"

C_StageManager::C_StageManager()
	: P_M_CurrentStage(nullptr)
{

}

C_StageManager::~C_StageManager()
{

}

HRESULT C_StageManager::MF_Initialize()
{
	P_M_CurrentStage->MF_Prepare();

	// 다른 관리자와의 통일성을 위해 HRESULT 값 반환 사용
	return S_OK;
}

void C_StageManager::MF_Update()
{
	E_STAGE_STATE T_STAGE_STATE = P_M_CurrentStage->MF_Get_StageState();

	if (T_STAGE_STATE)
	{
		P_M_CurrentStage->MF_Step();
		P_M_CurrentStage->MF_StepAfter();
	}
}
