#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <random>
#include <windows.h>
#include "card.h"
#include "figures.h"

using namespace std;


void run()
{

    int i =0, j = 0; sf::Vector2i mouse_pos;


    sf::Texture ok_sprite; if (!ok_sprite.loadFromFile("./../makao/ok_button.png"))
    {std::cerr << "Could not load texture" << std::endl;return;}

    sf::Texture blank_sprite;if (!blank_sprite.loadFromFile("./../makao/blank.png"))
    {std::cerr << "Could not load texture" << std::endl;return;}

    sf::Sprite ok_button;
    ok_button.setTexture(ok_sprite);
    ok_button.setPosition(585, 480);

    sf::Texture Cards = sprites(); //wgranie zrodla obrazow 
    std::vector<std::unique_ptr<sf::Sprite>> blanks;
    std::vector<std::unique_ptr<Card>> start_cards;
    std::vector<std::unique_ptr<Card>> cards;
    std::vector<std::unique_ptr<Card>> player;
    std::vector<std::unique_ptr<Card>> computer;
    std::vector<std::unique_ptr<Card>> stack;

    std::array<Color, 4> colors{ {spades, hearts, diamonds, clubs} };
    std::array<Value, 7> values{five, six, seven, eight, nine, ten, queen};
    Commons element; Aces ace; Twos two; Threes three; Fours four; Jacks jack; Kings king;

    for (int i = 0; i<4; i++)
    {auto e = colors[i]; auto u = i;
     for (int i =0; i<7; i++)
     {element.setTexture(Cards); element.drawCommonCard(e,values[i]); element.val=i+5; element.col=u; element.setPosition(70*i,25*u); start_cards.emplace_back(std::make_unique<Commons>(element));}}

    for (int i=0; i<4; i++)
    {ace.setTexture(Cards); ace.drawCard(colors[i]); ace.val=1; ace.col=i; ace.setPosition(490,25*i); cards.emplace_back(std::make_unique<Aces>(ace));
     two.setTexture(Cards); two.drawCard(colors[i]); two.val=2; two.col=i; two.setPosition(560,25*i); cards.emplace_back(std::make_unique<Twos>(two));
     three.setTexture(Cards); three.drawCard(colors[i]); three.val=3; three.col=i; three.setPosition(630,25*i); cards.emplace_back(std::make_unique<Threes>(three));
     four.setTexture(Cards); four.drawCard(colors[i]); four.val=4; four.col=i; four.setPosition(700,25*i); cards.emplace_back(std::make_unique<Fours>(four));
     jack.setTexture(Cards); jack.drawCard(colors[i]); jack.val=12; jack.col=i; jack.setPosition(770,25*i); cards.emplace_back(std::make_unique<Jacks>(jack));
     king.setTexture(Cards); king.drawCard(colors[i]); king.val=13; king.col=i; king.setPosition(840,25*i); cards.emplace_back(std::make_unique<Kings>(king));}

    std::srand(time(nullptr));
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(start_cards), std::end(start_cards), rng);
    std::random_shuffle(start_cards.begin(), start_cards.end()); //przetasowanie stosu 5-10 i Q

    move(start_cards.end()-1, start_cards.end(), back_inserter(stack));
    start_cards.pop_back(); //przesuniecie na srodek konkretnej karty ze stosu 5-10 i Q

    for (int i=0; i<27; i++){
     move(start_cards.end()-1, start_cards.end(), back_inserter(cards));
     start_cards.pop_back(); //przesuniecie pozostalych kart ze stosu 5-10 i Q do calej talii
 }

    //pierwsze przetasowanie talii:
    std::shuffle(std::begin(cards), std::end(cards), rng);
    std::random_shuffle(cards.begin(), cards.end());


   for (int i=0; i<25; i++){
    move(cards.end()-2, cards.end()-1, back_inserter(player));
    cards.pop_back();
}

   for (int i=0; i<5; i++){
    move(cards.end()-2, cards.end()-1, back_inserter(computer));
    cards.pop_back();
}


    sf::RenderWindow window(sf::VideoMode(1280, 720), "Makao");

    while (window.isOpen())
    {
        window.setFramerateLimit(10);
       sf::Event event;

       while (window.pollEvent(event)){
           if (event.type== sf::Event::Closed)
               window.close();
       }

       window.clear(sf::Color(10,50,10,255));

       for (auto &s:computer)
       {
           j++;

            for (int i=0; i<j; i++)
            {
                sf::Sprite back;
                back.setTexture(blank_sprite);
                back.setPosition(300+40*i, 40);
                blanks.emplace_back(std::make_unique<sf::Sprite>(back));
            }
       }

       for (auto &s:blanks)
       {
           window.draw(*s);
       }

       for (auto &s:stack)
       {
           i++;
           s->setPosition(590+40*i,310);
           window.draw(*s);
       }

       for (auto &s:player)
       {
           i++;
           s->setPosition(200+40*i,580);
           window.draw(*s);
       }

       window.draw(ok_button);

       window.display();


       if (event.type == sf::Event::MouseButtonPressed) {
           if(event.mouseButton.button == sf::Mouse::Left){
           mouse_pos = sf::Mouse::getPosition(window);
         //  std::cout << mouse_pos.x <<", "<<mouse_pos.y<<std::endl;
           }}

          if(isClicked(mouse_pos,ok_button) == true)
       {
              cout << "dvpa"<<endl;
//              for (auto &n : stack) {
//               //   if ((n->val == 5 )&&(n->val == 6)&&(n->val == 7))
//                  std::cout << n->val << "wartosc twojej karty " <<std::endl;
//              }
              mouse_pos.x =0; mouse_pos.y=0;
       }



//          for (auto &s:player)
//          {
//                v++;
//              if(s->is_Clicked(mouse_pos))
//              {
//                  mouse_pos.x =0; mouse_pos.y=0;
//                  std::cout<<" klikniecie karty" <<std:: endl;

//                  {
//                     // stack.push_back( std::move(*s) );
//                      //player.erase(player.begin()+v-1);
//                      Sleep(10);
//                  }

//              }
//          }

    if (!player.empty()){

          for(auto it=player.begin();it!=player.end();it++)
              {

                    Card *karta = dynamic_cast<Card*>(it->get());
                               if (karta!= nullptr){
                   if ( karta->is_Clicked(mouse_pos))
                   {
                     const int &wartosc = (karta)->val;
                     cout << wartosc << " wartosc karty"<<std::endl;
                     stack.emplace_back( std::move(*it) );
                     player.erase(it);
                     mouse_pos.x=0; mouse_pos.y=0;
                     Sleep(5);
                     break;
                   }}
               }
                         }






       i = 0, j = 0; //zerowanie iteratorow od wyswietlania kart
       blanks.clear(); //czyszczenie wektora od wyswietlania kart komputera





//       for(auto it=cards.begin();it!=cards.end();it++)
//         {


//           cards[it].draw();


////           sf::Transformable *karta= dynamic_cast<sf::Transformable *>(it->get());
////                               if (karta!= nullptr)
////                               {

////                                   it.setPosition(590,600);



////                               }
//         }


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
