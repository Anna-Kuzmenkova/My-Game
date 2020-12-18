#include <stdio.h>
#include "TXLib.h"

//             0     1     2      3     4     5     6       7     8    9      10     11     12
enum cellType{ROAD, PERS, WALL, HATCH, LAVA, COIN, PORT, POTION, KEY, BACK, FFALSE, TTRUE, HEART};

struct Maze   ///< структура лабиринта
{
    int maze[7][10][11] = {{{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
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
                            {2, 9, 2, 2, 0, 0, 0, 0, 0, 0, 2},
                            {2, 0, 0, 2, 0, 2, 2, 2, 2, 0, 2},
                            {2, 2, 0, 2, 0, 2, 0, 0, 0, 0, 2},     ///< второй уровень
                            {2, 0, 0, 0, 0, 2, 0, 2, 2, 2, 2},
                            {2, 0, 2, 0, 2, 2, 0, 0, 0, 0, 2},
                            {2, 0, 2, 0, 2, 2, 2, 2, 2, 0, 2},
                            {2, 0, 2, 0, 5, 5, 5, 2, 2, 0, 2},
                            {2, 0, 2, 0, 5, 5, 5, 2, 3, 0, 2},
                            {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}},

                           {{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                            {2, 0, 0, 0, 2, 9, 2, 0, 0, 0, 2},
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
                            {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}},

                           {{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                            {4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4},
                            {4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4},
                            {4, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2},     ///< заставка
                            {4, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0},
                            {4, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2},
                            {4, 2, 2, 0, 5, 5, 5, 0, 2, 2, 4},
                            {4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4},
                            {4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4},
                            {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}},

                           {{2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2},
                            {2,  2,  2,  2,  2,  0,  2,  2,  2,  2, 2},
                            {2,  2,  2,  2,  2,  0,  2,  2,  2,  2, 2},
                            {2,  2,  2,  2,  2,  0,  0,  0,  0, 12, 2},     ///< уровень конца
                            {2,  2,  2,  2,  2,  0,  2,  2,  2,  2, 2},
                            {2,  0,  0,  0,  0,  0,  0,  0,  0,  0, 2},
                            {2,  0,  2,  0,  2,  0,  2,  0,  2,  0, 2},
                            {2,  0,  2,  0,  2,  0,  2,  0,  2,  0, 2},
                            {2, 10,  2, 10,  2, 10,  2, 11,  2, 10, 2},
                            {2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2}}
                          };
};

class CMap    ///< класс карты
{
 private:

    //------- attributes -----------

    int  maze[10][11];             ///< матрица
    int  width = 65;               ///< ширина одной клетки карты
    bool prov = true;              ///< переменная для проверки окончания игры
    HDC  pic = NULL;               ///< картинки для лабиринта
    HDC  endd = NULL;              ///< картинки конца игры
    Maze *all_levels = NULL;

 public:
    //------- attributes -----------

    int level = 1;                 ///< номер уровня
    int port = 0;                  ///< переменная проверки портала
    int potion = 0;                ///< переменная проверки наличия зелья
    int key = 0;                   ///< переменная проверки наличия ключа
    int remember = 0;              ///< вспомогательная переменная для запоминания чего-нибудь
    int lifes = 3;                 ///< количество жизней
    int flag = 0;                  ///< условие победы в игре

    //------- methods --------------

    void init(Maze &all_levels1)   ///< инициализация карты
    {
        all_levels = &all_levels1;
        pic = txLoadImage ("For_maze.bmp");
        endd = txLoadImage ("end.bmp");
        if(!pic)
        {
            txMessageBox ("Не могу загрузить фон из For_maze_3.bmp");
        }
        if (!endd)
        {
            txMessageBox ("Не могу загрузить фон из end_1.bmp");
        }
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 11; j++)
            {
                maze[i][j] = all_levels->maze[0][i][j];
            }
        }
    }

    void levels();                                      ///< заполнение текущего уровня
    int  get_cell(int x, int y);                        ///< получение содержимого клетки, расположенной в точке с координатами x, y
    void set_cell(int x, int y, int type, int level);   ///< запись числа в клетку
    void draw();                                        ///< рисование карты
    void draw_end();                                    ///< рисование концовки
    void delete_all();                                  ///< удаление всех картинок
    int  proverka();                                    ///< проверка окончания игры
};

void CMap::delete_all()
{
    txDeleteDC(pic);
    txDeleteDC(endd);
}

void CMap::draw_end()
{
    int pc = 1430;
    if(lifes == 0)
        pc = 715;
    if(flag == 1)
        pc = 0;
    txBitBlt(txDC(), 0, 0, 715, 650, endd, pc, 0);
}

void CMap::levels()
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
                if(level == 5)
                    maze[i][j] = all_levels->maze[4][i][j];
                if(level == 6)
                    maze[i][j] = all_levels->maze[5][i][j];
                if(level == 7)
                    maze[i][j] = all_levels->maze[6][i][j];
            }
        }
    }
}

