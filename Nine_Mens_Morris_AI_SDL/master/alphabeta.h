#ifndef ALPHABETA_H
#define ALPHABETA_H

int max(int Table[24], int alpha, int beta, int deplacer[3], int Dernier_retour_positif,
        int Dernier_deploreur_negatif, int profondeur, int nbr_epuiseurs, int coef[19]);
int min(int Table[24], int alpha, int beta, int Dernier_retour_positif,
        int Dernier_deploreur_negatif, int profondeur, int nbr_epuiseurs, int coef[19]);
void alphabeta(int Table[24], int deplacer[3], int profondeur, int nbr_epuiseurs, int coef[19]);

#endif // ALPHABETA_H
