#include "gameSystem.h"
#include "string"
#include "time.h"
#include "easyx.h"
#include "wingdi.h"
#include "conio.h"

void gameObject::init(LPCTSTR skinPath, int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	if (skinPath != nullptr)
	{
		loadimage(&this->skin, skinPath);
	}
}

gameObject::gameObject(LPCTSTR skinPath, int, int, int width, int height)
{
	this->init(skinPath, x, y, width, height);
}
gameObject::~gameObject()
{ }

player::player(LPCTSTR skinPath, int x, int y, int width, int height)
{
	this->init(skinPath, x, y, width, height);
	this->maxSpeed = 10;
    this->is_lbutton_down = 0;
    this->is_left = 0;
    this->is_right = 0;
    this->is_up = 0;
    this->is_down = 0;
    this->mousex = 0;
    this->mousey = 0;
    this->dx = 0;
    this->dy = 0;
    this->is_moving = 0;
    this->facingRight = 0;
    this->count = 0;
    this->cur_x = 0;
    this->cur_y = 0;
}

void player::getMsg(ExMessage msg) 
{
    if (msg.vkcode == VK_ESCAPE) exit(0);
    switch (msg.message)
    {
    case WM_LBUTTONDOWN:
        setcapture();
        this->mousex = msg.x;
        this->mousey = msg.y;
        this->is_lbutton_down = 1;
        break;
    case WM_LBUTTONUP:
        releasecapture();
        this->is_lbutton_down = 0;
        break;
    case WM_KEYDOWN:
        switch (msg.vkcode)
        {
        case VK_UP:
            this->is_up = 1;
            break;
        case VK_DOWN:
            this->is_down = 1;
            break;
        case VK_LEFT:
            this->is_left = 1;
            break;
        case VK_RIGHT:
            this->is_right = 1;
            break;
        case 'W':
            this->is_up = 1;
            break;
        case 'S':
            this->is_down = 1;
            break;
        case 'A':
            this->is_left = 1;
            break;
        case 'D':
            this->is_right = 1;
            break;
        }
        break;
    case WM_KEYUP:
        switch (msg.vkcode)
        {
        case VK_UP:
            this->is_up = 0;
            break;
        case VK_DOWN:
            this->is_down = 0;
            break;
        case VK_LEFT:
            this->is_left = 0;
            break;
        case VK_RIGHT:
            this->is_right = 0;
            break;
        case 'W':
            this->is_up = 0;
            break;
        case 'S':
            this->is_down = 0;
            break;
        case 'A':
            this->is_left = 0;
            break;
        case 'D':
            this->is_right = 0;
            break;
        }
        break;
    default:
        break;
    }
}

void player::update(ExMessage msg, int bgWidth, int bgHeight)
{
    if (is_lbutton_down)
    {
        dx = msg.x - this->mousex;
        dy = msg.y - this->mousey;
        //printf("mousex:%6d mousey:%6d dx:%6d dy:%6d\n", this->mousex, this->mousey, dx, dy);
        facingRight = dx > 0 ? 1 : 0;
        is_moving = (dx && dy);
        dx = (dx < 0 ? -1 : 1) * min((int)abs(dx), 50 * abs(dx) / sqrt(pow(dx, 2) + pow(dy, 2)));
        dy = (dy < 0 ? -1 : 1) * min((int)abs(dy), 50 * abs(dy) / sqrt(pow(dx, 2) + pow(dy, 2)));
        x += dx * maxSpeed / 50;
        y += dy * maxSpeed / 50;
    }
    else
    {
        int moving = is_up ^ (is_down << 1) ^ (is_left << 2) ^ (is_right << 3);
        switch (moving)
        {
        case PL_UU:
            y -= (int)maxSpeed;
            is_moving = 1;
            break;
        case PL_DD:
            y += (int)maxSpeed;
            is_moving = 1;
            break;
        case PL_LL:
            x -= (int)maxSpeed;
            is_moving = 1;
            break;
        case PL_RR:
            x += (int)maxSpeed;
            is_moving = 1;
            break;
        case PL_UL:
            x -= (int)maxSpeed / 1.4;
            y -= (int)maxSpeed / 1.4;
            is_moving = 1;
            break;
        case PL_DL:
            x -= (int)maxSpeed / 1.4;
            y += (int)maxSpeed / 1.4;
            is_moving = 1;
            break;
        case PL_UR:
            x += (int)maxSpeed / 1.4;
            y -= (int)maxSpeed / 1.4;
            is_moving = 1;
            break;
        case PL_DR:
            x += (int)maxSpeed / 1.4;
            y += (int)maxSpeed / 1.4;
            is_moving = 1;
            break;
        case PL_LUD:
            x -= (int)maxSpeed;
            is_moving = 1;
            break;
        case PL_RUD:
            x += (int)maxSpeed;
            is_moving = 1;
            break;
        case PL_ULR:
            y -= (int)maxSpeed;
            is_moving = 1;
            break;
        case PL_DLR:
            y += (int)maxSpeed;
            is_moving = 1;
            break;
        case PL_STOP:
        case PL_LRUD:
        case PL_UD:
        case PL_LR:
            is_moving = 0;
            break;
        }
        if (is_moving) facingRight = (moving & PL_RR) ? 1 : ((moving & PL_LL) ? 0 : facingRight);
    }
    //printf("facingRight:%d\n", facingRight);
    x = max(x, 0); x = min(x, bgWidth - 1);
    y = max(y, 0); y = min(y, bgHeight - 1);
    count = (count + is_moving) % FRAME_CHANGE;
    if (count == 1)
    {
        cur_x = (cur_x + 1) % 2;
    }
    cur_y = facingRight ? 1 : 0;
}

