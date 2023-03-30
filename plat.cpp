#include "Plat.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "Pilka.h"
#include <vector>
Plat::Plat(float x, float y)
{
	shape.setPosition(x, y);
	shape.setFillColor(sf::Color::Green);
	shape.setSize(sf::Vector2f(this->szer, this->wys));
	shape.setOrigin(this->szer/2, this->wys/2);
}

void Plat::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->shape, state);
}

void Plat::ruch()
{

	if (this->kierunek == -1)
	{
		shape.move(this->predkosc,0);
		this->kierunek = -1;
	}
	if (this->kierunek == 1)
	{
		shape.move(this->predkosc - (2 * this->predkosc),0);
		this->kierunek = 1;
	}
	if (shape.getPosition().x > 800 - shape.getSize().x/2)
	{
		kierunek = 1;
	}
	if (shape.getPosition().x < 0 + shape.getSize().x/2)
		kierunek = -1;
}

float Plat::lewo()
{
	return this->shape.getPosition().x - shape.getSize().x/2;
}

float Plat::prawo()
{
	return this->shape.getPosition().x + shape.getSize().x / 2;
}

float Plat::dol()
{
	return this->shape.getPosition().y + shape.getSize().y / 2;
}

float Plat::gora()
{
	return this->shape.getPosition().y - shape.getSize().y / 2;
}

sf::Vector2f Plat::pozycja()
{
	return shape.getPosition();
}

void Plat::zmiana(int size)
{
	this->szer = size;
}
