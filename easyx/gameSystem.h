#pragma once
#include "easyx.h"
#define WIDTH 1024
#define HEIGHT 768
#define FRAME_CHANGE 15
#define FPS 75

enum gameState {
	gameState_menu,
	gameState_game,
	gameState_pause,
	gameState_gameover
};

enum playerDirection {
	PL_STOP = 0,
	PL_LRUD = 15,
	PL_UU = 1,
	PL_DD = 2,
	PL_LL = 4,
	PL_RR = 8,
	PL_UD = 3,
	PL_LR = 12,
	PL_UL = 5,
	PL_UR = 9,
	PL_DL = 6,
	PL_DR = 10,
	PL_ULR = 13,
	PL_DLR = 14,
	PL_LUD = 7,
	PL_RUD = 11
};


class gameObject
{
public:
	int x, y, width, height;
	IMAGE skin;
	gameObject(LPCTSTR skinPath = NULL, int x = 0, int y = 0, int width = 0, int height = 0);
	~gameObject();
	void init(LPCTSTR skinPath, int x, int y, int width, int height);
	//void draw();
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	void update();
};

class player : public gameObject
{
public:
	//IMAGE cur_frame;
	int facingRight;
	int is_moving;
	int is_up, is_down, is_left, is_right;
	int is_lbutton_down;
	int mousex, mousey;
	short dx, dy;
	double maxSpeed;
	int count;
	int cur_x, cur_y;
	player(LPCTSTR skinPath = NULL, int x = 0, int y = 0, int width = 0, int height = 0);
	~player();
	void getMsg(ExMessage msg);
	void update(ExMessage msg, int bgWidth, int bgHeight);
	//void update(ExMessage msg, int bgWidth, int bgHeight, int moving, short &dx, short &dy);
	void draw(int drawX, int drawY);
};

class gameSystem
{
public:
	int cameraX, cameraY;
	int windowWidth, windowHeight;
	int bgWidth, bgHeight;
	int fps;
	//int mousex, mousey;
	//int is_lbutton_down;
	player Pc;
	ExMessage msg;
	IMAGE background;
	gameSystem();
	~gameSystem();
	void init();
	void messageProc();
	void frameDraw(int drawX, int drawY);
	void fitCamera();
	//void dispatchMsg(ExMessage msg, int &moving);
};

void alphaPutImage(IMAGE *src, int drawX, int drawY, int w, int h);