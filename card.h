#ifndef CARD_H
#define CARD_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

enum Color{
    spades,
    hearts,
    diamonds,
    clubs,
};

enum Value{
    ace,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king
};


std::pair<int, int> figure(Color color,Value value)
{
   int a=21, b=37;

   switch (color){
       case clubs:{ a=0; break;}
       case diamonds:{ a=1; break;}
       case spades:{ a=2; break;}
       case hearts:{ a=3; break;}
                 }

   switch (value){
       case king:{ b=0; break;}
       case queen:{ b=1; break;}
       case jack:{ b=2; break;}
       case ten:{ b=3; break;}
       case nine:{ b=4; break;}
       case eight:{ b=5; break;}
       case seven:{ b=6; break;}
       case six:{ b=7;break;}
       case five:{ b=8;break;}
       case four:{ b=9;break;}
       case three:{ b=10;break;}
       case two:{ b=11;break;}
       case ace:{ b=12;break;}
                }

   std::cout << "dupa " << std::endl;
   return std::pair<int, int> (a,b);
}

sf::IntRect look(int a, int b)
{
    return sf::IntRect((18+88*b+b),(7+119*a+a),88,119);
}



class Card : public sf::Sprite
{
public:
    Card() : Sprite() {};
    virtual ~Card() = default;
    virtual void triggerAction()=0;
    virtual void drawCard(Color)=0;
    virtual void drawCommonCard(Color,Value){};
protected:
    Color color;
    Value value;
};

class Aces : public Card
{
public:
        void drawCard(Color const c)
    {
            auto [a,b] = figure(c,value);
            setTextureRect(look(a,b));
    }
protected:
    void triggerAction(){};
    Value value=ace;
    Color color;
};

class Twos : public Card
{
public:
    void drawCard(Color const c)
    {
            auto [a,b] = figure(c,value);
            setTextureRect(look(a,b));
    }
protected:
    void triggerAction(){};
    Value value = two;
};

class Threes : public Card
{
public:
            void drawCard(Color const c)
    {
            auto [a,b] = figure(c,value);
            setTextureRect(look(a,b));
    }
protected:
    void triggerAction(){};
    Value value = three;
};

class Fours : public Card
{
public:

    void drawCard(Color const c)
{
    auto [a,b] = figure(c,value);
    setTextureRect(look(a,b));
}

protected:
    void triggerAction(){};
    Value value = four;
};

class Commons : public Card
{
public:

    void drawCard(Color){};
  void drawCommonCard(Color const c, Value const v)
     {
                    auto [a,b] = figure(c,v);
                    setTextureRect(look(a,b));
     }
protected:
    void triggerAction(){};

};

class Jacks : public Card
{
public:
            void drawCard(Color const c)
    {
            auto [a,b] = figure(c,value);
            setTextureRect(look(a,b));
    }
protected:
    void triggerAction(){};
    Value value = jack;
};

class Kings : public Card
{
public:
            void drawCard(Color const c)
    {
            auto [a,b] = figure(c,value);
            setTextureRect(look(a,b));
    }
protected:
    void triggerAction(){};
    Value value = king;
};

#endif // CARD_H
