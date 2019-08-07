#include "pravila.h"
#include "heuristike.h"


// vérifie si le joueur a joué un jeu qui déplore légalement dans la première phase du jeu
// placemnt_legal_premiere_phase retourne 101 si non legale déplacer
// renvoie 1 si vous avez fabriqué une épée et que vous avez maintenant l'autre partie du déploreur dans laquelle vous vous trouvez
// retourne 0 si vous n'aviez qu'un seul déployeur et qu'il va bien

int placemnt_legal_premiere_phase(int Table[24], int joueurActuel, int deplacer)  {
    if (deplacer < 0 || deplacer > 23 || Table[deplacer] != 0)
        return 101;
    else
        return moulin_ferme_phase_UN(Table, joueurActuel, deplacer);
}



// il doit recevoir un déplaceur (c.-à-d. une position) sur lequel se trouve réellement la figure de l'adversaire
// retourne 0 si ce chiffre peut être pris, il retourne 1 sinon
int port_legal(int Table[24], int joueurActuel, int position) {
  int nombre;
  int indicateur = 0;

  for (nombre = 0; nombre < 24; nombre++)
    if(Table[nombre] == -joueurActuel && isTrio(Table, nombre)) {
      indicateur = 1;
      break;
    }

  if (indicateur == 1 && isTrio(Table, position))
    return 1;

  return 0;
   /*
   cela signifie que s'il n'y en a pas chez les souris, et que celui que vous voulez être le Jour du siècle chez les souris ne peut pas
   si vous voulez la petite chose dans la souris, vous pouvez la porter
   si l'indice est resté à 0, si toutes les figures de l'adversaire sont dans les souris, vous pouvez le porter même s'il est dans la souris
   */
}

/*
 * pour chaque position possible, il revient avec les décélérateurs sur lesquels il peut être joué
 * jusqu'à ce qu'il atteigne -101. il devrait être envoyé à une série de décodeurs int [4] = {-101, -101, -101, -101}
 * -101 est que je ne voudrais pas mélanger avec -1 en tant que joueur négatif dans cette position
 */

void deplacemnt_legal_deuxieme_phase(int Table[24], int position, int deplaceri[4]) {
    switch (position) {
        case 0:
            if (Table[1] == 0)
                deplaceri[0] = 1;
            if (Table[9] == 0)
                deplaceri[1] = 9;
        break;

        case 1:
            if (Table[0] == 0)
                deplaceri[0] = 0;
            if (Table[4] == 0)
                deplaceri[1] = 4;
            if (Table[2] == 0)
                deplaceri[2] = 2;
        break;

        case 2:
            if (Table[1] == 0)
                deplaceri[0] = 1;
            if (Table[14] == 0)
                deplaceri[1] = 14;
        break;

        case 3:
            if (Table[10] == 0)
                deplaceri[0] = 10;
            if (Table[4] == 0)
                deplaceri[1] = 4;
        break;

        case 4:
            if (Table[1] == 0)
                deplaceri[0] = 1;
            if (Table[3] == 0)
                deplaceri[1] = 3;
            if (Table[7] == 0)
                deplaceri[2] = 7;
            if (Table[5] == 0)
                deplaceri[3] = 5;
        break;

        case 5:
            if (Table[4] == 0)
                deplaceri[0] = 4;
            if (Table[13] == 0)
                deplaceri[1] = 13;
        break;

        case 6:
            if (Table[11] == 0)
                deplaceri[0] = 11;
            if (Table[7] == 0)
                deplaceri[1] = 7;
        break;

        case 7:
            if (Table[6] == 0)
                deplaceri[0] = 6;
            if (Table[4] == 0)
                deplaceri[1] = 4;
            if (Table[8] == 0)
                deplaceri[2] = 8;
        break;

        case 8:
            if (Table[7] == 0)
                deplaceri[0] = 7;
            if (Table[12] == 0)
                deplaceri[1] = 12;
        break;

        case 9:
            if (Table[0] == 0)
                deplaceri[0] = 0;
            if (Table[10] == 0)
                deplaceri[1] = 10;
            if (Table[21] == 0)
                deplaceri[2] = 21;
        break;

        case 10:
            if (Table[9] == 0)
                deplaceri[0] = 9;
            if (Table[3] == 0)
                deplaceri[1] = 3;
            if (Table[18] == 0)
                deplaceri[2] = 18;
            if (Table[11] == 0)
                deplaceri[3] = 11;
        break;

        case 11:
            if (Table[10] == 0)
                deplaceri[0] = 10;
            if (Table[6] == 0)
                deplaceri[1] = 6;
            if (Table[15] == 0)
                deplaceri[2] = 15;
        break;

        case 12:
            if (Table[8] == 0)
                deplaceri[0] = 8;
            if (Table[17] == 0)
                deplaceri[1] = 17;
            if (Table[13] == 0)
                deplaceri[2] = 13;
        break;


        case 13:
            if (Table[12] == 0)
                deplaceri[0] = 12;
            if (Table[5] == 0)
                deplaceri[1] = 5;
            if (Table[20] == 0)
                deplaceri[2] = 20;
            if (Table[14] == 0)
                deplaceri[3] = 14;
        break;


        case 14:
            if (Table[13] == 0)
                deplaceri[0] = 13;
            if (Table[2] == 0)
                deplaceri[1] = 2;
            if (Table[23] == 0)
                deplaceri[2] = 23;
        break;


        case 15:
            if (Table[11] == 0)
                deplaceri[0] = 11;
            if (Table[16] == 0)
                deplaceri[1] = 16;
        break;


        case 16:
            if (Table[15] == 0)
                deplaceri[0] = 15;
            if (Table[19] == 0)
                deplaceri[1] = 19;
            if (Table[17] == 0)
                deplaceri[2] = 17;
        break;


        case 17:
            if (Table[16] == 0)
                deplaceri[0] = 16;
            if (Table[12] == 0)
                deplaceri[1] = 12;
        break;


        case 18:
            if (Table[10] == 0)
                deplaceri[0] = 10;
            if (Table[19] == 0)
                deplaceri[1] = 19;
        break;


        case 19:
            if (Table[18] == 0)
                deplaceri[0] = 18;
            if (Table[16] == 0)
                deplaceri[1] = 16;
            if (Table[20] == 0)
                deplaceri[2] = 20;
            if (Table[22] == 0)
                deplaceri[3] = 22;
        break;


        case 20:
            if (Table[19] == 0)
                deplaceri[0] = 19;
            if (Table[13] == 0)
                deplaceri[1] = 13;
        break;


        case 21:
            if (Table[9] == 0)
                deplaceri[0] = 9;
            if (Table[22] == 0)
                deplaceri[1] = 22;
        break;


        case 22:
            if (Table[21] == 0)
                deplaceri[0] = 21;
            if (Table[19] == 0)
                deplaceri[1] = 19;
            if (Table[23] == 0)
                deplaceri[2] = 23;
        break;


        case 23:
            if (Table[22] == 0)
                deplaceri[0] = 22;
            if (Table[14] == 0)
                deplaceri[1] = 14;
        break;
    }
};
