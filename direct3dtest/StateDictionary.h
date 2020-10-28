#pragma once
//State Dictionary (include references to gameObject's state)

//Player State
//Animation State
#define COMMON_PLAYER_IDLE 10000
#define TOP_JASON_IDLE_LEFT 10001
#define TOP_JASON_IDLE_RIGHT 10002
#define TOP_JASON_IDLE_UP 10003
#define TOP_JASON_IDLE_DOWN 10004
#define TOP_JASON_WALK_LEFT 10005
#define TOP_JASON_WALK_RIGHT 10006
#define TOP_JASON_WALK_UP 10007
#define TOP_JASON_WALK_DOWN 10008

//control state (bitmask)
#define JASON_UP 1
#define JASON_DOWN 2
#define JASON_LEFT 4
#define JASON_RIGHT 8

//Enenmy State
#define WORM_IDLE_LEFT 100
#define WORM_IDLE_RIGHT 101
#define WORM_MOVE_LEFT 102
#define WORM_MOVE_RIGHT 103

#define FLOATER_IDLE_LEFT 200
#define FLOATER_IDLE_RIGHT 201
#define FLOATER_MOVE_LEFT 202	//changed from 301 (same as DOME_MOVE_LEFT)
#define FLOATER_MOVE_RIGHT 203

#define DOME_IDLE_LEFT 300
#define DOME_IDLE_RIGHT 301
#define DOME_MOVE_LEFT 302
#define DOME_MOVE_RIGHT 303

#define JUMPER_MOVE_LEFT 401

#define INSECT_MOVE_LEFT 501

#define CANNON_MOVE 601

#define EYEBALL_MOVE_LEFT 701

#define ORB_MOVE_LEFT 901

#define MINE_FLICK 1001			//changed from 1

#define SKULL_MOVE_LEFT 1101

#define TELEPORTER_TELEPORT 1201