//void player::update(ExMessage msg, int bgWidth, int bgHeight, int moving, short &dX, short &dY)
//{
//    if (is_lbutton_down)
//    {
//        //printf("mousex:%6d mousey:%6d dx:%6d dy:%6d\n", this->mousex, this->mousey, dx, dy);
//        facingRight = dX > 0 ? 1 : 0;
//        is_moving = (dX && dY);
//        double delta = sqrt(pow(dX, 2) + pow(dY, 2));
//        dX = (dX < 0 ? -1 : 1) * min(abs(dX), (int)(50.0 * abs(dX) / delta));
//        dY = (dY < 0 ? -1 : 1) * min(abs(dY), (int)(50.0 * abs(dY) / delta));
//        //dx = (dx < 0 ? -1 : 1) * min((int)abs(dx), 50 * abs(dx) / sqrt(pow(dx, 2) + pow(dy, 2)));
//        //dy = (dy < 0 ? -1 : 1) * min((int)abs(dy), 50 * abs(dy) / sqrt(pow(dx, 2) + pow(dy, 2)));
//        x += dX * maxSpeed / 50;
//        y += dY * maxSpeed / 50;
//    }
//    else
//    {
//        //int moving = is_up ^ (is_down << 1) ^ (is_left << 2) ^ (is_right << 3);
//        switch (moving)
//        {
//        case PL_UU:
//            y -= (int)maxSpeed;
//            is_moving = 1;
//            break;
//        case PL_DD:
//            y += (int)maxSpeed;
//            is_moving = 1;
//            break;
//        case PL_LL:
//            x -= (int)maxSpeed;
//            is_moving = 1;
//            break;
//        case PL_RR:
//            x += (int)maxSpeed;
//            is_moving = 1;
//            break;
//        case PL_UL:
//            x -= (int)maxSpeed / 1.4;
//            y -= (int)maxSpeed / 1.4;
//            is_moving = 1;
//            break;
//        case PL_DL:
//            x -= (int)maxSpeed / 1.4;
//            y += (int)maxSpeed / 1.4;
//            is_moving = 1;
//            break;
//        case PL_UR:
//            x += (int)maxSpeed / 1.4;
//            y -= (int)maxSpeed / 1.4;
//            is_moving = 1;
//            break;
//        case PL_DR:
//            x += (int)maxSpeed / 1.4;
//            y += (int)maxSpeed / 1.4;
//            is_moving = 1;
//            break;
//        case PL_LUD:
//            x -= (int)maxSpeed;
//            is_moving = 1;
//            break;
//        case PL_RUD:
//            x += (int)maxSpeed;
//            is_moving = 1;
//            break;
//        case PL_ULR:
//            y -= (int)maxSpeed;
//            is_moving = 1;
//            break;
//        case PL_DLR:
//            y += (int)maxSpeed;
//            is_moving = 1;
//            break;
//        case PL_STOP:
//        case PL_LRUD:
//        case PL_UD:
//        case PL_LR:
//            is_moving = 0;
//            break;
//        }
//        if (is_moving) facingRight = (moving & PL_RR) ? 1 : ((moving & PL_LL) ? 0 : facingRight);
//    }
//    //printf("facingRight:%d\n", facingRight);
//    x = max(x, 0); x = min(x, bgWidth - 1);
//    y = max(y, 0); y = min(y, bgHeight - 1);
//    count = (count + is_moving) % FRAME_CHANGE;
//    if (count == 1)
//    {
//        cur_x = (cur_x + 1) % 2;
//    }
//    cur_y = facingRight ? 1 : 0;
//}

int gameObject::getHeight() const
{
    return height;
}

int gameObject::getWidth() const
{
    return width;
}

int gameObject::getX() const
{
    return x;
}

int gameObject::getY() const
{
    return y;
}

void gameObject::update()
{ }

player::~player()
{ }

gameSystem::gameSystem()
{
	this->init();
}
gameSystem::~gameSystem()
{
}

