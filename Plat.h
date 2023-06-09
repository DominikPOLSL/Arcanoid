#pragma once
#include <SFML/Graphics.hpp>
class Plat : public sf::Drawable
{
public:

	Plat(float x, float y);
	~Plat() = default;
	Plat() = delete;
	sf::RectangleShape shape;

	void ruch();
	void zmiana(int size);

	float lewo();
	float prawo();
	float dol();
	float gora();

	sf::Vector2f pozycja();

private:

	float wys = 25;
	float szer = 250;
	float predkosc = 0.1;
	sf::Vector2f velo{ predkosc,predkosc };

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

};



