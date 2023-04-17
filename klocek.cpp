#pragma once
#include "Klocek.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
Klocek::Klocek(float x,float y,int r)
{
	shape.setOrigin(wymiar/2, wymiar/2);
	shape.setPosition(x, y);
	shape.setSize({wymiar,wymiar});
	shape.setFillColor(sf::Color(255,r, 255-r, 255));
}

void Klocek::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->shape, state);
}

float Klocek::lewo()
{
	return this->shape.getPosition().x - shape.getSize().x / 2;
}

float Klocek::prawo()
{
	return this->shape.getPosition().x + shape.getSize().x / 2;
}

float Klocek::dol()
{
	return this->shape.getPosition().y + shape.getSize().y / 2;
}

float Klocek::gora()
{
	return this->shape.getPosition().y - shape.getSize().y / 2;
}
sf::Vector2f Klocek::pozycja()
{
	return shape.getPosition();
}

sf::Vector2f Klocek::rozmiar()
{
	return shape.getSize();
}

bool Klocek::czy_zniszczony()
{
	return this->zniszony;
}

void Klocek::usun()
{
	shape.setPosition(1000, 1000);
}