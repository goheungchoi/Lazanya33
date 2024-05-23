#include "CSound.h"
#include <iostream>

namespace Music
{
  SoundManager* SoundManager::mInstance = nullptr;
  SoundManager* soundManager = SoundManager::GetInstance();  // √ ±‚»≠  

  SoundManager* SoundManager::GetInstance()
  {
    if (mInstance == nullptr)
      mInstance = new SoundManager();
    return mInstance;
  }

  void SoundManager::DestroyInstance()
  {
    delete mInstance;
    mInstance = nullptr;
  }

  void SoundManager::InitMusic()
  {
    FMOD_RESULT result = System_Create(&mSystem);
    if (result != FMOD_OK) {
      std::cerr << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
      return;
    }

    result = mSystem->init(32, FMOD_INIT_NORMAL, nullptr);
    if (result != FMOD_OK) {
      std::cerr << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
      return;
    }

    LoadMusic(eSoundList::Button, false, "sound//01_button.mp3");
    LoadMusic(eSoundList::BackSound, false, "sound//02_backSound.mp3");
    LoadMusic(eSoundList::PaperTeraing, false, "sound//03_paperTeraing.mp3");
    LoadMusic(eSoundList::Attack, false, "sound//04_Attack.mp3");
    LoadMusic(eSoundList::blockDamage, false, "sound//05_blockDamage.mp3");
    LoadMusic(eSoundList::block00_destroy_Malang, false, "sound//06_block00_destroy_Malang.mp3");
    LoadMusic(eSoundList::block01_destroy_Dan, false, "sound//07_block01_destroy_Dan.mp3");
    LoadMusic(eSoundList::block02_destroy_DDak, false, "sound//08_block02_destroy_DDak.mp3");
    LoadMusic(eSoundList::Block04_Destroy, false, "sound//09_Block04_Destroy.mp3");
    LoadMusic(eSoundList::Block05_destroy_gold, false, "sound//10_Block05_destroy_gold.mp3");
    LoadMusic(eSoundList::Block06_destroy_air, false, "sound//11_Block06_destroy_air.mp3");
    LoadMusic(eSoundList::rasgula, false, "sound//12_rasgula.mp3");
    LoadMusic(eSoundList::rasgula_shorts, false, "sound//12_rasgula_shorts.mp3");
    LoadMusic(eSoundList::death, false, "sound//13_death.mp3");
    LoadMusic(eSoundList::mother, false, "sound//18_mother.mp3");
    LoadMusic(eSoundList::bestScore, false, "sound//19_bestScore.mp3");
    LoadMusic(eSoundList::background01, true, "sound//21_background01.mp3");
    LoadMusic(eSoundList::BackGround02, true, "sound//22_BackGround02.mp3");
    LoadMusic(eSoundList::LevelUP, false, "sound//23_LevelUP.mp3");
    LoadMusic(eSoundList::FiveCombo, false, "sound//24_5ComboChant01.mp3");//o
    LoadMusic(eSoundList::PaperSwap, false, "sound//25_PaperSwap01.mp3");
    LoadMusic(eSoundList::TypeName, false, "sound//26_InitialSound01_1.mp3");//o
  }

  void SoundManager::LoadMusic(eSoundList soundlist, bool loopcheck, const char* music)
  {
    FMOD_RESULT result;

    if (loopcheck)
      result = mSystem->createSound(music, FMOD_LOOP_NORMAL, 0, &mSoundList[static_cast<int>(soundlist)]);
    else
      result = mSystem->createSound(music, FMOD_LOOP_OFF, 0, &mSoundList[static_cast<int>(soundlist)]);

    if (result != FMOD_OK) {
      std::cerr << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << " while loading " << music << std::endl;
    }
  }

  void SoundManager::PlayMusic(eSoundList soundlist, eSoundChannel channel)
  {
    mChannel[static_cast<int>(channel)]->stop();
    mSystem->playSound(mSoundList[static_cast<int>(soundlist)], NULL, 0, &mChannel[static_cast<int>(channel)]);
    mChannel[static_cast<int>(channel)]->setVolume(mVolume);
  }

  void SoundManager::StopMusic(eSoundChannel channel)
  {
    mChannel[static_cast<int>(channel)]->stop();
  }

  void SoundManager::SetVolume(float volume)
  {
    mVolume = volume;
    for (unsigned int i = 0; i < static_cast<unsigned int>(eSoundChannel::Size); ++i)
      mChannel[i]->setVolume(mVolume);
  }

  SoundManager::SoundManager() : mSystem(nullptr), mChannel{}, mSoundList{}, mVolume(0.5f)
  {
  }

  SoundManager::~SoundManager()
  {
    if (mSystem) {
      mSystem->close();
      mSystem->release();
    }
  }
};
