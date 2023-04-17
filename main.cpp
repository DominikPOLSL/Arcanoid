#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <Windows.h>
#include <vector>
#include "Plat.h"
#include "Pilka.h"
#include "Klocek.h"
#include "funkcje.h"

int main()
{ 
        start:

        sf::Font font;
        sf::Text text; //Punkty
        sf::Text poziomT;
        sf::Text wybierz2;
        sf::Text autor;
        sf::Texture tlo1;
        sf::Texture t1;
        sf::Sprite res;
        sf::Sprite tlo;

        t1.loadFromFile("reset.png");
        font.loadFromFile("arial.ttf");
        tlo1.loadFromFile("bg1.png");
        res.setTexture(t1);
        tlo.setTexture(tlo1);
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

        poziomT.setFont(font);
        poziomT.setCharacterSize(40);
        poziomT.setFillColor(sf::Color::White);


        text.setString("0");
        text.setFont(font);
        text.setCharacterSize(90);
        text.setFillColor(sf::Color::Red);
        text.setPosition(700, 700);

        std::vector<sf::Text>poziomy = {};       
        std::vector<sf::Text>szybkosci = {};

        for (int i = 1; i <= 7; i++)
        {           
            poziomT.setString(std::to_string(i));
            poziomT.setPosition(50 * i, 400);
            poziomy.push_back(poziomT);
        }
       
        int wyborPoziom,x = 15,y;
        bool wybrano = false;
        bool zamknij = false;
        sf::RenderWindow window2(sf::VideoMode(400, 500), "Arcanoid - Dominik Pindych ");
        while (window2.isOpen())
        {

            sf::Vector2i pos = sf::Mouse::getPosition(window2);
            auto translated_pos = window2.mapPixelToCoords(pos);
            sf::Event event;

            while (window2.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    zamknij = true;
                    window2.close();
                }

                for (int i = 0; i < poziomy.size(); i++)
                    if (poziomy[i].getGlobalBounds().contains(translated_pos))
                    {
                        poziomy[i].setFillColor(sf::Color::Red);
                        if (event.type == sf::Event::MouseButtonReleased)
                        {
                            poziomy[i].setFillColor(sf::Color::Red);
                            wyborPoziom = i;
                            wybrano = true;
                        }
                    }else poziomy[i].setFillColor(sf::Color::White);
            }

            switch (wyborPoziom)
            {
                case 0: { y = 1; res.setPosition(250, y * 20 + 200); break;  }
                case 1: { y = 2; res.setPosition(250, y * 20 + 200); break;  }
                case 2: { y = 3; res.setPosition(250, y * 20 + 200); break;  }
                case 3: { y = 4; res.setPosition(250, y * 20 + 200); break;  }
                case 4: { y = 5; res.setPosition(250, y * 20 + 200); break;  }
                case 5: { y = 6; res.setPosition(250, y * 20 + 200); break;  }
                case 6: { y = 7; res.setPosition(250, y * 20 + 200); break;  }
                default: { y = 1; res.setPosition(250, y * 20 + 200); break; }
            }

            window2.clear();
            window2.draw(tlo);
            window2.draw(wybierz2);
            window2.draw(autor);
            for (auto i : poziomy)
                window2.draw(i);
            window2.display();

            //Restart opcji wybrania poziomu
            if (wybrano)
            {
                wybrano = false;
                break;               
            }
        }
        
        if (!zamknij)
        {
        restart:
            sf::RenderWindow window(sf::VideoMode(800, 800), "Dominik Pindych 21.03.2023");
            std::vector<Klocek>klocki;

            Pilka obiekt(500, 400 + (y * 15));  //Pilka
            Plat test(300, 700); //Platforma

            int iloscX{ x }, iloscY{ y }; //X i Y wybierane sa wyzej w swtich(case) na podstawie okna wyboru poziomu
            int punkty = 0;

            //Utworzenie klockow 
            for (int j = 2; j < iloscX-2; j++)
            {
                srand(time(NULL));
                for (int i = 1; i < iloscY+1; i++)
                    klocki.emplace_back((j + 1) * 50, (i + 1) * 50, rand() % 255);
            }

            while (window.isOpen())
            {
                sf::Vector2i pos = sf::Mouse::getPosition(window); //ALBO BEZ WINDOW
                auto translated_pos = window.mapPixelToCoords(pos);
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    {
                        window.close();
                        goto start;
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    test.shape.move({ -0.15 }, 0);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    test.shape.move({ 0.15 }, 0);

                //RESET GRY
                if (res.getGlobalBounds().contains(translated_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && obiekt.reset(klocki, punkty))
                {
                    obiekt.resetuj();
                    punkty = 0;
                    text.setString(std::to_string(punkty));
                    goto restart;
                }

                //KONIEC POZIOMU
                if (klocki.size() == punkty)
                {
                    text.setPosition(200, 200);
                    text.setString("WYGRANA");
                    res.setPosition(270, 300);
                    if (text.getGlobalBounds().contains(translated_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        obiekt.resetuj();
                        punkty = 0;
                        text.setString(std::to_string(punkty));
                        goto start;
                    }
                }


                window.clear();
                window.draw(tlo);
                test.ruch();

                czy_kolizja(test, obiekt);

                for (auto& klocek : klocki)
                    if (czy_kolizja2(klocek, obiekt, punkty))
                    {
                        klocek.usun();
                        text.setString(std::to_string(punkty));
                        break;
                    }

                //WYSWIETLANIE
                if (obiekt.reset(klocki, punkty))
                    window.draw(res);


                //std::cout << "  " << rand() % 2;
                //std::cout << "\n" << rand()%2;
                obiekt.ruch();
                window.draw(text);
                window.draw(test);
                window.draw(obiekt);

                for (auto& klocek : klocki)
                    window.draw(klocek);
                window.display();
            }
        }
        return 0;

}