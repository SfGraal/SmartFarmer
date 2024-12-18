#include <iostream>
#include <conio.h>

#include "unelte_piese.h"
#include "utilitati.h"

#pragma warning(disable : 4996)

using namespace std;

int main()
{
    bool playing=1;
    int index_piesa_Selectata;

    initializare_Nivel(matrice_Tarc);
    initializare_matrice_piese();
    copiere_matrice_tarc(matrice_Tarc, stiva_table_de_joc[0]);

    afisare_nivel(matrice_Tarc);
    while (playing)
    {
        cout << "Selecteaza o actiune:" << endl << "-Plasare piesa:tasta p" << endl << "-Undo miscare:tasta u"<<endl;
        switch (getch())
        {
        case 'p':
selectare_piesa:system("CLS");
            afisare_nivel(matrice_Tarc);
            cout << "Selecteaza piesa:" << endl << "1.Piesa in forma de L" << endl << "2.Piesa dreapta lunga" << endl << "3.Piesa dreapta scurta" << endl;
            switch (getch())
            {
            case '1':
                index_piesa_Selectata = 1;
                for (int i = 0; i < 3; i++)
                    if (piese_utilizate[i] == index_piesa_Selectata)
                    {
                        cout << "Piesa a fost deja utilizata.Apasati orice tasta pentru a continua.";
                        getch();
                        goto selectare_piesa;
                    }
                piese_utilizate[index_pozitie_curenta_piese_utilizate] = index_piesa_Selectata;
                index_pozitie_curenta_piese_utilizate++;
                system("CLS");
                afisare_nivel(matrice_Tarc);
                cout << "Ai selectat piesa in forma de L.Apasati orice tasta pentru a continua." << endl;
                copiere_matrice_piese(matrice_L, matrice_piesa_curenta);
                getch();
                break;
            case '2':
                index_piesa_Selectata = 2;
                for (int i = 0; i < 3; i++)
                    if (piese_utilizate[i] == index_piesa_Selectata)
                    {
                        cout << "Piesa a fost deja utilizata.Apasati orice tasta pentru a continua.";
                        getch();
                        goto selectare_piesa;
                    }
                piese_utilizate[index_pozitie_curenta_piese_utilizate] = index_piesa_Selectata;
                index_pozitie_curenta_piese_utilizate++;
                system("CLS");
                afisare_nivel(matrice_Tarc);
                cout << "Ai selectat piesa dreapta lunga.Apasati orice tasta pentru a continua." << endl;
                copiere_matrice_piese(matrice_gard_lung, matrice_piesa_curenta);
                getch();
                break;
            case '3':
                index_piesa_Selectata = 3;
                for (int i = 0; i < 3; i++)
                    if (piese_utilizate[i] == index_piesa_Selectata)
                    {
                        cout << "Piesa a fost deja utilizata.Apasati orice tasta pentru a continua.";
                        getch();
                        goto selectare_piesa;
                    }
                piese_utilizate[index_pozitie_curenta_piese_utilizate] = index_piesa_Selectata;
                index_pozitie_curenta_piese_utilizate++;
                system("CLS");
                afisare_nivel(matrice_Tarc);
                cout << "Ai selectat piesa dreapta scurta.Apasati orice tasta pentru a continua." << endl;
                copiere_matrice_piese(matrice_gard_scurt, matrice_piesa_curenta);
                index_piesa_Selectata = 3;
                getch();
                break;
            case 27: ///ASCII 32=tasta escape
                playing = false;
                break;
            default:
                cout << "Selectie invalida! Va rugam faceti o selectie valida." << endl;
                goto selectare_piesa;
                break;
            }
            system("CLS");
            afisare_nivel(matrice_Tarc);
            if (playing)
            {
                int cod_returnare = plasare_piesa(index_piesa_Selectata);
                if (cod_returnare == -1)
                    playing = false;
                else if (cod_returnare == 0)
                    goto selectare_piesa;
                else if (cod_returnare == 1)
                    if (verificare_victorie() == true)
                    {
                        system("CLS");
                        cout << "Felicitari!Ati castigat!";
                        playing = 0;
                    }
            }
            break;
        case 'u':
            if (index_tabla_curenta >= 1)
            {
                system("CLS");
                index_tabla_curenta--;
                copiere_matrice_tarc(stiva_table_de_joc[index_tabla_curenta], matrice_Tarc);
                index_pozitie_curenta_piese_utilizate--;
                piese_utilizate[index_pozitie_curenta_piese_utilizate] = 0;
                afisare_nivel(matrice_Tarc);
            }
            else {
                cout << "Tabla de joc este cea originala.";
            }
            break;

        }
    }

    return 0;
}