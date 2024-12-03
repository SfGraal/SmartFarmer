#include <iostream>
#pragma warning(disable : 4996)

using namespace std;

/*
LEGENDA
c-cai
o-oi
p-porci
v-vaci
g-gard
q-colt/capat gard
#-spatiu gol
a-troaca

nivel1+nivel2:dificultate start
nivel3+nivel4:dificultate junior
nivel5:dificultate master

======
CONDITII GARD
g intalneste g = not ok
orice alta combinatie = ok
======
*/
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

int main()
{
    char tarc[7][9];
    bool playing;
    initializare_Nivel(tarc);
    initializare_matrice_piese();
    cout << endl;
    for (int nr = 0; nr < 5; nr++)
    {
        roteste(matrice_L);
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 7; j++)
                cout << matrice_L[i][j] << " ";
            cout << endl;
        }
        cout << endl;
    }
    for (int nr = 0; nr < 5; nr++)
    {
        roteste(matrice_gard_lung);
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 7; j++)
                cout << matrice_gard_lung[i][j] << " ";
            cout << endl;
        }
        cout << endl;
    }
    for (int nr = 0; nr < 5; nr++)
    {
        roteste(matrice_gard_scurt);
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 7; j++)
                cout << matrice_gard_scurt[i][j] << " ";
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}
