#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "card.h"
#include "figures.h"

using namespace std;

void run()
{
    test();
    sf::Texture Cards;
    if (!Cards.loadFromFile("./../makao/cards.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return;
    }

   Commons siodemka;
   siodemka.setTexture(Cards); siodemka.drawCommonCard(clubs,seven); siodemka.setPosition(570,360);
   Aces as;
   as.setTexture(Cards);
   as.drawCard(clubs);
   as.setPosition(600, 360);

   Kings king;
   king.setTexture(Cards); king.drawCard(clubs); king.setPosition(630,360);

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Makao");

    while (window.isOpen())
    {
       sf::Event event;

       while (window.pollEvent(event)){
           if (event.type== sf::Event::Closed)
               window.close();
       }

       window.clear(sf::Color(10,50,10,255));

       window.draw(siodemka);
       window.draw(as);
       window.draw(king);




       window.display();




    }



}

int main()
{
    run();
    auto [a, b] = figure(spades,ace);
    std::cout <<a << b <<std::endl;
    cout << "Hello World!" << endl;
    return 0;
}
