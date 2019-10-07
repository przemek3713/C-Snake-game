#ifndef __SNAKE_H__
#define __SNAKE_H__
#include "screen.h"
#include "winsys.h"
#include <vector>
struct Point
{
    int x;
    int y;
};
class CSnake:public CFramedWindow
{
public:
    vector <Point> Waz;
    CSnake(CRect r, char _c = ' ');
    //bools
    bool pause=true;
    bool handleEvent(int key);
    bool lost=false;
    bool tutorial=true;
    bool ustawieniaFabryczne=false;
    //other values
    int score=0;
    unsigned int kierunek=0;
    unsigned int predkoscGry = 20;
    //points
    Point Jedzenie;
    //paints
    void paint();
    void paintSnake();
    void paintScore();
    void paintRest();
    void paintFood();

    //move
    void moveSnake(int X, int Y);
    void moveHead(int Kierunek);
    void moveTail();

    //others
    void defaults();
    void zdobyciePunktu();
    void wykrywaczSmierci();
};

#endif
