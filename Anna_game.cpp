///\@author Anna Kuzmenkova

#include <stdio.h>
#include "TXLib.h"
#include "Cmap.h"
#include "Cpers.h"

int rules();

int main()
{
    txCreateWindow(715,650);

    Maze maze;
    CPers pers;
    CMap mapp;

    mapp.init(maze);
    pers.init(580, 60, 49, 53, 49, 53, TX_WHITE, mapp);

    rules();
    pers.start();

    txBegin();
    while(mapp.proverka())
    {
        txSleep(100);
        txClear();
        pers.step();
        mapp.draw();
        pers.draw();
        pers.schet_coins();
    }
    txEnd();
    mapp.draw_end();
    return 0;
}

int rules()
{
    txSetFillColor(TX_BLACK);
    txSetColor(TX_WHITE);
    txClear();
    txSelectFont("Comic Sans MS",26, 12);
    txDrawText(50, 10, 665, 640, "����������� ����, �����.\n\n"
                      "��� ������ ������� �������:\n\n"
                      "- ��� ������������ ��������� ��������� �� ������� �� ���������;\n\n"
                      "- �� ������ �������� ������, �� ������� ����� ����� � ����� ������ ����;\n\n"
                      "- � ��� ���� �����, ���������� ������� ������������ � ������ ������� ����;\n\n"
                      "- � ������ ������ ���� ������ - �� ������������, ���� ������ �� ����� - �����������;\n\n"
                      "- ���� ����� ��������� � ����� ������ �������� ������ Escape, �� ����� ������� �������� ������;\n\n"
                      "�� ���� ��, ����� �����!\n\n"
                      "��� �������� ������ ������� Enter" );
    while(!GetAsyncKeyState(VK_RETURN))
    {
        txSleep(50);
    }
    return 0;
}

