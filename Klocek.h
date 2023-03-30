#pragma once
#include <SFML/Graphics.hpp>
class Klocek : public sf::Drawable
{
public:
	Klocek() = delete;
	~Klocek() = default;
	Klocek(float x, float y,int r);

	float lewo();
	float prawo();
	float dol();
	float gora();

	sf::Vector2f pozycja();
	sf::Vector2f rozmiar();

	bool czy_zniszczony();
	void usun();
	sf::RectangleShape shape;

private:
	const float wymiar = 35;
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	bool zniszony = false;
};
