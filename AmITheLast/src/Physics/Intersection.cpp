#include "Intersection.h"

bool Intersection::Check(sf::FloatRect HitBox, std::vector<sf::FloatRect> Tiles)
{
    for (unsigned int i = 0; i < Tiles.size(); i++) {
        if (HitBox.intersects(Tiles[i])) {
            return true;
        }
    }
    return false;
}

bool Intersection::Check(sf::IntRect HitBox, std::vector<sf::FloatRect> Tiles)
{
    sf::FloatRect Temp(HitBox);
    for (unsigned int i = 0; i < Tiles.size(); i++) {
        if (Temp.intersects(Tiles[i])) {
            return true;
        }
    }
    return false;
}
