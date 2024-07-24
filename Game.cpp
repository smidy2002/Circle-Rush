#include "Engine.h"
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>
//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 'A', 'B')
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  clear_buffer() - set all pixels in buffer to 'black'
//  is_window_active() - returns true if window is active
//  schedule_quit_game() - quit game after act()


// initialize game data in this function
//int alpha = 255; // Fully opaque
//int red = 255;
//int green = 0;
//int blue = 0;
//int rgb = (red << 16) | (green << 8) | blue;
using namespace std;
bool playerDir;
int a = 700;
int score;
int xo = (SCREEN_WIDTH)/2;
int yo = SCREEN_HEIGHT/2;
float player1X;
float player1Y;
float player2X;
float player2Y;
float enemysX[10] = { -50,-50,-50,-50,-50,-50,-50,-50,-50,-50 };
float enemysY[10] = { -50,-50,-50,-50,-50,-50,-50,-50,-50,-50 };
float enemyDir[10]= { 10,10,10,10,10,10,10,10,10,10 };
int enemyCounter;
float enemyCD;
float friendsY[10] = { -50,-50,-50,-50,-50,-50,-50,-50,-50,-50 };
float friendsX[10] = { -50,-50,-50,-50,-50,-50,-50,-50,-50,-50 };  
float friendDir[10]= { 10,10,10,10,10,10,10,10,10,10 };
int friendCounter;
float friendCD;
float angle;
float pi = 3.14159274101257324219;
uint32_t PlayerColor;
uint32_t EnemyColor;
uint32_t FriendColor;
uint32_t BackgroundColor;
uint32_t NumColor;
bool doOnce;
void initialize()
{
    PlayerColor = (0 << 16) | (0 << 8) | 255;
    EnemyColor = 0;
    FriendColor = (255 << 16) | (255 << 8) | 255;
    BackgroundColor = (100 << 16) | (200 << 8) | 255;
    NumColor = (200 << 16) | (255 << 8) | 100;
    playerDir = 1;
    angle = 0;
    score = 0;
    enemyCounter = 0;
    enemyCD = 0;
    friendCounter = 0;
    friendCD = 0;
}
//draw square with given parameters
void drawS(float x, float y, float r, int color)
{
    int i=x-r;
    while (i < x + r)
    {
        int j = y - r;
        while (j < y + r)
        {
            if ((i >= 0) && (i < SCREEN_WIDTH) && (j >= 0) && (j < SCREEN_HEIGHT))
            {
                buffer[j][i] = color;
            }
            j++;
        }
        i++;
    }
}
void drawNum(float x, float y, char num)
{
    switch (num)
    {
    case '0':
    {
        drawS(x + 10, y, 5, NumColor);
        drawS(x + 20, y, 5, NumColor);
        drawS(x, y + 10, 5, NumColor);
        drawS(x + 30, y + 10, 5, NumColor);
        drawS(x, y + 20, 5, NumColor);
        drawS(x + 30, y + 20, 5, NumColor);
        drawS(x, y + 30, 5, NumColor);
        drawS(x + 30, y + 30, 5, NumColor);
        drawS(x, y + 40, 5, NumColor);
        drawS(x + 30, y + 40, 5, NumColor);
        drawS(x + 10, y + 50, 5, NumColor);
        drawS(x + 20, y + 50, 5, NumColor);
        break;
    }
    case '1':
    {
        drawS(x + 20, y, 5, NumColor);
        drawS(x + 20, y + 10, 5, NumColor);
        drawS(x + 10, y + 10, 5, NumColor);
        drawS(x + 20, y + 20, 5, NumColor);
        drawS(x, y + 20, 5, NumColor);
        drawS(x + 20, y + 30, 5, NumColor);
        drawS(x + 20, y + 40, 5, NumColor);
        drawS(x + 20, y + 50, 5, NumColor);
        break;
    }
    case '2':
    {
        drawS(x + 10, y, 5, NumColor);
        drawS(x + 20, y, 5, NumColor);
        drawS(x, y + 10, 5, NumColor);
        drawS(x + 30, y + 10, 5, NumColor);
        drawS(x + 20, y + 20, 5, NumColor);
        drawS(x + 10, y + 30, 5, NumColor);
        drawS(x, y + 40, 5, NumColor);
        drawS(x, y + 50, 5, NumColor);
        drawS(x + 10, y + 50, 5, NumColor);
        drawS(x + 20, y + 50, 5, NumColor);
        drawS(x + 30, y + 50, 5, NumColor);
        break;
    }
    case '3':
    {
        drawS(x, y, 5, NumColor);
        drawS(x + 10, y, 5, NumColor);
        drawS(x + 20, y, 5, NumColor);
        drawS(x + 30, y + 10, 5, NumColor);
        drawS(x + 10, y+20, 5, NumColor);
        drawS(x + 20, y+20, 5, NumColor);
        drawS(x + 30, y + 30, 5, NumColor);
        drawS(x + 30, y + 40, 5, NumColor);
        drawS(x, y + 50, 5, NumColor);
        drawS(x + 10, y + 50, 5, NumColor);
        drawS(x + 20, y + 50, 5, NumColor);
        break;

    }
    case '4':
    {
        drawS(x + 20, y, 5, NumColor);
        drawS(x + 30, y, 5, NumColor);
        drawS(x + 10, y+10, 5, NumColor);
        drawS(x + 30, y+10, 5, NumColor);
        drawS(x, y + 20, 5, NumColor);
        drawS(x + 30, y + 20, 5, NumColor);
        drawS(x, y + 30, 5, NumColor);
        drawS(x + 10, y + 30, 5, NumColor);
        drawS(x + 20, y + 30, 5, NumColor);
        drawS(x + 30, y + 30, 5, NumColor);
        drawS(x + 30, y + 40, 5, NumColor);
        drawS(x + 30, y + 50, 5, NumColor);
        break;

    }
    case '5':
    {
        drawS(x, y, 5, NumColor);
        drawS(x + 10, y, 5, NumColor);
        drawS(x + 20, y, 5, NumColor);
        drawS(x + 30, y, 5, NumColor);
        drawS(x, y + 10, 5, NumColor);
        drawS(x, y+20, 5, NumColor);
        drawS(x + 10, y+20, 5, NumColor);
        drawS(x + 20, y+20, 5, NumColor);
        drawS(x + 30, y + 30, 5, NumColor);
        drawS(x + 30, y + 40, 5, NumColor);
        drawS(x, y + 50, 5, NumColor);
        drawS(x + 10, y + 50, 5, NumColor);
        drawS(x + 20, y + 50, 5, NumColor);
        break;
    }
    case '6':
    {
        drawS(x + 10, y, 5, NumColor);
        drawS(x + 20, y, 5, NumColor);
        drawS(x, y + 10, 5, NumColor);
        drawS(x + 30, y + 10, 5, NumColor);
        drawS(x, y + 20, 5, NumColor);
        drawS(x + 10, y+30, 5, NumColor);
        drawS(x + 20, y+30, 5, NumColor);
        drawS(x, y + 30, 5, NumColor);
        drawS(x, y + 40, 5, NumColor);
        drawS(x + 30, y + 40, 5, NumColor);
        drawS(x + 10, y + 50, 5, NumColor);
        drawS(x + 20, y + 50, 5, NumColor);
        break;
    }
    case '7':
    {
        drawS(x, y, 5, NumColor);
        drawS(x + 10, y, 5, NumColor);
        drawS(x + 20, y, 5, NumColor);
        drawS(x + 30, y, 5, NumColor);
        drawS(x + 30, y+10, 5, NumColor);
        drawS(x + 20, y+20, 5, NumColor);
        drawS(x + 10, y + 30, 5, NumColor);
        drawS(x + 10, y + 40, 5, NumColor);
        drawS(x + 10, y + 50, 5, NumColor);
        break;
    }
    case '8':
    {
        drawS(x + 10, y, 5, NumColor);
        drawS(x + 20, y, 5, NumColor);
        drawS(x, y + 10, 5, NumColor);
        drawS(x + 30, y + 10, 5, NumColor);
        drawS(x, y + 20, 5, NumColor);
        drawS(x + 30, y + 30, 5, NumColor);
        drawS(x, y + 40, 5, NumColor);
        drawS(x + 30, y + 40, 5, NumColor);
        drawS(x + 10, y + 50, 5, NumColor);
        drawS(x + 20, y + 50, 5, NumColor);
        drawS(x + 10, y + 20, 5, NumColor);
        drawS(x + 20, y + 20, 5, NumColor);
        drawS(x + 10, y + 30, 5, NumColor);
        drawS(x + 20, y + 30, 5, NumColor);
        break;
    }
    case '9':
    {
        drawS(x + 10, y, 5, NumColor);
        drawS(x + 20, y, 5, NumColor);
        drawS(x, y + 10, 5, NumColor);
        drawS(x + 30, y + 10, 5, NumColor);
        drawS(x, y + 20, 5, NumColor);
        drawS(x + 30, y + 20, 5, NumColor);
        drawS(x + 30, y + 30, 5, NumColor);
        drawS(x + 30, y + 40, 5, NumColor);
        drawS(x + 10, y + 50, 5, NumColor);
        drawS(x + 20, y + 50, 5, NumColor);
        drawS(x + 10, y + 30, 5, NumColor);
        drawS(x + 20, y + 30, 5, NumColor);
        break;
    }
    }
}
void drawScore(string a)
{
    int i = a.size();
    int j = 0;
    while (i > 0)
    {
        drawNum(980 - i * 50, 30, a[j]);
        i--;
        j++;
    }
}
// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
    if (is_key_pressed(VK_SPACE)&&(doOnce))
    {
        doOnce = 0;// close the gate
        if (playerDir == 1)
        {playerDir = 0;}
        else
        {playerDir = 1;}
    }
    if (!is_key_pressed(VK_SPACE)) {doOnce = 1;}// open the gate
    //player draw setup
    if (playerDir == 1)
    {
        angle += (1.5*pi * dt);
    }
    else
    {
        angle -= (1.5*pi * dt);
    }
    player1X = xo + 100 * cos(angle);
    player1Y = yo + 100 * sin(angle);
    player2X = xo + 100 * cos(angle-pi);
    player2Y = yo + 100 * sin(angle-pi);
    //enemy draw setup
    enemyCD += dt;
    srand(time(0));
    if (enemyCD > (rand() % (9 ) + 3))
    {
        enemysX[enemyCounter] = -30+30;
        enemysY[enemyCounter] = rand() % (SCREEN_HEIGHT + 30 + 1) - 100;
        enemyDir[enemyCounter] = (player1Y - enemysY[enemyCounter]) / (player1X - enemysX[enemyCounter]); 
        enemyCounter++; if (enemyCounter == 10) { enemyCounter = 0; }
        enemyCD = 0;
    }
    //make ememys moove
    int i = 0;
    while (i < size(enemysX))
    {
        if (enemyDir[i]==10){}
        else
        {
            enemysX[i] += cos(enemyDir[i]) * dt * 100;
            enemysY[i] += sin(enemyDir[i]) * dt * 100;
        }
            i++;
    }
    //friend draw setup
    if (enemyCD != 0); 
    {
        friendCD += dt;
        srand(time(0));
        if (friendCD > (rand() % (9 ) + 2))
        {
            friendsX[friendCounter] = -30 + 30;
            friendsY[friendCounter] = rand() % (SCREEN_HEIGHT + 30 + 1) - 30;
            friendDir[friendCounter] = (player1Y - friendsY[friendCounter]) / (player1X - friendsX[friendCounter]);
            friendCounter++; if (friendCounter == 10) { friendCounter = 0; }
            friendCD = 0;
        }
    }
    //make friends moove
    i = 0;
    while (i < size(friendsX))
    {
        if (friendDir[i] == 10) {}
        else
        {
            friendsX[i] += cos(friendDir[i]) * dt * 120;
            friendsY[i] += sin(friendDir[i]) * dt * 120;
        }
        i++;
    }
  if (is_key_pressed(VK_ESCAPE))
    schedule_quit_game();

}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)
void draw()
{
    //clear_buffer();
    drawS(xo, yo, 1024, BackgroundColor);
    //draw player
    drawS(player1X, player1Y , 10, PlayerColor);
    drawS(player2X, player2Y, 10, PlayerColor);
    //draw enemys
    int i = 0;
    while (i < size(enemysX))
    {
        if ((enemysX[i] >= 0) && (enemysX[i] < SCREEN_WIDTH) && (enemysY[i] >= 0) && (enemysY[i] < SCREEN_HEIGHT))
        if (buffer[int(enemysY[i])][int(enemysX[i])] == PlayerColor) { schedule_quit_game(); }
        drawS(enemysX[i], enemysY[i], 15, EnemyColor);
        i++;
    }
    //draw friends
    i = 0;
    while (i < size(friendsX))
    {
        if ((friendsX[i] >= 0) && (friendsX[i] < SCREEN_WIDTH) && (friendsY[i] >= 0) && (friendsY[i] < SCREEN_HEIGHT))
            if (buffer[int(friendsY[i])][int(friendsX[i])] == PlayerColor) { score++; friendsX[i] = -100; friendsY[i] = -100; friendDir[i] = 10;/*добавлять бвлл и удалять обьект*/ }
        drawS(friendsX[i], friendsY[i], 15, FriendColor);
        i++;
    }
    drawScore(std::to_string(score));
}

// free game data in this function
void finalize()
{
    std::cout << "hello";
}

