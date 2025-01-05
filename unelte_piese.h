#pragma once
#include <iostream>

#include "utilitati.h"

#pragma warning(disable : 4996)

using namespace std;

char matrice_L[9][9];
char matrice_gard_lung[9][9];
char matrice_gard_scurt[9][9];
char matrice_piesa_curenta[9][9];
char stiva_table_de_joc[4][7][9];
int index_tabla_curenta = 0;
int piese_utilizate[3] = { 0 }, index_pozitie_curenta_piese_utilizate = 0;

void initializare_matrice_piese()
{
    FILE* fpiese = fopen("piese.txt", "r+");
    char buffer;
    ///initializare matrice piesa L
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fread(&matrice_L[i][j], sizeof(char), 1, fpiese);
            fread(&buffer, sizeof(char), 1, fpiese);
        }
        fread(&buffer, sizeof(char), 1, fpiese);
    }
    ///initializare matrice piesa gard lung
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fread(&matrice_gard_lung[i][j], sizeof(char), 1, fpiese);
            fread(&buffer, sizeof(char), 1, fpiese);
        }
        fread(&buffer, sizeof(char), 1, fpiese);
    }
    ///initializare matrice piesa gard scurt
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fread(&matrice_gard_scurt[i][j], sizeof(char), 1, fpiese);
            fread(&buffer, sizeof(char), 1, fpiese);
        }
        fread(&buffer, sizeof(char), 1, fpiese);
    }
    fclose(fpiese);
}

void snap_top_left(char mat[9][9]) {
    int rand_minim = 9, coloana_minima = 9;
    for (int i = 1; i < 8; i++) {
        for (int j = 1; j < 8; j++) {
            if (mat[i][j] == 'q' || mat[i][j] == 'g') {
                if (i < rand_minim) rand_minim = i;
                if (j < coloana_minima) coloana_minima = j;
            }
        }
    }
    char matrice_temporara[9][9];
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            matrice_temporara[i][j] = '#';
        }
    }
    for (int i = 1; i < 8; i++) {
        for (int j = 1; j < 8; j++) {
            if (mat[i][j] == 'q' || mat[i][j] == 'g') {
                int new_i = i - rand_minim + 1;
                int new_j = j - coloana_minima + 1;
                if (new_i >= 0 && new_i < 8 && new_j >= 0 && new_j < 8) {
                    matrice_temporara[new_i][new_j] = mat[i][j];
                }
            }
        }
    }
    matrice_temporara[0][0] = mat[0][0];
    matrice_temporara[0][8] = mat[0][8];
    matrice_temporara[8][8] = mat[8][8];
    matrice_temporara[7][0] = mat[7][0];
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            mat[i][j] = matrice_temporara[i][j];
        }
    }
}



void roteste(char m[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = i + 1; j < 9; j++)
        {
            std::swap(m[i][j], m[j][i]);
        }
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::swap(m[i][j], m[i][9 - j - 1]);
        }
    }
    snap_top_left(m);
}

void copiere_matrice_piese(char sursa[9][9], char destinatie[9][9])
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            destinatie[i][j] = sursa[i][j];
}

void copiere_matrice_tarc(char sursa[7][9], char destinatie[7][9])
{
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 9; j++)
            destinatie[i][j] = sursa[i][j];
}

