#include "pch.h"
#include "C_Stage.h"

C_Stage::C_Stage(E_STAGE_NUMBER _StageNumber)
	: C_Entity()
	, L_M_StageNumber(_StageNumber)
	, M_StageState(_STAGE_PLAY)
	, P_M_Group_s{}
{
	for (size_t i = 0; i < _GROUP_END; ++i)
	{
		P_M_Group_s[i] = new C_Group;
		P_M_Group_s[i]->MF_Set_GroupIndex((E_GROUP_INDEX)i);
	}
}

C_Stage::~C_Stage()
{
	DELETEALL_FIXEDARRAY_HEAP(P_M_Group_s, _GROUP_END)
}

void C_Stage::MF_Prepare()
{
	for (size_t i = 0; i < _GROUP_END; ++i)
	{
		if (nullptr == P_M_Group_s[i])				// 规绢内靛;
		{
			continue;
		}
		P_M_Group_s[i]->MF_Prepare();
	}
}

void C_Stage::MF_Step()
{
	for (size_t i = 0; i < _GROUP_END; ++i)
	{
		if (nullptr == P_M_Group_s[i])				// 规绢内靛
		{
			continue;
		}

		P_M_Group_s[i]->MF_Tick();
	}
}

void C_Stage::MF_StepAfter()
{
	for (size_t i = 0; i < _GROUP_END; ++i)
	{
		if (nullptr == P_M_Group_s[i])				// 规绢内靛
		{
			continue;
		}

		P_M_Group_s[i]->MF_TickAfter();
	}
}

void C_Stage::DetachGroups()
{
	for (size_t i = 0; i < _GROUP_END; ++i)
	{
		if (nullptr == P_M_Group_s[i])				// 规绢内靛
		{
			continue;
		}
		P_M_Group_s[i]->STL_P_M_AllObject.clear();
	}
}
