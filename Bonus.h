#pragma once
#include <SFML/Graphics.hpp>
#include "Plat.h"
class Bonus : public sf::Drawable
{
public:
	Bonus(float x, float y);
	Bonus() = delete;
	~Bonus() = default;

	float lewo();
	float prawo();
	float dol();
	float gora();
	void ruch();
	void usun();

	sf::CircleShape shape;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	int rozmiar = 10;
	float predkosc = 0.13;
	sf::Vector2f velo{ predkosc,predkosc };
};