void gameSystem::init()
{
	this->cameraX = 0;
	this->cameraY = 0;
	this->windowWidth = WIDTH;
	this->windowHeight = HEIGHT;
	this->fps = FPS;
    //this->mousex = 0;
    //this->mousey = 0;
    //this->is_lbutton_down = 0;
    loadimage(&background, _T("wallhaven-6ov8kl_3840x2160.png"));
    this->bgWidth = background.getwidth();
    this->bgHeight = background.getheight();
    this->Pc = player(_T("Reimu.png"), windowWidth / 2, windowHeight / 2, 18, 24);
    initgraph(windowWidth, windowHeight);
    cleardevice();
    putimage(0, 0, windowWidth, windowHeight, &background, cameraX, cameraY);
}

void gameSystem::messageProc()
{
    int moving = 0;
    short dx = 0, dy = 0;
    while (peekmessage(&msg))
    {
        //dispatchMsg(msg, moving);
        //dx = msg.x - this->mousex;
        //dy = msg.y - this->mousey;
        Pc.getMsg(msg);
    }
    Pc.update(msg, bgWidth, bgHeight);
    //修正相机位置
    this->fitCamera();
    //确定绘制人物的位置
    int drawX = Pc.getX() - cameraX;
    int drawY = Pc.getY() - cameraY;
    //修正绘制位置
    drawX = max(drawX, 0); drawX = min(drawX, windowWidth - 1);
    drawY = max(drawY, 0); drawY = min(drawY, windowHeight - 1);
    //绘制帧
    frameDraw(drawX, drawY);
}

void alphaPutImage(IMAGE* src, int drawX, int drawY, int cur_x, int cur_y, int w, int h)
{
    AlphaBlend(GetImageHDC(NULL), drawX, drawY, w, h, GetImageHDC(src), cur_x * w, cur_y * h, w, h, {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA});
}

void player::draw(int drawX, int drawY)
{
    //绘制人物（透明）
    alphaPutImage(&skin, drawX, drawY, cur_x, cur_y, width, height);
    //绘制鼠标位置
    if (is_lbutton_down)
    {
        setlinecolor(LIGHTGRAY);
        setfillcolor(LIGHTGRAY);
        fillcircle(mousex, mousey, 50);
        setfillcolor(WHITE);
        setlinecolor(RED);
        fillcircle(mousex + dx, mousey + dy, 20);
    }
}

void gameSystem::frameDraw(int drawX, int drawY)
{
    //cleardevice();
    putimage(0, 0, windowWidth, windowHeight, &background, cameraX, cameraY);
    Pc.draw(drawX - Pc.getWidth() / 2, drawY - Pc.getHeight() / 2);
}

void gameSystem::fitCamera()
{
    cameraX = Pc.getX() - windowWidth / 2;
    cameraY = Pc.getY() - windowHeight / 2;
    cameraX = max(cameraX, 0); cameraX = min(cameraX, bgWidth - windowWidth);
    cameraY = max(cameraY, 0); cameraY = min(cameraY, bgHeight - windowHeight);
}

//void gameSystem::dispatchMsg(ExMessage msg, int &moving)
//{
//    if (msg.vkcode == VK_ESCAPE) exit(0);
//    int static is_up = 0, is_down = 0, is_left = 0, is_right = 0;
//    switch (msg.message)
//    {
//    case WM_LBUTTONDOWN:
//        setcapture();
//        this->mousex = msg.x;
//        this->mousey = msg.y;
//        this->is_lbutton_down = 1;
//        break;
//    case WM_LBUTTONUP:
//        releasecapture();
//        this->is_lbutton_down = 0;
//        break;
//    case WM_KEYDOWN:
//        switch (msg.vkcode)
//        {
//        case VK_UP:
//            is_up = 1;
//            break;
//        case VK_DOWN:
//            is_down = 1;
//            break;
//        case VK_LEFT:
//            is_left = 1;
//            break;
//        case VK_RIGHT:
//            is_right = 1;
//            break;
//        case 'W':
//            is_up = 1;
//            break;
//        case 'S':
//            is_down = 1;
//            break;
//        case 'A':
//            is_left = 1;
//            break;
//        case 'D':
//            is_right = 1;
//            break;
//        }
//        break;
//    case WM_KEYUP:
//        switch (msg.vkcode)
//        {
//        case VK_UP:
//            is_up = 0;
//            break;
//        case VK_DOWN:
//            is_down = 0;
//            break;
//        case VK_LEFT:
//            is_left = 0;
//            break;
//        case VK_RIGHT:
//            is_right = 0;
//            break;
//        case 'W':
//            is_up = 0;
//            break;
//        case 'S':
//            is_down = 0;
//            break;
//        case 'A':
//            is_left = 0;
//            break;
//        case 'D':
//            is_right = 0;
//            break;
//        }
//        break;
//    default:
//        break;
//    }
//    moving = is_up ^ (is_down << 1) ^ (is_left << 2) ^ (is_right << 3);
//}