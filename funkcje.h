#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Plat.h"
#include "Pilka.h"
#include "Bonus.h"
#include <vector>

template <class tekstura2, class T2> bool Kolizja(tekstura2& a, T2& b)
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
    if (b.pozycja().x < a.pozycja().x + 80 && b.pozycja().x > a.pozycja().x)
        b.ruchP2();
    if (b.pozycja().x < a.pozycja().x && b.pozycja().x > a.pozycja().x - 80)
        b.ruchL2();
    if (b.pozycja().x < a.pozycja().x + 30 && b.pozycja().x > a.pozycja().x)
        b.ruchP3();
    if (b.pozycja().x < a.pozycja().x && b.pozycja().x > a.pozycja().x - 30)
        b.ruchL3();



}


unsigned short lfsr = 0xACE1u;
unsigned bit;
unsigned randR()
{
    bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
    return lfsr = (lfsr >> 1) | (bit << 15);
}
bool czy_kolizja2(Klocek& a, Pilka& b, int &punkty, std::vector<Bonus>&bonusy)
{   
    int r = 0;
    if (!Kolizja(a, b))
        return false;
    else
    {
        r = randR() % 20;
        std::cout <<  "  " << r;
        if (r <= 3) //10% szans na bonus
            bonusy.emplace_back(a.pozycja().x,a.pozycja().y);
    }
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

    //b.dodaj();
    a.usun();
    punkty++;
    return true;
}

void start(sf::Font&font, sf::Text& text, sf::Text & poziomTrudnosci, sf::Text& wybierz2, sf::Text &autor, sf::Texture &tekstura1, sf::Texture &tekstura2, sf::Sprite & restartPrzycisk, sf::Sprite& tlo, std::vector<sf::Text>&poziomy)
{

    tekstura2.loadFromFile("reset.png");
    font.loadFromFile("arial.ttf");
    tekstura1.loadFromFile("bg1.png");
    restartPrzycisk.setTexture(tekstura2);
    tlo.setTexture(tekstura1);
    tlo.setPosition(0, 0);

    autor.setString("       Arcanoid\n\nDominik Pindych");
    autor.setFont(font);
    autor.setCharacterSize(30);
    autor.setFillColor(sf::Color::White);
    autor.setPosition(100, 50);

    wybierz2.setString("Poziom trudnosci");
    wybierz2.setFont(font);
    wybierz2.setCharacterSize(30);
    wybierz2.setFillColor(sf::Color::White);
    wybierz2.setPosition(100, 350);

    poziomTrudnosci.setFont(font);
    poziomTrudnosci.setCharacterSize(40);
    poziomTrudnosci.setFillColor(sf::Color::White);


    text.setString("0");
    text.setFont(font);
    text.setCharacterSize(90);
    text.setFillColor(sf::Color::Red);
    text.setPosition(700, 700);

    for (int i = 1; i <= 7; i++)
    {
        poziomTrudnosci.setString(std::to_string(i));
        poziomTrudnosci.setPosition(50 * i, 400);
        poziomy.push_back(poziomTrudnosci);
    }
}
