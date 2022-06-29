#ifndef CARD_H
#define CARD_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

enum Color:int{
    spades,
    hearts,
    diamonds,
    clubs,
};

enum Value:int{
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
    virtual int triggerAction()=0;
    virtual void drawCard(Color)=0;
    virtual void drawCommonCard(Color,Value){};
    virtual bool is_Clicked(const sf::Vector2i){return 0;}
    Color color;
    Value value;
    int val; int col;
};

class Aces : public Card
{
public:
        void drawCard(Color const c)
    {
            auto [a,b] = figure(c,value);
            setTextureRect(look(a,b));
    }
                    bool is_Clicked(const sf::Vector2i mouse_pos)
                      {sf::FloatRect  rectangle_bounds = getGlobalBounds();
            if (mouse_pos.x > rectangle_bounds.left && mouse_pos.x < rectangle_bounds.left + rectangle_bounds.width)
                       {{if (mouse_pos.y > rectangle_bounds.top && mouse_pos.y < rectangle_bounds.top + rectangle_bounds.height)
                       return true;}}
            return false;}
            Value value=ace;
            Color color;
protected:
    int triggerAction(){std::cout<<"TO JEST FUNKCJA Z ASA! \n";
                       return 0;};
};

class Twos : public Card
{
public:
    void drawCard(Color const c)
    {
            auto [a,b] = figure(c,value);
            setTextureRect(look(a,b));
    }
                    bool is_Clicked(const sf::Vector2i mouse_pos)
                      {sf::FloatRect  rectangle_bounds = getGlobalBounds();
            if (mouse_pos.x > rectangle_bounds.left && mouse_pos.x < rectangle_bounds.left + rectangle_bounds.width)
                       {{if (mouse_pos.y > rectangle_bounds.top && mouse_pos.y < rectangle_bounds.top + rectangle_bounds.height)
                       return true;}}
            return false;}
                Value value = two;
protected:
    int triggerAction(){std::cout<<"TO JEST FUNKCJA Z DWOJKI! \n";
                       return 2;};

};

class Threes : public Card
{
public:
            void drawCard(Color const c)
    {
            auto [a,b] = figure(c,value);
            setTextureRect(look(a,b));
    }
                    bool is_Clicked(const sf::Vector2i mouse_pos)
                      {sf::FloatRect  rectangle_bounds = getGlobalBounds();
            if (mouse_pos.x > rectangle_bounds.left && mouse_pos.x < rectangle_bounds.left + rectangle_bounds.width)
                       {{if (mouse_pos.y > rectangle_bounds.top && mouse_pos.y < rectangle_bounds.top + rectangle_bounds.height)
                       return true;}}
            return false;}
                Value value = three;
protected:
    int triggerAction(){std::cout<<"TO JEST FUNKCJA Z TROJKI! \n";
                       return 3;};

};

class Fours : public Card
{
public:

    void drawCard(Color const c)
{
    auto [a,b] = figure(c,value);
    setTextureRect(look(a,b));
}
            bool is_Clicked(const sf::Vector2i mouse_pos)
              {sf::FloatRect  rectangle_bounds = getGlobalBounds();
    if (mouse_pos.x > rectangle_bounds.left && mouse_pos.x < rectangle_bounds.left + rectangle_bounds.width)
               {{if (mouse_pos.y > rectangle_bounds.top && mouse_pos.y < rectangle_bounds.top + rectangle_bounds.height)
               return true;}}
    return false;}
        Value value = four;

protected:
    int triggerAction(){std::cout<<"TO JEST FUNKCJA Z CZWORKI! \n";
                       return 1;};

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
                            bool is_Clicked(const sf::Vector2i mouse_pos)
                              {sf::FloatRect  rectangle_bounds = getGlobalBounds();
                    if (mouse_pos.x > rectangle_bounds.left && mouse_pos.x < rectangle_bounds.left + rectangle_bounds.width)
                               {{if (mouse_pos.y > rectangle_bounds.top && mouse_pos.y < rectangle_bounds.top + rectangle_bounds.height)
                               return true;}}
                    return false;}
protected:
   int triggerAction(){return 0;};

};

class Jacks : public Card
{
public:
            void drawCard(Color const c)
    {
            auto [a,b] = figure(c,value);
            setTextureRect(look(a,b));
    }
                    bool is_Clicked(const sf::Vector2i mouse_pos)
                      {sf::FloatRect  rectangle_bounds = getGlobalBounds();
            if (mouse_pos.x > rectangle_bounds.left && mouse_pos.x < rectangle_bounds.left + rectangle_bounds.width)
                       {{if (mouse_pos.y > rectangle_bounds.top && mouse_pos.y < rectangle_bounds.top + rectangle_bounds.height)
                       return true;}}
            return false;}
                Value value = jack;
protected:
    int triggerAction(){std::cout<<"TO JEST FUNKCJA Z JOPKA! \n";
                       return 0;};

};

class Kings : public Card
{
public:
            void drawCard(Color const c)
    {
            auto [a,b] = figure(c,value);
            setTextureRect(look(a,b));
    }
                    bool is_Clicked(const sf::Vector2i mouse_pos)
                      {sf::FloatRect  rectangle_bounds = getGlobalBounds();
            if (mouse_pos.x > rectangle_bounds.left && mouse_pos.x < rectangle_bounds.left + rectangle_bounds.width)
                       {{if (mouse_pos.y > rectangle_bounds.top && mouse_pos.y < rectangle_bounds.top + rectangle_bounds.height)
                       return true;}}
            return false;}
                Value value = king;
protected:
    int triggerAction(){std::cout<<"TO JEST FUNKCJA Z KROLA! \n";
                       return 5;};

};

#endif // CARD_H
