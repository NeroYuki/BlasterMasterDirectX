#pragma once
//State Dictionary (include references to gameObject's state)

//Player State
#define PLAYER_IDLE 10001
#define PLAYER_WALK 10002
#define PLAYER_JUMP 10003
#define PLAYER_CLIMB 10004

//Enenmy State
#define WORM_IDLE_LEFT 100
#define WORM_IDLE_RIGHT 101
#define WORM_MOVE_LEFT 102
#define WORM_MOVE_RIGHT 103

#define FLOATER_IDLE_LEFT 200
#define FLOATER_IDLE_RIGHT 201
#define FLOATER_MOVE_LEFT 202	//changed from 301 (same as DOME_MOVE_LEFT)
#define FLOATER_MOVE_RIGHT 203

#define DOME_MOVE_LEFT 301

#define JUMPER_MOVE_LEFT 401

#define INSECT_MOVE_LEFT 501

#define CANNON_MOVE 601

#define EYEBALL_MOVE_LEFT 701

#define ORB_MOVE_LEFT 901

#define MINE_FLICK 1001			//changed from 1

#define SKULL_MOVE_LEFT 1101

#define TELEPORTER_TELEPORT 1201
