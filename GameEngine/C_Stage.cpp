#include "pch.h"
#include "C_Stage.h"

C_Stage::C_Stage(E_STAGE_NUMBER _StageNumber)
	: C_Entity()
	, L_M_StageNumber(_StageNumber)
	, M_StageState(_STAGE_PLAY)
	, P_M_Group_s{}
{
}

C_Stage::~C_Stage()
{

}

void C_Stage::MF_Prepare()
{
	for (size_t i = 0; i < _GROUP_END; i++)
	{
		P_M_Group_s[i]->MF_Prepare();
	}
}

void C_Stage::MF_Step()
{
	for (size_t i = 0; i < _GROUP_END; i++)
	{
		P_M_Group_s[i]->MF_Tick();
	}
}

void C_Stage::MF_StepAfter()
{
	for (size_t i = 0; i < _GROUP_END; i++)
	{
		P_M_Group_s[i]->MF_TickAfter();
	}
}

void C_Stage::DetachGroups()
{
	DELETEALL_FIXEDARRAY_HEAP(P_M_Group_s, _GROUP_END)
}
