#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LIGNE 50
#define MAX_TAILLE 101

// Tableau dynamique pour stocker les nombres en toutes lettres
char TL[MAX_TAILLE][MAX_LIGNE];
int tailleTL = 0;

// Fonction pour charger les nombres en toutes lettres depuis un fichier
int charger_nombres(const char *nombre)
{
    FILE *fichier = fopen(nombre, "r");
    if (fichier == NULL)
    {
        perror("Erreur : Impossible d'ouvrir le fichier");
        return 0;
    }

    char ligne[MAX_LIGNE];
    while (fgets(ligne, sizeof(ligne), fichier))
    {
        // Supprimer le caractère de nouvelle ligne (\n) s'il existe
        ligne[strcspn(ligne, "\n")] = '\0';
        strcpy(TL[tailleTL], ligne);
        tailleTL++;
        if (tailleTL >= MAX_TAILLE)
        {
            printf("Erreur : Trop de nombres dans le fichier\n");
            fclose(fichier);
            return 0;
        }
    }

    fclose(fichier);
    return 1;
}

// Fonction pour convertir la partie entière d'un nombre reel
void convertir_entier(long long int partieEnt)
{
    if (partieEnt < 0)
    {
        printf("moins ");
        convertir_entier(-partieEnt);
        return;
    }

    if (0 <= partieEnt && partieEnt < 100)
    {
        printf("%s", TL[partieEnt]);
    }
    else if (partieEnt < 1000)
    {
        int cent = partieEnt / 100;
        int reste = partieEnt % 100;

        if (cent == 1)
            printf("cent");
        else if (cent > 1)
            printf("%s cent", TL[cent]);

        if (reste > 0)
        {
            printf(" ");
            convertir_entier(reste);
        }
    }
    else if (partieEnt < 1000000)
    {
        long long int mille = partieEnt / 1000;
        long long int reste = partieEnt % 1000;

        if (mille == 1)
            printf("mille");
        else
        {
            convertir_entier(mille);
            printf(" mille");
        }

        if (reste > 0)
        {
            printf(" ");
            convertir_entier(reste);
        }
    }
    else if (partieEnt < 1000000000)
    {
        long long int millions = partieEnt / 1000000;
        long long int reste = partieEnt % 1000000;

        if (millions == 1)
            printf("un million");
        else
        {
            convertir_entier(millions);
            printf(" millions");
        }

        if (reste > 0)
        {
            printf(" ");
            convertir_entier(reste);
        }
    }
    else if (partieEnt < 1000000000000)
    {
        long long int milliards = partieEnt / 1000000000;
        long long int reste = partieEnt % 1000000000;

        if (milliards == 1)
            printf("un milliard");
        else
        {
            convertir_entier(milliards);
            printf(" milliards");
        }

        if (reste > 0)
        {
            printf(" ");
            convertir_entier(reste);
        }
    }
}

// Fonction pour convertir la partie décimale d'un nombre réel
void convertir_decimale(int partieDec)
{
    if (partieDec > 0)
    {
        printf(" virgule ");
        while (partieDec > 0)
        {
            int chiffre = partieDec / 1000; // Obtenir le chiffre le plus significatif
            printf("%s ", TL[chiffre]);
            partieDec %= 1000; // Recuperer le reste
            partieDec *= 10;   // Decaler pour le chiffre suivant
        }
    }
}

// Fonction principale pour convertir un nombre réel
void convertir_reel(double reel)
{
    long long int partieEnt = (long long int)reel;
    int partieDec = (int)(fabs(reel - partieEnt) * 10000);

    convertir_entier(partieEnt);
    convertir_decimale(partieDec);
}

// Programme principal
int main()
{
    if (!charger_nombres("nombre.txt"))
    {
        return 1; // Arreter le programme si le fichier ne peut pas etre charge
    }

    double reel;
    printf("Entrer un reel entre -999999999999 et 999999999999 : ");
    scanf("%lf", &reel);

    if (reel >= -999999999999 && reel < 1000000000000)
    {
        convertir_reel(reel);
    }
    else
    {
        printf("Le nombre n'est pas dans l'intervalle.");
    }

    return 0;
}
