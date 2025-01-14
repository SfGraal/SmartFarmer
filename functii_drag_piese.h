#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Button.h"
#include "meniu.h"
#include "unelte_piese.h"
#include "utilitati.h"
using namespace sf;
using namespace std;



void drag_in_place_oriz(RectangleShape& obiect, RenderWindow& window, int id)
{
    FloatRect bounds = obiect.getGlobalBounds();
    float centrux = bounds.left + bounds.width / 2;
    float centruy = bounds.top + bounds.height / 2;

    copiere_matrice_tarc(matrice_Tarc, matrice_tarc_temporar);

    switch (id)
    {

    case 1://gard L
    {
        if (centrux >= 0 && centruy >= 153 && centrux <= 220 && centruy <= 290 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(155.5f, 222.f);

        else  if (centrux >= 220.5 && centruy >= 153 && centrux <= 363.5 && centruy <= 290 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(299.f, 222.f);

        else if (centrux >= 364 && centruy >= 153 && centrux <= 508 && centruy <= 290 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(442.5f, 222.f);



        else if (centrux >= 0 && centruy >= 0 && centrux <= 220 && centruy <= 152.5 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(155.5f, 80.f);

        else  if (centrux >= 220.5 && centruy >= 0 && centrux <= 363.5 && centruy <= 152.5 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(299.f, 80.f);

        else if (centrux >= 364 && centruy >= 0 && centrux <= 508 && centruy <= 152.5 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(442.5f, 80.f);


        else if (centrux >= 0 && centruy >= 290.5 && centrux <= 220 && centruy <= 442.5 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(155.5f, 365.f);

        else  if (centrux >= 220.5 && centruy >= 290.5 && centrux <= 363.5 && centruy <= 442.5 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(299.f, 365.f);

        else if (centrux >= 364 && centruy >= 290.5 && centrux <= 508 && centruy <= 442.5 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(442.5f, 365.f);

        else if (Keyboard::isKeyPressed(Keyboard::Enter))cout << "pozitie invalida";


        break;
    }

    case 2:
    {

        if (centrux >= 85 && centruy >= 85 && centrux <= 302.5 && centruy <= 225 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(230.f, 155.f);

        else  if (centrux >= 303 && centruy >= 85 && centrux <= 447 && centruy <= 225 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(373.f, 155.f);



        else if (centrux >= 85 && centruy >= 225.5 && centrux <= 302.5 && centruy <= 365.5 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(230.f, 297.5f);

        else  if (centrux >= 303 && centruy >= 225.5 && centrux <= 447 && centruy <= 365.5 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(373.f, 297.5f);

        break;
    }
    case 3:
    {

        if (centrux >= 85 && centruy >= 85 && centrux <= 225 && centruy <= 225 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(160.f, 153.f);

        else  if (centrux >= 225.5 && centruy >= 85 && centrux <= 365.5 && centruy <= 225 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(300.f, 153.f);

        else if (centrux >= 367 && centruy >= 85 && centrux <= 507 && centruy <= 225 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(440.f, 153.f);




        else if (centrux >= 85 && centruy >= 225.5 && centrux <= 225 && centruy <= 365.5 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(160.f, 297.5f);

        else  if (centrux >= 225.5 && centruy >= 225.5 && centrux <= 370.5 && centruy <= 365.5 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(300.f, 297.5f);

        else if (centrux >= 371 && centruy >= 225.5 && centrux <= 513 && centruy <= 365.5 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(440.f, 297.5f);
        break;
    }
    }
}

void drag_in_place_vert(RectangleShape& obiect, RenderWindow& window, int id)
{
    FloatRect bounds = obiect.getGlobalBounds();
    float centrux = bounds.left + bounds.width / 2;
    float centruy = bounds.top + bounds.height / 2;

    //Vector2f centru = obiect.getTransform().transformPoint(obiect.getOrigin());

    switch (id)
    {
    case 1:
    {

        if (centrux >= 0 && centruy >= 0 && centrux <= 160 && centruy <= 221.5 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(84.f, 155.f);

        else  if (centrux >= 160.5 && centruy >= 0 && centrux <= 303.5 && centruy <= 221.5 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(228.f, 155.f);

        else if (centrux >= 304 && centruy >= 0 && centrux <= 450 && centruy <= 221.5 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(372.f, 155.f);



        else if (centrux >= 150 && centruy >= 222 && centrux <= 293.5 && centruy <= 335 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(227.f, 294.f);

        else  if (centrux >= 294 && centruy >= 222 && centrux <= 437.5 && centruy <= 335 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(371.f, 294.f);

        else if (centrux >= 438 && centruy >= 222 && centrux <= 581.5 && centruy <= 335 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(515.f, 294.f);


        break;

    }
    case 2:
    {


        if (centrux >= 85 && centruy >= 145 && centrux <= 223 && centruy <= 333 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(155.f, 224.f);

        else  if (centrux >= 223.5 && centruy >= 145 && centrux <= 375 && centruy <= 333 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(300.f, 224.f);

        else  if (centrux >= 375.5 && centruy >= 145 && centrux <= 515 && centruy <= 333 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(443.f, 224.f);

        break;
    }
    case 3:
    {


        if (centrux >= 85 && centruy >= 80 && centrux <= 223 && centruy <= 215 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(155.f, 152.f);

        else  if (centrux >= 223.5 && centruy >= 80 && centrux <= 375 && centruy <= 215 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(300.f, 152.f);

        else  if (centrux >= 375.5 && centruy >= 80 && centrux <= 515 && centruy <= 215 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(443.f, 152.f);

        else if (centrux >= 85 && centruy >= 215 && centrux <= 227 && centruy <= 380 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(155.f, 295.f);

        else  if (centrux >= 227.5 && centruy >= 215 && centrux <= 370 && centruy <= 380 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(300.f, 295.f);

        else  if (centrux >= 370.5 && centruy >= 215 && centrux <= 515 && centruy <= 380 && Keyboard::isKeyPressed(Keyboard::Enter))
            obiect.setPosition(443.f, 295.f);

        break;
    }
    }
}