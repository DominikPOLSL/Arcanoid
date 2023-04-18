#pragma once
#include "Bonus.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Plat.h"

Bonus::Bonus(float x, float y)
{
	shape.setOrigin(this->rozmiar, this->rozmiar);
	shape.setFillColor(sf::Color::Red);
	shape.setRadius(this->rozmiar);
	shape.setPosition(x, y);
	shape.setOutlineThickness(3);
	shape.setOutlineColor(sf::Color::Black);
}

void Bonus::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->shape, state);
}

float Bonus::lewo()
{
	return this->shape.getPosition().x - shape.getRadius();
}

float Bonus::prawo()
{
	return this->shape.getPosition().x + shape.getRadius();
}

float Bonus::dol()
{
	return this->shape.getPosition().y + shape.getRadius();
}

float Bonus::gora()
{
	return this->shape.getPosition().y - shape.getRadius();
}

void Bonus::ruch()
{
	if(shape.getPosition().y <= 1000)
		shape.move(0, predkosc);
}
void Bonus::usun()
{
	shape.setPosition(0, 1000);
}
