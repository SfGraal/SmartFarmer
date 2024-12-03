#pragma once
#include <iostream>
#pragma warning(disable : 4996)

using namespace std;

char matrice_L[7][7];
char matrice_gard_lung[7][7];
char matrice_gard_scurt[7][7];

void initializare_matrice_piese()
{
    FILE* fpiese = fopen("piese.txt", "r+");
    char buffer;
    ///initializare matrice piesa L
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            fread(&matrice_L[i][j], sizeof(char), 1, fpiese);
            fread(&buffer, sizeof(char), 1, fpiese);
        }
        fread(&buffer, sizeof(char), 1, fpiese);
    }
    ///initializare matrice piesa gard lung
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            fread(&matrice_gard_lung[i][j], sizeof(char), 1, fpiese);
            fread(&buffer, sizeof(char), 1, fpiese);
        }
        fread(&buffer, sizeof(char), 1, fpiese);
    }
    ///initializare matrice piesa gard scurt
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            fread(&matrice_gard_scurt[i][j], sizeof(char), 1, fpiese);
            fread(&buffer, sizeof(char), 1, fpiese);
        }
        fread(&buffer, sizeof(char), 1, fpiese);
    }
    fclose(fpiese);
}

void snap_top_left(char mat[7][7]) {
    int rand_minim = 7, coloana_minima = 7;
    for (int i = 1; i < 6; i++) {
        for (int j = 1; j < 6; j++) {
            if (mat[i][j] == 'q' || mat[i][j] == 'g') {
                if (i < rand_minim) rand_minim = i;
                if (j < coloana_minima) coloana_minima = j;
            }
        }
    }
    char matrice_temporara[7][7];
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            matrice_temporara[i][j] = '#';
        }
    }
    for (int i = 1; i < 6; i++) {
        for (int j = 1; j < 6; j++) {
            if (mat[i][j] == 'q' || mat[i][j] == 'g') {
                matrice_temporara[i - rand_minim + 1][j - coloana_minima + 1] = mat[i][j];
            }
        }
    }
    matrice_temporara[0][0] = mat[0][0];
    matrice_temporara[0][6] = mat[0][6];
    matrice_temporara[6][6] = mat[6][6];
    matrice_temporara[6][0] = mat[6][0];
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            mat[i][j] = matrice_temporara[i][j];
        }
    }
}

void roteste(char m[7][7])
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = i + 1; j < 7; j++)
            swap(m[i][j], m[j][i]);
    }

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            swap(m[i][j], m[i][7 - j - 1]);
        }
    }
    snap_top_left(m);
}

void copiere_matrice(char sursa[7][7], char destinatie[7][7])
{
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++)
            destinatie[i][j] = sursa[i][j];
}