#pragma once
#include <iostream>

#include "unelte_piese.h"

#pragma warning(disable : 4996)

using namespace std;

char matrice_tarc_temporar[7][9];
char matrice_Tarc[7][9];

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
        }
        fread(&buffer, sizeof(char), 1, ftarc);
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

void fill_victorie(int i, int j,char matrice_temporara[7][9],char vector_animale[63], int& indice_vector_animale, int& contor_troaca)
{
    if (matrice_temporara[i][j] != '#')
        if (matrice_temporara[i][j] == 'a')
        {
            contor_troaca++;
            matrice_temporara[i][j] = 'X';
        }
        else {
            vector_animale[indice_vector_animale] = matrice_temporara[i][j];
            indice_vector_animale++;
            matrice_temporara[i][j] = 'X';
        }
    else matrice_temporara[i][j] = 'X';
    if (matrice_temporara[i][j - 1] != 'g' && matrice_temporara[i][j-1]!='q' && matrice_temporara[i][j-1]!='X')
        fill_victorie(i,j-1,matrice_temporara,vector_animale,indice_vector_animale,contor_troaca);
    if (matrice_temporara[i+1][j] != 'g' && matrice_temporara [i+1][j]!='q' && matrice_temporara[i+1][j]!='X')
        fill_victorie(i+1, j, matrice_temporara, vector_animale, indice_vector_animale, contor_troaca);
    if (matrice_temporara[i][j +1] != 'g' && matrice_temporara[i][j+1]!='q' && matrice_temporara[i][j+1]!='X')
        fill_victorie(i, j + 1, matrice_temporara, vector_animale, indice_vector_animale, contor_troaca);
    if (matrice_temporara[i-1][j] != 'g' && matrice_temporara[i-1][j]!='q' && matrice_temporara[i - 1][j] != 'X')
        fill_victorie(i-1, j, matrice_temporara, vector_animale, indice_vector_animale, contor_troaca);
}
