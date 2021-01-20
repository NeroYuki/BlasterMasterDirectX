#include "SoundManager.h"

SoundManager* SoundManager::_instance;

SoundManager* SoundManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new SoundManager();
	}
	return _instance;
}

void SoundManager::loadSound(HWND hWnd)
{
	DirectSound_Init(hWnd);

	CSound* sound = nullptr;

	sound = LoadSound("resource\\Sound_data\\Area2_BG.wav");
	_listSound[eSoundId::SOUND_BG_AREA2] = sound;

	sound = LoadSound("resource\\Sound_data\\Intro.wav");
	_listSound[eSoundId::SOUND_BG_INTRO] = sound;

	sound = LoadSound("resource\\Sound_data\\Ending.wav");
	_listSound[eSoundId::SOUND_BG_ENDING] = sound;

	sound = LoadSound("resource\\Sound_data\\Boss_warning.wav");
	_listSound[eSoundId::SOUND_BOSS_WARNING] = sound;

	sound = LoadSound("resource\\Sound_data\\Dome_move.wav");
	_listSound[eSoundId::SOUND_DOME_MOVING] = sound;

	sound = LoadSound("resource\\Sound_data\\Enemy_explode.wav");
	_listSound[eSoundId::SOUND_ENEMY_DYING] = sound;

	sound = LoadSound("resource\\Sound_data\\Insect_fly.wav");
	_listSound[eSoundId::SOUND_INSECT_FLYING] = sound;

	sound = LoadSound("resource\\Sound_data\\Jason_die.wav");
	_listSound[eSoundId::SOUND_JASON_DYING] = sound;

	sound = LoadSound("resource\\Sound_data\\Jason_fire.wav");
	_listSound[eSoundId::SOUND_JASON_FIRING] = sound;

	sound = LoadSound("resource\\Sound_data\\Jason_hurt.wav");
	_listSound[eSoundId::SOUND_JASON_HURTING] = sound;

	sound = LoadSound("resource\\Sound_data\\JasonShot_explode.wav");
	_listSound[eSoundId::SOUND_JASON_BULLET_EXPLODE] = sound;

	sound = LoadSound("resource\\Sound_data\\Jumper_jump.wav");
	_listSound[eSoundId::SOUND_JUMPER_JUMPING] = sound;

	sound = LoadSound("resource\\Sound_data\\Mine_ticking.wav");
	_listSound[eSoundId::SOUND_MINE_TICKING] = sound;

	sound = LoadSound("resource\\Sound_data\\Open.wav");
	_listSound[eSoundId::SOUND_OPEN] = sound;

	sound = LoadSound("resource\\Sound_data\\Pickup_collect.wav");
	_listSound[eSoundId::SOUND_PICKUP_COLLECT] = sound;

	sound = LoadSound("resource\\Sound_data\\Player_jump.wav");
	_listSound[eSoundId::SOUND_SOPHIA_JUMPING] = sound;

	sound = LoadSound("resource\\Sound_data\\Skull_bombing.wav");
	_listSound[eSoundId::SOUND_SKULL_BOMBING] = sound;

	sound = LoadSound("resource\\Sound_data\\SmallJason_fire.wav");
	_listSound[eSoundId::SOUND_SMALLJASON_FIRING] = sound;

	sound = LoadSound("resource\\Sound_data\\Sophia_die.wav");
	_listSound[eSoundId::SOUND_SOPHIA_DYING] = sound;

	sound = LoadSound("resource\\Sound_data\\Sophia_fire.wav");
	_listSound[eSoundId::SOUND_SOPHIA_FIRING] = sound;

	sound = LoadSound("resource\\Sound_data\\Sophia_thunder.wav");
	_listSound[eSoundId::SOUND_SOPHIA_THUNDER] = sound;

	sound = LoadSound("resource\\Sound_data\\Teleporter_shoot.wav");
	_listSound[eSoundId::SOUND_TELEPORTER_SHOOTING] = sound;

	sound = LoadSound("resource\\Sound_data\\Teleporter_teleport.wav");
	_listSound[eSoundId::SOUND_TELEPORTER_TELEPORT] = sound;

	sound = LoadSound("resource\\Sound_data\\Worm_moving.wav");
	_listSound[eSoundId::SOUND_WORM_MOVING] = sound;
}

bool SoundManager::IsPlaying(eSoundId soundid)
{
	auto sound = _listSound[soundid];
	if (sound != nullptr)
	{
		return sound->IsSoundPlaying();
	}
	return false;
}

void SoundManager::Play(eSoundId soundid)
{
	auto sound = _listSound[soundid];
	if (sound != nullptr)
	{
		PlaySound(sound);
		this->currentSound = sound;
	}
}
void SoundManager::PlayLoop(eSoundId soundid)
{
	auto sound = _listSound[soundid];
	if (sound != nullptr)
	{
		sound->Play(0, DSBPLAY_LOOPING);
	}
}
void SoundManager::Stop(eSoundId soundid)
{
	auto sound = _listSound[soundid];
	if (sound != nullptr)
	{
		StopSound(sound);
	}
}

SoundManager::SoundManager()
{
	currentSound = nullptr;
}

SoundManager::~SoundManager()
{
}