int plasare_piesa(int index_piesa_selectata) /// returneaza 1 = piesa plasata; returneaza 0 = piesa nu a fost plasata(adica trebuie selectata una noua); returneaza -1 = program incheiat
{
    char matrice_tarc_temporar[7][9];
    int lungime_piesa, inaltime_piesa;
    int x_offset=0, y_offset=0;
    bool asezare_corecta = 1;

    copiere_matrice_tarc(matrice_Tarc, matrice_tarc_temporar);

    switch (index_piesa_selectata)
    {
    case 1:
        lungime_piesa = 5;
        inaltime_piesa = 3;
        if (matrice_L[0][0] == 'v')
            intSwap (lungime_piesa, inaltime_piesa);
        break;
    case 2:
        lungime_piesa = 7;
        inaltime_piesa = 1;
        if (matrice_gard_lung[0][0] == 'v')
            intSwap(lungime_piesa, inaltime_piesa);
        break;
    case 3:
        lungime_piesa = 5;
        inaltime_piesa = 1;
        if (matrice_gard_scurt[0][0] == 'v')
            intSwap(lungime_piesa, inaltime_piesa);
        break;
    }

selectare_actiune:
    asezare_corecta = 1;
    copiere_matrice_tarc(matrice_Tarc, matrice_tarc_temporar);
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
    system("CLS");
    afisare_nivel(matrice_tarc_temporar);
    cout << "Actiuni posibile:" << endl << "-Rotire piesa:tasta 'r'" << endl << "-Mutare piesa:tastele sageti" << endl << "-Reselectare piesa:tasta Backspace" << endl << "-Confirmare plasare:tasta Enter" << endl ;
    switch (getch())
    {
    case 'r':
        roteste(matrice_piesa_curenta);
        system("CLS");
        intSwap(lungime_piesa, inaltime_piesa);
        while (x_offset + inaltime_piesa > 7)
            x_offset -= 2;
        while (y_offset + lungime_piesa > 9)
            y_offset -= 2;
        copiere_matrice_tarc(matrice_Tarc, matrice_tarc_temporar);
        for (int i = 1; i < inaltime_piesa + 1; i++)
            for (int j = 1; j < lungime_piesa + 1; j++)
            {
                if (matrice_tarc_temporar[i + x_offset - 1][j + y_offset - 1] == 'g' && matrice_piesa_curenta[i][j] == 'g')
                    matrice_tarc_temporar[i + x_offset - 1][j + y_offset - 1] = 'x';
                else if (matrice_tarc_temporar[i + x_offset - 1][j + y_offset - 1] == 'g' && matrice_piesa_curenta[i][j] == 'q')
                    matrice_tarc_temporar[i + x_offset - 1][j + y_offset - 1] = 'G';
                else if (matrice_tarc_temporar[i + x_offset - 1][j + y_offset - 1] == 'g' && matrice_piesa_curenta[i][j] == '#')
                    matrice_tarc_temporar[i + x_offset - 1][j + y_offset - 1] = 'G';
                else if (matrice_tarc_temporar[i + x_offset - 1][j + y_offset - 1] == '#')
                    matrice_tarc_temporar[i + x_offset - 1][j + y_offset - 1] = matrice_piesa_curenta[i][j];

            }
        goto selectare_actiune;
        break;
    case 8:///backspace
        system("CLS");
        index_pozitie_curenta_piese_utilizate--;
        piese_utilizate[index_pozitie_curenta_piese_utilizate] = 0;
        
        return 0;
        break;
    case 75:///left arrow 
        if (y_offset >= 2)
            y_offset -= 2;
        goto selectare_actiune;
        break;
    case 72:///up arrow 
        if (x_offset >= 2)
            x_offset -= 2;
        goto selectare_actiune;
        break;
    case 77:///right arrow 
        if (y_offset + lungime_piesa - 1 <= 7)
            y_offset += 2;
        goto selectare_actiune;
        break;
    case 80:///down arrow 
        if (x_offset + inaltime_piesa - 1 <= 5)
            x_offset += 2;
        goto selectare_actiune;
        break;
    case 27: ///ASCII 32=tasta escape
        return -1;
        break;
    case 13: ///ASCII 13=tasta Enter
        
        for (int i = 0; i < 7; i++)
            for (int j = 0; j < 9; j++)
                if (matrice_tarc_temporar[i][j] == 'X')
                    asezare_corecta = 0;
        if (asezare_corecta == 1)
        {
            index_tabla_curenta++;
            copiere_matrice_tarc(matrice_tarc_temporar, matrice_Tarc);
            copiere_matrice_tarc(matrice_Tarc, stiva_table_de_joc[index_tabla_curenta]);
            return 1;
        }
        else {
            cout << "ASEZARE INCORECTA.Apasati orice tasta pentru a continua.";
            getch();
            goto selectare_actiune;
        }
        break;
    default:
        system("CLS");
        afisare_nivel(matrice_Tarc);
        goto selectare_actiune;
        break;
    }
}

bool verificare_victorie()
{
    char matrice_temporara[7][9];
    char vector_animale[63] = { 'X' };
    int indice_vector_animale = 0;
    int contor_troaca = 0;
    int contor_animale_curente = 0;
    copiere_matrice_tarc(matrice_Tarc, matrice_temporara);
    for (int i = 1; i < 6; i++)
        for (int j = 1; j < 8; j++)
            if (matrice_temporara[i][j] != 'g' && matrice_temporara[i][j] != 'q' && matrice_temporara[i][j] != 'X')
            {
                fill_victorie(i, j, matrice_temporara, vector_animale, indice_vector_animale, contor_troaca);
                for (int k = 1; k < indice_vector_animale; k++)
                    if (vector_animale[k] != vector_animale[0])
                        return 0;
                for (int i = 1; i < 6; i++)
                    for (int j = 1; j < 8; j++)
                        if (matrice_Tarc[i][j] == vector_animale[0])
                            contor_animale_curente++;
                if (contor_animale_curente != indice_vector_animale)
                    return 0;
                if (matrice_temporara[0][0] == 'd' && contor_troaca == 0)
                    return 0;
                for (int k = 0; k < 63; k++)
                    vector_animale[k] = '1';
                contor_animale_curente = 0;
                indice_vector_animale = 0;
                contor_troaca = 0;
            }
    return 1;
}

