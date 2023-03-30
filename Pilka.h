#pragma once
#include "Plat.h"
#include "Klocek.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
class Pilka : public sf::Drawable
{

public:

	Pilka() = delete;
	~Pilka() = default;
	Pilka(float x, float y);

	void ruch();
	void ruchG();
	void ruchD();
	void ruchL();
	void ruchP();
	void resetuj();
	void stop();
	void pierwsze();

	bool reset(std::vector<Klocek>klocki,int punkty);
	bool pierwszyR = true;

	float lewo();
	float prawo();
	float dol();
	float gora();

	sf::Vector2f pozycja();

private:

	sf::CircleShape shape;
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	int rozmiar = 25;
	int kierunek;
	float predkosc = 0.1;
	sf::Vector2f velo{predkosc,predkosc};

};

