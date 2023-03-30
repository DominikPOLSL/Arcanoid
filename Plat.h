#pragma once
#include <SFML/Graphics.hpp>
class Plat : public sf::Drawable
{
public:

	Plat(float x, float y);
	~Plat() = default;
	Plat() = delete;
	sf::RectangleShape shape;
	float kierunek;

	void ruch();
	void zmiana(int size);

	float lewo();
	float prawo();
	float dol();
	float gora();

	sf::Vector2f pozycja();

private:

	int wys = 25;
	int szer = 250;
	float predkosc = 0.1;
	sf::Vector2f velo{ predkosc,predkosc };

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

};



