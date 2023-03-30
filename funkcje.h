#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Plat.h"
#include "Pilka.h"
#include <vector>

template <class T1, class T2> bool Kolizja(T1& a, T2& b)
{
    return a.prawo() >= b.lewo() && a.lewo() <= b.prawo()
        && a.dol() >= b.gora() && a.gora() <= b.dol();
}

bool czy_kolizja(Plat& a, Pilka& b)
{
    if (!Kolizja(a, b))
        return false;

    if (b.pierwszyR)      
        b.pierwszyR = false;

    b.ruchG();

    if (b.pozycja().x < a.pozycja().x)
        b.ruchL();
    if (b.pozycja().x > a.pozycja().x)
        b.ruchP();

    return true;
}

bool czy_kolizja2(Klocek& a, Pilka& b, int &punkty)
{
    if (!Kolizja(a, b))
        return false;

    
    float przesuniecieL { b.prawo() - a.lewo() };
    float przesuniecieP{ a.prawo() - b.lewo() };
    float przesuniecieG{ b.gora() - a.dol() };
    float przesuniecieD{ a.gora() - b.dol() };
    
    bool zlewej(abs(przesuniecieL) < abs(przesuniecieP));
    bool zgory(abs(przesuniecieG) < abs(przesuniecieD));

    float minX{ zlewej ? przesuniecieL : przesuniecieP };
    float minY{ zgory ? przesuniecieG : przesuniecieD };

    if (abs(minX) < abs(minY))
    {
        zlewej ? b.ruchL() : b.ruchP();
    }
    else 
    {
        zgory ? b.ruchD() : b.ruchG();
    }

    a.usun();
    punkty++;
    return true;
}
