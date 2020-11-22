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

#define COMMON_JASON_CRAW_IDLE 20000
#define COMMON_JASON_IDLE 20001
#define JASON_IDLE_LEFT 20002
#define JASON_IDLE_RIGHT 20003
#define	JASON_WALK_LEFT 20004
#define JASON_WALK_RIGHT 20005
#define JASON_CRAW_LEFT 20006
#define JASON_CRAW_RIGHT 20007
#define	JASON_JUMP_LEFT 20008
#define JASON_JUMP_RIGHT 20009
#define JASON_CRAW_IDLE_LEFT 20010
#define JASON_CRAW_IDLE_RIGHT 20011

#define COMMON_SOPHIA_IDLE 30000
//#define SOPHIA_IDLE_LEFT 30001
//#define SOPHIA_IDLE_RIGHT 30002
//#define SOPHIA_MOVE_LEFT 30003
//#define SOPHIA_MOVE_RIGHT 30004
//#define SOPHIA_JUMP_LEFT 30005
//#define SOPHIA_JUMP_RIGHT 30006
//#define SOPHIA_TURN_LEFT 30007
//#define SOPHIA_TURN_RIGHT 30008
//#define SOPHIA_GUN_SLANT_LEFT 30009
//#define SOPHIA_GUN_SLANT_RIGHT 30010
#define SOPHIA_GUN_MOUNT_RAISE 30011
#define SOPHIA_GUN_MOUNT_UNRAISE 30012
#define SOPHIA_MOVING_IDLE 30013
#define SOPHIA_MOVING_LEFT 30014
#define SOPHIA_MOVING_RIGHT 30015

#define SOPHIA_BODY_FLAT_IDLE_LEFT 40001
#define SOPHIA_BODY_FLAT_IDLE_RIGHT 40002
#define SOPHIA_BODY_FLAT_MOVE_LEFT 40003
#define SOPHIA_BODY_FLAT_MOVE_RIGHT 40004
#define SOPHIA_BODY_SLANT_LEFT 40005
#define SOPHIA_BODY_SLANT_RIGHT 40006
#define SOPHIA_BODY_UP_LEFT 40007
#define SOPHIA_BODY_UP_RIGHT 40008
#define SOPHIA_BODY_TURN_TO_LEFT 40009
#define SOPHIA_BODY_TURN_TO_RIGHT 40010
#define SOPHIA_WHEEL_NORMAL_LEFT 40020
#define SOPHIA_WHEEL_NORMAL_RIGHT 40021
#define SOPHIA_WHEEL_CLOSE_LEFT 40022
#define SOPHIA_WHEEL_CLOSE_RIGHT 40023
#define SOPHIA_WHEEL_CLOSER_LEFT 40024
#define SOPHIA_WHEEL_CLOSER_RIGHT 40025
#define SOPHIA_WHEEL_NORMAL_LEFT_IDLE 40026
#define SOPHIA_WHEEL_NORMAL_RIGHT_IDLE 40027
#define SOPHIA_WHEEL_CLOSE_LEFT_IDLE 40028
#define SOPHIA_WHEEL_CLOSE_RIGHT_IDLE 40029
#define SOPHIA_WHEEL_CLOSER_LEFT_IDLE 40030
#define SOPHIA_WHEEL_CLOSER_RIGHT_IDLE 40031

//control state (bitmask)
#define IDLE 0
#define UP 1
#define DOWN 2
#define LEFT 4
#define RIGHT 8
#define PRIMARY 16
#define SECONDARY 32

//Enenmy State
#define WORM_IDLE_LEFT 100
#define WORM_IDLE_RIGHT 101
#define WORM_MOVE_LEFT 102
#define WORM_MOVE_RIGHT 103

#define FLOATER_IDLE_LEFT 200
#define FLOATER_IDLE_RIGHT 201
#define FLOATER_MOVE_LEFT 202	//changed from 301 (same as DOME_MOVE_LEFT)
#define FLOATER_MOVE_RIGHT 203

#define DOME_IDLE_LEFT_FLOOR 300
#define DOME_IDLE_RIGHT_FLOOR 301
#define DOME_IDLE_LEFT_CEIL 302
#define DOME_IDLE_RIGHT_CEIL 303
#define DOME_IDLE_UP_RIGHT 304
#define DOME_IDLE_DOWN_RIGHT 305
#define DOME_IDLE_UP_LEFT 306
#define DOME_IDLE_DOWN_LEFT 307
#define DOME_MOVE_LEFT_FLOOR 308
#define DOME_MOVE_RIGHT_FLOOR 309
#define DOME_MOVE_LEFT_CEIL 310
#define DOME_MOVE_RIGHT_CEIL 311
#define DOME_MOVE_UP_RIGHT 312
#define DOME_MOVE_DOWN_RIGHT 313
#define DOME_MOVE_UP_LEFT 314
#define DOME_MOVE_DOWN_LEFT 315

#define JUMPER_IDLE_LEFT 400
#define JUMPER_IDLE_RIGHT 401
#define JUMPER_MOVE_LEFT 402
#define JUMPER_MOVE_RIGHT 403

#define INSECT_IDLE_LEFT 500
#define INSECT_IDLE_RIGHT 501
#define INSECT_MOVE_LEFT 502
#define INSECT_MOVE_RIGHT 503

#define CANNON_MOVE 601

#define EYEBALL_MOVE_LEFT 701

#define ORB_MOVE_LEFT 901

#define MINE_FLICK 1001			//changed from 1

#define SKULL_MOVE_LEFT 1101

#define TELEPORTER_TELEPORT 1201
