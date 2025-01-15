#pragma once
#include <chrono>
#include <thread>
#include "SFML/Graphics.hpp"
#include "Button.h"
#include "functii_piese_butoane.h"
#include "functii_drag_piese.h"
#include "Maps.h";


using namespace sf;
using namespace std;

void show_nivele(); 
void goBack();      
void show_menu();
void show_win();
void show_harta(char nivel);
void show_custom(char matr[7][9]);

extern char matrice_Tarc[7][9];
extern char stiva_table_de_joc[4][7][9];
void initializare_Nivel(char tarc[7][9], char nivel);
void afisare_nivel(char tarc[7][9]);
void genereaza_nivel(char matrice_Tarc[7][9]);
void initializare_matrice_piese();
extern int index_tabla_curenta;
void copiere_matrice_tarc(char sursa[7][9], char destinatie[7][9]);

enum State { MAIN_MENU, LEVELS_MENU, NIVEL_NORMAL, ALT_NIVEL, WIN_MENU };

const int MAX_HISTORY_SIZE = 100; 
State stateHistory[MAX_HISTORY_SIZE];
int historyIndex = -1; // Index-ul poziției curente în istoric (-1 indică că e gol)

State currentState = MAIN_MENU;

void changeState(State newState) 
{
    if (historyIndex < MAX_HISTORY_SIZE - 1) {
        stateHistory[++historyIndex] = currentState;
    }
    else {
        std::cout << "Istoricul este plin, nu mai putem salva starea curentă!\n";
    }

    // Schimbăm la noua stare
    currentState = newState;
    //printCurrentState();
}

void goBack() 
{
    if (historyIndex >= 0) 
    {
        currentState = stateHistory[historyIndex--];
        std::cout <<"Stare curentă: ";
        switch (currentState) {
        case MAIN_MENU:
            std::cout << "MAIN_MENU\n";
            show_menu();
            break;
        case LEVELS_MENU:
            std::cout << "LEVELS_MENU\n";
            show_nivele();
            break;
        case ALT_NIVEL:
            std::cout << "ALT_NIVEL\n";
            show_custom(matrice_Tarc);
            break;
        case NIVEL_NORMAL:
            cout << "NIVEL_NORMAL\n";
            show_harta('1');
            break;
        case WIN_MENU:
            cout << "WIN_MENU\n";
            show_win();
            break;
        default:
            std::cout <<"STARE NECUNOSCUTĂ\n";
            break;
        }

    }
    else 
    {
        std::cout <<"Nu există stări anterioare!\n";
    }
}

