#pragma once


#define SINGLETON(ClassType) public:\
								static ClassType* GetInst()\
								{\
									static ClassType inst;\
									return &inst;\
								}\
							 public:\
								 ClassType* operator = (const ClassType& _Origin) = delete;\
							 private:\
								 ClassType();\
								 ClassType(const ClassType& _Origin) = delete;\
							 	 ~ClassType();

#define KEY_CHECK(Key, State) CKeyMgr::GetInst()->GetKeyState(Key) == State
#define DT	CTimeMgr::GetInst()->GetDeltaTime()

#define KEY_TAP(Key) KEY_CHECK(Key, TAP)
#define KEY_PRESSED(Key) KEY_CHECK(Key, PRESSED)
#define KEY_RELEASED(Key) KEY_CHECK(Key, RELEASED)
#define KEY_NONE(Key) KEY_CHECK(Key, NONE)

#define PI	3.14159265348979f

#define GAME_FOLDER MyGame

#define GENERATED_OBJECT(type) typedef type Super;
							  


#define DEBUG_RENDER CEngine::GetInst()->DebugRender()
#define SELECT_PEN(DC, TYPE) FSelectPen tempPenSelect(DC, TYPE)
#define SELECT_BRUSH(DC, hBrush) FSelectBrush tempBrushSelect(DC, hBrush)

#define TILE_SIZE 72

#define CLONE(type) virtual type* Clone() {return new type(*this);}
#define CLONE_DISABLE(type) virtual type* Clone() {return nullptr;}








// Key Value
enum KEY
{
	_0,
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,

	NUM0,
	NUM1,
	NUM2,
	NUM3,
	NUM4,
	NUM5,
	NUM6,
	NUM7,
	NUM8,
	NUM9,

	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,

	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,

	Z,
	X,
	C,
	V,
	B,
	N,
	M,

	TAB,
	LSHIFT,
	LALT,
	LCTRL,
	SPACE,

	ESC,
	ENTER,
	BACK,

	LEFT,
	RIGHT,
	UP,
	DOWN,

	LBTN,
	RBTN,

	KEY_END,
};

enum KEY_STATE
{
	NONE,
	TAP,
	PRESSED,
	RELEASED,
};

enum LAYER
{
	DEFAULT,
	TILE,
	PLATFORM,
	PLAYER,
	MONSTER,
	PLAYER_PJ,
	MONSTER_PJ,
	WORLD_STATIC,




	UI = 31,
	END = 32,
};


enum TASK_TYPE
{
	// Param1 : Layer Type, Param2 : Object Adress
	CREATE_OBJECT,

	// Param1 : Object Adress
	DELETE_OBJECT,

	// Param1 : LEVEL_TYPE
	LEVEL_CHANGE,
};



enum PEN_TYPE
{
	GREEN_PEN,
	BLUE_PEN,
	RED_PEN,

	PEN_END,
};


enum LOG_LEVEL
{
	LOG,
	WARNING,
	ERR,
};

enum class LEVEL_TYPE
{
	START_LEVEL,
	PLAY_LEVEL,
	EDITOR_LEVEL,
	END,
};




enum class ENORMAL_MON_STATE
{
	NORMAL_MON_IDLE,
	NORMAL_MON_TRACE,
};

// Tile Type
enum Tile_Type
{
	MARIO,
	BONUS_BOX,
	EVOLVE_BOX,
	COIN,
	UNBREAK_BLOCK,
	BLOCK,
	GROUND_L,
	GROUND_M,
	GROUND_R,
	WALL_L,
	WALL_M,
	WALL_R,
	PIPE_UP_L,
	PIPE_UP_R,
	PIPE_DOWN_L,
	PIPE_DOWN_R,
	PLAT_0,
	PLAT_1,
	PLAT_2,
	PLAT_3,
	PLAT_4,
	PLAT_5,
	PLAT_6,
	PLAT_7,
	PLAT_8,
	GAME_END,
	GOOMBA,
	TURTLE,
	PLANT,
	RED_PLANT,
	END_TYPE,
};