#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h"
#include "functii_drag_piese.h"
using namespace sf;
using namespace std;

bool dragging = false;
Vector2f dragOffset;
void drag_in_place_oriz(RectangleShape& obiect, RenderWindow& window, int id);
void drag_in_place_vert(RectangleShape& obiect, RenderWindow& window, int id);
void roteste(char m[9][9]);
extern char matrice_piesa_curenta[9][9];
extern char matrice_L[9][9];
extern char matrice_gard_lung[9][9];
extern char matrice_gard_scurt[9][9];
void copiere_matrice_piese(char sursa[9][9], char destinatie[9][9]);
void copiere_matrice_tarc(char sursa[7][9], char destinatie[7][9]);
void afisare_piesa(char tarc[9][9]);
char matrice_tarc_temporar[7][9];
extern char matrice_piesa_curenta[9][9];
extern char stiva_table_de_joc[4][7][9];
extern char matrice_Tarc[7][9];
extern int index_tabla_curenta;
extern void afisare_nivel(char tarc[7][9]);
void show_win();

void show_coords(RenderWindow& window)
{
    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
    if (Mouse::isButtonPressed(Mouse::Left))
    {
        cout << "x: " << mousePos.x << "   y: " << mousePos.y << '\n';

    }
}
/*bool is_mouse_in_map(RenderWindow& window, RectangleShape& obiect)
{
    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

    if (mousePos.x >= 0.f && mousePos.x <= 600.f && mousePos.y >= 0 && mousePos.y <= 450)
        return true;
    return false;
}
*/
bool utilizat(int index_obiect, int piese_utilizate[3], int index_pozitie_curenta_piesa_utilizata)
{
    for (int i = 0; i <index_pozitie_curenta_piesa_utilizata; i++)
        if (piese_utilizate[i] == index_obiect)
        {
            cout << "e deja in stiva bro" << '\n';
            return true;
            
        }
    return false;
}

bool object_on_map(RectangleShape& obiect, RectangleShape& harta)
{
    FloatRect map_bounds = harta.getGlobalBounds();
    FloatRect object_bounds = obiect.getGlobalBounds();

    if (map_bounds.contains(object_bounds.left, object_bounds.top) && //stanga sus
        map_bounds.contains(object_bounds.left + object_bounds.width, object_bounds.top) && //dreapta sus
        map_bounds.contains(object_bounds.left, object_bounds.top + object_bounds.height) && // stanga jos
        map_bounds.contains(object_bounds.left + object_bounds.width, object_bounds.top + object_bounds.height) //dreapta jos
        )
        return true;
    return false;
}

void openFile()
{
    system("Reguli-de-joc.txt");
}

