#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Button.h"
#include "meniu.h"
#include "functii_drag_piese.h"
#include "unelte_piese.h"
#include <chrono>
#include <thread>
using namespace sf;
using namespace std;
void goBack();      // Declari că această funcție există


int show_fermier;
int directie;
int piese_utilizate[3];
int index_pozitie_curenta_piesa_utilizata = -1;
int used[5];
bool rezolvare_automata();

char mat[7][9] = {
    {'u','g','g','g','g','g','g','g','g'},
    {'g','o','#','a','#','#','#','p','g'},
    {'q','g','g','g','q','g','q','#','g'},
    {'g','#','#','c','g','p','#','#','g'},
    {'q','g','g','g','q','g','g','g','g'},
    {'g','o','#','#','#','#','#','c','g'},
    {'g','g','g','g','g','g','g','g','g'},
};
/*
void init_matrice(char mat[7][9])
{
     mat[7][9] = 
     {
        {'u', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
        {'g', 'p', '#', 'o', '#', 'o', '#', 'v', 'g'},
        {'g', '#', '#', '#', '#', '#', '#', '#', 'g'},
        {'g', 'p', '#', '#', '#', 'c', '#', 'v', 'g'},
        {'g', '#', '#', '#', '#', '#', '#', '#', 'g'},
        {'g', 'c', '#', '#', '#', '#', '#', '#', 'g'},
        {'u', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'} 
     };
}
*/

void undo(int piese_utilizate[3], int &index_pozitie_curenta_piesa_utilizata, RenderWindow &window, RectangleShape &gard_L, RectangleShape& gard_lung, RectangleShape& gard_scurt)
{
    bool ok = false;
    
    if (index_tabla_curenta < 1)
        return;
    else index_tabla_curenta--;
    for (int i = 0; i < 4; i++)
    {
        afisare_nivel(stiva_table_de_joc[i]);
        cout << endl;
    }

    copiere_matrice_tarc(stiva_table_de_joc[index_tabla_curenta], matrice_Tarc);

    if (piese_utilizate[ index_pozitie_curenta_piesa_utilizata ] == 1)//L
    {
        gard_L.setPosition(600.f, 790.0f);
        used[1] = 0;
        ok = true;

    }
    else  if (piese_utilizate[ index_pozitie_curenta_piesa_utilizata ] == 2)//lung
    {
        gard_lung.setPosition((float)(600 * 3 / 8), 720.0f + (float)(500 / 40));
        used[2] = 0;
        ok = true;

    }
    else  if (piese_utilizate[ index_pozitie_curenta_piesa_utilizata ] == 3)//scurt
    {
        gard_scurt.setPosition((float)(600 / 4), 835.0f + (float)(500 / 40));
        used[3] = 0;
        ok = true;
    }
    cout << " \n INAINTE DE UNDO: ";
    for (int i = 0; i <= index_pozitie_curenta_piesa_utilizata; i++)
        cout << piese_utilizate[i] << ' ';


    if(ok == true) 
        index_pozitie_curenta_piesa_utilizata--;

    cout << "\n DUPA UNDO: ";
    for (int i = 0; i <= index_pozitie_curenta_piesa_utilizata; i++)
         cout << piese_utilizate[i] << ' ';
}
void show_win()
{
    RenderWindow window_1(VideoMode(1000, 900), "WIN", Style::Close);
    RectangleShape win_screen(Vector2f(1000.f, 900.f));
    Texture win_texture;
    win_texture.loadFromFile("win-screen.png");
    win_screen.setTexture(&win_texture);
    while (window_1.isOpen())
    {
        Event evnt;
        while (window_1.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case Event::Closed:
                window_1.close();
                break;
            case Event::TextEntered:
                if (evnt.text.unicode == 27)
                {
                    window_1.close();
                }
                break;
            }
            window_1.clear();
            window_1.draw(win_screen);
            window_1.display();
        }
    }
}
void show_no_solution()
{
    RenderWindow window_1(VideoMode(1000, 900), "WIN", Style::Close);
    RectangleShape win_screen(Vector2f(1000.f, 900.f));
    Texture win_texture;
    win_texture.loadFromFile("nu_e_solutie.png");
    win_screen.setTexture(&win_texture);
    while (window_1.isOpen())
    {
        Event evnt;
        while (window_1.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case Event::Closed:
                window_1.close();
                break;
            case Event::TextEntered:
                if (evnt.text.unicode == 27)
                {
                    window_1.close();
                }
                break;
            }
            window_1.clear();
            window_1.draw(win_screen);
            window_1.display();
        }
    }
}

