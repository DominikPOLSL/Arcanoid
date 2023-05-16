#pragma once
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Plat.h"
#include "Pilka.h"
#include "Bonus.h"
#include <vector>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

inline void zapis(int wynik, std::string gracz)
{
    
    std::fstream file("wyniki.txt", std::ios::app | std::ios::out);

    fs::path stare = fs::path{ fs::current_path() / "wyniki.txt" };
    fs::path folder = fs::path{ fs::current_path() / "Wyniki" };
    fs::path nowe = fs::path{ fs::current_path() / "Wyniki/wyniki.txt" };
    std::cout << "Gracz: " << gracz << " -> " << wynik << " pkt\n";

    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    file << "Gracz: " << gracz << " -> " << wynik << " pkt     " << std::ctime(&end_time) << "\n";
    file.close();

    if(!fs::exists(folder))
        fs::create_directory(folder);

    if (fs::exists(nowe))
        fs::remove(nowe);

    fs::copy(stare, nowe);

}
template <class tekstura2, class T2> bool Kolizja(tekstura2& a, T2& b)
{
    return a.prawo() >= b.lewo() && a.lewo() <= b.prawo()
        && a.dol() >= b.gora() && a.gora() <= b.dol();
}

inline bool czy_kolizja(Plat& a, Pilka& b)
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



inline unsigned randR()
{
    unsigned short lfsr = 0xACE1u;
    unsigned bit;
    bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
    return lfsr = (lfsr >> 1) | (bit << 15);
}

inline bool czy_kolizja2(Klocek& a, Pilka& b, int &punkty, std::vector<Bonus>&bonusy)
{   
    int r = 0;
    if (!Kolizja(a, b))
        return false;
    else
    {
        r = randR() % 20;
        //std::cout <<  "  " << r;
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

inline void start(sf::Font&font, sf::Text& text, sf::Text & poziomTrudnosci, sf::Text& wybierz2, sf::Text &autor, sf::Texture &tekstura1, sf::Texture &tekstura2, sf::Sprite & restartPrzycisk, sf::Sprite& tlo, std::vector<sf::Text>&poziomy, sf::Text &nick, sf::Text &nazwaGracza)
{

    tekstura2.loadFromFile("reset.png");
    font.loadFromFile("arial.ttf");
    tekstura1.loadFromFile("bg1.png");
    restartPrzycisk.setTexture(tekstura2);
    tlo.setTexture(tekstura1);
    tlo.setPosition(0, 0);

    autor.setString("Arcanoid");
    autor.setFont(font);
    autor.setCharacterSize(30);
    autor.setFillColor(sf::Color::White);
    autor.setPosition(150, 50);

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

    nick.setCharacterSize(20);
    nick.setFont(font);
    nick.setPosition(200, 200);

    nazwaGracza.setString("Podaj nazwe gracza: ");
    nazwaGracza.setFont(font);
    nazwaGracza.setCharacterSize(20);
    nazwaGracza.setPosition(125, 150);


    for (int i = 1; i <= 7; i++)
    {
        poziomTrudnosci.setString(std::to_string(i));
        poziomTrudnosci.setPosition(50 * i, 400);
        poziomy.push_back(poziomTrudnosci);
    }
}

inline void wyborPoziomu(int wyborPoziom, sf::Sprite &restartPrzycisk, int &y)
{
    switch (wyborPoziom)
    {
        case 0: { y = 1; restartPrzycisk.setPosition(250, y * 20 + 200); break;  }
        case 1: { y = 2; restartPrzycisk.setPosition(250, y * 20 + 200); break;  }
        case 2: { y = 3; restartPrzycisk.setPosition(250, y * 20 + 200); break;  }
        case 3: { y = 4; restartPrzycisk.setPosition(250, y * 20 + 200); break;  }
        case 4: { y = 5; restartPrzycisk.setPosition(250, y * 20 + 200); break;  }
        case 5: { y = 6; restartPrzycisk.setPosition(250, y * 20 + 200); break;  }
        case 6: { y = 7; restartPrzycisk.setPosition(250, y * 20 + 200); break;  }
        default: { y = 1; restartPrzycisk.setPosition(250, y * 20 + 200); break; }
    }
}
