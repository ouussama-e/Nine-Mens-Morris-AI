#ifndef regles_H
#define regles_H

int placemnt_legal_premiere_phase(int Table[24], int joueurActuel, int deplacer);
int port_legal(int Table[24], int joueurActuel, int position);
void deplacemnt_legal_deuxieme_phase(int Table[24], int position, int niz[4]);

#endif // regles_H
