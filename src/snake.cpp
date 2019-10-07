#include "snake.h"
#include "screen.h"
#include <ctype.h>
#include <time.h>

int odliczanieCzasu=0;

CSnake::CSnake(CRect r, char _c /*=' '*/):
  CFramedWindow(r, _c)
{
}
void CSnake::paintSnake()
{
    for (unsigned int a=0; a<Waz.size(); ++a)
    {
        gotoyx(Waz[a].y,Waz[a].x);
        if (a==0) printl("o");
        else printl("*");
    }
}
void CSnake::paint()
{
    CFramedWindow::paint();
    paintSnake();
    paintScore();
    paintRest();
    paintFood();
}
void CSnake::paintScore()
{
    if (pause==true)
    {
        gotoyx(geom.topleft.y-1,geom.topleft.x);
        printl("|Gra zatrzymana|");
    }
    else
    {
        gotoyx(geom.topleft.y-1,geom.topleft.x);
        printl("|Wynik:%d|",score);
    }
}
void CSnake::paintRest()
{
    if (tutorial==true)
    {
        gotoyx(geom.topleft.y+2,geom.topleft.x+3);
        printl("Wcisnij 'h' dla poradnika");
        gotoyx(geom.topleft.y+3,geom.topleft.x+3);
        printl("Wcisnij 'q' zeby wyjsc");
        gotoyx(geom.topleft.y+4,geom.topleft.x+3);
        printl("Wcisnij 'p' zeby zatrzymac");
        gotoyx(geom.topleft.y+5,geom.topleft.x+3);
        printl("Wcisnij 'r' zeby zrestartowac");
        gotoyx(geom.topleft.y+6,geom.topleft.x+3);
        printl("Strzalki do poruszania gra lub plansza");
    }
    else if (lost==true)
    {
        gotoyx(geom.topleft.y+4,geom.topleft.x+3);
        printl("Przegrales - twoj wynik to: %d",score);
    }
}
void CSnake::paintFood()
{
    gotoyx(Jedzenie.y, Jedzenie.x);
    printl("$");
}
bool CSnake::handleEvent(int key)
{
    defaults();
    zdobyciePunktu();
    wykrywaczSmierci();
    if (pause==true || lost==true)
    {
        switch (key)
        {
            case KEY_UP:
                move (CPoint (0, -1));
                moveSnake(0, -1);
                return true;
            case KEY_DOWN:
                move (CPoint (0, 1));
                moveSnake(0, 1);
                return true;
            case KEY_RIGHT:
                move (CPoint (1, 0));
                moveSnake(1, 0);
                return true;
            case KEY_LEFT:
                move (CPoint (-1, 0));
                moveSnake(-1, 0);
                return true;
            case 'h':
                tutorial == false ? pause = true : pause = false;
                tutorial == true ? tutorial = false : tutorial = true;
                return true;
            case 'p':
                pause = false;
                return true;
            case 'r':
                ustawieniaFabryczne = false;
                return true;

        };
    }
    else if (pause==false && lost==false)
    {
        if (key==KEY_UP)
        {
            moveHead(KEY_UP);
            return true;
        }
        else if (key==KEY_DOWN)
        {
            moveHead(KEY_DOWN);
            return true;
        }
        else if (key==KEY_RIGHT)
        {
            moveHead(KEY_RIGHT);
            return true;
        }
        else if (key==KEY_LEFT)
        {
            moveHead(KEY_LEFT);
            return true;
        }
        else if (key=='h')
        {
            tutorial == false ? pause = true : pause = false;
            tutorial == true ? tutorial = false : tutorial = true;
            return true;
        }
        else if (key=='p')
        {
            pause = true;
            return true;
        }
        else if (key=='r')
        {
            ustawieniaFabryczne = false;
            return true;
        }
        else
        {
            if(((odliczanieCzasu++)%predkoscGry)==0 && pause==false && lost==false)
            {
                moveHead(kierunek);
                paint();
                //jedynie tutaj wystepuje paint, bo jest grupa klas w tym programie
                //za kazdym razem jak funkcja handlEvent zwroci true, to kazdy obiekt
                //w grupie uzywa wlasnej funkcji paint()
                //do tej grupy nalezy kazda klasa ktora wysiwetla cos na ekranie
            }
        }


    }
    //zwracasz tutaj false, dzieki czemu jak klikniesz tab to mozesz przelaczyc na inne okno

    return false;
}
void CSnake::defaults()
{
    if (ustawieniaFabryczne == false)
    {
        Waz.clear();
        Waz.push_back({geom.topleft.x+10,geom.topleft.y+10});
        score = 0;
        if (Waz.size()==1)
        {
            Waz.push_back({geom.topleft.x+11,geom.topleft.y+11});
        }
        Jedzenie = {geom.topleft.x+25,geom.topleft.y+12};
        ustawieniaFabryczne = true;
    }
}
void CSnake::moveSnake(int X, int Y)
{
    for (unsigned int a = 0; a<Waz.size(); ++a)
    {
        Waz[a].x+=X;
        Waz[a].y+=Y;
    }
    Jedzenie.x += X;
    Jedzenie.y += Y;
}
void CSnake::moveHead(int Kierunek)
{
    if (Kierunek==KEY_UP)
    {
        if (kierunek!=KEY_DOWN)
        {
            kierunek = KEY_UP;
            moveTail();
            if (Waz[0].y>geom.topleft.y+1)
            {
                Waz[0].y--;
            }
            else
            {
                Waz[0].y+=17;
            }
        }
    }
    else if (Kierunek==KEY_DOWN)
    {
        if (kierunek!=KEY_UP)
        {
            kierunek = KEY_DOWN;
            moveTail();
            if (Waz[0].y<geom.topleft.y+18)
            {
                Waz[0].y++;
            }
            else
            {
                Waz[0].y-=17;
            }
        }
    }
    else if (Kierunek==KEY_RIGHT)
    {
        if (kierunek!=KEY_LEFT)
        {
            kierunek = KEY_RIGHT;
            moveTail();
            if (Waz[0].x<geom.topleft.x+42)
            {
                Waz[0].x++;
            }
            else
            {
                Waz[0].x-=41;
            }
        }
    }
    else if (Kierunek==KEY_LEFT)
    {
        if (kierunek!=KEY_RIGHT)
        {
            kierunek = KEY_LEFT;
            moveTail();
            if (Waz[0].x>geom.topleft.x+1)
            {
                Waz[0].x--;
            }
            else
            {
                Waz[0].x+=41;
            }
        }
    }
    zdobyciePunktu();
}
void CSnake::moveTail()
{
    for (unsigned int a = Waz.size(); a>0; a--)
    {
        Waz[a]=Waz[a-1];
    }
}
void CSnake::zdobyciePunktu()
{
    srand(time(NULL));
    if (Waz[0].x == Jedzenie.x && Waz[0].y == Jedzenie.y)
    {
        score++;
        Jedzenie.x = (geom.topleft.x+1) + rand()%41;
        Jedzenie.y = (geom.topleft.y+1) + rand()%17;
        for (unsigned int a = 0; a<Waz.size(); a++)
        {
            if (Jedzenie.x == Waz[a].x && Jedzenie.y == Waz[a].y)
            {
                Jedzenie.x = (geom.topleft.x+1) + rand()%41;
                Jedzenie.y = (geom.topleft.y+1) + rand()%17;
                a = 0;
            }
        }
        Waz.push_back({Waz[Waz.size()].x,Waz[Waz.size()].y});
    }
}
void CSnake::wykrywaczSmierci()
{
    for (unsigned int a=1; a<Waz.size(); a++)
    {
        if (Waz[0].x == Waz[a].x && Waz[0].y == Waz[a].y)
        {
            pause = true;
            lost = true;
        }
    }
}