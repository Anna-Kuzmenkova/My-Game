#include <stdio.h>
#include "TXLib.h"

class CPers   ///< класс персонажа
{
 private:

    //------- attributes -----------

    int x = 0, y = 0, w = 0, h = 0, xpic = 0, ypic = 0;
    COLORREF color = 0;
    char schet[5] = "0";
    int  coins = 0;        ///< счётчик монет
    CMap *mapp = NULL;
    HDC pic = NULL;        ///< картинка персонажа

    //------- methods --------------

    void right();
    void left();           ///< расчет положения персонажа от нажатия кнопок
    void up();
    void down();
    void interaction();    ///< взаимодействие персонажа с картой
    void add_coins(int c); ///< добавление очков
    void for_teacher();    ///< быстрый переход на другой уровень (для использования нажмите на пробел)
    void delete_all();     ///< удаление всех картинок
    int  message();        ///< вывод текста с информацией

 public :

    //------- methods --------------

    void draw();           ///< рисование персонажа
    void step();           ///< проверка нажатия кнопок
    void schet_coins();    ///< рисование счётчика
    void start();          ///< рисование заставки

    void init(int xi, int yi, int wi, int hi, int xpici, int ypici, COLORREF colori, CMap &mappi)   ///< инициализация персонажа
    {
        x = xi;
        y = yi;
        w = wi;
        h = hi;
        xpic = xpici;
        ypic = ypici;
        color = colori;
        mapp = &mappi;
        pic = txLoadImage("snake.bmp");
        if(!pic)
        {
            txMessageBox ("Не могу загрузить фон из snake.bmp");
        }
    }

    ~CPers()               ///< деструктор
    {
        delete_all();
    }
};

void CPers::start()
{
    mapp->lifes = 0;
    mapp->level = 6;
    mapp->levels();
    x = 200;
    y = 225;
    xpic = 0;
    ypic = 0;
    while(mapp->get_cell(x + 30, y + 55) != WALL)
    {
        mapp->draw();
        draw();
        y += 10;
        xpic += 49;
        if( xpic > 98)
        {
            xpic = 0;
        }
        mapp->set_cell(x + 30, y + 30, 1, mapp->level);
        txSleep(100);
        txClear();
    }
    ypic = 106;
    xpic = 0;
    w = 48;
    h = 37;
    x += 10;
    y -= 10;
    while(mapp->get_cell(x + 64, y + 30) != WALL)
    {
        mapp->draw();
        draw();
        x += 15;
        xpic += 48;
        if( xpic > 96)
        {
            xpic = 0;
        }
        mapp->set_cell(x + 30, y + 30, 1, mapp->level);
        txSleep(100);
        txClear();
    }
    y -= 10;
    x -= 3;
    ypic = 142;
    xpic = 0;
    while(mapp->get_cell(x + 30, y ) != WALL)
    {
        mapp->draw();
        draw();
        y -= 10;
        xpic += 49;
        if( xpic > 98)
        {
            xpic = 0;
        }
        txSleep(100);
        txClear();
    }
    ypic = 106;
    xpic = 0;
    w = 48;
    h = 37;
    x += 20;
    y += 10;
    while(mapp->get_cell(x + 30, y + 30) != WALL)
    {
        txClear();
        mapp->draw();
        draw();
        x += 15;
        xpic += 48;
        if( xpic > 96)
        {
            xpic = 0;
        }
        txSleep(100);
    }
    mapp->lifes = 3;
    mapp->level = 1;
    mapp->levels();
    x = 580;
    y = 60;
    xpic = 49;
    ypic = 53;
    txSleep(300);
}

void CPers::draw()
{
     Win32::TransparentBlt (txDC(), x, y, w, h, pic, xpic, ypic, w, h, color);
}

