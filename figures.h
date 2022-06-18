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


std::vector<std::unique_ptr<Card>> test(sf::Texture Cards)
{
    std::vector<std::unique_ptr<Card>> cards;
    std::array<Color, 4> colors{ {spades, hearts, diamonds, clubs} };
    std::array<Value, 6> values{ace, two, three, four, jack, king};
    Commons element;

    for (int i = 0; i<4; i++)
    {
        auto e = colors[i];
        auto u = i;
     for (int i =0; i<6; i++)
     {
         element.setTexture(Cards); element.drawCommonCard(e,values[i]); element.setPosition(100+i*70,100+u*80); cards.emplace_back(std::make_unique<Commons>(element));
     }
    }

    Commons siodemka;   siodemka.setTexture(Cards); siodemka.drawCommonCard(clubs,seven); siodemka.setPosition(570,360); cards.emplace_back(std::make_unique<Commons>(siodemka));

return cards;
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
