#ifndef HEURISTIKE_H
#define HEURISTIKE_H

int isTrio(int Table[24], int deplacer);
int moulin_ferme_phase_UN(int Table[24], int joueurActuel, int deplacer);
int moulin_ferme_phase_UnETDeux(int Table[24], int joueurActuel, int deplacer[3]);
int zatvaraMicuDeuxiemePhase(int Table[24], int position);
int figure_bloque(int Table[24], int position);
void nbrBlockee(int Table[24], int resultat[4]);
void nbrPierre(int Table[24], int resultat[2]);
void deplacemnt_sourie_ouverte(int Table[24], int resultat[3]);
int nbr_fig_U_premiere_phase(int Table[24]);
int _figure(int Table[24], int position);
void N__figures(int Table[24], int resultat[2]);
int libres_autour_position(int Table[24], int position);
int liberer(int Table[24]);


#endif // HEURISTIKE_H
