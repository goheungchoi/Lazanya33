#pragma once
#include <Windows.h>
// FMOD
#ifndef _WIN64
#include "fmod.hpp"
#pragma comment (lib, "fmod_vc.lib")
#include "fmod_errors.h"  // Include FMOD error strings
using namespace FMOD;
#endif
#ifdef _WIN64
#include "fmod.hpp"
#include "fmod_errors.h"  // Include FMOD error strings
#pragma comment (lib, "fmod_vc.lib")
using namespace FMOD;
#endif

namespace Music
{
  enum class eSoundChannel
  {
    BGM,
    Effect,
    BrickDamage,
    Default,
    Stone,
    Rock,
    Bomb,
    Gold,
    Oxygen,
    Lasgulla,
    LevelUP,
    Death,
    Mother,
    Acient,
    Type1,
    Type2,
    Type3,
    Attack,
    Combo,
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
    FiveCombo,
    PaperSwap,
    TypeName,
    Size
  };
  class SoundManager;  // 클래스 전방 선언
  extern SoundManager* soundManager;  // extern을 사용하여 외부에서 접근 가능하도록 선언

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
