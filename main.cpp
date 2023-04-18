#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <Windows.h>
#include <vector>
#include "Plat.h"
#include "Pilka.h"
#include "Klocek.h"
#include "Bonus.h"
#include "funkcje.h"

int main()
{ 
        start:

        sf::Font font;
        sf::Text text; //Punkty
        sf::Text poziomTrudnosci;
        sf::Text wybierz2;
        sf::Text autor;
        sf::Texture tlo1;
        sf::Texture t1;
        sf::Sprite restartPrzycisk;
        sf::Sprite tlo;


        std::vector<sf::Text>poziomy = {};       
        std::vector<sf::Text>szybkosci = {};
        start(font,text, poziomTrudnosci,wybierz2,autor,tlo1,t1, restartPrzycisk,tlo,poziomy);

        
       
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
                case 0: { y = 1; restartPrzycisk.setPosition(250, y * 20 + 200); break;  }
                case 1: { y = 2; restartPrzycisk.setPosition(250, y * 20 + 200); break;  }
                case 2: { y = 3; restartPrzycisk.setPosition(250, y * 20 + 200); break;  }
                case 3: { y = 4; restartPrzycisk.setPosition(250, y * 20 + 200); break;  }
                case 4: { y = 5; restartPrzycisk.setPosition(250, y * 20 + 200); break;  }
                case 5: { y = 6; restartPrzycisk.setPosition(250, y * 20 + 200); break;  }
                case 6: { y = 7; restartPrzycisk.setPosition(250, y * 20 + 200); break;  }
                default: { y = 1; restartPrzycisk.setPosition(250, y * 20 + 200); break; }
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
            std::vector<Bonus>bonusy;

            Pilka obiekt(500, 400 + (y * 15));  //Pilka
            Plat test(300, 700); //Platforma

            int iloscX{ x }, iloscY{ y }; //X i Y wybierane sa wyzej w swtich(case) na podstawie okna wyboru poziomu
            int punkty = 0;
            int dodatkowe = 0;
            int wynik = 0;

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
                if (restartPrzycisk.getGlobalBounds().contains(translated_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && obiekt.reset(klocki, punkty))
                {
                    obiekt.resetuj();
                    punkty = 0;
                    wynik = 0;
                    text.setString(std::to_string(wynik));
                    text.setPosition(700, 700);
                    goto restart;
                }

                //KONIEC POZIOMU
                if (klocki.size() == punkty - dodatkowe)
                {
                    text.setPosition(200, 200);
                    text.setString("WYGRANA");
                    restartPrzycisk.setPosition(270, 300);
                    if (text.getGlobalBounds().contains(translated_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        obiekt.resetuj();
                        punkty = 0;
                        text.setString(std::to_string(wynik));
                        goto start;
                    }
                }


                window.clear();
                window.draw(tlo);
                test.ruch();

                czy_kolizja(test, obiekt);

                for (auto& klocek : klocki)
                    if (czy_kolizja2(klocek, obiekt, punkty,bonusy))
                    {
                        klocek.usun();
                        //wynik = punkty + dodatkowe;
                        wynik++;
                        text.setString(std::to_string(wynik));
                        break;
                    }

                //WYSWIETLANIE
                if (obiekt.reset(klocki, punkty))
                    window.draw(restartPrzycisk);

                obiekt.ruch();
                window.draw(text);
                window.draw(test);
                window.draw(obiekt);
                for (auto& i : bonusy)
                {
                    window.draw(i);
                    if (i.shape.getGlobalBounds().intersects(test.shape.getGlobalBounds()))
                    {
                        wynik++;
                        text.setString(std::to_string(wynik));
                        i.usun();
                    }
                    i.ruch();
                }
                //wynik = punkty + dodatkowe;
                for (auto& klocek : klocki)
                    window.draw(klocek);
                window.display();
            }
        }
        return 0;

}