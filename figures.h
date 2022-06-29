#ifndef FIGURES_H
#define FIGURES_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "card.h"
#include <iostream>

sf::Texture sprites(){

    sf::Texture Cards;
    if (!Cards.loadFromFile("./../makao/cards.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
    }

    return Cards;
}


bool isClicked(sf::Vector2i &mouse_pos, sf::Sprite &sprite)
{
    sf::FloatRect  rectangle_bounds = sprite.getGlobalBounds();

    if (mouse_pos.x > rectangle_bounds.left && mouse_pos.x < rectangle_bounds.left + rectangle_bounds.width)
    {
        {
            if (mouse_pos.y > rectangle_bounds.top && mouse_pos.y < rectangle_bounds.top + rectangle_bounds.height)
        {       std::cout<<"OK"<< std::endl;
                return true;}
        }
    }
    return false;
}

#endif // FIGURES_H
