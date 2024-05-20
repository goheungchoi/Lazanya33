#pragma once
#include <Windows.h>
// FMOD
#ifndef _WIN64
#include "fmod.hpp"
#pragma comment (lib, "fmod_vc.lib")
using namespace FMOD;
#endif
#ifdef _WIN64
#include "fmod.hpp"
#pragma comment (lib, "fmod_vc.lib")
using namespace FMOD;
#endif

namespace Music
{
    enum class eSoundChannel
    {
        BGM,
        Effect,
        Size
    };

    enum class eSoundList
    {
        Button,
        BackSound,
        PaperTeraing,
        Attack,
        blockDamage,
        block00_destroy_Malang,
        block01_destroy_Dan,
        block02_destroy_DDak,
        Block04_Destroy,
        Block05_destroy_gold,
        Block06_destroy_air,
        rasgula,
        rasgula_shorts,
        death,
        mother,
        bestScore,
        background01,
        BackGround02,
        LevelUP,
        Size
    };
    class SoundManager;  // Ŭ���� ���� ����
    extern SoundManager* soundManager;  // extern�� ����Ͽ� �ܺο��� ���� �����ϵ��� ����

    class SoundManager final
    {
    public:
        static SoundManager* GetInstance();

        static void DestroyInstance();

        void InitMusic();

        void LoadMusic(eSoundList list, bool loopcheck, const char* music);

        void PlayMusic(eSoundList list, eSoundChannel channel);

        void StopMusic(eSoundChannel channel);

        void SetVolume(float volume);

    private:
        SoundManager();

        ~SoundManager();

    private:
        static SoundManager* mInstance;

        FMOD::System* mSystem;
        FMOD::Channel* mChannel[static_cast<int>(eSoundChannel::Size)];
        FMOD::Sound* mSoundList[static_cast<int>(eSoundList::Size)];
        float mVolume;
    };

}