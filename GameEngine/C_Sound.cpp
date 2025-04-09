#include "pch.h"
#include "C_Sound.h"

FMOD_RESULT CHANNEL_CALLBACK(FMOD_CHANNELCONTROL* ChannelControl, FMOD_CHANNELCONTROL_TYPE ControlType		// 컴파일러 인식을 위한 함수 링킹
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
	// 조기 반환 패턴 사용
	if (STL_P_M_F_SoundChannel.empty() && !_IsOverlapSound)			// 비어 있거나, 오버랩 조건이 없으면 조기 반환
	{
		POPUP_DEBUG(L"STL_P_M_F_SoundChannel.empty() && !_IsOverlapSound", L"in C_Sound::MF_Play_Sound(), STL_P_M_F_SoundChannel.empty() && !_IsOverlapSound")
			return E_FAIL;
	}

	// 조기 반환 패턴
	if (0 > _LoopCount)												// 루프값이 없으면 조기 반환
	{
		POPUP_DEBUG(L"0 > _LoopCount", L"in C_Sound::MF_Play_Sound(), 0 > _LoopCount")
		return E_FAIL;
	}

	_LoopCount -= 1;

	FMOD::Channel* T_Channel = nullptr;
	C_GameEngine::SF_Get_Instance()->MF_Get_FMODSystem()->playSound(P_M_F_SoundBuffer, nullptr, false, &T_Channel);

	// 재생 실패
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

	// 인덱스 관련 전달
	int T_ChannelIndex = -1;						// 재생관련 인덱스 초기화 인자
	T_Channel->getIndex(&T_ChannelIndex);			// 재생 중이면 인덱스 정보를 초기화 인자를 통해서 전달

	return S_OK;
}

HRESULT C_Sound::MF_Adjust_Volume(float _Volume, int _ChannelIndex)
{
	return E_NOTIMPL;
}

void C_Sound::MF_Stop()				// 기존 while문의 무한 루프 문제 해결
{
	for (list<FMOD::Channel*>::iterator T_Iterator = STL_P_M_F_SoundChannel.begin(); T_Iterator != STL_P_M_F_SoundChannel.end(); ++T_Iterator)
	{
		(*T_Iterator)->stop();
	}
}

HRESULT C_Sound::MF_Detach_Channel(FMOD::Channel* _EraseChannel)
{
	if (nullptr == _EraseChannel)					// 방어코드; 인자 값이 널포인터일 떄 조기 반환
	{
		POPUP_DEBUG(L"nullptr == _EraseChannel", L"in C_Sound::MF_Detach_Channel, nullptr == _EraseChannel")
		return E_FAIL;
	}
	else if (STL_P_M_F_SoundChannel.empty())     // 방어코드; 오버헤드 최소화를 위해 if - else if문으로 작성
	{
		POPUP_DEBUG(L"STL_P_M_F_SoundChannel.empty()", L"in C_Sound::MF_Detach_Channel, STL_P_M_F_SoundChannel.empty()")
		return E_FAIL;
	}

	list<FMOD::Channel*>::iterator T_Iterator = STL_P_M_F_SoundChannel.begin();
	for (; T_Iterator != STL_P_M_F_SoundChannel.end(); ++T_Iterator)			// 유의! 리스트는 배열이 아니기 때문에 그냥 써야함!; vector 형식은 이런 for문으로 하면 문제 생김!
	{
		if (*T_Iterator == _EraseChannel)
		{
			STL_P_M_F_SoundChannel.erase(T_Iterator);
		}
	}
	return S_OK;
}

// 향후, Save 및 Load 함수 구현예정

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