#include "pch.h"
#include "C_Sound.h"

FMOD_RESULT CHANNEL_CALLBACK(FMOD_CHANNELCONTROL* ChannelControl, FMOD_CHANNELCONTROL_TYPE ControlType		// �����Ϸ� �ν��� ���� �Լ� ��ŷ
	, FMOD_CHANNELCONTROL_CALLBACK_TYPE CallbackType
	, void* CommandData1, void* CommanddData2);

C_Sound::C_Sound()
	: C_Resource(_RESOURCE_SOUND)
	, P_M_F_SoundBuffer(nullptr)
	, STL_P_M_F_SoundChannel{}
{
}

C_Sound::~C_Sound()
{
}

HRESULT C_Sound::MF_Play_Sound(int _LoopCount, float _Volume, bool _IsOverlapSound)
{
	// ���� ��ȯ ���� ���
	if (STL_P_M_F_SoundChannel.empty() && !_IsOverlapSound)			// ��� �ְų�, ������ ������ ������ ���� ��ȯ
	{
		POPUP_DEBUG(L"STL_P_M_F_SoundChannel.empty() && !_IsOverlapSound", L"in C_Sound::MF_Play_Sound(), STL_P_M_F_SoundChannel.empty() && !_IsOverlapSound")
			return E_FAIL;
	}

	// ���� ��ȯ ����
	if (0 > _LoopCount)												// �������� ������ ���� ��ȯ
	{
		POPUP_DEBUG(L"0 > _LoopCount", L"in C_Sound::MF_Play_Sound(), 0 > _LoopCount")
		return E_FAIL;
	}

	_LoopCount -= 1;

	FMOD::Channel* T_Channel = nullptr;
	C_GameEngine::SF_Get_Instance()->MF_Get_FMODSystem()->playSound(P_M_F_SoundBuffer, nullptr, false, &T_Channel);

	// ��� ����
	if (nullptr == T_Channel)
	{
		return E_FAIL;
	}
		
	T_Channel->setVolume(_Volume);

	T_Channel->setCallback(&CHANNEL_CALLBACK);
	T_Channel->setUserData(this);

	T_Channel->setMode(FMOD_LOOP_NORMAL);
	T_Channel->setLoopCount(_LoopCount);

	STL_P_M_F_SoundChannel.push_back(T_Channel);

	// �ε��� ���� ����
	int T_ChannelIndex = -1;						// ������� �ε��� �ʱ�ȭ ����
	T_Channel->getIndex(&T_ChannelIndex);			// ��� ���̸� �ε��� ������ �ʱ�ȭ ���ڸ� ���ؼ� ����

	return S_OK;
}

HRESULT C_Sound::MF_Adjust_Volume(float _Volume, int _ChannelIndex)
{
	return E_NOTIMPL;
}

void C_Sound::MF_Stop()				// ���� while���� ���� ���� ���� �ذ�
{
	for (list<FMOD::Channel*>::iterator T_Iterator = STL_P_M_F_SoundChannel.begin(); T_Iterator != STL_P_M_F_SoundChannel.end(); ++T_Iterator)
	{
		(*T_Iterator)->stop();
	}
}

HRESULT C_Sound::MF_Detach_Channel(FMOD::Channel* _EraseChannel)
{
	if (nullptr == _EraseChannel)					// ����ڵ�; ���� ���� ���������� �� ���� ��ȯ
	{
		POPUP_DEBUG(L"nullptr == _EraseChannel", L"in C_Sound::MF_Detach_Channel, nullptr == _EraseChannel")
		return E_FAIL;
	}
	else if (STL_P_M_F_SoundChannel.empty())     // ����ڵ�; ������� �ּ�ȭ�� ���� if - else if������ �ۼ�
	{
		POPUP_DEBUG(L"STL_P_M_F_SoundChannel.empty()", L"in C_Sound::MF_Detach_Channel, STL_P_M_F_SoundChannel.empty()")
		return E_FAIL;
	}

	list<FMOD::Channel*>::iterator T_Iterator = STL_P_M_F_SoundChannel.begin();
	for (; T_Iterator != STL_P_M_F_SoundChannel.end(); ++T_Iterator)			// ����! ����Ʈ�� �迭�� �ƴϱ� ������ �׳� �����!; vector ������ �̷� for������ �ϸ� ���� ����!
	{
		if (*T_Iterator == _EraseChannel)
		{
			STL_P_M_F_SoundChannel.erase(T_Iterator);
		}
	}
	return S_OK;
}

// ����, Save �� Load �Լ� ��������

// Call Back
FMOD_RESULT CHANNEL_CALLBACK(FMOD_CHANNELCONTROL* ChannelControl, FMOD_CHANNELCONTROL_TYPE ControlType
	, FMOD_CHANNELCONTROL_CALLBACK_TYPE CallbackType
	, void* CommandData1, void* CommanDdata2)
{
	FMOD::Channel* T_Channel = (FMOD::Channel*)ChannelControl;
	C_Sound* T_Sound = nullptr;

	switch (ControlType)
	{
	case FMOD_CHANNELCONTROL_CALLBACK_END:
		T_Channel->getUserData((void**)&T_Sound);
		T_Sound->MF_Detach_Channel(T_Channel);
	}
	return FMOD_OK;
}