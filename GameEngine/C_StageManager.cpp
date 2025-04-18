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

	if (nullptr == P_M_CurrentStage)					// ����ڵ�
	{
		MF_Set_CurrentStage(P_M_Stage_s[_STAGE_0]);
	}
	P_M_CurrentStage->MF_Prepare();

	// �ٸ� �����ڿ��� ���ϼ��� ���� HRESULT �� ��ȯ ���
	return S_OK;
}

void C_StageManager::MF_Update()
{
	if (nullptr == P_M_CurrentStage)					// ����ڵ�; ����, �������� �ٽ� üũ �ʿ�
	{
			return;
	}
	E_STAGE_STATE T_STAGE_STATE = P_M_CurrentStage->MF_Get_StageState();

	if (T_STAGE_STATE)
	{
		P_M_CurrentStage->MF_Step();
		P_M_CurrentStage->MF_StepAfter();
	}
}

