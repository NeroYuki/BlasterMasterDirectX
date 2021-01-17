#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include <dsound.h>
#include "dxaudio.h"


#include <map>

enum eSoundId
{
	BACKGROUND_STAGE1,					// Done.

	BACKGROUND_STAGE2,

	BACKGROUND_STAGE3,

	ATTACK_CANNON,					// Done.

	BASE_BULLET_FIRE,					// Done.

	FBULLET_FIRE,					// Done.

	SBULLET_FIRE,					// Done.

	MBULLET_FIRE,					// Done.

	LBULLET_FIRE,					// Done.

	BOOM,

	BOSS_SOUNG1,

	DEAD,

	DESTROY_BOSS,

	DESTROY_BRIDGE,					// Done.

	DESTROY_ENEMY,					// Done.

	BRIDGE_BURN,					// Done.

	EAT_ITEM,						// Done.

	ENEMY_ATTACK,

	GAME_OVER,

	GAMEOVER_BOSS,

	INTRO,

	JUMP_SOUND,						// Done.

	PASS_BOSS,

	WINGAME
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