int CMap::get_cell(int x, int y)
{
    int j = x / width;
    int i = y / width;
    return maze[i][j];
}

void CMap::set_cell(int x, int y, int type, int leveli)
{
    int j = x / width;
    int i = y / width;
    maze[i][j] = type;
    all_levels->maze[leveli - 1][i][j] = type;
}

void CMap::draw()
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            if(maze[i][j] == WALL)
            {
                txBitBlt (txDC(), width * j, width * i, width, width, pic, width, 0);
            }
            if(maze[i][j] == ROAD || maze[i][j] == PERS || maze[i][j] == COIN || maze[i][j] == PORT || maze[i][j] == POTION || maze[i][j] == KEY)
            {
                txBitBlt (txDC(), width * j, width * i, width, width, pic, width * 2, 0);
            }
            if(maze[i][j] == HATCH || maze[i][j] == BACK || maze[i][j] == FFALSE || maze[i][j] == TTRUE)
            {
                txBitBlt (txDC(), width * j, width * i, width, width, pic, 0, 0);
            }
            if(maze[i][j] == LAVA)
            {
                txBitBlt (txDC(), width * j, width * i, width, width, pic, 195, 0);
            }
            if(maze[i][j] == COIN)
            {
                Win32::TransparentBlt (txDC(), width * j + 12, width * i + 12, 40, 40, pic, 260, 0, 40, 40, RGB(255, 255, 255));
            }
            if(maze[i][j] == PORT)
            {
                Win32::TransparentBlt (txDC(), width * j, width * i , width, width, pic, 301, 0, width, width, RGB(0, 0, 0));
            }
            if(maze[i][j] == POTION)
            {
                Win32::TransparentBlt (txDC(), width * j, width * i, width, width, pic, 366, 0, width, width, RGB(255, 255, 255));
            }
            if(maze[i][j] == KEY)
            {
                Win32::TransparentBlt (txDC(), width * j, width * i, width, width, pic, 476, 0, width, width, RGB(255, 255, 255));
            }
            if(lifes >= 1)
            {
                Win32::TransparentBlt (txDC(), 0, 0, 45, 45, pic, 431, 0, 45, 45, RGB(255, 255, 255));
                if(lifes >= 2)
                {
                    Win32::TransparentBlt (txDC(), 45, 0, 45, 45, pic, 431, 0, 45, 45, RGB(255, 255, 255));
                    if(lifes >= 3)
                    {
                        Win32::TransparentBlt (txDC(), 90, 0, 45, 45, pic, 431, 0, 45, 45, RGB(255, 255, 255));
                        if(lifes >= 4)
                        {
                            Win32::TransparentBlt (txDC(), 135, 0, 45, 45, pic, 431, 0, 45, 45, RGB(255, 255, 255));
                            if(lifes >= 5)
                            {
                                Win32::TransparentBlt (txDC(), 180, 0, 45, 45, pic, 431, 0, 45, 45, RGB(255, 255, 255));
                                if(lifes == 6)
                                {
                                    Win32::TransparentBlt (txDC(), 225, 0, 45, 45, pic, 431, 0, 45, 45, RGB(255, 255, 255));
                                }
                            }
                        }
                    }
                }
            }
            if(potion == 1)
            {
                Win32::TransparentBlt (txDC(), 650, 0, width, width, pic, 366, 0, width, width, RGB(255, 255, 255));
            }
            if(key == 1)
            {
                Win32::TransparentBlt (txDC(), 650, 0, width, width, pic, 476, 0, width, width, RGB(255, 255, 255));
            }
            if((maze[i][j] == HATCH) && (level == 3))
            {
                Win32::TransparentBlt (txDC(), width * j + 2, width * i + 2, 60, 60, pic, 541, 0, 60, 60, RGB(255, 255, 255));
            }
            if(maze[i][j] == HEART)
            {
                txBitBlt (txDC(), width * j, width * i, width, width, pic, 601, 0);
            }
        }
    }

}

int CMap::proverka()
{
   if((flag == 1) || (lifes == 0) || (GetAsyncKeyState(VK_ESCAPE)))
   {
       prov = false;
   }
   return prov;
}

