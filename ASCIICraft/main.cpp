#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <fstream>
using namespace std;
void clearScreen()
{
    short posx = 0;
    short posy = 0;
    COORD coord = {posx, posy};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
char Map[60][66] =
{


    "                                                                 ",
    "                                                                 ",
    "                                                                 ",
    "                                                                 ",
    "                                                                 ",
    "                                                                 ",
    "                                                                 ",
    "                                                                 ",
    "                                                                 ",
    "                                                                 ",
    "                                                                 ",
    "                                                                 ",
    "                                                                 ",
    "                                                                 ",
    "                                                                 ",
    "                                                                 ",
    "                                                                 ",
    "                                                                 ",
    "                                                                 ",
    "                                                                 ",
    "#################################################################",
    "#################################################################",
    "#################################################################"

};
int n = 1;
int x = 8, y = 1;
void showmap(int selection)
{
    for(int i = 0; i <= 40; i++)
    {
        for(int j = selection; j <= selection + 40; j++)
        {
            printf("%c", Map[i][j]);
        }
        putchar('\n');
    }
}
bool jumping = false;
bool flying = false;
ofstream save;
ifstream load;
int direction = 2;
int main()
{
    for( ; ; )
    {
        if(!flying)
        {
            switch(Map[y+1][x])
            {
            case ' ':
            {
                y++;
                Map[y-1][x] = ' ';
                Map[y][x] = 1;
                break;
            }
            default:
            {
                jumping = false;
            }
            }
        }
        if(GetAsyncKeyState('H'))
        {
            save.open("level.bin",ios::out |ios::binary);
            for(int g = 0; g < 60; g++)
            {
                for(int h = 0; h < 66; h++)
                {
                    save << Map[g][h];
                }
                save << endl;
            }
        }
        if(GetAsyncKeyState(VK_RIGHT))
        {
            switch(Map[y][x+1])
            {
            case ' ':
            {
                x++;
                Map[y][x-1] = ' ';
                Map[y][x] = 1;
                n++;
            }
            }
        }
        else if(GetAsyncKeyState(VK_LEFT))
        {
            switch(Map[y][x-1])
            {
            case ' ':
            {
                x--;
                Map[y][x+1] = ' ';
                Map[y][x] = 1;
                n--;
            }
            }
        }
        else if(GetAsyncKeyState(VK_UP) && flying)
        {
            switch(Map[y-1][x])
            {
            case ' ':
            {
                y--;
                Map[y+1][x] = ' ';
                Map[y][x] = 1;
            }
            }
        }
        else if(GetAsyncKeyState(VK_DOWN) && flying)
        {
            switch(Map[y+1][x])
            {
            case ' ':
            {
                y++;
                Map[y-1][x] = ' ';
                Map[y][x] = 1;
            }
            }
        }
        else if(GetAsyncKeyState('F') && !flying)
        {
            flying = true;
        }
        else if(GetAsyncKeyState('G') && flying)
        {
            flying = false;
        }
        if(GetAsyncKeyState(VK_SPACE) && !jumping && !flying)
        {
            jumping = true;
            for(int i = 0; i < 3; i++)
            {
                switch(Map[y-1][x])
                {
                case ' ':
                {
                    y--;
                    Map[y+1][x] = ' ';
                    Map[y][x] = 1;
                }
                }
            }
        }
        else if(GetAsyncKeyState('W'))
        {
            direction = 1;
        }
        else if(GetAsyncKeyState('A'))
        {
            direction = 2;
        }
        else if(GetAsyncKeyState('S'))
        {
            direction = 3;
        }
        else if(GetAsyncKeyState('D'))
        {
            direction = 4;
        }
        if(GetAsyncKeyState(VK_CONTROL))
        {
            if(direction == 1)
            {
                Map[y-1][x] = '#';
            }
            else if(direction == 2)
            {
                Map[y][x-1] = '#';
            }
            else if(direction == 3)
            {
                Map[y+1][x] = '#';
            }
            else if(direction == 4)
            {
                Map[y][x+1] = '#';
            }
        }
        if(GetAsyncKeyState(VK_DELETE))
        {
            if(direction == 1)
            {
                Map[y-1][x] = ' ';
            }
            else if(direction == 2)
            {
                Map[y][x-1] = ' ';
            }
            else if(direction == 3)
            {
                Map[y+1][x] = ' ';
            }
            else if(direction == 4)
            {
                Map[y][x+1] = ' ';
            }
        }
        showmap(n);
        clearScreen();
        Map[y][x] = 1;
        Sleep(10);
    }
}
