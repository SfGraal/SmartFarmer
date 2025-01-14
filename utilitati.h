#ifndef UNELTE_PIESE_H
#define UNELTE_PIESE_H

bool verificare_victorie();

#endif
#pragma once
#include <iostream>

#include "unelte_piese.h"
#include "Button.h"
#include "functii_drag_piese.h"
#include "functii_piese_butoane.h"
#include "Maps.h"
#include "meniu.h"

#pragma warning(disable : 4996)

using namespace std;

void initializare_Nivel(char tarc[7][9], char nivel)
{
    char buffer;
    FILE* ftarc = 0;

    switch (nivel)
    {
    case '1':
        ftarc = fopen("Nivele\\nivel1.txt", "r+");
        break;
    case '2':
        ftarc = fopen("Nivele\\nivel2.txt", "r+");
        break;
    case '3':
        ftarc = fopen("Nivele\\nivel3.txt", "r+");
        break;
    case '4':
        ftarc = fopen("Nivele\\nivel4.txt", "r+");
        break;
    case '5':
        ftarc = fopen("Nivele\\nivel5.txt", "r+");
        break;
    default:
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

    copiere_matrice_tarc(matrice_Tarc, stiva_table_de_joc[0]);
    for (int i = 0; i < 4; i++)
        copiere_matrice_tarc(matrice_Tarc, stiva_table_de_joc[i]);
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

void afisare_piesa(char tarc[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
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

void genereaza_nivel(char matrice_Tarc[7][9])
{
    system("CLS");
generare_nivel:
    srand(time(0));
    char buffer;
    FILE* ftarc;
    ftarc = fopen("Nivele\\nivelGol.txt", "r+");
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fread(&matrice_Tarc[i][j], sizeof(char), 1, ftarc);
            fread(&buffer, sizeof(char), 1, ftarc);
        }
        fread(&buffer, sizeof(char), 1, ftarc);
    }
    fclose(ftarc);
    int numar_piese;
    int x_pozitie = 0;
    int y_pozitie = 0;
    ///generare piese cai
    numar_piese = rand() % 3;
    for (int i = 1; i <= numar_piese; i++)
    {
        while (x_pozitie == 0 || y_pozitie == 0 || matrice_Tarc[x_pozitie][y_pozitie] != '#' || x_pozitie % 2 == 0 || y_pozitie % 2 == 0)
        {
            x_pozitie = rand() % 7;
            y_pozitie = rand() % 9;
        }
        matrice_Tarc[x_pozitie][y_pozitie] = 'c';
    }
    ///generare piese vaci
    numar_piese = rand() % 3;
    for (int i = 1; i <= numar_piese; i++)
    {
        while (x_pozitie == 0 || y_pozitie == 0 || matrice_Tarc[x_pozitie][y_pozitie] != '#' || x_pozitie % 2 == 0 || y_pozitie % 2 == 0)
        {
            x_pozitie = rand() % 7;
            y_pozitie = rand() % 9;
        }
        matrice_Tarc[x_pozitie][y_pozitie] = 'v';
    }
    ///generare piese oi
    numar_piese = rand() % 3;
    for (int i = 1; i <= numar_piese; i++)
    {
        while (x_pozitie == 0 || y_pozitie == 0 || matrice_Tarc[x_pozitie][y_pozitie] != '#' || x_pozitie % 2 == 0 || y_pozitie % 2 == 0)
        {
            x_pozitie = rand() % 7;
            y_pozitie = rand() % 9;
        }
        matrice_Tarc[x_pozitie][y_pozitie] = 'o';
    }
    ///generare piese porci
    numar_piese = rand() % 3;
    for (int i = 1; i <= numar_piese; i++)
    {
        while (x_pozitie == 0 || y_pozitie == 0 || matrice_Tarc[x_pozitie][y_pozitie] != '#' || x_pozitie % 2 == 0 || y_pozitie % 2 == 0)
        {
            x_pozitie = rand() % 7;
            y_pozitie = rand() % 9;
        }
        matrice_Tarc[x_pozitie][y_pozitie] = 'p';
    }
    ///generare piese troaca cu apa
    numar_piese = 0;
    char vector_animale[4] = { 'c' , 'v' , 'o' , 'p'};
    for (int i=1;i<6;i++)
        for (int j=1;j<8;j++)
            for (int k=0;k<4;k++)
                if (matrice_Tarc[i][j] == vector_animale[k])
                {
                    vector_animale[k] = 'x';
                    numar_piese++;
                }
    for (int i = 1; i <= numar_piese; i++)
    {
        while (x_pozitie == 0 || y_pozitie == 0 || matrice_Tarc[x_pozitie][y_pozitie] != '#' || x_pozitie % 2 == 0 || y_pozitie % 2 == 0)
        {
            x_pozitie = rand() % 7;
            y_pozitie = rand() % 9;
        }
        matrice_Tarc[x_pozitie][y_pozitie] = 'a';
    }
    ///marcarea dificultatii nivelului
    matrice_Tarc[0][0] = 'u';
    for (int i = 1; i < 6; i++)
        for (int j = 1; j < 8; j++)
            if (matrice_Tarc[i][j] == 'a')
                matrice_Tarc[0][0] = 'd';
    if (verificare_victorie() == 1)
        goto generare_nivel;
}

void intSwap(int& a, int& b)
{
    int aux;
    aux = a;
    a = b;
    b = aux;
}

void charSwap(char& a, char& b)
{
    char aux;
    aux = a;
    a = b;
    b = aux;
}

