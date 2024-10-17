// easyx.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//#include <iostream>
#include<conio.h>
#include"graphics.h"
#include"windows.h"
#include"math.h"
#include"time.h"

#define WIDTH 800
#define HEIGHT 600

int x = 400, y = 300, r = 10;
short mousex=400, mousey=300;
const double maxSpeed = 5;

int is_lbutton_down = 0;

int is_up = 0, is_down = 0, is_left = 0, is_right = 0;

int main()
{
    //std::cout << "Hello World!\n";
    initgraph(WIDTH, HEIGHT);
    setbkcolor(WHITE);
    cleardevice();
    ExMessage msg;
    setcolor(BLACK);
    setfillcolor(BLACK);
    circle(x, y, r);
    while (true)
    {
        clock_t start = clock();
        while (peekmessage(&msg))
        {
            //if (msg.message == WM_QUIT) return 0;
            if (msg.vkcode == VK_ESCAPE) return 0;
            if (msg.message == WM_LBUTTONDOWN)
            {
                mousex = msg.x;
                mousey = msg.y;
                is_lbutton_down = 1;
            }
            else if (msg.message == WM_LBUTTONUP)
            {
                is_lbutton_down = 0;
            }
            if (msg.message == WM_KEYDOWN)
            {
                switch (msg.vkcode)
                {
                case VK_UP:
                    is_up = 1;
                    break;
                case VK_DOWN:
                    is_down = 1;
                    break;
                case VK_LEFT:
                    is_left = 1;
                    break;
                case VK_RIGHT:
                    is_right = 1;
                    break;
                case 'W':
                    is_up = 1;
                    break;
                case 'S':
                    is_down = 1;
                    break;
                case 'A':
                    is_left = 1;
                    break;
                case 'D':
                    is_right = 1;
                    break;
                }
            }
            else if (msg.message == WM_KEYUP)
            {
                switch (msg.vkcode)
                {
                case VK_UP:
                    is_up = 0;
                    break;
                case VK_DOWN:
                    is_down = 0;
                    break;
                case VK_LEFT:
                    is_left = 0;
                    break;
                case VK_RIGHT:
                    is_right = 0;
                    break;
                case 'W':
                    is_up = 0;
                    break;
                case 'S':
                    is_down = 0;
                    break;
                case 'A':
                    is_left = 0;
                    break;
                case 'D':
                    is_right = 0;
                    break;
                }
            }
        }

        if (is_lbutton_down)
        //peekmessage(&msg);
        //if (msg.vkcode == VK_ESCAPE) return 0;
        //if (msg.lbutton)
        {
            short dx = msg.x - mousex;
            short dy = msg.y - mousey;
            dx = (dx < 0 ? -1 : 1)*min((int)abs(dx),50*abs(dx)/sqrt(pow(dx,2)+pow(dy,2)));
            dy = (dy < 0 ? -1 : 1)*min((int)abs(dy),50*abs(dy)/sqrt(pow(dx,2)+pow(dy,2)));
            x += dx*maxSpeed/50;
            y += dy*maxSpeed/50;
            //x=max(x,0);x=min(x,799);
            //y=max(y,0);y=min(y,599);
            cleardevice();
            setcolor(BLACK);
            setfillcolor(BLACK);
            fillcircle(mousex, mousey, 50);
            setfillcolor(WHITE);
            setcolor(RED);
            fillcircle(mousex+ dx, mousey + dy,20);
            //setcolor(BLACK);
            //circle(x, y, r);
            //Sleep(10);
            //continue;
        }
        else if (!is_lbutton_down)
        {
            cleardevice();
        }
        if (is_up)
        {
            y -= is_left^is_right?maxSpeed/2+1:maxSpeed;
        }
        if (is_down)
        {
            y += is_left^is_right?maxSpeed/2+1:maxSpeed;
        }
        if (is_left)
        {
            x -= is_up^is_down?maxSpeed/2+1:maxSpeed;
        }
        if (is_right)
        {
            x += is_up^is_down?maxSpeed/2+1:maxSpeed;
        }
        x=max(x,0);x=min(x,799);
        y=max(y,0);y=min(y,599);
        setcolor(BLACK);
        circle(x, y, r);
        //else if(!msg.lbutton)
        //{
        //    mousex = msg.x;
        //    mousey = msg.y;
        //    cleardevice();
        //    circle(x, y, r);
        //    //Sleep(10);
        //    //continue;
        //}
        clock_t end = clock();
        int elapsed = (int)(end - start)*1000/CLOCKS_PER_SEC;
        if (elapsed < 1000 / 75)
        {
            Sleep(1000 / 75 - elapsed);
        }
        //Sleep(16);
    }
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