void CPers::step()
{
    if(GetAsyncKeyState(VK_SPACE))
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
    interaction();
}
void CPers::right()
{
    ypic = 106;
    w = 48;
    h = 37;
    xpic += 48;
    if( xpic > 96)
    {
        xpic = 0;
    }

    if(mapp->get_cell(x + 54, y + 30) != WALL)
    {
        if(mapp->get_cell(x + 30, y + 30) != HATCH && mapp->get_cell(x + 30, y + 30) != BACK && mapp->get_cell(x + 30, y + 30) != HEART)
        {
            mapp->set_cell(x + 30, y + 30, 1, mapp->level);
        }
        x += 20;
    }

    if(mapp->get_cell(x + 30, y + 30) == HEART && coins >= 6)
    {
        add_coins(-6);
        mapp->lifes += 1;
    }
}
void CPers::left()
{
    ypic = 57;
    w = 49;
    h = 53;
    xpic += 49;
    if( xpic > 98)
    {
        xpic = 0;
    }

    if(mapp->get_cell(x, y + 30) != WALL)
    {
        if(mapp->get_cell(x + 30, y + 30) != 3 && mapp->get_cell(x + 30, y + 30) != 9 && mapp->get_cell(x + 30, y + 30) != 12)
        {
            mapp->set_cell(x + 30, y + 30, 1, mapp->level);
        }
        x -= 20;
    }

    if((mapp->get_cell(x + 30, y + 30) == HATCH) && (mapp->level == 2))
    {
        mapp->level = 3;
        mapp->levels();
        x = 342;
        y = 135;
        xpic = 61;
        ypic = 0;
    }

}
void CPers::up()
{
    ypic = 142;
    w = 49;
    h = 54;
    xpic += 49;
    if( xpic > 98)
    {
        xpic = 0;
    }

    if(mapp->get_cell(x + 30, y) != WALL)
    {
        if(mapp->get_cell(x + 30, y + 30) != 3 && mapp->get_cell(x + 30, y + 30) != 9 && mapp->get_cell(x + 30, y + 30) != 12)
        {
            mapp->set_cell(x + 30, y + 30, 1, mapp->level);
        }
        y -= 20;
    }

    if((mapp->get_cell(x + 30, y + 30) == BACK) && (mapp->level == 2))
    {
        mapp->level = 1;
        mapp->levels();
        x = 605;
        y = 270;
        xpic = 61;
        ypic = 0;
    }

    if((mapp->get_cell(x + 30, y + 30) == BACK) && (mapp->level == 3))
    {
        mapp->level = 2;
        mapp->levels();
        x = 595;
        y = 530;
        xpic = 61;
        ypic = 0;
    }

    if(mapp->get_cell(x + 30, y + 30) == PORT)
    {
        mapp->port = 1;
        mapp->level = 4;
        mapp->levels();
        x = 132;
        y = 135;
    }

}
void CPers::down()
{
    ypic = 0;
    w = 49;
    h = 52;
    xpic += 49;
    if( xpic > 98)
    {
        xpic = 0;
    }

    if(mapp->get_cell(x + 30, y + 55) != WALL)
    {
        if(mapp->get_cell(x + 30, y + 30) != 3 && mapp->get_cell(x + 30, y + 30) != 9 && mapp->get_cell(x + 30, y + 30) != 12)
        {
            mapp->set_cell(x + 30, y + 30, 1, mapp->level);
        }
        y += 20;
    }
}