void show_solved(char mat[7][9], RenderWindow& window)
{
    int cnt = 0;
    float top_left_x = 90;
    float top_left_y = 155;
    float top_vert_x = 155;
    float top_vert_y = 90;

    float offset_x = 70;
    float offset_y = 71;
    float offsetv_x = 73;
    float offsetv_y = 70;

    RectangleShape tarc(Vector2f((float)600, (float)600 * 3 / 4));
    RectangleShape gard_o(Vector2f(70.f, 25.f));
    RectangleShape gard_v(Vector2f(25.f, 70.f));

    gard_o.setOrigin(70.f, 12.5f);
    gard_v.setOrigin(12.5f, 70.f);

    ///prima pozitie, stanga sus, 90.f,155.f;
                                    /// a doua pozitie, 232,155
                                    /// a 3 a pozitie 374,155
                                    /// a 4 a pozitie 516.f,155.f
                                    /// ratie = 142.f

    ///155.f, 90.f
    ///155.f, 161.f
    /// 155.f, 332.f
    Texture gardo_texture;
    Texture gardv_texture;
    Texture tarcTexture;

    tarcTexture.loadFromFile("harta-goala-cu-spatii.png");

    tarc.setTexture(&tarcTexture);

    for (int i = 2; i < 5; i += 2)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((mat[i][j] == 'g' || mat[i][j] == 'q') && (mat[i][j + 1] == 'g' || mat[i][j + 1] == 'q'))
            {
                cnt++;
                if (j % 2 == 0)
                    gardo_texture.loadFromFile("bucata-gard-stanga.png");
                else
                    gardo_texture.loadFromFile("bucata-gard-dreapta.png");

                gard_o.setTexture(&gardo_texture);
                gard_o.setPosition(top_left_x + j * offset_x, top_left_y + (i - 2) * offset_y);
                window.draw(gard_o);

            }
        }
    }
    for (int j = 2; j < 7; j += 2)
    {
        for (int i = 0; i < 7; i++)
        {
            if ((mat[i][j] == 'g' || mat[i][j] == 'q') && (mat[i + 1][j] == 'g' || mat[i + 1][j] == 'q'))
            {
                cnt++;
                if (i % 2 == 0)
                    gardv_texture.loadFromFile("bucata-gard-sus.png");
                else
                    gardv_texture.loadFromFile("bucata-gard-jos.png");

                gard_v.setTexture(&gardv_texture);
                gard_v.setPosition(top_vert_x + (j - 2) * offsetv_x, top_vert_y + i * offsetv_y);

                window.draw(gard_v);

            }
        }
    }

}
void show_custom(char matr[7][9])
{
    int ok = 0;
    for (int i = 0; i < 4; i++)
        copiere_matrice_tarc(matrice_Tarc, stiva_table_de_joc[i]);

    RenderWindow window_1(VideoMode(1000, 900), "my window", Style::Close);

    Button buton1(" ", { 60,60 }, 25, Color::Transparent, Color::White);
    buton1.setPos({ 930,10 });
    Font font;

    Button buton2("Rezolva", { 100,50 }, 25, Color::Transparent, Color::White);
    buton2.setPos({ 890,80 });

    Button buton3("Undo", { 100,50 }, 25, Color::Transparent, Color::White);
    buton3.setPos({ 890,150 });

    Button buton_back("Back ", { 70,60 }, 25, Color::Transparent, Color::White);
    buton_back.setPos({ 840,10 });

    if (!font.loadFromFile("VistolsansBlack-RplJo.otf"))
    {
        cout << "Eroare la incarcarea fontului!" << '\n';
        return;
    }
    buton1.setFont(font);
    buton2.setFont(font);
    buton3.setFont(font);
    buton_back.setFont(font);

    RectangleShape text_fermier(Vector2f(400.f, 400.f));
    RectangleShape fundal_info(Vector2f(60.f, 60.f));
    RectangleShape fermier(Vector2f((float)(431 / 1.5), (float)(565 / 1.5)));
    RectangleShape main_background(Vector2f(1000.f, 900.f));
    RectangleShape gard_L(Vector2f((float)300, (float)155));
    RectangleShape gard_lung(Vector2f((float)430, (float)25));
    RectangleShape gard_scurt(Vector2f((float)(600 / 2), (float)(500 / 20)));

    text_fermier.setPosition(600.f, 150.f);
    fermier.setPosition(730.f, 500.f);
    fundal_info.setPosition(930.f, 10.f);
    gard_L.setPosition(600.f, 790.0f);
    gard_L.setOrigin((float)(300 / 2), (float)(155 / 2));
    gard_lung.setPosition((float)(600 * 3 / 8), 720.0f + (float)(500 / 40));
    gard_lung.setOrigin((float)(430 / 2), (float)(12));
    gard_scurt.setPosition((float)(600 / 4), 835.0f + (float)(500 / 40));
    gard_scurt.setOrigin((float)(600 / 4), (float)(500 / 40));

    Texture text_fermier_texture;
    Texture fermier_texture;
    Texture fundal_info_texture;
    Texture main_background_texture;
    Texture gard_L_Texture;
    Texture gard_lung_Texture;
    Texture gard_scurt_Texture;

    text_fermier_texture.loadFromFile("text-fermier.png");
    fermier_texture.loadFromFile("fermier.png");
    fundal_info_texture.loadFromFile("buton-info.png");
    gard_L_Texture.loadFromFile("gard-L.png");
    gard_lung_Texture.loadFromFile("gard-lung.png");
    gard_scurt_Texture.loadFromFile("gard-scurt.png");
    main_background_texture.loadFromFile("fundal-flori-iarba-2.png");

    text_fermier.setTexture(&text_fermier_texture);
    fermier.setTexture(&fermier_texture);
    fundal_info.setTexture(&fundal_info_texture);
    main_background.setTexture(&main_background_texture);
    gard_L.setTexture(&gard_L_Texture);
    gard_lung.setTexture(&gard_lung_Texture);
    gard_scurt.setTexture(&gard_scurt_Texture);

    RectangleShape background_buton(Vector2f(100.f, 50.f));
    Texture background_buton_texture;
    background_buton_texture.loadFromFile("poza-buton-test-2-colorat.jpg.png");
    background_buton.setTexture(&background_buton_texture);

    float distantax = 150;
    float distantay = 145;
    Vector2f stanga_sus(82.f, 85.f);

    RectangleShape tarc(Vector2f(600.f, (float)600 * 3 / 4));
    RectangleShape oaie(Vector2f(100.f, 100.f));
    RectangleShape cal(Vector2f(100.f, 100.f));
    RectangleShape vaca(Vector2f(100.f, 100.f));
    RectangleShape porc(Vector2f(100.f, 100.f));
    RectangleShape apa(Vector2f(100.f, 100.f));


    oaie.setOrigin(50.f, 50.f);
    porc.setOrigin(50.f, 50.f);
    cal.setOrigin(50.f, 50.f);
    vaca.setOrigin(50.f, 50.f);
    apa.setOrigin(50.f, 50.f);

    Texture oaie_texture;
    Texture cal_texture;
    Texture porc_texture;
    Texture vaca_texture;
    Texture tarcTexture;
    Texture apa_texture;


    oaie_texture.loadFromFile("oaie.png");
    cal_texture.loadFromFile("cal.png");
    porc_texture.loadFromFile("porc.png");
    vaca_texture.loadFromFile("vaca.png");
    apa_texture.loadFromFile("apa.png");


    oaie.setTexture(&oaie_texture);
    cal.setTexture(&cal_texture);
    porc.setTexture(&porc_texture);
    vaca.setTexture(&vaca_texture);
    apa.setTexture(&apa_texture);

    tarcTexture.loadFromFile("harta-goala-cu-spatii.png");
    tarc.setTexture(&tarcTexture);


    while (window_1.isOpen())
    {
        Event evnt;
        while (window_1.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case Event::Closed:
                window_1.close();
                break;
            case Event::TextEntered:
                if (evnt.text.unicode == 27)
                {
                    window_1.close();
                }
                break;
            }



            if (buton1.isMouseOver(window_1))
            {
                buton1.setBackColor(Color::Black);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    openFile();
                }
            }
            else
                buton1.setBackColor(Color::Transparent);

            if (buton2.isMouseOver(window_1))
            {
                buton2.setBackColor(Color::Black);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    if (object_on_map(gard_L, tarc) || object_on_map(gard_lung, tarc) || object_on_map(gard_scurt, tarc))
                    {
                        show_fermier = 1; cout << show_fermier << '\n';
                    }
                    else
                    {
                        ok = 1;
                        if (rezolvare_automata() != 1)
                            show_no_solution();
                    }

                }
            }
            else
                buton2.setBackColor(Color::Transparent);

            if (buton3.isMouseOver(window_1))
            {
                buton3.setBackColor(Color::Black);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    undo(piese_utilizate, index_pozitie_curenta_piesa_utilizata, window_1, gard_L, gard_lung, gard_scurt);
                }
            }
            else
                buton3.setBackColor(Color::Transparent);

            if (buton_back.isMouseOver(window_1))
            {
                buton_back.setBackColor(Color::Black);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    window_1.close();
                    goBack();                    //show_custom();

                }
            }
            else
                buton_back.setBackColor(Color::Transparent);

            if (!ok)
            {
                object_selection(gard_L, tarc, window_1, 1, directie, piese_utilizate, index_pozitie_curenta_piesa_utilizata, used);
                object_selection(gard_lung, tarc, window_1, 2, directie, piese_utilizate, index_pozitie_curenta_piesa_utilizata, used);
                object_selection(gard_scurt, tarc, window_1, 3, directie, piese_utilizate, index_pozitie_curenta_piesa_utilizata, used);
            }

            window_1.clear();
            window_1.draw(main_background);
            window_1.draw(tarc);
            for (int i = 0; i < 7; i++)
            {
                for (int j = 0; j < 9; j++)
                {

                    switch (matr[i][j])
                    {
                    case 'c':
                    {
                        cal.setPosition(82.f + j / 2 * distantax, 85.f + i / 2 * distantay);
                        window_1.draw(cal);
                        break;

                    }
                    case 'p':
                    {
                        porc.setPosition(82.f + j / 2 * distantax, 85.f + i / 2 * distantay);
                        window_1.draw(porc);
                        break;
                    }
                    case 'o':
                    {
                        oaie.setPosition(82.f + j / 2 * distantax, 85.f + i / 2 * distantay);
                        window_1.draw(oaie);
                        break;
                    }
                    case 'v':
                    {
                        vaca.setPosition(82.f + j / 2 * distantax, 85.f + i / 2 * distantay);
                        window_1.draw(vaca);
                        break;
                    }
                    case 'a':
                    {
                        apa.setPosition(82.f + j / 2 * distantax, 85.f + i / 2 * distantay);
                        window_1.draw(apa);
                        break;
                    }
                    default:
                        break;
                    }
                }
            }


            background_buton.setPosition(890.f, 80.f);
            window_1.draw(background_buton);
            background_buton.setPosition(890.f, 150.f);
            window_1.draw(background_buton);


            RectangleShape background_back(Vector2f(70.f, 60.f));
            Texture background_back_texture;
            background_back_texture.loadFromFile("poza-buton-test-2-colorat.jpg.png");
            background_back.setTexture(&background_back_texture);

            background_back.setPosition((float)840, (float)10);
            window_1.draw(background_back);

            window_1.draw(fundal_info);
            buton3.drawTo(window_1);
            buton1.drawTo(window_1);
            buton2.drawTo(window_1);
            buton_back.drawTo(window_1);
            if (!ok)
            {
                window_1.draw(gard_L);
                window_1.draw(gard_lung);
                window_1.draw(gard_scurt);
            }

            if (show_fermier)
            {
                window_1.draw(fermier);
                window_1.draw(text_fermier);
            }
            if (ok)
                show_solved(matr, window_1);
            window_1.display();
        }
    }
}

