///\@author Anna Kuzmenkova

// есть недочеты, они в процессе исправления :)
// со счетчиком как-то не сложилось, не понимаю как его сделать
// подсказка: с зельем можно зайти в лаву, но только один раз

#include <stdio.h>
#include "TXLib.h"

struct Maze   ///< структура лабиринта
{
    int maze[5][10][11];

    void init()     ///< инициализация лабиринта
    {
        int mazze[5][10][11] = { {{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                                 {2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
                                 {2, 0, 2, 0, 2, 2, 2, 0, 2, 2, 2},
                                 {2, 0, 2, 0, 2, 6, 2, 0, 2, 3, 2},     ///< первый уровень
                                 {2, 0, 2, 2, 2, 0, 2, 0, 0, 0, 2},
                                 {2, 0, 0, 0, 2, 0, 2, 0, 2, 2, 2},
                                 {2, 4, 2, 0, 2, 0, 2, 0, 0, 0, 2},
                                 {2, 0, 2, 0, 2, 0, 2, 2, 2, 0, 2},
                                 {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
                                 {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}},

                                {{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                                 {2, 1, 2, 2, 0, 0, 0, 0, 0, 0, 2},
                                 {2, 0, 0, 2, 0, 2, 2, 2, 2, 0, 2},
                                 {2, 2, 0, 2, 0, 2, 0, 0, 0, 0, 2},     ///< второй уровень
                                 {2, 0, 0, 0, 0, 2, 0, 2, 2, 2, 2},
                                 {2, 0, 2, 0, 2, 2, 0, 0, 0, 0, 2},
                                 {2, 0, 2, 0, 2, 2, 2, 2, 2, 0, 2},
                                 {2, 0, 2, 0, 5, 5, 5, 2, 2, 0, 2},
                                 {2, 0, 2, 0, 5, 5, 5, 2, 3, 0, 2},
                                 {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}},

                                {{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                                 {2, 0, 0, 0, 2, 0, 2, 0, 0, 0, 2},
                                 {2, 0, 2, 0, 0, 0, 0, 0, 2, 0, 2},
                                 {2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2},     ///< третий уровень
                                 {2, 0, 5, 5, 5, 5, 5, 5, 5, 0, 2},
                                 {2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2},
                                 {2, 0, 0, 0, 0, 0, 0, 4, 2, 0, 2},
                                 {2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2},
                                 {2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 2},
                                 {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}},

                                {{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                                 {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                                 {2, 2, 0, 0, 0, 0, 0, 0, 7, 2, 2},
                                 {2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2},     ///< уровень портала
                                 {2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2},
                                 {2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2},
                                 {2, 2, 0, 5, 5, 5, 0, 0, 0, 2, 2},
                                 {2, 2, 0, 5, 5, 5, 0, 0, 6, 2, 2},
                                 {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                                 {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}},

                                {{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                                 {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                                 {4, 4, 4, 2, 2, 2, 2, 2, 4, 4, 4},
                                 {4, 4, 4, 2, 0, 0, 3, 2, 4, 4, 4},     ///< уровень лавы
                                 {4, 4, 4, 2, 0, 0, 0, 2, 4, 4, 4},
                                 {4, 4, 4, 2, 0, 0, 0, 2, 4, 4, 4},
                                 {4, 4, 4, 2, 8, 0, 0, 2, 4, 4, 4},
                                 {4, 4, 4, 2, 2, 2, 2, 2, 4, 4, 4},
                                 {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                                 {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}}
                            };

        for(int l = 0; l < 5; l++)
        {
            for(int i = 0; i < 10; i++)
            {
                for(int j = 0; j < 11; j++)
                {
                    maze[l][i][j] = mazze[l][i][j];
                }
            }
        }
    }
};

struct Map   ///< структура карты
{
    int maze[10][11]; ///< матрица
    int width = 65;   ///< ширина одной клетки карты
    int level = 1;    ///< номер уровня
    int port = 0;     ///< переменная проверки портала
    int lifes = 3;    ///< количество жизней
    int potion = 0;   ///< переменная проверки наличия зелья
    int key = 0;      ///< переменная проверки наличия ключа
    HDC pic = txLoadImage ("For_maze_2.bmp");    ///< картинки для лабиринта
    HDC endd = txLoadImage ("end.bmp");        ///< картинки конца игры
    Maze *all_levels;

    //------- functions --------------

    void init(Maze &all_levels)     ///< инициализация карты
    {
        this->all_levels = &all_levels;
        if(!pic)
        {
            txMessageBox ("Не могу загрузить фон из For_maze_2.bmp");
        }
        if (!endd)
        {
            txMessageBox ("Не могу загрузить фон из end.bmp");
        }
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 11; j++)
            {
                maze[i][j] = this->all_levels->maze[0][i][j];
            }
        }
    }

    void levels();                                 ///< заполнение текущего уровня
    int get_cell(int x, int y);                    ///< получение содержимого клетки, расположенной в точке с координатами x, y
    void set_cell(int x, int y, int type);         ///< запись числа в клетку
    void draw();                                   ///< рисование карты
    void draw_end();                               ///< рисование концовки
};

struct Pers    ///< структура персонажа
{
    int x, y, w, h, xpic, ypic;
    COLORREF color;
    HDC pic = txLoadImage("raccoon.bmp");
    Map *mapp;
    char info[20];
    int coins = 0;

    //------- functions --------------

    void draw();    ///< рисование персонажа
    void right();
    void left();    ///< рассчет положения персонажа от нажатия кнопок
    void up();
    void down();
    void step();    ///< проверка нажатия кнопок

    void init(int x, int y, int w, int h, int xpic, int ypic, COLORREF color, Map &mapp)   ///< инициализация персонажа
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->xpic = xpic;
        this->ypic = ypic;
        this->color = color;
        this->mapp = &mapp;
        if(!pic)
        {
            txMessageBox ("Не могу загрузить фон из raccoon.bmp");
        }
    }

    void for_teacher();   ///< быстрый переход на другой уровень (для использования нажмите на Enter)
    void delete_all();    ///< удаление всех картинок
};

int main()
{
    txCreateWindow(715,650);

    Maze maze;
    Pers pers;
    Map mapp;

    maze.init();
    mapp.init(maze);
    pers.init(580, 60, 59, 60, 64, 54, TX_WHITE, mapp);

    txBegin();
    while(!(((mapp.get_cell(pers.x + 30, pers.y + 30) == 3) && (mapp.level == 3) && (mapp.key == 1)) || (mapp.lifes == 0)))  ///< условия окончания игры
    {
        txClear();
        pers.step();
        mapp.draw();
        pers.draw();
        txSleep(100);
    }
    txEnd();
    mapp.draw_end();
    pers.delete_all();
    return 0;
}

void Pers::draw()
{
     Win32::TransparentBlt (txDC(), x, y, w , h, pic, xpic, ypic, w, h, color);
}

void Pers::step()
{
    if(GetAsyncKeyState(VK_RETURN))
    {
        for_teacher();
    }
    if(GetAsyncKeyState(VK_RIGHT))
    {
        right();
    }
    if(GetAsyncKeyState(VK_LEFT))
    {
        left();
    }
    if(GetAsyncKeyState(VK_UP))
    {
        up();
    }
    if(GetAsyncKeyState(VK_DOWN))
    {
        down();
    }
}
void Pers::right()
{
    ypic = 2 * h;
    xpic += w - 7;
    if( xpic >=  3 * (w - 7))
    {
        xpic = 0;
    }

    if(mapp->get_cell(x + 54, y + 30) != 2)
    {
        if(mapp->get_cell(x + 30, y + 30) != 3 && mapp->get_cell(x + 30, y + 30) != 6)
        {
            mapp->set_cell(x + 30, y + 30, 1);
        }
        x += 20;
    }

    if(mapp->get_cell(x + 30, y + 30) == 4)
    {
        if(mapp->potion == 1)
        {
            mapp->potion = 0;
            mapp->level = 4;
            mapp->levels();
            x =  290;
            y =  225;
        }
        else
        {
            mapp->lifes -= 1;
            mapp->potion = 0;
            mapp->key = 0;
            if(mapp->level = 1)
            {
                x = 580;
                y = 60;
                xpic = 64;
                ypic = 54;
            }
            else
            {
                if(mapp->level = 3)
                {
                    x = 332;
                    y = 75;
                    xpic = 61;
                    ypic = 0;
                }
            }
        }
    }

    if(mapp->get_cell(x + 30, y + 30) == 5)
    {
        coins++;
    }

    if((mapp->get_cell(x + 30, y + 30) == 6) && (mapp->port == 1))
    {
        mapp->port = 0;
        mapp->level = 1;
        mapp->levels();
        x = 350;
        y = 220;
    }

    if(mapp->get_cell(x + 28, y + 30) == 7)
    {
        mapp->potion = 1;
    }

    if((mapp->get_cell(x + 30, y + 30) == 3) && ((mapp->level == 1) || (mapp->level == 4)))
    {
        mapp->level = 2;
        mapp->levels();
        x = 72;
        y = 75;
        xpic = 61;
        ypic = 0;
    }
}
void Pers::left()
{
    ypic =  h - 4;
    xpic += w - 2;
    if( xpic >= 3 * (w - 2))
    {
        xpic = 0;
    }

    if(mapp->get_cell(x, y + 30) != 2)
    {
        if(mapp->get_cell(x + 30, y + 30) != 3 && mapp->get_cell(x + 30, y + 30) != 6)
        {
            mapp->set_cell(x + 30, y + 30, 1);
        }
        x -= 20;
    }

    if((mapp->get_cell(x + 30, y + 30) == 3) && (mapp->level == 2))
    {
        mapp->level = 3;
        mapp->levels();
        x = 332;
        y = 75;
        xpic = 61;
        ypic = 0;
    }

    if(mapp->get_cell(x + 30, y + 30) == 5)
    {
        coins++;
    }

    if(mapp->get_cell(x + 30, y + 30) == 8)
    {
        mapp->key = 1;
    }
}
void Pers::up()
{
    ypic = 2 * h + 45;
    xpic += w - 4 ;
    if( xpic >= 3 * (w - 4))
    {
        xpic = 0;
    }

    if(mapp->get_cell(x + 30, y + 8) != 2)
    {
        if(mapp->get_cell(x + 30, y + 30) != 3 && mapp->get_cell(x + 30, y + 30) != 6)
        {
            mapp->set_cell(x + 30, y + 30, 1);
        }
        y -= 20;
    }

    if(mapp->get_cell(x + 30, y + 30) == 4)
    {
        if(mapp->potion == 1)
        {
            mapp->potion = 0;
            mapp->level = 4;
            mapp->levels();
            x =  290;
            y =  225;
        }
        else
        {
            mapp->lifes -= 1;
            mapp->potion = 0;
            mapp->key = 0;
            if(mapp->level = 1)
            {
                x = 580;
                y = 60;
                xpic = 64;
                ypic = 54;
            }
            else
            {
                if(mapp->level = 3)
                {
                    x = 332;
                    y = 75;
                    xpic = 61;
                    ypic = 0;
                }
            }
        }
    }

    if((mapp->get_cell(x + 30, y + 30) == 3) && ((mapp->level == 1) || (mapp->level == 4)))
    {
        mapp->level = 2;
        mapp->levels();
        x = 72;
        y = 75;
        xpic = 61;
        ypic = 0;
    }

    if(mapp->get_cell(x + 30, y + 30) == 5)
    {
        coins++;
    }

    if(mapp->get_cell(x + 30, y + 30) == 6)
    {
        mapp->port = 1;
        mapp->levels();
        x = 132;
        y = 135;
    }

    if(mapp->get_cell(x + 15, y + 30) == 7)
    {
        mapp->potion = 1;
    }
}
void Pers::down()
{
    ypic = 0;
    xpic += w - 4;
    if( xpic >= 3 * (w - 4) )
    {
        xpic = 0;
    }

    if(mapp->get_cell(x + 30, y + 55) != 2)
    {
        if(mapp->get_cell(x + 30, y + 30) != 3 && mapp->get_cell(x + 30, y + 30) != 6)
        {
            mapp->set_cell(x + 30, y + 30, 1);
        }
        y += 20;
    }

    if(mapp->get_cell(x + 30, y + 30) == 4)
    {
        if(mapp->potion == 1)
        {
            mapp->potion = 0;
            mapp->level = 4;
            mapp->levels();
            x =  290;
            y =  225;
        }
        else
        {
            mapp->lifes -= 1;
            mapp->potion = 0;
            mapp->key = 0;
            if(mapp->level = 1)
            {
                x = 580;
                y = 60;
                xpic = 64;
                ypic = 54;
            }
            else
            {
                if(mapp->level = 3)
                {
                    x = 332;
                    y = 75;
                    xpic = 61;
                    ypic = 0;
                }
            }
        }
    }

    if(mapp->get_cell(x + 30, y + 30) == 5)
    {
        coins++;
    }

    if((mapp->get_cell(x + 30, y + 30) == 6) && (mapp->port == 1))
    {
        mapp->port = 0;
        mapp->level = 1;
        mapp->levels();
        x = 350;
        y = 220;
    }

    if(mapp->get_cell(x + 30, y + 30) == 8)
    {
        mapp->key = 1;
    }
}

void Pers::for_teacher()
{
    if(mapp->level == 1)
    {
        mapp->level = 2;
        mapp->levels();
        x = 72;
        y = 75;
        xpic = 61;
        ypic = 0;
    }
    else
    {
        if(mapp->level == 2)
        {
            mapp->level = 3;
            mapp->levels();
            x = 332;
            y = 75;
            xpic = 61;
            ypic = 0;
        }
    }
}

void Pers::delete_all()
{
    txDeleteDC(pic);
    txDeleteDC(mapp->pic);
    txDeleteDC(mapp->endd);
}

void Map::draw_end()
{
    if(lifes == 0)  ///< проигрыш
    {
        txBitBlt (txDC(), 0, 0, 715, 650, endd, 715, 0);
    }
    else            ///< победа
    {
        txBitBlt (txDC(), 0, 0, 715, 650, endd, 0, 0);
    }
}

void Map::levels()
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            if(port == 1)
                maze[i][j] = all_levels->maze[3][i][j];
            else
            {
                if(level == 1)
                     maze[i][j] = all_levels->maze[0][i][j];
                if(level == 2)
                     maze[i][j] = all_levels->maze[1][i][j];
                if(level == 3)
                    maze[i][j] = all_levels->maze[2][i][j];
                if(level == 4)
                    maze[i][j] = all_levels->maze[4][i][j];
            }
        }
    }
}

int Map::get_cell(int x, int y)
{
    int j = x / width;
    int i = y / width;
    return maze[i][j];
}

void Map::set_cell(int x, int y, int type)
{
    int j = x / width;
    int i = y / width;
    maze[i][j] = type;
}

void Map::draw()
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            if(maze[i][j] == 2)
            {
                txBitBlt (txDC(), width * j, width * i, width, width, pic, 65, 0);
            }
            if(maze[i][j] == 0 || maze[i][j] == 1 || maze[i][j] == 5 || maze[i][j] == 6 || maze[i][j] == 7 || maze[i][j] == 8)
            {
                txBitBlt (txDC(), width * j, width * i, width, width, pic, 130, 0);
            }
            if(maze[i][j] == 3)
            {
                txBitBlt (txDC(), width * j, width * i, width, width, pic, 0, 0);
            }
            if(maze[i][j] == 4)
            {
                txBitBlt (txDC(), width * j, width * i, width, width, pic, 195, 0);
            }
            if(maze[i][j] == 5)
            {
                Win32::TransparentBlt (txDC(), width * j + 12, width * i + 12, 40, 40, pic, 260, 0, 40, 40, RGB(255, 255, 255));
            }
            if(maze[i][j] == 6)
            {
                Win32::TransparentBlt (txDC(), width * j, width * i , width, width, pic, 301, 0, 65, 65, RGB(0, 0, 0));
            }
            if(maze[i][j] == 7)
            {
                Win32::TransparentBlt (txDC(), width * j, width * i, width, width, pic, 366, 0, 65, 65, RGB(255, 255, 255));
            }
            if(maze[i][j] == 8)
            {
                Win32::TransparentBlt (txDC(), width * j, width * i, width, width, pic, 476, 0, 65, 65, RGB(255, 255, 255));
            }
            if(lifes >= 1)
            {
                Win32::TransparentBlt (txDC(), 0, 0, 45, 45, pic, 431, 0, 45, 45, RGB(255, 255, 255));
                if(lifes >= 2)
                {
                    Win32::TransparentBlt (txDC(), 45, 0, 45, 45, pic, 431, 0, 45, 45, RGB(255, 255, 255));
                    if(lifes == 3)
                    {
                        Win32::TransparentBlt (txDC(), 90, 0, 45, 45, pic, 431, 0, 45, 45, RGB(255, 255, 255));
                    }
                }
            }
            if(potion == 1)
            {
                Win32::TransparentBlt (txDC(), 650, 0, width, width, pic, 366, 0, 65, 65, RGB(255, 255, 255));
            }
            if(key == 1)
            {
                Win32::TransparentBlt (txDC(), 650, 0, width, width, pic, 476, 0, 65, 65, RGB(255, 255, 255));
            }
            if((maze[i][j] == 3) && (level == 3))
            {
                Win32::TransparentBlt (txDC(), width * j + 2, width * i + 2, 60, 60, pic, 541, 0, 60, 60, RGB(255, 255, 255));
            }
        }
    }

}
