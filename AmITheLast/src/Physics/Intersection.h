#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <vector>
class Intersection
{
public:
	static bool Check(sf::FloatRect HitBox, std::vector<sf::FloatRect> Tiles);
	static bool Check(sf::IntRect HitBox,std::vector<sf::FloatRect> Tiles);
};

