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
    list<FMOD::Channel*>        STL_P_M_F_SoundChannel;         // ���� ä���� ��� �� ������ ����ϹǷ�, ����Ʈ ������ ��

public:
    // ���� ���� ����
    HRESULT MF_Play_Sound(int _LoopCount, float _Volume, bool _IsOverlapSound);         // �Ҹ� ����ϴ� �Լ�

    void MF_Stop();                                                                     // �Ҹ� ����� �����ϴ� �Լ�

    HRESULT MF_Adjust_Volume(float _Volume, int _ChannelIndex);                         // �Ҹ��� �����ϴ� �Լ�

    // Channel ����
    HRESULT MF_Detach_Channel(FMOD::Channel* _EraseChannel);                                 // Detach; ä�ο��� ���� ����

};