bool mouse_over_object(RectangleShape& obiect, RenderWindow& window)
{
    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
    Vector2f localMousePos = obiect.getInverseTransform().transformPoint(mousePos);

    FloatRect localBounds(Vector2f(0, 0), obiect.getSize());
    if (localBounds.contains(localMousePos))
        return true;
    return false;
}
void object_rotation(RectangleShape& obiect, int &directie,int object_id,int& lungime_piesa, int& inaltime_piesa)
{
    if (Mouse::isButtonPressed(Mouse::Right)) {
        roteste(matrice_piesa_curenta);
        switch (object_id)
        {
        case 1:
            roteste(matrice_L);
            break;
        case 2:
            roteste(matrice_gard_lung);
            break;
        case 3:
            roteste(matrice_gard_scurt);
            break;
        }
        obiect.rotate(90.f);
        directie++;
    }
}
void object_movement(RectangleShape& obiect, RenderWindow& window)
{
    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
    if (!dragging && Mouse::isButtonPressed(Mouse::Left))
    {
        dragging = true;
        dragOffset = obiect.getPosition() - mousePos;
    }

    if (dragging)
        obiect.setPosition(mousePos + dragOffset);

    if (!Mouse::isButtonPressed(Mouse::Left))
        dragging = false;
}
void object_selection(RectangleShape& object, RectangleShape& map, RenderWindow& window, int object_id, int &directie, int piese_utilizate[3], int &index_pozitie_curenta_piesa_utilizata, int used[4])
{
    static int selected_object = -1;
    int x_offset = 1;
    int y_offset = 1;
    int lungime_piesa = 0;
    int inaltime_piesa = 0;
    bool pozitionare_corecta = 1;
    FloatRect bounds = object.getGlobalBounds();

    if (mouse_over_object(object, window)  && !used[object_id])
    {
        if (selected_object == -1 || selected_object == object_id)
        {
            switch (object_id)
            {
            case 1:
                copiere_matrice_piese(matrice_L, matrice_piesa_curenta);
                if (matrice_L[0][0] == 'o')
                {
                    lungime_piesa = 5;
                    inaltime_piesa = 3;
                }
                else {
                    lungime_piesa = 3;
                    inaltime_piesa = 5;
                }
                break;
            case 2:
                copiere_matrice_piese(matrice_gard_lung, matrice_piesa_curenta);
                if (matrice_gard_lung[0][0] == 'o')
                {
                    lungime_piesa = 7;
                    inaltime_piesa = 1;
                }
                else {
                    lungime_piesa = 1;
                    inaltime_piesa = 7;
                }
                break;
            case 3:
                copiere_matrice_piese(matrice_gard_scurt, matrice_piesa_curenta);
                if (matrice_gard_scurt[0][0] == 'o')
                {
                    lungime_piesa = 5;
                    inaltime_piesa = 1;
                }
                else {
                    lungime_piesa = 1;
                    inaltime_piesa = 5;
                }
                break;
            }
            object_rotation(object,directie,object_id,lungime_piesa,inaltime_piesa);
            object_movement(object, window);

            selected_object = object_id;

            if (Keyboard::isKeyPressed(Keyboard::Enter))//&& object_on_map(object, map)
            {
                copiere_matrice_tarc(matrice_Tarc, matrice_tarc_temporar);
                show_coords(window);
                selected_object = -1;

                

                x_offset = bounds.top / 65;
                y_offset = bounds.left / 65;

                cout << x_offset << endl << y_offset << endl;

                for (int i = 1; i < inaltime_piesa + 1; i++)
                    for (int j = 1; j < lungime_piesa + 1; j++)
                    {
                        if (matrice_tarc_temporar[i + x_offset - 1][j + y_offset - 1] == 'g' && matrice_piesa_curenta[i][j] == 'g')
                            matrice_tarc_temporar[i + x_offset - 1][j + y_offset - 1] = 'X';
                        else if (matrice_tarc_temporar[i + x_offset - 1][j + y_offset - 1] == 'g' && matrice_piesa_curenta[i][j] == 'q')
                            matrice_tarc_temporar[i + x_offset - 1][j + y_offset - 1] = 'g';
                        else if (matrice_tarc_temporar[i + x_offset - 1][j + y_offset - 1] == 'g' && matrice_piesa_curenta[i][j] == '#')
                            matrice_tarc_temporar[i + x_offset - 1][j + y_offset - 1] = 'g';
                        else if (matrice_tarc_temporar[i + x_offset - 1][j + y_offset - 1] == '#')
                            matrice_tarc_temporar[i + x_offset - 1][j + y_offset - 1] = matrice_piesa_curenta[i][j];

                    }

                for (int i = 1; i < 7; i++)
                    for (int j = 1; j < 9; j++)
                        if (matrice_tarc_temporar[i][j] == 'X')
                        {
                            pozitionare_corecta = 0;
                        }
                if (pozitionare_corecta == 0)
                    goto _nu_plasa_piesa;
                else
                {
                    cout << lungime_piesa << " " << inaltime_piesa<<endl;
                    if (utilizat(object_id, piese_utilizate, index_pozitie_curenta_piesa_utilizata) == false)
                        piese_utilizate[++index_pozitie_curenta_piesa_utilizata] = object_id;
                    copiere_matrice_tarc(matrice_tarc_temporar, matrice_Tarc);
                    index_tabla_curenta++;
                    afisare_nivel(matrice_Tarc);
                    copiere_matrice_tarc(matrice_Tarc, stiva_table_de_joc[index_tabla_curenta]);
                    if (verificare_victorie() == 1)
                        show_win();
                }


                for (int i = 0; i <= index_pozitie_curenta_piesa_utilizata; i++)
                    cout << piese_utilizate[i] << ' ';

                show_coords(window);
                cout << '\n';
                used[object_id] = 1;
                switch (matrice_piesa_curenta[0][0])
                {
                case 'o':
                    drag_in_place_oriz(object, window, object_id);
                    break;
                case 'v':
                    drag_in_place_vert(object, window, object_id);
                    break;
                }
            

            }
        }

    }
_nu_plasa_piesa:
    if (!mouse_over_object(object, window) && selected_object == object_id)
    {
        selected_object = -1;
    }

}