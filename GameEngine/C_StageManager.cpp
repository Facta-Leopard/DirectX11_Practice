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
		return E_FAIL;
	}
	P_M_CurrentStage->MF_Prepare();

	// �ٸ� �����ڿ��� ���ϼ��� ���� HRESULT �� ��ȯ ���
	return S_OK;
}

void C_StageManager::MF_Update()
{
	if (nullptr == P_M_CurrentStage)					// ����ڵ�; ���⼭ ������ ������ �������Ƿ�, ����, �������� �ٽ� üũ �ʿ�
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