void CPers::interaction()
{
    if(mapp->get_cell(x + 30, y + 30) == LAVA)
    {
        if(mapp->potion == 1)
        {
            mapp->remember = mapp->level;
            mapp->potion = 0;
            mapp->level = 5;
            mapp->levels();
            x =  290;
            y =  225;
        }
        else
        {
            mapp->lifes -= 1;
            mapp->potion = 0;
            mapp->key = 0;
            coins = 0;
            if(mapp->level == 1)
            {
                x = 580;
                y = 60;
                xpic = 0;
                ypic = 57;
            }
            else
            {
                if(mapp->level == 3)
                {
                    x = 337;
                    y = 135;
                    xpic = 49;
                    ypic = 0;
                    w = 49;
                    h = 52;
                }
            }
        }
    }

    if(mapp->get_cell(x + 30, y + 30) == COIN)
    {
        add_coins(1);
    }

    if((mapp->get_cell(x + 30, y + 30) == PORT) && (mapp->port == 1))
    {
        mapp->port = 0;
        mapp->level = 1;
        mapp->levels();
        x = 350;
        y = 220;
    }

    if(mapp->get_cell(x + 28, y + 30) == POTION)
    {
        mapp->potion = 1;
    }

    if((mapp->get_cell(x + 30, y + 30) == HATCH) && (mapp->level == 1))
    {
        mapp->level = 2;
        mapp->levels();
        x = 72;
        y = 135;
        xpic = 61;
        ypic = 0;
    }

    if((mapp->get_cell(x + 30, y + 30) == HATCH) && (mapp->level == 5))
    {
        mapp->level = mapp->remember;
        mapp->levels();
        if(mapp->remember == 1)
        {
            x = 580;
            y = 60;
            xpic = 49;
            ypic = 53;
        }
        if(mapp->remember == 3)
        {
            x = 342;
            y = 135;
            xpic = 49;
            ypic = 10;
        }
    }

    if((mapp->get_cell(x + 30, y + 30) == HATCH) && (mapp->level == 3) && (mapp->key == 1))
    {
        message();
        mapp->key = 0;
        mapp->level = 7;
        mapp->levels();
         x = 337;
        y = 75;
        xpic = 49;
        ypic = 0;
        w = 49;
        h = 52;
    }

    if(mapp->get_cell(x + 30, y + 30) == FFALSE)
    {
        mapp->lifes -= 1;
        x = 337;
        y = 75;
        xpic = 49;
        ypic = 0;
    }

    if(mapp->get_cell(x + 30, y + 30) == TTRUE)
    {
        mapp->flag = 1;
    }

    if(mapp->get_cell(x + 30, y + 30) == KEY)
    {
        mapp->key = 1;
    }

}

void CPers::add_coins(int c)
{
     coins += c;
     sprintf(schet, "%d", coins);
}

void CPers::schet_coins()
{
    txSetColor     (TX_BLACK);
    txSetFillColor (TX_WHITE);
    Win32::RoundRect (txDC(), 15, 595, 85, 635, 20, 20);
    txSelectFont ("Arial", 20, 0);
    txDrawText  (15, 595, 85, 635, schet);

}

void CPers::for_teacher()
{
    if(mapp->level == 1)
    {
        mapp->level = 2;
        mapp->levels();
        x = 79;
        y = 135;
        xpic = 61;
        ypic = 0;
    }
    else
    {
        if(mapp->level == 2)
        {
            mapp->level = 3;
            mapp->levels();
            x = 339;
            y = 135;
            xpic = 61;
            ypic = 0;
        }
    }
}

void CPers::delete_all()
{
    txDeleteDC(pic);
    mapp->delete_all();
}

int CPers::message()
{
    txSetFillColor(TX_BLACK);
    txSetColor(TX_WHITE);
    txClear();
    txSelectFont("Comic Sans MS",26, 12);
    txDrawText(50, 50, 665, 600, "Ого, ты уже очень близко к концу, поздравляю! \n\n"
                                 "Сейчас тебя ждёт мини игра, которая проверит твою интуицию и удачу;\n\n"
                                 "- Перед тобой будет 5 люков, и лишь один из них ведёт тебя к победе;\n\n"
                                 "- В случае, если ты выбираешь неправильный люк - у тебя отнимается одна жизнь;\n\n"
                                 "- Но не волнуйся, если ты собирал монеты - у тебя есть возможность докупить жизни и обеспечить себе победу!\n\n"
                                 "- Одна жизнь - 6 монет;\n\n"
                                 "Надеюсь всё понятно, так что удачи тебе!\n\n "
                                 "Чтобы продолжить, нажмите Enter" );
    while(!GetAsyncKeyState(VK_RETURN))
    {
        txSleep(50);
    }
    return 0;
}


