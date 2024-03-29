#pragma once
//State Dictionary (include references to gameObject's state)

//Player State
//Animation State
#define FIRST_INTRO 100001
#define SECOND_INTRO 100002
#define THIRD_INTRO 100003

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
#define JASON_CLIMB_IDLE 20012
#define JASON_CLIMB 20013

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

#define MINE_TICK 800

//#define CANNON_MOVE 601

#define EYEBALL_MOVE_LEFT 701

#define ORB_CIRCLE 901
#define ORB_LEFT_1 902
#define ORB_RIGHT_1 903
#define ORB_LEFT_2 904
#define ORB_RIGHT_2 905

#define MINE_FLICK 1001			//changed from 1

#define SKULL_MOVE_LEFT 1101
#define SKULL_MOVE_RIGHT 1102
#define SKULL_OPEN_LEFT 1103
#define SKULL_OPEN_RIGHT 1104

#define TELEPORTER_TELEPORT 1201

#define SOPHIA_BULLET_RIGHT 900000
#define SOPHIA_BULLET_LEFT 900001
#define SOPHIA_BULLET_UP 900002
#define SOPHIA_SMALL_BULLET_RIGHT 900003
#define SOPHIA_SMALL_BULLET_LEFT 900004
#define SOPHIA_SMALL_BULLET_UP 900005
#define SOPHIA_SMALL_ROCKET_RIGHT 900006
#define SOPHIA_SMALL_ROCKET_LEFT 900007
#define SOPHIA_SMALL_ROCKET_TOP 900008
#define SOPHIA_SMALL_ROCKET_DOWN 900009
#define SOPHIA_LIGHTNING 900010
#define SOPHIA_SMALL_BULLET_DOWN 900011
#define JASON_BULLET 900012
#define CIRCLE_BULLET 900013
#define BULLET_EXPLO 9000100
#define ENEMY_BULLET_1 900100
#define ENEMY_BULLET_2 900101
#define ENEMY_BULLET_3 900102
#define ENEMY_BULLET_4 900103

#define HIT_POINT_BAR_8 999001
#define HIT_POINT_BAR_7 999002
#define HIT_POINT_BAR_6 999003
#define HIT_POINT_BAR_5 999004
#define HIT_POINT_BAR_4 999005
#define HIT_POINT_BAR_3 999006
#define HIT_POINT_BAR_2 999007
#define HIT_POINT_BAR_1 999008
#define HIT_POINT_BAR_0 999009
#define GUN_BAR_8 999011
#define GUN_BAR_7 999012
#define GUN_BAR_6 999013
#define GUN_BAR_5 999014
#define GUN_BAR_4 999015
#define GUN_BAR_3 999016
#define GUN_BAR_2 999017
#define GUN_BAR_1 999018
#define GUN_BAR_0 999019

#define CANON_IDLE 1400
#define CANON_LEFTRIGHT 1401
#define CANON_TOPDOWN 1402
#define EYE_IDLE 1200
#define EYE_MOVE 1201
#define TELEPORTER_STOP 1300
#define TELEPORTER_MOVE 1301
#define GRENADE_STATE 900300
#define GRENADE_EXPLOSION 900301

#define POWER_UP_HOVER 999200
#define POWER_UP_THUNDER 999201
#define POWER_UP_X3MISSLE 999202
#define POWER_UP_HP 999203
#define POWER_UP_HOMINGMISSLE 999204
#define POWER_UP_GUN_UPGRADE 999205
#define POWER_UP_HOMINGMISSLE_TICK 999206
#define POWER_UP_X3MISSLE_TICK 999207
#define POWER_UP_THUNDER_TICK 999208
#define CHARSET_0 60000
#define CHARSET_1 60001
#define CHARSET_2 60002
#define CHARSET_3 60003
#define CHARSET_4 60004
#define CHARSET_5 60005
#define CHARSET_6 60006
#define CHARSET_7 60007
#define CHARSET_8 60008
#define CHARSET_9 60009

#define DEADSCENE_CHOICE 70000
#define STILL_ALIVE_SCENE 70001
#define DEAD_SCENE 70002

#define JASON_TOP_DEAD_ANI 10009
#define JASON_DEAD_ANI 20014
#define SOPHIA_DEAD_ANI 40040

#define BOSS_BODY 50000
#define BOSS_JOINT 50004
#define BOSS_CLAW 50006
#define BOSS_RIGHT_CLAW 50007