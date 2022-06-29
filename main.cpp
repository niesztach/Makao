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

    int /*i =0,*/ ii =0, iii = 0, j = 0; sf::Vector2i mouse_pos; //iteratory, ktore cos robia
    int val_=0; int col_=0; //zainicjalizowanie wartosci do sczytywania kart ze stosu
    bool demanding = false; //zadanie karty jopkiem
    bool changing = false; //zmiana koloru
    bool computer_turn=false;
    int queue = 0; //kolejki na stosie
    int pause = 0; //tury do stania przez komputer
    string name; //jaka karte jopek wywolal albo jaki as kolor
    bool should_take = false; //czy powinnismy stac kolejke

    sf::Texture ok_sprite; if (!ok_sprite.loadFromFile("./../makao/ok_button.png"))
    {std::cerr << "Could not load texture" << std::endl;return;}

    sf::Texture blank_sprite;if (!blank_sprite.loadFromFile("./../makao/blank.png")) //wczytanie obrazu kart komputera
    {std::cerr << "Could not load texture" << std::endl;return;}

    sf::Sprite ok_button;
    ok_button.setTexture(ok_sprite);
    ok_button.setPosition(585, 480);

    sf::Texture Cards = sprites(); //wgranie zrodla obrazow
    std::vector<std::unique_ptr<sf::Sprite>> blanks; blanks.reserve(52); //wektor ilosci spritow, obrazujacych karty komputera
    std::vector<std::unique_ptr<Card>> start_cards; blanks.reserve(52); //wektor kart 5-10Q, zeby dobrze rozdac na srodek
    std::vector<std::unique_ptr<Card>> cards; blanks.reserve(52); //wektor calej talii
    std::vector<std::unique_ptr<Card>> gamer[2]; gamer[0].reserve(52); gamer[1].reserve(52); //wektor graczy, komputerow
    std::vector<std::unique_ptr<Card>> stack; stack.reserve(52); //wektor srodka

    std::array<Color, 4> colors{ {spades, hearts, diamonds, clubs} };
    std::array<Value, 7> values{five, six, seven, eight, nine, ten, queen};
    Commons element; Aces ace; Twos two; Threes three; Fours four; Jacks jack; Kings king; //potworzenie wstepnych obiektow z klas na tworzenie kart

    for (int i = 0; i<4; i++) //wyrysowanie kart 5, 6, 7, 8, 9, 10 i Q(11)
    {auto e = colors[i]; auto u = i;
        for (int i =0; i<7; i++)
        {element.setTexture(Cards); element.drawCommonCard(e,values[i]); element.val=i+7; element.col=u; element.setPosition(70*i,25*u); start_cards.emplace_back(std::make_unique<Commons>(element));}}

    for (int i=0; i<4; i++) //wyrysowanie reszty kart, korzystajac z tego, ze maja juz wartosc nadana z klasy, ale bez koloru
    {ace.setTexture(Cards); ace.drawCard(colors[i]); ace.val=1; ace.col=i; ace.setPosition(490,25*i); cards.emplace_back(std::make_unique<Aces>(ace));
        two.setTexture(Cards); two.drawCard(colors[i]); two.val=2; two.col=i; two.setPosition(560,25*i); cards.emplace_back(std::make_unique<Twos>(two));
        three.setTexture(Cards); three.drawCard(colors[i]); three.val=3; three.col=i; three.setPosition(630,25*i); cards.emplace_back(std::make_unique<Threes>(three));
        four.setTexture(Cards); four.drawCard(colors[i]); four.val=4; four.col=i; four.setPosition(700,25*i); cards.emplace_back(std::make_unique<Fours>(four));
        jack.setTexture(Cards); jack.drawCard(colors[i]); jack.val=5; jack.col=i; jack.setPosition(770,25*i); cards.emplace_back(std::make_unique<Jacks>(jack));
        king.setTexture(Cards); king.drawCard(colors[i]); king.val=6; king.col=i; king.setPosition(840,25*i); cards.emplace_back(std::make_unique<Kings>(king));}

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


    int tura = rand() % 1; //losowanie tury - kto zaczyna
    if (tura == 1)
    {
        computer_turn = false;
    }
    else if (tura==0)
        computer_turn = true;


    for (int i=0; i<5; i++){
        move(cards.end()-1, cards.end(), back_inserter(gamer[0]));
        cards.pop_back();
    } //rozdanie kart graczowi

    for (int i=0; i<5; i++){
        move(cards.end()-1, cards.end(), back_inserter(gamer[1]));
        cards.pop_back();
    } //rozdanie kart komputerowi


    sf::RenderWindow window(sf::VideoMode(1280, 720), "Makao"); //rysowanie okna

    while (window.isOpen())
    {
        window.setFramerateLimit(30);
        sf::Event event;

        while (window.pollEvent(event)){
            if (event.type== sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(10,50,10,255));

        for (auto &s:gamer[1]) //rysowanie kart komputera
        {
            j++;

            for (int i=0; i<j; i++)
            {
                sf::Sprite back;
                back.setTexture(blank_sprite);
                back.setPosition(300+40*i, 40);
                blanks.emplace_back(std::make_unique<sf::Sprite>(back));
            }

            //            i++;
            //            s->setPosition(10+20*i,270);  <- zakomentowane, ale mozna by tym podejrzec karty komputera
            //            window.draw(*s);
        }

        for (auto &s:blanks) //odzwierciedlenie ilosci kart komputera
        {
            window.draw(*s);
        }

        for (auto &s:stack) //rysowanie stacka
        {
            ii++;
            s->setPosition(190+15*ii,310);
            window.draw(*s);
        }

        for (auto &s:gamer[0]) //rysowanie gracza
        {
            iii++;
            s->setPosition(10+70*iii,580);
            window.draw(*s);
        }


        window.draw(ok_button); //wyrysowanie przycisku ok



        window.display();

        if (gamer[0].empty()) //stos gracza pusty = wygrana
        {
            std::cout<< "WYGRALES!!!" <<std::endl;
            Sleep(3000);
            window.close();
        }

        if (gamer[1].empty()) //stos komputera pusty = przegrana
        {
            std::cout<<"PRZEGRANA" <<std::endl;
            Sleep(3000);
            window.close();
        }



        if (event.type == sf::Event::MouseButtonPressed) {
            if(event.mouseButton.button == sf::Mouse::Left){
                mouse_pos = sf::Mouse::getPosition(window);
                //  std::cout << mouse_pos.x <<", "<<mouse_pos.y<<std::endl;
            }}


        for (auto it = stack.end()-1; it!=stack.end();it++) //sczytanie karty na srodku
        {
            Card *stos = dynamic_cast<Card*>(it->get());
            if (stos!=nullptr){
                val_ = stos->val;
                col_ = stos->col;
            }
        }





////       OBSŁUGA !!!!!!!!!!!!!!!!!!
////        GRACZA !!!!!!!!!!!!!!!!!!


////        OBSŁUGA !!!!!!!!!!!!!!!!!
////        GRACZA !!!!!!!!!!!!!!!!!!


        for (auto it = stack.end()-1; it!=stack.end();it++) ////szczytanie karty z gory stosu
        {
            Card *stos = dynamic_cast<Card*>(it->get());
            if (stos!=nullptr){
                val_ = stos->val;
                col_ = stos->col;
            }
        }


        if ((val_ == 5)&&(computer_turn=false)){ ////zlapanie czy rzucono jopka
            demanding = true;}

        if((val_ == 1) &&(computer_turn=false)) ////zlapanie czy rzucono asa
        {changing = true;}

        if (demanding) ////zazadanie losowej karty z przedzialu 5-10 i Q
        {
            std::srand(time(NULL));
            val_ = rand() % 7 + 7;
            switch (val_){case 7:{ name="PIATKE"; break;} case 8:{ name="SZOSTKE"; break;} case 9:{ name="SIODEMKE"; break;}
            case 10:{ name="OSEMKE"; break;} case 11:{ name="DZIEWIATKE"; break;} case 12: { name="DZIESIATKE"; break;} case 13:{ name="DAME"; break;}}
            demanding = false;
            cout << "ZMIANA WARTOSCI KARTY NA SRODKU NA: " << name <<endl;
        }

        if (changing) ////zazadanie losowego koloru
        {
            std::srand(time(NULL));
            col_ = (rand() % 4) + 1;
            switch (col_){case 1:{ name="KIER"; break;}case 2:{ name="KARO"; break;}case 3:{ name="TREFL"; break;}case 4:{ name="PIK"; break;}}
            changing = false;
            cout << "ZMIANA KOLORU KARTY NA SRODKU NA: " << name << endl;
        }


        if ((!cards.empty())&&(!gamer[0].empty())&&(computer_turn == false)){


            for(auto it=gamer[0].begin();it!=gamer[0].end();it++)
            {


                if(isClicked(mouse_pos,ok_button) == true){
                    move(cards.end()-1, cards.end(), back_inserter(gamer[0]));
                    cards.pop_back();
                    mouse_pos.x = 0; mouse_pos.y=0;
                    computer_turn=true;

                }
                {

                    Card *karta = dynamic_cast<Card*>(it->get());
                    if (karta!= nullptr){
                        if ( karta->is_Clicked(mouse_pos))
                        {
                            mouse_pos.x =0; mouse_pos.y=0;
                            const int &wartosc = (karta)->val;
                            const int &kolor = (karta)->col;
                            // cout << wartosc << " wartosc karty"<<std::endl;
                            if ((wartosc == val_)||(kolor==col_)){
                                stack.emplace_back( std::move(*it) );
                                gamer[0].erase(it);
                                computer_turn=true;
                                if ((wartosc == 5)&&(computer_turn)){ ////zlapanie czy rzucono jopka
                                    demanding = true;}
                                if((wartosc == 1) &&(computer_turn)) ////zlapanie czy rzucono asa
                                {changing = true; }

                                if (should_take == true)
                                    if ((wartosc == 4)&&(computer_turn))
                                    {
                                        queue ++;
                                        should_take = false;
                                    }

                                break;}
                        }}
                }}

        }


//        ////jeszcze raz zlapanie jaka karta lezy na koncu

//        for (auto it = stack.end()-1; it!=stack.end();it++)
//        {
//            Card *stos = dynamic_cast<Card*>(it->get());
//            if (stos!=nullptr){
//                val_ = stos->val;
//                col_ = stos->col;}}





        if (should_take){
            {
                for (int yy = 0; yy<val_; yy++)
                    if (!cards.empty()){
                        move(cards.end()-1, cards.end(), back_inserter(gamer[1]));
                        cards.pop_back();}

                if (cards.empty()) //pusta talia = tasowanie jej
                {
                    stack.swap(cards);
                    move(cards.end()-1, cards.end(), back_inserter(stack));
                    cards.pop_back();
                    std::shuffle(std::begin(cards), std::end(cards), rng);
                    std::random_shuffle(cards.begin(), cards.end());
                }
            }
            should_take=false;
        }



        if (demanding) ///zazadanie losowej figury
        {
            std::srand(time(NULL));
            val_ = rand() % 7 + 7;
            switch (val_){case 7:{ name="PIATKE"; break;} case 8:{ name="SZOSTKE"; break;} case 9:{ name="SIODEMKE"; break;}
            case 10:{ name="OSEMKE"; break;} case 11:{ name="DZIEWIATKE"; break;} case 12: { name="DZIESIATKE"; break;} case 13:{ name="DAME"; break;}}
            demanding = false;
            cout << "ZMIANA WARTOSCI KARTY NA SRODKU NA: " << name <<endl;}

        if (changing) ////zazadanie losowego koloru
        {
            std::srand(time(NULL));
            col_ = (rand() % 4) + 1;
            switch (col_){case 1:{ name="KIER"; break;}case 2:{ name="KARO"; break;}case 3:{ name="TREFL"; break;}case 4:{ name="PIK"; break;}}
            changing = false;
            cout << "ZMIANA KOLORU KARTY NA SRODKU NA: " << name << endl;
        }



        if (pause > 0) ///sprawdzenie, czy komputer stoi kolejke
        {   pause--;
            cout << "Komputer stoi kolejke, pozostalo: " << pause <<endl;
            computer_turn = false;}


        ///    no i komputer sam rzuca cos tutaj (w przypadku jak nie stoi kolejki)
        if ((!cards.empty())&&(!gamer[1].empty())&&(computer_turn == true)){

            Sleep (200);

            if (queue > 0)
            {
                for(auto it=gamer[1].begin();it!=gamer[1].end();it++)
                {

                    Card *karta = dynamic_cast<Card*>(it->get());
                    if (karta!= nullptr){

                        const int &wartosc = (karta)->val;

                        if (wartosc==4)
                        {
                            stack.emplace_back( std::move(*it) );
                            gamer[1].erase(it);
                            computer_turn=false;
                            queue ++;
                            break;
                        }
                    }


                }
            }

            if ((queue >0)&&(computer_turn))
            {
                computer_turn = false;
                pause = queue;
                queue = 0;
            }

            if (computer_turn == true) ///
                for(auto it=gamer[1].begin();it!=gamer[1].end();it++)
                {

                    Card *karta = dynamic_cast<Card*>(it->get());
                    if (karta!= nullptr){
                        const int &wartosc = (karta)->val;
                        const int &kolor = (karta)->col;


                        if ((wartosc == val_)||(kolor == col_)) ///dorzucenie kart graczowi
                        {
                            stack.emplace_back( std::move(*it) );
                            gamer[1].erase(it);
                            if (wartosc==2) ///dwojka - dobiernie
                            {for (int g =0; g<2; g++){
                             if (!cards.empty()){move(cards.end()-1, cards.end(), back_inserter(gamer[0]));cards.pop_back();}}}

                            if (wartosc==3) ///trojka - dobieranie
                            {for (int g =0; g<3; g++){
                             if (!cards.empty()){move(cards.end()-1, cards.end(), back_inserter(gamer[0]));cards.pop_back();}}}

                            if (((wartosc==13)&&(kolor==1))||((wartosc==13)&&(kolor==4))) ///odpowiedni krol - dobieranie
                            {for (int g =0; g<5; g++){
                             if (!cards.empty()){move(cards.end()-1, cards.end(), back_inserter(gamer[0]));cards.pop_back();}}}

                            computer_turn=false;
                            break;
                        }
                    }}}

        if (computer_turn == true)
        {
            {
                if (!cards.empty()){
                    move(cards.end()-1, cards.end(), back_inserter(gamer[1]));
                    cards.pop_back();}

                computer_turn = false;}
        }

        if (cards.empty()) //pusta talia = tasowanie jej
        {
            stack.swap(cards);
            move(cards.end()-1, cards.end(), back_inserter(stack));
            cards.pop_back();
            std::shuffle(std::begin(cards), std::end(cards), rng);
            std::random_shuffle(cards.begin(), cards.end());
        }


        if (cards.empty())
        {
            std::cout<<"NIE MA JUZ KART DO CIAGNIECIA, REMIS \n"; //zabezpieczenie przed brakiem kart
            Sleep(3000);
            window.close();
        }

        /*i = 0,*/ j = 0; ii = 0, iii=0;//zerowanie iteratorow od wyswietlania kart
        blanks.clear(); //czyszczenie wektora od wyswietlania kart komputera
        mouse_pos.x =0; mouse_pos.y=0;
    }
}

int main()
{
    cout << "Witaj w grze, zainspirowana makao. Wygrywa gracz, ktory pozbedzie sie wszystkich kart jako pierwszy. Komputer jest w stanie"
            " dorzucic karty graczowi, uzywajac dwojek, trojek i kroli. Gracz ma mozliwosc uzycia czworki, by zapauzowac komputer"
            ", asy i jopki zmieniaja kolor i figure, ktora trzeba rzucic na srodek, na losowy \n"
            " Kliknij OK by dobrac karte, rzuc karte odpowiedniej figury lub koloru na srodek \n";
    run();
    return 0;
}