void lvl_buttons_interactions(Button& buton, char numar_buton, RenderWindow& window)
{
    if (buton.isMouseOver(window))
    {
        buton.setBackColor(Color::Black);
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (numar_buton >= '1' && numar_buton <= '5')
            {
                initializare_Nivel(matrice_Tarc, numar_buton);
                afisare_nivel(matrice_Tarc);
                window.close();
                changeState(NIVEL_NORMAL);
                show_harta(numar_buton);
            }
        }
    }
    else
        buton.setBackColor(Color::Transparent);
}
void show_nivele()
{
    initializare_matrice_piese();
    index_tabla_curenta = 0;
    index_pozitie_curenta_piesa_utilizata = 0;
    for (int i = 1; i <= 4; i++)
        used[i] = 0;

    RenderWindow w_nivele(VideoMode(700, 700), "Nivele", Style::Close);
    w_nivele.setSize(Vector2u(700, 700));

    RectangleShape scris(Vector2f(350.f, 250.f));
    Texture scris_texture;
    scris_texture.loadFromFile("scris_meniu.png");
    scris.setTexture(&scris_texture);
    scris.setOrigin((float)175, (float)125);
    scris.setPosition((float)350, (float)100);

    RectangleShape background(Vector2f(700.f, 700.f));
    Texture background_texture;
    background_texture.loadFromFile("test-meniu-1.jpg");
    background.setTexture(&background_texture);

    RectangleShape background_buton(Vector2f(150.f, 50.f));
    Texture background_buton_texture;
    background_buton_texture.loadFromFile("poza-buton-test-2-colorat.jpg.png");
    background_buton.setTexture(&background_buton_texture);


    Button buton_nivel1("Nivelul 1", { 150,50 }, 25, Color::Transparent, Color::White);
    Button buton_nivel2("Nivelul 2", { 150,50 }, 25, Color::Transparent, Color::White);
    Button buton_nivel3("Nivelul 3", { 150,50 }, 25, Color::Transparent, Color::White);
    Button buton_nivel4("Nivelul 4", { 150,50 }, 25, Color::Transparent, Color::White);
    Button buton_nivel5("Nivelul 5", { 150,50 }, 25, Color::Transparent, Color::White);
    Button buton_custom("Aleatoriu ", { 150,50 }, 25, Color::Transparent, Color::White);
    Button buton_back("Back ", { 100,50 }, 25, Color::Transparent, Color::White);


    buton_nivel1.setPos({ 20, 100 });
    buton_nivel2.setPos({ 20, 200 });
    buton_nivel3.setPos({ 20, 300 });
    buton_nivel4.setPos({ 20, 400 });
    buton_nivel5.setPos({ 20, 500 });
    buton_custom.setPos({ 500,150 });
    buton_back.setPos({ 550,50 });


    Font font;
    if (!font.loadFromFile("VistolsansBlack-RplJo.otf"))
    {
        cout << "Eroare la incarcarea fontului!" << '\n';
        return;
    }
    buton_nivel1.setFont(font);
    buton_nivel2.setFont(font);
    buton_nivel3.setFont(font);
    buton_nivel4.setFont(font);
    buton_nivel5.setFont(font);
    buton_custom.setFont(font);
    buton_back.setFont(font);


    while (w_nivele.isOpen())
    {
        Event evnt;
        while (w_nivele.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case Event::Closed:
                w_nivele.close();
                break;

            case Event::TextEntered:
                if (evnt.text.unicode == 27)
                    w_nivele.close();
                break;
            }
        }

        lvl_buttons_interactions(buton_nivel1, '1', w_nivele);
        lvl_buttons_interactions(buton_nivel2, '2', w_nivele);
        lvl_buttons_interactions(buton_nivel3, '3', w_nivele);
        lvl_buttons_interactions(buton_nivel4, '4', w_nivele);
        lvl_buttons_interactions(buton_nivel5, '5', w_nivele);
        if (buton_custom.isMouseOver(w_nivele))
        {
            buton_custom.setBackColor(Color::Black);
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                    genereaza_nivel(matrice_Tarc);
                    afisare_nivel(matrice_Tarc);
                    w_nivele.close();
                    changeState(ALT_NIVEL);
                    show_custom(matrice_Tarc);

            }
        }
        else
            buton_custom.setBackColor(Color::Transparent);

        if (buton_back.isMouseOver(w_nivele))
        {
            buton_back.setBackColor(Color::Black);
            if (Mouse::isButtonPressed(Mouse::Left))
            {              
                w_nivele.close();
                goBack();
                //show_custom();

            }
        }
        else
            buton_back.setBackColor(Color::Transparent);

        w_nivele.clear();
        w_nivele.draw(background);

        background_buton.setPosition((float)20, (float)100);
        w_nivele.draw(background_buton);

        background_buton.setPosition((float)20, (float)200);
        w_nivele.draw(background_buton);

        background_buton.setPosition((float)20, (float)300);
        w_nivele.draw(background_buton);

        background_buton.setPosition((float)20, (float)400);
        w_nivele.draw(background_buton);

        background_buton.setPosition((float)20, (float)500);
        w_nivele.draw(background_buton);

        background_buton.setPosition((float)500, (float)150);
        w_nivele.draw(background_buton);

        //background_buton.setPosition((float)550, (float)50);
        //w_nivele.draw(background_buton);
        RectangleShape background_back(Vector2f(100.f, 50.f));
        Texture background_back_texture;
        background_back_texture.loadFromFile("poza-buton-test-2-colorat.jpg.png");
        background_back.setTexture(&background_back_texture);

        background_back.setPosition((float)550, (float)50);
        w_nivele.draw(background_back);


        buton_custom.drawTo(w_nivele);
        buton_nivel1.drawTo(w_nivele);
        buton_nivel2.drawTo(w_nivele);
        buton_nivel3.drawTo(w_nivele);
        buton_nivel4.drawTo(w_nivele);
        buton_nivel5.drawTo(w_nivele);
        buton_back.drawTo(w_nivele);

        w_nivele.draw(scris);
        w_nivele.display();
    }

}
void show_menu()
{
    index_tabla_curenta = 0;
    initializare_matrice_piese();

    RectangleShape scris(Vector2f(350.f, 250.f));
    Texture scris_texture;
    scris_texture.loadFromFile("scris_meniu.png");
    scris.setTexture(&scris_texture);
    scris.setOrigin((float)175, (float)125);
    scris.setPosition((float)350, (float)100);

    RenderWindow window(VideoMode(700, 700), "Menu", Style::Close);
    Button buton1("Play", { 150,50 }, 25, Color::Transparent, Color::White);
    buton1.setPos({ 0,150 });
    Font font;

    Button buton2("Info", { 150,50 }, 25, Color::Transparent, Color::White);
    buton2.setPos({ 0,230 });

    RectangleShape background(Vector2f(700.f, 700.f));
    Texture background_texture;
    background_texture.loadFromFile("test-meniu-1.jpg");
    background.setTexture(&background_texture);

    RectangleShape background_buton(Vector2f(150.f, 50.f));
    Texture background_buton_texture;
    background_buton_texture.loadFromFile("poza-buton-test-2-colorat.jpg.png");
    background_buton.setTexture(&background_buton_texture);

    if (!font.loadFromFile("VistolsansBlack-RplJo.otf"))
    {
        cout << "Eroare la incarcarea fontului!" << '\n';
        return;
    }

    buton1.setFont(font);
    buton2.setFont(font);

    while (window.isOpen())
    {
        Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case Event::Closed:
                window.close();
                break;
            case Event::TextEntered:
                if (evnt.text.unicode == 27)
                    window.close();
                break;
            }
        }

        if (buton1.isMouseOver(window))
        {
            buton1.setBackColor(Color::Black);
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                window.close();
                changeState(LEVELS_MENU);
                show_nivele();
            }
        }
        else
            buton1.setBackColor(Color::Transparent);

        if (buton2.isMouseOver(window))
        {
            buton2.setBackColor(Color::Black);
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                openFile();
            }
        }
        else
            buton2.setBackColor(Color::Transparent);

        window.clear();
        window.draw(background);
        window.draw(scris);

        background_buton.setPosition((float)0, (float)150);
        window.draw(background_buton);
        buton1.drawTo(window);

        background_buton.setPosition((float)0, (float)230);
        window.draw(background_buton);
        buton2.drawTo(window);

        window.display();
    }
}