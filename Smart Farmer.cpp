#include <iostream>
#include <conio.h>

#include "unelte_piese.h"

#pragma warning(disable : 4996)

using namespace std;

char tarc[7][9];
char piesa_curenta[7][7];

void initializare_Nivel(char tarc[7][9])
{
    char buffer;
    FILE* ftarc;
    int nivel;

select_nivel:
    cout << "selectaza nivelul: ";
    cin >> nivel;
    switch (nivel)
    {
    case 1:
        ftarc = fopen("Nivele\\nivel1.txt", "r+");
        break;
    case 2:
        ftarc = fopen("Nivele\\nivel2.txt", "r+");
        break;
    case 3:
        ftarc = fopen("Nivele\\nivel3.txt", "r+");
        break;
    case 4:
        ftarc = fopen("Nivele\\nivel4.txt", "r+");
        break;
    case 5:
        ftarc = fopen("Nivele\\nivel5.txt", "r+");
        break;
    default:
        cout << "nivel invalid\n";
        goto select_nivel;
        break;
    }
    system("CLS");

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fread(&tarc[i][j], sizeof(char), 1, ftarc);
            fread(&buffer, sizeof(char), 1, ftarc);
            cout << tarc[i][j] << " ";
        }
        fread(&buffer, sizeof(char), 1, ftarc);
        cout << endl;
    }
    fclose(ftarc);
}

void afisare_nivel(char tarc[7][9])
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 9; j++)
            cout << tarc[i][j] << " ";
        cout << endl;
    }
}

void afisare_piesa(char tarc[7][7])
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
            cout << tarc[i][j] << " ";
        cout << endl;
    }
}

int main()
{
    bool playing=1;
    initializare_Nivel(tarc);
    initializare_matrice_piese();
    while (playing)
    {
        selectare_piesa:cout << "Selecteaza piesa:" << endl << "1.Piesa in forma de L" << endl << "2.Piesa dreapta lunga" << endl << "3.Piesa dreapta scurta" << endl;
        switch (getch())
        {
        case '1':
            system("CLS");
            afisare_nivel(tarc);
            cout << "Ai selectat piesa in forma de L.Apasati orice tasta pentru a continua."<<endl;
            copiere_matrice(matrice_L, piesa_curenta);
            getch();
            break;
        case '2':
            system("CLS");
            afisare_nivel(tarc);
            cout << "Ai selectat piesa dreapta lunga.Apasati orice tasta pentru a continua."<<endl;
            copiere_matrice(matrice_gard_lung,piesa_curenta);
            getch();
            break;
        case '3':
            system("CLS");
            afisare_nivel(tarc);
            cout << "Ai selectat piesa dreapta scurta.Apasati orice tasta pentru a continua."<<endl;
            copiere_matrice(matrice_gard_scurt,piesa_curenta);
            getch();
            break;
        case 27: ///ASCII 32=tasta escape
            playing = false;
            break;
        default:
            cout << "Selectie invalida! Va rugam faceti o selectie valida."<<endl;
            goto selectare_piesa;
            break;
        }
        system("CLS");
        afisare_nivel(tarc);
        if (playing)
        {

        selectare_actiune:cout << "Actiuni posibile:" << endl << "-Rotire piesa:tasta 'r'" << endl << "-Mutare piesa:tastele sageti" << " -Reselectare piesa:tasta Backspace\n";
        switch (getch())
        {
            case 'r':
                roteste(piesa_curenta);
                cout << "Aceasta este piesa dupa rotire:\n";
                afisare_piesa(piesa_curenta);
                getch();
                goto selectare_actiune;
                break;
            case '\b':///backspace
                goto selectare_piesa;
                getch();
                break;
            case '37':///left arrow ?
                getch();
                break;
            case '38':///up arrow ?
                getch();
                break;
            case '39':///right arrow ?
                getch();
                break;
            case '40':///down arrow ?
                getch();
                break;
            case 27: ///ASCII 32=tasta escape
                playing = false;
                break;
            default:
                system("CLS");
                afisare_nivel(tarc);
                goto selectare_actiune;
                break;
        }
        }
        

    }

    return 0;
}
