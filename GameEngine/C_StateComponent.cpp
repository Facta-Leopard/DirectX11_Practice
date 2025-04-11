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

void C_StateComponent::MF_Count_TimeLeft()
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
	if (0.f > M_TimeLeftToDie)
	{
		MF_Set_IsDelete(true);
	}

	if (0.f > M_TimeLeftToDie)
	{
		MF_Set_IsDie(true);
	}
}



