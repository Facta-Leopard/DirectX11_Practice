#include "pch.h"
#include "C_StateComponent.h"

C_StateComponent::C_StateComponent()
	: C_Component(_COMPONENT_SCRIPT)
	, M_IsDelete(false)
	, M_TimeLeftToDelete(0.f)
	, M_IsDie(false)
	, M_TimeLeftToDie(0.f)
{
}

C_StateComponent::~C_StateComponent()
{
}

void C_StateComponent::MF_Prepare()
{
}

void C_StateComponent::MF_ComponentTick()									// 유의! 오버헤드를 줄이기 위한 모듈화 설계임!
{
	MF_Count_TimeLeft();
}

void C_StateComponent::MF_ComponentTickAfter()								// 유의! 오버헤드를 줄이기 위한 모듈화 설계임!
{
	MF_Check_State();
}

void C_StateComponent::MF_Count_TimeLeft()									// 향후, 확장시에는 별도로 분기를 정리하는 것이 좋을 듯
{
	float T_DeltaTime = C_TimeManager::SF_Get_Instance()->MF_Get_DeltaTime();

	if (0 < M_TimeLeftToDelete)
	{
		M_TimeLeftToDelete -= T_DeltaTime;
	}
	if (0 < M_TimeLeftToDie)
	{
		M_TimeLeftToDie -= T_DeltaTime;
	}
}

void C_StateComponent::MF_Check_State()
{
	if (0.f > M_TimeLeftToDelete)							// 유의! 오버헤드 개선을 위해 분기로 처리; 향후, 상태가 늘어나면 다른 방법을 생각해보는 것도 좋을 듯
	{
		MF_Set_IsDelete(true);
	}
	else if (0.f > M_TimeLeftToDie)
	{
		MF_Set_IsDie(true);
	}
}



