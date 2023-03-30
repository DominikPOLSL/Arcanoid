#include "Pilka.h"
#include "Plat.h"
#include "Klocek.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <Windows.h>

Pilka::Pilka(float x, float y)
{
		shape.setOrigin(this->rozmiar, this->rozmiar);
		shape.setFillColor(sf::Color::Cyan);
		shape.setRadius(this->rozmiar);
		shape.setPosition(x, y);
		shape.setOutlineThickness(3);
		shape.setOutlineColor(sf::Color::Black);
}

void Pilka::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->shape, state);
}

void Pilka::ruch()
{

	
	if (pierwszyR)
	{
		shape.move(velo.x, velo.y/1.3);

		if (this->lewo() < 0)
			velo.x = predkosc;
		else if (this->prawo() > 800)
			velo.x = -predkosc;
		else if (this->gora() < 0)
			velo.y = predkosc;
		else if (this->dol() > 800)
			velo.y = -predkosc;
	}

	if (!pierwszyR)
	{
		shape.move(velo);

		if (this->lewo() < 0)
			velo.x = predkosc;
		else if (this->prawo() > 800)
			velo.x = -predkosc;
		else if (this->gora() < 0)
			velo.y = predkosc;
		else if (this->dol() > 800)
			velo.y = -predkosc;
	}
}

void Pilka::resetuj()
{
	srand(time(NULL));
	int r = rand() % 10;

	this->shape.setPosition(rand()%600, 500);
	if (r > 5)
	{
		velo.x = predkosc;
		velo.y = predkosc;
	}
	else if (r <= 5)
	{
		velo.x = -predkosc;
		velo.y = predkosc;
	}
}
bool Pilka::reset(std::vector<Klocek>klocki, int punkty)
{
	if (this->dol() >= 800)
	{
		velo.x = 0;
		velo.y = 0;
		return true;
	}

	if (klocki.size() == punkty)
	{
		velo.x = 0;
		velo.y = 0;
		return true;
	}
	else return false;

}
float Pilka::lewo()
{
	return this->shape.getPosition().x - shape.getRadius();
}

float Pilka::prawo()
{
	return this->shape.getPosition().x + shape.getRadius();
}

float Pilka::dol()
{
	return this->shape.getPosition().y + shape.getRadius();
}

float Pilka::gora()
{
	return this->shape.getPosition().y - shape.getRadius();
}

void Pilka::ruchG()
{
	this->velo.y = -predkosc;
}

void Pilka::ruchD()
{
	this->velo.y = predkosc;
}

void Pilka::ruchL()
{
	this->velo.x = -predkosc;
}

void Pilka::ruchP()
{
	this->velo.x = predkosc;
}

sf::Vector2f Pilka::pozycja()
{
	return shape.getPosition();
}

void Pilka::stop()
{
	velo.x = 0;
	velo.y = 0;
}

void Pilka::pierwsze()
{
	//
}