void show_harta(char nivel)
{
    int ok = 0;

    for (int i = 0; i < 4; i++)
        copiere_matrice_tarc(matrice_Tarc, stiva_table_de_joc[i]);

    RenderWindow window_1(VideoMode(1000, 900), "my window", Style::Close);

    Button buton1(" ", { 60,60 }, 25, Color::Transparent, Color::White);
    buton1.setPos({ 930,10 });
    Font font;

    Button buton2("Rezolva", { 100,50 }, 25, Color::Transparent, Color::White);
    buton2.setPos({ 890,80 });

    Button buton3("Undo", { 100,50 }, 25, Color::Transparent, Color::White);
    buton3.setPos({ 890,150 });

    Button buton_back("Back ", { 70,60 }, 25, Color::Transparent, Color::White);
    buton_back.setPos({ 840,10 });

    if (!font.loadFromFile("VistolsansBlack-RplJo.otf"))
    {
        cout << "Eroare la incarcarea fontului!" << '\n';
        return;
    }
    buton1.setFont(font);
    buton2.setFont(font);
    buton3.setFont(font);
    buton_back.setFont(font);

    RectangleShape text_fermier(Vector2f(300.f, 400.f));
    RectangleShape fundal_info(Vector2f(60.f, 60.f));
    RectangleShape fermier(Vector2f((float)(431 / 1.5), (float)(565 / 1.5)));
    RectangleShape main_background(Vector2f(1000.f, 900.f));
    RectangleShape tarc(Vector2f((float)600, (float)600 * 3 / 4));
    RectangleShape gard_L(Vector2f((float)300, (float)155));
    RectangleShape gard_lung(Vector2f((float)430, (float)25));
    RectangleShape gard_scurt(Vector2f((float)(600 / 2), (float)(500 / 20)));

    text_fermier.setPosition(600.f, 150.f);
    fermier.setPosition(730.f, 500.f);
    fundal_info.setPosition(930.f, 10.f);
    gard_L.setPosition(600.f, 790.0f);
    gard_L.setOrigin((float)(300 / 2), (float)(155 / 2));
    gard_lung.setPosition((float)(600 * 3 / 8), 720.0f + (float)(500 / 40));
    gard_lung.setOrigin((float)(430 / 2), (float)(12));
    gard_scurt.setPosition((float)(600 / 4), 835.0f + (float)(500 / 40));
    gard_scurt.setOrigin((float)(600 / 4), (float)(500 / 40));

    Texture text_fermier_texture;
    Texture fermier_texture;
    Texture fundal_info_texture;
    Texture main_background_texture;
    Texture tarcTexture;
    Texture gard_L_Texture;
    Texture gard_lung_Texture;
    Texture gard_scurt_Texture;

    text_fermier_texture.loadFromFile("text-fermier.png");
    fermier_texture.loadFromFile("fermier.png");
    fundal_info_texture.loadFromFile("buton-info.png");
    gard_L_Texture.loadFromFile("gard-L.png");
    gard_lung_Texture.loadFromFile("gard-lung.png");
    gard_scurt_Texture.loadFromFile("gard-scurt.png");
    main_background_texture.loadFromFile("fundal-flori-iarba-2.png");
    switch (nivel)
    {
    case '1':
    {
        tarcTexture.loadFromFile("harta-nivel-1.png");
        break;
    }
    case '2':
    {
        tarcTexture.loadFromFile("harta-nivel-2.png");
        break;
    }
    case '3':
    {
        tarcTexture.loadFromFile("harta-nivel-3.png");
        break;
    }
    case '4':
    {
        tarcTexture.loadFromFile("harta-nivel-4.png");
        break;
    }
    case '5':
    {
        tarcTexture.loadFromFile("harta-nivel-5.png");
        break;
    }
    }
    text_fermier.setTexture(&text_fermier_texture);
    fermier.setTexture(&fermier_texture);
    fundal_info.setTexture(&fundal_info_texture);
    main_background.setTexture(&main_background_texture);
    tarc.setTexture(&tarcTexture);
    gard_L.setTexture(&gard_L_Texture);
    gard_lung.setTexture(&gard_lung_Texture);
    gard_scurt.setTexture(&gard_scurt_Texture);

    RectangleShape background_buton(Vector2f(100.f, 50.f));
    Texture background_buton_texture;
    background_buton_texture.loadFromFile("poza-buton-test-2-colorat.jpg.png");
    background_buton.setTexture(&background_buton_texture);

    while (window_1.isOpen())
    {
        Event evnt;
        while (window_1.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case Event::Closed:
                window_1.close();
                break;
            case Event::TextEntered:
                if (evnt.text.unicode == 27)
                {
                    window_1.close();
                }
                break;
            }



            if (buton1.isMouseOver(window_1))
            {
                buton1.setBackColor(Color::Black);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    openFile();
                }
            }
            else
                buton1.setBackColor(Color::Transparent);

            if (buton2.isMouseOver(window_1))
            {
                buton2.setBackColor(Color::Black);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    if (object_on_map(gard_L, tarc) || object_on_map(gard_lung, tarc) || object_on_map(gard_scurt, tarc))
                    {
                        show_fermier = 1; cout << show_fermier << '\n';
                    }
                    else
                    {
                        if (rezolvare_automata() != 1)
                            show_no_solution();
                        else ok = 1;
                        //window_1.close();
                        //show_solved(mat);
                    }

                }
            }
            else
                buton2.setBackColor(Color::Transparent);

            if (buton_back.isMouseOver(window_1))
            {
                buton_back.setBackColor(Color::Black);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    window_1.close();
                    goBack();

                    //show_custom();

                }
            }
            else
                buton_back.setBackColor(Color::Transparent);

            if (!ok)
            {
                object_selection(gard_L, tarc, window_1, 1, directie, piese_utilizate, index_pozitie_curenta_piesa_utilizata, used);
                object_selection(gard_lung, tarc, window_1, 2, directie, piese_utilizate, index_pozitie_curenta_piesa_utilizata, used);
                object_selection(gard_scurt, tarc, window_1, 3, directie, piese_utilizate, index_pozitie_curenta_piesa_utilizata, used);
            }

            if (buton3.isMouseOver(window_1))
            {
                buton3.setBackColor(Color::Black);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    if (index_pozitie_curenta_piesa_utilizata >= 0)
                        undo(piese_utilizate, index_pozitie_curenta_piesa_utilizata, window_1, gard_L, gard_lung, gard_scurt);
                }
            }
            else
                buton3.setBackColor(Color::Transparent);
            window_1.clear();
            window_1.draw(main_background);



            background_buton.setPosition(890.f, 80.f);
            window_1.draw(background_buton);

            background_buton.setPosition(890.f, 150.f);
            window_1.draw(background_buton);

            RectangleShape background_back(Vector2f(70.f, 60.f));
            Texture background_back_texture;
            background_back_texture.loadFromFile("poza-buton-test-2-colorat.jpg.png");
            background_back.setTexture(&background_back_texture);

            background_back.setPosition((float)840, (float)10);
            window_1.draw(background_back);

            window_1.draw(fundal_info);
            buton1.drawTo(window_1);
            buton2.drawTo(window_1);
            buton3.drawTo(window_1);
            buton_back.drawTo(window_1);
            window_1.draw(tarc);
            if (!ok)
            {
                window_1.draw(gard_L);
                window_1.draw(gard_lung);
                window_1.draw(gard_scurt);
            }

            if (ok)
                show_solved(matrice_Tarc, window_1);
            if (show_fermier)
            {
                window_1.draw(fermier);
                window_1.draw(text_fermier);
            }
            window_1.display();
        }
    }
}
