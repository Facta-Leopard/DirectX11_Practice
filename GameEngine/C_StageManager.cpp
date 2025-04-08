#include "pch.h"
#include "C_StageManager.h"

C_StageManager::C_StageManager()
{

}

C_StageManager::~C_StageManager()
{

}

void C_StageManager::Initialize()
{
	P_M_CurrentStage->MF_Prepare();
}

void C_StageManager::Update()
{
	E_STAGE_STATE T_STAGE_STATE = P_M_CurrentStage->MF_Get_StageState();

	if (T_STAGE_STATE)
	{
		P_M_CurrentStage->MF_Step();
		P_M_CurrentStage->MF_StepAfter();
	}
}
