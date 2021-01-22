#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include <dsound.h>
#include "dxaudio.h"


#include <map>

enum eSoundId
{
	SOUND_BG_AREA2,					
	SOUND_BG_INTRO,
	SOUND_BG_ENDING,
	SOUND_BOSS_WARNING,
	SOUND_DOME_MOVING,
	SOUND_ENEMY_DYING,
	SOUND_INSECT_FLYING,
	SOUND_JASON_DYING,
	SOUND_JASON_FIRING,
	SOUND_JASON_HURTING,
	SOUND_JASON_BULLET_EXPLODE,
	SOUND_JUMPER_JUMPING,
	SOUND_MINE_TICKING,
	SOUND_OPEN,
	SOUND_PICKUP_COLLECT,
	SOUND_SOPHIA_JUMPING,
	SOUND_SKULL_BOMBING,
	SOUND_SMALLJASON_FIRING,
	SOUND_SOPHIA_DYING,
	SOUND_SOPHIA_FIRING,
	SOUND_SOPHIA_FLYING,
	SOUND_SOPHIA_THUNDER,
	SOUND_TELEPORTER_SHOOTING,
	SOUND_TELEPORTER_TELEPORT,
	SOUND_WORM_MOVING,
	BOSS_BG
};

class SoundManager
{
private:
	SoundManager();
	static SoundManager* _instance;
	map<eSoundId, CSound*> _listSound;
	CSound* currentSound;
	float volume;
public:
	~SoundManager();
	static SoundManager* getInstance();
	void loadSound(HWND hWnd);
	void Play(eSoundId);
	void Stop(eSoundId);
	void PlayLoop(eSoundId);
	bool IsPlaying(eSoundId);
};
