#pragma once
#include "C_Resource.h"

class C_Sound :
    public C_Resource
{
public:
    C_Sound();

protected:
    C_Sound(const C_Sound& _Origin) = delete;

public:
    ~C_Sound();

protected:
    FMOD::Sound*                P_M_F_SoundBuffer;              // FMOD::Sound
    list<FMOD::Channel*>        STL_P_M_F_SoundChannel;         // 사운드 채널의 등록 및 해제가 빈번하므로, 리스트 구조를 씀

public:
    // 사운드 버퍼 관련
    HRESULT MF_Play_Sound(int _LoopCount, float _Volume, bool _IsOverlapSound);         // 소리 재생하는 함수

    void MF_Stop();                                                                     // 소리 재생을 중지하는 함수

    HRESULT MF_Adjust_Volume(float _Volume, int _ChannelIndex);                         // 소리를 조정하는 함수

    // Channel 관련
    HRESULT MF_Detach_Channel(FMOD::Channel* _EraseChannel);                                 // Detach; 채널에서 사운드 해제

};