bool rezolvare_automata()
{
    ///piesa1 = piesa L ; piesa2 = piesa lunga ; piesa3 = piesa scurta
    for (int i = 0; i < 4; i++)
        copiere_matrice_tarc(stiva_table_de_joc[0], stiva_table_de_joc[i]);
    system("CLS");
    int x_offset1 = 0, x_offset2 = 0, x_offset3 = 0;
    int y_offset1 = 0, y_offset2 = 0, y_offset3 = 0;
    char matrice_tarc_temporar[7][9];
    int lungime_piesa1 = 3, inaltime_piesa1 = 5;
    int lungime_piesa2 = 1, inaltime_piesa2 = 7;
    int lungime_piesa3 = 1, inaltime_piesa3 = 5;
    bool asezare_corecta1 = 1;
    bool asezare_corecta2 = 1;
    bool asezare_corecta3 = 1;
    int rotiri1 = 0, rotiri2 = 0, rotiri3 = 0;
    copiere_matrice_tarc(matrice_Tarc, stiva_table_de_joc[0]);
    ///prima piesa asezata e L,apoi se incearca ordinea lunga->scurta, apoi se incearca ordinea scurta->lunga
    while (rotiri1 <= 3)
    {
        for (x_offset1 = 0; x_offset1 + inaltime_piesa1 - 1 <= 6; x_offset1 += 2)
            for (y_offset1 = 0; y_offset1 + lungime_piesa1 - 1 <= 8; y_offset1 += 2)
            {
                asezare_corecta1 = 1;
                copiere_matrice_tarc(matrice_Tarc, matrice_tarc_temporar);
                for (int i = 1; i < inaltime_piesa1 + 1; i++)
                    for (int j = 1; j < lungime_piesa1 + 1; j++)
                    {
                        if (matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] == 'g' && matrice_L[i][j] == 'g')
                            matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] = 'X';
                        else if (matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] == 'g' && matrice_L[i][j] == 'q')
                            matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] = 'g';
                        else if (matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] == 'g' && matrice_L[i][j] == '#')
                            matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] = 'g';
                        else if (matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] == '#')
                            matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] = matrice_L[i][j];
                    }
                for (int i = 0; i < 7; i++)
                    for (int j = 0; j < 9; j++)
                        if (matrice_tarc_temporar[i][j] == 'X')
                            asezare_corecta1 = 0;
                if (asezare_corecta1 == 1)
                {
                    copiere_matrice_tarc(matrice_tarc_temporar, matrice_Tarc);
                    copiere_matrice_tarc(matrice_Tarc, stiva_table_de_joc[1]);
                    if (verificare_victorie() == 1)
                        return 1;
                    rotiri2 = 0;
                    while (rotiri2 <= 1)
                    {
                        for (x_offset2 = 0; x_offset2 + inaltime_piesa2 - 1 <= 6; x_offset2 += 2)
                            for (y_offset2 = 0; y_offset2 + lungime_piesa2 - 1 <= 8; y_offset2 += 2)
                            {
                                asezare_corecta2 = 1;
                                copiere_matrice_tarc(matrice_Tarc, matrice_tarc_temporar);
                                for (int i = 1; i < inaltime_piesa2 + 1; i++)
                                    for (int j = 1; j < lungime_piesa2 + 1; j++)
                                    {
                                        if (matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] == 'g' && matrice_gard_lung[i][j] == 'g')
                                            matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] = 'X';
                                        else if (matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] == 'g' && matrice_gard_lung[i][j] == 'q')
                                            matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] = 'g';
                                        else if (matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] == 'g' && matrice_gard_lung[i][j] == '#')
                                            matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] = 'g';
                                        else if (matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] == '#')
                                            matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] = matrice_gard_lung[i][j];
                                    }
                                for (int i = 0; i < 7; i++)
                                    for (int j = 0; j < 9; j++)
                                        if (matrice_tarc_temporar[i][j] == 'X')
                                            asezare_corecta2 = 0;
                                if (asezare_corecta2 == 1)
                                {
                                    index_tabla_curenta++;
                                    copiere_matrice_tarc(matrice_tarc_temporar, matrice_Tarc);
                                    copiere_matrice_tarc(matrice_Tarc, stiva_table_de_joc[2]);
                                    if (verificare_victorie() == 1)
                                        return 1;
                                    rotiri3 = 0;
                                    while (rotiri3 <= 1)
                                    {
                                        for (x_offset3 = 0; x_offset3 + inaltime_piesa3 - 1 <= 6; x_offset3 += 2)
                                            for (y_offset3 = 0; y_offset3 + lungime_piesa3 - 1 <= 8; y_offset3 += 2)
                                            {
                                                asezare_corecta3 = 1;
                                                copiere_matrice_tarc(matrice_Tarc, matrice_tarc_temporar);
                                                for (int i = 1; i < inaltime_piesa3 + 1; i++)
                                                    for (int j = 1; j < lungime_piesa3 + 1; j++)
                                                    {
                                                        if (matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] == 'g' && matrice_gard_scurt[i][j] == 'g')
                                                            matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] = 'X';
                                                        else if (matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] == 'g' && matrice_gard_scurt[i][j] == 'q')
                                                            matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] = 'g';
                                                        else if (matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] == 'g' && matrice_gard_scurt[i][j] == '#')
                                                            matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] = 'g';
                                                        else if (matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] == '#')
                                                            matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] = matrice_gard_scurt[i][j];
                                                    }
                                                for (int i = 0; i < 7; i++)
                                                    for (int j = 0; j < 9; j++)
                                                        if (matrice_tarc_temporar[i][j] == 'X')
                                                            asezare_corecta3 = 0;

                                                if (asezare_corecta3 == 1)
                                                {
                                                    copiere_matrice_tarc(matrice_tarc_temporar, matrice_Tarc);
                                                    copiere_matrice_tarc(matrice_Tarc, stiva_table_de_joc[3]);
                                                    if (verificare_victorie() == 1)
                                                        return 1;
                                                }
                                                else continue;
                                                copiere_matrice_tarc(stiva_table_de_joc[2], matrice_Tarc);

                                            }
                                        roteste(matrice_gard_scurt);
                                        intSwap(lungime_piesa3, inaltime_piesa3);
                                        rotiri3++;
                                    }
                                    if (verificare_victorie() == 1)
                                        return 1;
                                }
                                else continue;
                                copiere_matrice_tarc(stiva_table_de_joc[1], matrice_Tarc);

                            }
                        roteste(matrice_gard_lung);
                        intSwap(lungime_piesa2, inaltime_piesa2);
                        rotiri2++;
                    }
                    rotiri3 = 0;
                    while (rotiri3 <= 1)
                    {
                        for (x_offset3 = 0; x_offset3 + inaltime_piesa3 - 1 <= 6; x_offset3 += 2)
                            for (y_offset3 = 0; y_offset3 + lungime_piesa3 - 1 <= 8; y_offset3 += 2)
                            {
                                asezare_corecta3 = 1;
                                copiere_matrice_tarc(matrice_Tarc, matrice_tarc_temporar);
                                for (int i = 1; i < inaltime_piesa3 + 1; i++)
                                    for (int j = 1; j < lungime_piesa3 + 1; j++)
                                    {
                                        if (matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] == 'g' && matrice_gard_scurt[i][j] == 'g')
                                            matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] = 'X';
                                        else if (matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] == 'g' && matrice_gard_scurt[i][j] == 'q')
                                            matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] = 'g';
                                        else if (matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] == 'g' && matrice_gard_scurt[i][j] == '#')
                                            matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] = 'g';
                                        else if (matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] == '#')
                                            matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] = matrice_gard_scurt[i][j];
                                    }
                                for (int i = 0; i < 7; i++)
                                    for (int j = 0; j < 9; j++)
                                        if (matrice_tarc_temporar[i][j] == 'X')
                                            asezare_corecta3 = 0;
                                if (asezare_corecta3 == 1)
                                {
                                    index_tabla_curenta++;
                                    copiere_matrice_tarc(matrice_tarc_temporar, matrice_Tarc);
                                    copiere_matrice_tarc(matrice_Tarc, stiva_table_de_joc[2]);
                                    if (verificare_victorie() == 1)
                                        return 1;
                                    rotiri2 = 0;
                                    while (rotiri2 <= 1)
                                    {
                                        for (x_offset2 = 0; x_offset2 + inaltime_piesa2 - 1 <= 6; x_offset2 += 2)
                                            for (y_offset2 = 0; y_offset2 + lungime_piesa2 - 1 <= 8; y_offset2 += 2)
                                            {
                                                asezare_corecta2 = 1;
                                                copiere_matrice_tarc(matrice_Tarc, matrice_tarc_temporar);
                                                for (int i = 1; i < inaltime_piesa2 + 1; i++)
                                                    for (int j = 1; j < lungime_piesa2 + 1; j++)
                                                    {
                                                        if (matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] == 'g' && matrice_gard_lung[i][j] == 'g')
                                                            matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] = 'X';
                                                        else if (matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] == 'g' && matrice_gard_lung[i][j] == 'q')
                                                            matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] = 'g';
                                                        else if (matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] == 'g' && matrice_gard_lung[i][j] == '#')
                                                            matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] = 'g';
                                                        else if (matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] == '#')
                                                            matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] = matrice_gard_lung[i][j];
                                                    }
                                                for (int i = 0; i < 7; i++)
                                                    for (int j = 0; j < 9; j++)
                                                        if (matrice_tarc_temporar[i][j] == 'X')
                                                            asezare_corecta2 = 0;

                                                if (asezare_corecta2 == 1)
                                                {
                                                    copiere_matrice_tarc(matrice_tarc_temporar, matrice_Tarc);
                                                    copiere_matrice_tarc(matrice_Tarc, stiva_table_de_joc[3]);
                                                    if (verificare_victorie() == 1)
                                                        return 1;
                                                }
                                                else continue;
                                                copiere_matrice_tarc(stiva_table_de_joc[2], matrice_Tarc);

                                            }
                                        roteste(matrice_gard_lung);
                                        intSwap(lungime_piesa2, inaltime_piesa2);
                                        rotiri2++;
                                    }
                                    if (verificare_victorie() == 1)
                                        return 1;
                                }
                                else continue;
                                copiere_matrice_tarc(stiva_table_de_joc[1], matrice_Tarc);

                            }
                        roteste(matrice_gard_scurt);
                        intSwap(lungime_piesa3, inaltime_piesa3);
                        rotiri3++;
                    }
                    if (verificare_victorie() == 1)
                        return 1;
                }
                else continue;
                copiere_matrice_tarc(stiva_table_de_joc[0], matrice_Tarc);

            }
        roteste(matrice_L);
        intSwap(lungime_piesa1, inaltime_piesa1);
        rotiri1++;
    }
    rotiri1 = rotiri2 = rotiri3 = 0;
    x_offset1 = x_offset2 = x_offset3 = 0;
    y_offset1 = y_offset2 = y_offset3 = 0;
    ///prima piesa asezata e cea lunga, apoi se incearca ordinea L->scurta , apoi scurta->L
    while (rotiri2 <= 1)
    {
        for (x_offset2 = 0; x_offset2 + inaltime_piesa2 - 1 <= 6; x_offset2 += 2)
            for (y_offset2 = 0; y_offset2+ lungime_piesa2 - 1 <= 8; y_offset2 += 2)
            {
                asezare_corecta2 = 1;
                copiere_matrice_tarc(matrice_Tarc, matrice_tarc_temporar);
                for (int i = 1; i < inaltime_piesa2 + 1; i++)
                    for (int j = 1; j < lungime_piesa2 + 1; j++)
                    {
                        if (matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] == 'g' && matrice_gard_lung[i][j] == 'g')
                            matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] = 'X';
                        else if (matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] == 'g' && matrice_gard_lung[i][j] == 'q')
                            matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] = 'g';
                        else if (matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] == 'g' && matrice_gard_lung[i][j] == '#')
                            matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] = 'g';
                        else if (matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] == '#')
                            matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] = matrice_gard_lung[i][j];
                    }
                for (int i = 0; i < 7; i++)
                    for (int j = 0; j < 9; j++)
                        if (matrice_tarc_temporar[i][j] == 'X')
                            asezare_corecta2 = 0;
                if (asezare_corecta2 == 1)
                {
                    copiere_matrice_tarc(matrice_tarc_temporar, matrice_Tarc);
                    copiere_matrice_tarc(matrice_Tarc, stiva_table_de_joc[1]);
                    if (verificare_victorie() == 1)
                        return 1;
                    rotiri1 = 0;
                    while (rotiri1 <= 3)
                    {
                        for (x_offset1 = 0; x_offset1 + inaltime_piesa1 - 1 <= 6; x_offset1 += 2)
                            for (y_offset1 = 0; y_offset1 + lungime_piesa1 - 1 <= 8; y_offset1 += 2)
                            {
                                asezare_corecta1 = 1;
                                copiere_matrice_tarc(matrice_Tarc, matrice_tarc_temporar);
                                for (int i = 1; i < inaltime_piesa1 + 1; i++)
                                    for (int j = 1; j < lungime_piesa1 + 1; j++)
                                    {
                                        if (matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] == 'g' && matrice_L[i][j] == 'g')
                                            matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] = 'X';
                                        else if (matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] == 'g' && matrice_L[i][j] == 'q')
                                            matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] = 'g';
                                        else if (matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] == 'g' && matrice_L[i][j] == '#')
                                            matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] = 'g';
                                        else if (matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] == '#')
                                            matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] = matrice_L[i][j];
                                    }
                                for (int i = 0; i < 7; i++)
                                    for (int j = 0; j < 9; j++)
                                        if (matrice_tarc_temporar[i][j] == 'X')
                                            asezare_corecta1 = 0;
                                if (asezare_corecta1 == 1)
                                {
                                    index_tabla_curenta++;
                                    copiere_matrice_tarc(matrice_tarc_temporar, matrice_Tarc);
                                    copiere_matrice_tarc(matrice_Tarc, stiva_table_de_joc[2]);
                                    if (verificare_victorie() == 1)
                                        return 1;
                                    rotiri3 = 0;
                                    while (rotiri3 <= 1)
                                    {
                                        for (x_offset3 = 0; x_offset3 + inaltime_piesa3 - 1 <= 6; x_offset3 += 2)
                                            for (y_offset3 = 0; y_offset3 + lungime_piesa3 - 1 <= 8; y_offset3 += 2)
                                            {
                                                asezare_corecta3 = 1;
                                                copiere_matrice_tarc(matrice_Tarc, matrice_tarc_temporar);
                                                for (int i = 1; i < inaltime_piesa3 + 1; i++)
                                                    for (int j = 1; j < lungime_piesa3 + 1; j++)
                                                    {
                                                        if (matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] == 'g' && matrice_gard_scurt[i][j] == 'g')
                                                            matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] = 'X';
                                                        else if (matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] == 'g' && matrice_gard_scurt[i][j] == 'q')
                                                            matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] = 'g';
                                                        else if (matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] == 'g' && matrice_gard_scurt[i][j] == '#')
                                                            matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] = 'g';
                                                        else if (matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] == '#')
                                                            matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] = matrice_gard_scurt[i][j];
                                                    }
                                                for (int i = 0; i < 7; i++)
                                                    for (int j = 0; j < 9; j++)
                                                        if (matrice_tarc_temporar[i][j] == 'X')
                                                            asezare_corecta3 = 0;

                                                if (asezare_corecta3 == 1)
                                                {
                                                    copiere_matrice_tarc(matrice_tarc_temporar, matrice_Tarc);
                                                    copiere_matrice_tarc(matrice_Tarc, stiva_table_de_joc[3]);
                                                    if (verificare_victorie() == 1)
                                                        return 1;
                                                }
                                                else continue;
                                                copiere_matrice_tarc(stiva_table_de_joc[2], matrice_Tarc);

                                            }
                                        roteste(matrice_gard_scurt);
                                        intSwap(lungime_piesa3, inaltime_piesa3);
                                        rotiri3++;
                                    }
                                    if (verificare_victorie() == 1)
                                        return 1;
                                }
                                else continue;
                                copiere_matrice_tarc(stiva_table_de_joc[1], matrice_Tarc);

                            }
                        roteste(matrice_L);
                        intSwap(lungime_piesa1, inaltime_piesa1);
                        rotiri1++;
                    }
                    rotiri3 = 0;
                    while (rotiri3 <= 1)
                    {
                        for (x_offset3 = 0; x_offset3 + inaltime_piesa3 - 1 <= 6; x_offset3 += 2)
                            for (y_offset3 = 0; y_offset3 + lungime_piesa3 - 1 <= 8; y_offset3 += 2)
                            {
                                asezare_corecta3 = 1;
                                copiere_matrice_tarc(matrice_Tarc, matrice_tarc_temporar);
                                for (int i = 1; i < inaltime_piesa3 + 1; i++)
                                    for (int j = 1; j < lungime_piesa3 + 1; j++)
                                    {
                                        if (matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] == 'g' && matrice_gard_scurt[i][j] == 'g')
                                            matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] = 'X';
                                        else if (matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] == 'g' && matrice_gard_scurt[i][j] == 'q')
                                            matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] = 'g';
                                        else if (matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] == 'g' && matrice_gard_scurt[i][j] == '#')
                                            matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] = 'g';
                                        else if (matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] == '#')
                                            matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] = matrice_gard_scurt[i][j];
                                    }
                                for (int i = 0; i < 7; i++)
                                    for (int j = 0; j < 9; j++)
                                        if (matrice_tarc_temporar[i][j] == 'X')
                                            asezare_corecta3 = 0;
                                if (asezare_corecta3 == 1)
                                {
                                    index_tabla_curenta++;
                                    copiere_matrice_tarc(matrice_tarc_temporar, matrice_Tarc);
                                    copiere_matrice_tarc(matrice_Tarc, stiva_table_de_joc[2]);
                                    if (verificare_victorie() == 1)
                                        return 1;
                                    rotiri1 = 0;
                                    while (rotiri1 <= 3)
                                    {
                                        for (x_offset1 = 0; x_offset1 + inaltime_piesa1 - 1 <= 6; x_offset1 += 2)
                                            for (y_offset1 = 0; y_offset1 + lungime_piesa1 - 1 <= 8; y_offset1 += 2)
                                            {
                                                asezare_corecta1 = 1;
                                                copiere_matrice_tarc(matrice_Tarc, matrice_tarc_temporar);
                                                for (int i = 1; i < inaltime_piesa1 + 1; i++)
                                                    for (int j = 1; j < lungime_piesa1 + 1; j++)
                                                    {
                                                        if (matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] == 'g' && matrice_L[i][j] == 'g')
                                                            matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] = 'X';
                                                        else if (matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] == 'g' && matrice_L[i][j] == 'q')
                                                            matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] = 'g';
                                                        else if (matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] == 'g' && matrice_L[i][j] == '#')
                                                            matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] = 'g';
                                                        else if (matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] == '#')
                                                            matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] = matrice_L[i][j];
                                                    }
                                                for (int i = 0; i < 7; i++)
                                                    for (int j = 0; j < 9; j++)
                                                        if (matrice_tarc_temporar[i][j] == 'X')
                                                            asezare_corecta1 = 0;

                                                if (asezare_corecta1 == 1)
                                                {
                                                    copiere_matrice_tarc(matrice_tarc_temporar, matrice_Tarc);
                                                    copiere_matrice_tarc(matrice_Tarc, stiva_table_de_joc[3]);
                                                    if (verificare_victorie() == 1)
                                                        return 1;
                                                }
                                                else continue;
                                                copiere_matrice_tarc(stiva_table_de_joc[2], matrice_Tarc);

                                            }
                                        roteste(matrice_L);
                                        intSwap(lungime_piesa1, inaltime_piesa1);
                                        rotiri1++;
                                    }
                                    if (verificare_victorie() == 1)
                                        return 1;
                                }
                                else continue;
                                copiere_matrice_tarc(stiva_table_de_joc[1], matrice_Tarc);

                            }
                        roteste(matrice_gard_scurt);
                        intSwap(lungime_piesa3, inaltime_piesa3);
                        rotiri3++;
                    }
                    if (verificare_victorie() == 1)
                        return 1;
                }
                else continue;
                copiere_matrice_tarc(stiva_table_de_joc[0], matrice_Tarc);

            }
        roteste(matrice_gard_lung);
        intSwap(lungime_piesa2, inaltime_piesa2);
        rotiri2++;
    }
    rotiri1 = rotiri2 = rotiri3 = 0;
    x_offset1 = x_offset2 = x_offset3 = 0;
    y_offset1 = y_offset2 = y_offset3 = 0;
    ///prima piesa asezata e cea scurta, apoi se incearca ordinea L->lunga , apoi lunga->L
    while (rotiri3 <= 3)
    {
        for (x_offset3 = 0; x_offset3 + inaltime_piesa3 - 1 <= 6; x_offset3 += 2)
            for (y_offset3 = 0; y_offset3 + lungime_piesa3 - 1 <= 8; y_offset3 += 2)
            {
                asezare_corecta3 = 1;
                copiere_matrice_tarc(matrice_Tarc, matrice_tarc_temporar);
                for (int i = 1; i < inaltime_piesa3 + 1; i++)
                    for (int j = 1; j < lungime_piesa3 + 1; j++)
                    {
                        if (matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] == 'g' && matrice_gard_scurt[i][j] == 'g')
                            matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] = 'X';
                        else if (matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] == 'g' && matrice_gard_scurt[i][j] == 'q')
                            matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] = 'g';
                        else if (matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] == 'g' && matrice_gard_scurt[i][j] == '#')
                            matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] = 'g';
                        else if (matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] == '#')
                            matrice_tarc_temporar[i + x_offset3 - 1][j + y_offset3 - 1] = matrice_gard_scurt[i][j];
                    }
                for (int i = 0; i < 7; i++)
                    for (int j = 0; j < 9; j++)
                        if (matrice_tarc_temporar[i][j] == 'X')
                            asezare_corecta3 = 0;
                if (asezare_corecta3 == 1)
                {
                    copiere_matrice_tarc(matrice_tarc_temporar, matrice_Tarc);
                    copiere_matrice_tarc(matrice_Tarc, stiva_table_de_joc[1]);
                    if (verificare_victorie() == 1)
                        return 1;
                    rotiri1 = 0;
                    while (rotiri1 <= 3)
                    {
                        for (x_offset1 = 0; x_offset1 + inaltime_piesa1 - 1 <= 6; x_offset1 += 2)
                            for (y_offset1 = 0; y_offset1 + lungime_piesa1 - 1 <= 8; y_offset1 += 2)
                            {
                                asezare_corecta1 = 1;
                                copiere_matrice_tarc(matrice_Tarc, matrice_tarc_temporar);
                                for (int i = 1; i < inaltime_piesa1 + 1; i++)
                                    for (int j = 1; j < lungime_piesa1 + 1; j++)
                                    {
                                        if (matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] == 'g' && matrice_L[i][j] == 'g')
                                            matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] = 'X';
                                        else if (matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] == 'g' && matrice_L[i][j] == 'q')
                                            matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] = 'g';
                                        else if (matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] == 'g' && matrice_L[i][j] == '#')
                                            matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] = 'g';
                                        else if (matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] == '#')
                                            matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] = matrice_L[i][j];
                                    }
                                for (int i = 0; i < 7; i++)
                                    for (int j = 0; j < 9; j++)
                                        if (matrice_tarc_temporar[i][j] == 'X')
                                            asezare_corecta1 = 0;
                                if (asezare_corecta1 == 1)
                                {
                                    index_tabla_curenta++;
                                    copiere_matrice_tarc(matrice_tarc_temporar, matrice_Tarc);
                                    copiere_matrice_tarc(matrice_Tarc, stiva_table_de_joc[2]);
                                    if (verificare_victorie() == 1)
                                        return 1;
                                    rotiri2 = 0;
                                    while (rotiri2 <= 1)
                                    {
                                        for (x_offset2 = 0; x_offset2 + inaltime_piesa2 - 1 <= 6; x_offset2 += 2)
                                            for (y_offset2 = 0; y_offset2 + lungime_piesa2 - 1 <= 8; y_offset2 += 2)
                                            {
                                                asezare_corecta2 = 1;
                                                copiere_matrice_tarc(matrice_Tarc, matrice_tarc_temporar);
                                                for (int i = 1; i < inaltime_piesa2 + 1; i++)
                                                    for (int j = 1; j < lungime_piesa2 + 1; j++)
                                                    {
                                                        if (matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] == 'g' && matrice_gard_lung[i][j] == 'g')
                                                            matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] = 'X';
                                                        else if (matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] == 'g' && matrice_gard_lung[i][j] == 'q')
                                                            matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] = 'g';
                                                        else if (matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] == 'g' && matrice_gard_lung[i][j] == '#')
                                                            matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] = 'g';
                                                        else if (matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] == '#')
                                                            matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] = matrice_gard_lung[i][j];
                                                    }
                                                for (int i = 0; i < 7; i++)
                                                    for (int j = 0; j < 9; j++)
                                                        if (matrice_tarc_temporar[i][j] == 'X')
                                                            asezare_corecta2 = 0;

                                                if (asezare_corecta2 == 1)
                                                {
                                                    copiere_matrice_tarc(matrice_tarc_temporar, matrice_Tarc);
                                                    copiere_matrice_tarc(matrice_Tarc, stiva_table_de_joc[3]);
                                                    if (verificare_victorie() == 1)
                                                        return 1;
                                                }
                                                else continue;
                                                copiere_matrice_tarc(stiva_table_de_joc[2], matrice_Tarc);

                                            }
                                        roteste(matrice_gard_lung);
                                        intSwap(lungime_piesa2, inaltime_piesa2);
                                        rotiri2++;
                                    }
                                    if (verificare_victorie() == 1)
                                        return 1;
                                }
                                else continue;
                                copiere_matrice_tarc(stiva_table_de_joc[1], matrice_Tarc);

                            }
                        roteste(matrice_L);
                        intSwap(lungime_piesa1, inaltime_piesa1);
                        rotiri1++;
                    }
                    rotiri2 = 0;
                    while (rotiri2 <= 1)
                    {
                        for (x_offset2 = 0; x_offset2 + inaltime_piesa2 - 1 <= 6; x_offset2 += 2)
                            for (y_offset2 = 0; y_offset2 + lungime_piesa2 - 1 <= 8; y_offset2 += 2)
                            {
                                asezare_corecta2 = 1;
                                copiere_matrice_tarc(matrice_Tarc, matrice_tarc_temporar);
                                for (int i = 1; i < inaltime_piesa2 + 1; i++)
                                    for (int j = 1; j < lungime_piesa2 + 1; j++)
                                    {
                                        if (matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] == 'g' && matrice_gard_lung[i][j] == 'g')
                                            matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] = 'X';
                                        else if (matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] == 'g' && matrice_gard_lung[i][j] == 'q')
                                            matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] = 'g';
                                        else if (matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] == 'g' && matrice_gard_lung[i][j] == '#')
                                            matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] = 'g';
                                        else if (matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] == '#')
                                            matrice_tarc_temporar[i + x_offset2 - 1][j + y_offset2 - 1] = matrice_gard_lung[i][j];
                                    }
                                for (int i = 0; i < 7; i++)
                                    for (int j = 0; j < 9; j++)
                                        if (matrice_tarc_temporar[i][j] == 'X')
                                            asezare_corecta2 = 0;
                                if (asezare_corecta2 == 1)
                                {
                                    index_tabla_curenta++;
                                    copiere_matrice_tarc(matrice_tarc_temporar, matrice_Tarc);
                                    copiere_matrice_tarc(matrice_Tarc, stiva_table_de_joc[2]);
                                    if (verificare_victorie() == 1)
                                        return 1;
                                    rotiri1 = 0;
                                    while (rotiri1 <= 3)
                                    {
                                        for (x_offset1 = 0; x_offset1 + inaltime_piesa1 - 1 <= 6; x_offset1 += 2)
                                            for (y_offset1 = 0; y_offset1 + lungime_piesa1 - 1 <= 8; y_offset1 += 2)
                                            {
                                                asezare_corecta1 = 1;
                                                copiere_matrice_tarc(matrice_Tarc, matrice_tarc_temporar);
                                                for (int i = 1; i < inaltime_piesa1 + 1; i++)
                                                    for (int j = 1; j < lungime_piesa1 + 1; j++)
                                                    {
                                                        if (matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] == 'g' && matrice_L[i][j] == 'g')
                                                            matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] = 'X';
                                                        else if (matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] == 'g' && matrice_L[i][j] == 'q')
                                                            matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] = 'g';
                                                        else if (matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] == 'g' && matrice_L[i][j] == '#')
                                                            matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] = 'g';
                                                        else if (matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] == '#')
                                                            matrice_tarc_temporar[i + x_offset1 - 1][j + y_offset1 - 1] = matrice_L[i][j];
                                                    }
                                                for (int i = 0; i < 7; i++)
                                                    for (int j = 0; j < 9; j++)
                                                        if (matrice_tarc_temporar[i][j] == 'X')
                                                            asezare_corecta1 = 0;

                                                if (asezare_corecta1 == 1)
                                                {
                                                    copiere_matrice_tarc(matrice_tarc_temporar, matrice_Tarc);
                                                    copiere_matrice_tarc(matrice_Tarc, stiva_table_de_joc[3]);
                                                    if (verificare_victorie() == 1)
                                                        return 1;
                                                }
                                                else continue;
                                                copiere_matrice_tarc(stiva_table_de_joc[2], matrice_Tarc);

                                            }
                                        roteste(matrice_L);
                                        intSwap(lungime_piesa1, inaltime_piesa1);
                                        rotiri1++;
                                    }
                                    if (verificare_victorie() == 1)
                                        return 1;
                                }
                                else continue;
                                copiere_matrice_tarc(stiva_table_de_joc[1], matrice_Tarc);

                            }
                        roteste(matrice_gard_lung);
                        intSwap(lungime_piesa2, inaltime_piesa2);
                        rotiri2++;
                    }
                    if (verificare_victorie() == 1)
                        return 1;
                }
                else continue;
                copiere_matrice_tarc(stiva_table_de_joc[0], matrice_Tarc);

            }
        roteste(matrice_gard_scurt);
        intSwap(lungime_piesa3, inaltime_piesa3);
        rotiri3++;
    }
    return 0;
}