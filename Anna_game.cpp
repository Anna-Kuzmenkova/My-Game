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
    txDrawText(50, 10, 665, 640, "Приветствую тебя, игрок.\n\n"
                      "Для начала быстрые правила:\n\n"
                      "- Для передвижения персонажа нажимайте на клавиши со стрелками;\n\n"
                      "- Вы можете собирать монеты, их счётчик будет виден в левом нижнем углу;\n\n"
                      "- У вас есть жизни, количество которых отображается в правом верхнем углу;\n\n"
                      "- В случае потери всех жизней - вы проигрываете, если дойдёте до конца - выигрываете;\n\n"
                      "- Игру можно завершить в любой момент нажатием кнопки Escape, но тогда придётся начинать занова;\n\n"
                      "На этом всё, желаю удачи!\n\n"
                      "Для пропуска правил нажмите Enter" );
    while(!GetAsyncKeyState(VK_RETURN))
    {
        txSleep(50);
    }
    return 0;
}

