#include "pch.h"
#include "C_Stage.h"

C_Stage::C_Stage(E_STAGE_NUMBER _StageNumber)
	: C_Entity()
	, L_E_M_StageNumber(_StageNumber)
	, E_M_StageState(_STAGE_PLAY)
	, P_M_Group_s{}
{
	for (int i = 0; i < (int)_GROUP_END; ++i)
	{
		P_M_Group_s[(E_GROUP_INDEX)i] = new C_Group;
		P_M_Group_s[(E_GROUP_INDEX)i]->MF_Set_GroupIndex((E_GROUP_INDEX)i);
	}
}

C_Stage::~C_Stage()
{
	DELETEALL_FIXEDARRAY_HEAP(P_M_Group_s, _GROUP_END)
}

void C_Stage::MF_Prepare()
{
	for (int i = 0; i < (int)_GROUP_END; ++i)
	{
		if (nullptr == P_M_Group_s[i])				// 规绢内靛;
		{
			continue;
		}
		P_M_Group_s[(E_GROUP_INDEX)i]->MF_Prepare();
	}
}

void C_Stage::MF_Step()
{
	for (int i = 0; i < (int)_GROUP_END; ++i)
	{
		if (nullptr == P_M_Group_s[(E_GROUP_INDEX)i])				// 规绢内靛
		{
			continue;
		}

		P_M_Group_s[(E_GROUP_INDEX)i]->MF_Tick();
	}
}

void C_Stage::MF_StepAfter()
{
	for (int i = 0; i < (int)_GROUP_END; ++i)
	{
		if (nullptr == P_M_Group_s[(E_GROUP_INDEX)i])				// 规绢内靛
		{
			continue;
		}

		P_M_Group_s[(E_GROUP_INDEX)i]->MF_TickAfter();
	}
}
