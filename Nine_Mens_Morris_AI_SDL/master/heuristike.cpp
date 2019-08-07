#include "heuristike.h"


/*
vérifie si le chiffre dans cette position est dans la souris
renvoie 1 si oui, 0 sinon
*/
int isTrio(int Table[24], int deplacer) {
  switch (deplacer) {
    case 0:
      if ((Table[0] == Table[1] && Table[0] == Table[2]) || (Table[0] == Table[9] && Table[0] == Table[21]))
        return 1;
      else
        return 0;

    case 1:
      if ((Table[1] == Table[0] && Table[1] == Table[2]) || (Table[1] == Table[4] && Table[1] == Table[7]))
        return 1;
      else
        return 0;

    case 2:
      if ((Table[2] == Table[1] && Table[2] == Table[0]) || (Table[2] == Table[14] && Table[2] == Table[23]))
        return 1;
      else
        return 0;

    case 3:
      if ((Table[3] == Table[4] && Table[3] == Table[5]) || (Table[3] == Table[10] && Table[3] == Table[18]))
        return 1;
      else
        return 0;

    case 4:
      if ((Table[4] == Table[1] && Table[4] == Table[7]) || (Table[4] == Table[3] && Table[4] == Table[5]))
        return 1;
      else
        return 0;

    case 5:
      if ((Table[5] == Table[3] && Table[5] == Table[4]) || (Table[5] == Table[13] && Table[13] == Table[20]))
        return 1;
      else
        return 0;

    case 6:
      if ((Table[6] == Table[7] && Table[6] == Table[8]) || (Table[6] == Table[11] && Table[6] == Table[15]))
        return 1;
      else
        return 0;

    case 7:
      if ((Table[7] == Table[6] && Table[7] == Table[8]) || (Table[7] == Table[4] && Table[7] == Table[1]))
        return 1;
      else
        return 0;

    case 8:
      if ((Table[8] == Table[7] && Table[8] == Table[6]) || (Table[8] == Table[12] && Table[8] == Table[17]))
        return 1;
      else
        return 0;

    case 9:
      if ((Table[9] == Table[10] && Table[9] == Table[11]) || (Table[9] == Table[0] && Table[9] == Table[21]))
        return 1;
      else
        return 0;

    case 10:
      if ((Table[10] == Table[9] && Table[10] == Table[11]) || (Table[10] == Table[3] && Table[10] == Table[18]))
        return 1;
      else
        return 0;

    case 11:
      if ((Table[11] == Table[10] && Table[11] == Table[9]) || (Table[11] == Table[6] && Table[11] == Table[15]))
        return 1;
      else
        return 0;

    case 12:
      if ((Table[12] == Table[13] && Table[12] == Table[14]) || (Table[12] == Table[8] && Table[12] == Table[17]))
        return 1;
      else
        return 0;

    case 13:
      if ((Table[13] == Table[5] && Table[13] == Table[20]) || (Table[13] == Table[12] && Table[13] == Table[14]))
        return 1;
      else
        return 0;

    case 14:
      if ((Table[14] == Table[2] && Table[14] == Table[23]) || (Table[14] == Table[13] && Table[14] == Table[12]))
        return 1;
      else
        return 0;

    case 15:
      if ((Table[15] == Table[16] && Table[15] == Table[17]) || (Table[15] == Table[11] && Table[15] == Table[6]))
        return 1;
      else
        return 0;

    case 16:
      if ((Table[16] == Table[15] && Table[16] == Table[17]) || (Table[16] == Table[19] && Table[16] == Table[22]))
        return 1;
      else
        return 0;

    case 17:
      if ((Table[17] == Table[16] && Table[17] == Table[15]) || (Table[17] == Table[12] && Table[17] == Table[8]))
        return 1;
      else
        return 0;

    case 18:
      if ((Table[18] == Table[19] && Table[18] == Table[20]) || (Table[18] == Table[10] && Table[18] == Table[3]))
        return 1;
      else
        return 0;

    case 19:
      if ((Table[19] == Table[16] && Table[19] == Table[22]) || (Table[19] == Table[18] && Table[19] == Table[20]))
        return 1;
      else
        return 0;

    case 20:
      if ((Table[20] == Table[13] && Table[20] == Table[5]) || (Table[20] == Table[19] && Table[20] == Table[18]))
        return 1;
      else
        return 0;

    case 21:
      if ((Table[21] == Table[22] && Table[21] == Table[23]) || (Table[21] == Table[9] && Table[21] == Table[0]))
        return 1;
      else
        return 0;

    case 22:
      if ((Table[22] == Table[19] && Table[22] == Table[16]) || (Table[22] == Table[21] && Table[22] == Table[23]))
        return 1;
      else
        return 0;

    case 23:
      if ((Table[23] == Table[21] && Table[23] == Table[22]) || (Table[23] == Table[14] && Table[23] == Table[2]))
        return 1;
      else
        return 0;

    default:
      return 0;
  }
}


// 1 s'il ferme la souris, 0 sinon
// un dépliant légal doit lui être transmis
// il n'aura pas besoin de nous, mais le laissera rester pour chaque cas

int moulin_ferme_phase_UN(int Table[24], int joueurActuel, int deplacer) {
    Table[deplacer] = joueurActuel;
    int retourVal = isTrio(Table, deplacer);
    Table[deplacer] = 0;
    return retourVal;
}


 /*
  * Vérifiez si le joueur épuisé ferme la souris
  * retourne 1 s'il ferme la souris, 0 sinon
  * deplacer [0] jela position avec kojedéplacer la figure, deplacer [1] jela position où nous déplaçons la figure
  * fs doit être envoyé à un dépliant légal
*/
int moulin_ferme_phase_UnETDeux(int Table[24], int joueurActuel, int deplacer[3])
{
    Table[deplacer[0]] = 0;
    Table[deplacer[1]] = joueurActuel;
    int retourVal = isTrio(Table, deplacer[1]);
    Table[deplacer[1]] = 0;
    Table[deplacer[0]] = joueurActuel;
    return retourVal;
}


// retourne 1 s'il ferme la souris, 0 sinon
// cela ne sert pas à vérifier si le jeest juste un mica fermé mais seulement à regarder si une position ferme les souris
// ie. s'il y a un micro ouvert
int zatvaraMicuDeuxiemePhase(int Table[24], int position) {
    switch (position) {
        case 0:
            if ((Table[1] == 0 && Table[4] == Table[0] && Table[7] == Table[0]) ||
                (Table[9] == 0 && Table[10] == Table[0] && Table[11] == Table[0]))
                return 1;
            else
                return 0;

        case 1:
            if ((Table[0] == 0 && Table[9] == Table[1] && Table[21] == Table[1]) ||
                (Table[2] == 0 && Table[14] == Table[1] && Table[23] == Table[1]) ||
                (Table[4] == 0 && Table[3] == Table[1] && Table[5] == Table[1]))
                return 1;
            else
                return 0;

        case 2:
            if ((Table[1] == 0 && Table[4] == Table[2] && Table[7] == Table[2]) ||
                (Table[14] == 0 && Table[13] == Table[2] && Table[12] == Table[2]))
                return 1;
            else
                return 0;

        case 3:
            if ((Table[4] == 0 && Table[1] == Table[3] && Table[7] == Table[3]) ||
                (Table[10] == 0 && Table[9] == Table[3] && Table[11] == Table[3]))
                return 1;
            else
                return 0;

        case 4:
            if ((Table[1] == 0 && Table[0] == Table[4] && Table[2] == Table[4]) ||
                (Table[3] == 0 && Table[10] == Table[4] && Table[18] == Table[4]) ||
                (Table[5] == 0 && Table[13] == Table[4] && Table[20] == Table[4]) ||
                (Table[7] == 0 && Table[6] == Table[4] && Table[8] == Table[4]))
                return 1;
            else
                return 0;

        case 5:
            if ((Table[4] == 0 && Table[1] == Table[5] && Table[7] == Table[5]) ||
                (Table[13] == 0 && Table[12] == Table[5] && Table[14] == Table[5]))
                return 1;
            else
                return 0;

        case 6:
            if ((Table[7] == 0 && Table[4] == Table[6] && Table[1] == Table[6]) ||
                (Table[11] == 0 && Table[10] == Table[6] && Table[9] == Table[6]))
                return 1;
            else
                return 0;

        case 7:
            if ((Table[4] == 0 && Table[3] == Table[7] && Table[5] == Table[7]) ||
                (Table[6] == 0 && Table[11] == Table[7] && Table[15] == Table[7]) ||
                (Table[8] == 0 && Table[12] == Table[7] && Table[17] == Table[7]))
                return 1;
            else
                return 0;

        case 8:
            if ((Table[7] == 0 && Table[4] == Table[8] && Table[1] == Table[8]) ||
                (Table[12] == 0 && Table[13] == Table[8] && Table[14] == Table[8]))
                return 1;
            else
                return 0;

        case 9:
            if ((Table[10] == 0 && Table[18] == Table[9] && Table[3] == Table[9]) ||
                (Table[0] == 0 && Table[1] == Table[9] && Table[2] == Table[9]) ||
                (Table[21] == 0 && Table[22] == Table[9] && Table[23] == Table[9]))
                return 1;
            else
                return 0;

        case 10:
            if ((Table[9] == 0 && Table[0] == Table[10] && Table[21] == Table[10]) ||
                (Table[3] == 0 && Table[4] == Table[10] && Table[5] == Table[10]) ||
                (Table[18] == 0 && Table[19] == Table[10] && Table[20] == Table[10]) ||
                (Table[11] == 0 && Table[15] == Table[10] && Table[6] == Table[10]))
                return 1;
            else
                return 0;

        case 11:
            if ((Table[10] == 0 && Table[3] == Table[11] && Table[18] == Table[11]) ||
                (Table[6] == 0 && Table[7] == Table[11] && Table[8] == Table[11]) ||
                (Table[15] == 0 && Table[16] == Table[11] && Table[17] == Table[11]))
                return 1;
            else
                return 0;

        case 12:
            if ((Table[8] == 0 && Table[7] == Table[12] && Table[6] == Table[12]) ||
                (Table[17] == 0 && Table[16] == Table[12] && Table[15] == Table[12]) ||
                (Table[13] == 0 && Table[5] == Table[12] && Table[20] == Table[12]))
                return 1;
            else
                return 0;

        case 13:
            if ((Table[12] == 0 && Table[17] == Table[13] && Table[8] == Table[13]) ||
                (Table[20] == 0 && Table[19] == Table[13] && Table[18] == Table[13]) ||
                (Table[5] == 0 && Table[4] == Table[13] && Table[3] == Table[13]) ||
                (Table[14] == 0 && Table[2] == Table[13] && Table[23] == Table[13]))
                return 1;
            else
                return 0;

        case 14:
            if ((Table[13] == 0 && Table[5] == Table[14] && Table[20] == Table[14]) ||
                (Table[2] == 0 && Table[1] == Table[14] && Table[0] == Table[14]) ||
                (Table[23] == 0 && Table[22] == Table[14] && Table[21] == Table[14]))
                return 1;
            else
                return 0;

        case 15:
            if ((Table[11] == 0 && Table[10] == Table[15] && Table[9] == Table[15]) ||
                (Table[16] == 0 && Table[19] == Table[15] && Table[22] == Table[15]))
                return 1;
            else
                return 0;

        case 16:
            if ((Table[19] == 0 && Table[18] == Table[16] && Table[20] == Table[16]) ||
                (Table[15] == 0 && Table[11] == Table[16] && Table[6] == Table[16]) ||
                (Table[17] == 0 && Table[12] == Table[16] && Table[8] == Table[16]))
                return 1;
            else
                return 0;

        case 17:
            if ((Table[16] == 0 && Table[19] == Table[17] && Table[22] == Table[17]) ||
                (Table[12] == 0 && Table[13] == Table[17] && Table[14] == Table[17]))
                return 1;
            else
                return 0;

        case 18:
            if ((Table[10] == 0 && Table[9] == Table[18] && Table[11] == Table[18]) ||
                (Table[19] == 0 && Table[16] == Table[18] && Table[22] == Table[18]))
                return 1;
            else
                return 0;

        case 19:
            if ((Table[16] == 0 && Table[17] == Table[19] && Table[15] == Table[19]) ||
                (Table[18] == 0 && Table[10] == Table[19] && Table[3] == Table[19]) ||
                (Table[20] == 0 && Table[13] == Table[19] && Table[5] == Table[19]) ||
                (Table[22] == 0 && Table[21] == Table[19] && Table[23] == Table[19]))
                return 1;
            else
                return 0;

        case 20:
            if ((Table[19] == 0 && Table[22] == Table[20] && Table[16] == Table[20]) ||
                (Table[13] == 0 && Table[12] == Table[20] && Table[14] == Table[20]))
                return 1;
            else
                return 0;

        case 21:
            if ((Table[9] == 0 && Table[10] == Table[21] && Table[11] == Table[21]) ||
                (Table[22] == 0 && Table[19] == Table[21] && Table[16] == Table[21]))
                return 1;
            else
                return 0;

        case 22:
            if ((Table[19] == 0 && Table[18] == Table[22] && Table[20] == Table[22]) ||
                (Table[21] == 0 && Table[9] == Table[22] && Table[0] == Table[22]) ||
                (Table[23] == 0 && Table[14] == Table[22] && Table[2] == Table[22]))
                return 1;
            else
                return 0;

        case 23:
            if ((Table[22] == 0 && Table[19] == Table[23] && Table[16] == Table[23]) ||
                (Table[14] == 0 && Table[13] == Table[23] && Table[12] == Table[23]))
                return 1;
            else
                return 0;
    }
}


// si la route est bloquée, le blocage renvoie 1, si n'est pas bloqué, il renvoie 0
int figure_bloque(int Table[24], int position) {
  switch (position) {
    case 0:
      if (Table[1] != 0 && Table[9] != 0)
        return 1;
      else
        return 0;

    case 1:
      if(Table[0] != 0 && Table[2] != 0 && Table[4] != 0)
        return 1;
      else
        return 0;

    case 2:
      if(Table[1] != 0 && Table[14] != 0)
        return 1;
      else
        return 0;

    case 3:
      if(Table[10] != 0 && Table[4] != 0)
        return 1;
      else
        return 0;

    case 4:
      if(Table[3] != 0 && Table[7] != 0 && Table[5] != 0 && Table[1] != 0)
        return 1;
      else
        return 0;

    case 5:
      if(Table[4] != 0 && Table[13] != 0)
        return 1;
      else
        return 0;

    case 6:
      if(Table[11] != 0 && Table[7] != 0)
        return 1;
      else
        return 0;

    case 7:
      if(Table[6] != 0 && Table[8] != 0 && Table[4] != 0)
        return 1;
      else
        return 0;

    case 8:
      if(Table[7] != 0 && Table[12] != 0)
        return 1;
      else
        return 0;

    case 9:
      if(Table[0] != 0 && Table[21] != 0 && Table[10] != 0)
        return 1;
      else
        return 0;

    case 10:
      if(Table[9] != 0 && Table[11] != 0 && Table[3] != 0 && Table[18] != 0)
        return 1;
      else
        return 0;

    case 11:
      if(Table[10] != 0 && Table[15] != 0 && Table[6] != 0)
        return 1;
      else
        return 0;

    case 12:
      if(Table[8] != 0 && Table[13] != 0 && Table[17] != 0)
        return 1;
      else
        return 0;

    case 13:
      if(Table[12] != 0 && Table[5] != 0 && Table[14] != 0 && Table[20] != 0)
        return 1;
      else
        return 0;

    case 14:
      if(Table[2] != 0 && Table[13] != 0 && Table[23] != 0)
        return 1;
      else
        return 0;

    case 15:
      if(Table[11] != 0 && Table[16] != 0)
        return 1;
      else
        return 0;

    case 16:
      if(Table[15] != 0 && Table[17] != 0 && Table[19] != 0)
        return 1;
      else
        return 0;

    case 17:
      if(Table[16] != 0 && Table[12] != 0)
        return 1;
      else
        return 0;

    case 18:
      if(Table[10] != 0 && Table[19] != 0)
        return 1;
      else
        return 0;

    case 19:
      if(Table[16] != 0 && Table[18] != 0 && Table[22] != 0 && Table[20] != 0)
        return 1;
      else
        return 0;

    case 20:
      if(Table[19] != 0 && Table[13] != 0)
        return 1;
      else
        return 0;

    case 21:
      if(Table[9] != 0 && Table[22] != 0)
        return 1;
      else
        return 0;

    case 22:
      if(Table[19] != 0 && Table[21] != 0 && Table[23] != 0)
        return 1;
      else
        return 0;

    case 23:
      if(Table[22] != 0 && Table[14] != 0)
        return 1;
      else
        return 0;
  }
}


/*Calculer le nombre de chiffres bloqués et le nombre de chiffres pour les deux joueurs
le résultat de l'entrée dans la séquence où la route a transmis forward est en tant qu'argument
*/
void nbrBlockee(int Table[24], int resultat[4]) {
  int nbrPierrePozitivnog = 0;
  int nbrPierreNegativnog = 0;

  int blokiranihPozitivnog = 0;
  int blokiranihNegativnog = 0;

  int i;

  for (i = 0; i < 24; i++)
    if (Table[i] == 1)    // case du joueur
      if (figure_bloque(Table, i)) {
        blokiranihPozitivnog++;
        nbrPierrePozitivnog++;
      }
      else
        nbrPierrePozitivnog++;

    else if (Table[i] == -1) {  // case de la machine
      if (figure_bloque(Table, i)) {
        blokiranihNegativnog++;
        nbrPierreNegativnog++;
      }
      else
        nbrPierreNegativnog++;
    }


  resultat[0] = blokiranihPozitivnog;
  resultat[1] = blokiranihNegativnog;
  resultat[2] = nbrPierrePozitivnog;
  resultat[3] = nbrPierreNegativnog;
}


// compte le nombre de chiffres pour chacun des joueurs, le résultat de l'entrée dans la chaîne [2] qui devient un argument
// en position 0, nombre de joueurs positifs
// en position 1, nombre de joueurs négatifs
// bien que nous comptions le nombre de chiffres bloqués dans la route pour la boucle, nous travaillons également sur le nombre de chiffres
// laisse ce f être suspendu car il pourrait en avoir besoin
void nbrPierre(int Table[24], int resultat[2]) {
  int nbr_pierre_joueur = 0;
  int nbr_pierre_machine = 0;

  int i;

  for (i = 0; i < 24; i++)
    if (Table[i] == 1)
      nbr_pierre_joueur++;
    else if (Table[i] == -1)
      nbr_pierre_machine++;

  resultat[0] = nbr_pierre_joueur;
  resultat[1] = nbr_pierre_machine;
}


/*
F dans le résultat [0] entrez la différence entre le nombre de chiffres dans les premier et deuxième joueurs,
dans resultat [1] l'entrée de la différence dans le nombre de micros ouverts des premier et second joueurs,
dans resultat [2] Entrer la différence entre le nombre de premier et deuxième joueurs
la séquence de résultats int [3] affectée à la piste doit être {0, 0, 0}
*/
void deplacemnt_sourie_ouverte(int Table[24], int resultat[3]) {
    int i;
    int indicateur;

    for (i = 0; i < 24; i++) {
        indicateur = 0;
        if(Table[i] == 1) {
            if (isTrio(Table, i)) {
                resultat[0]++;
                indicateur++;
            }
            if (zatvaraMicuDeuxiemePhase(Table, i)) {
                resultat[1]++;
                indicateur++;
            }
            if (indicateur == 2)
                resultat[2]++;

        }
        else if (Table[i] == -1) {
            if (isTrio(Table, i)) {
                resultat[0]--;
                indicateur++;
            }
            if (zatvaraMicuDeuxiemePhase(Table, i)) {
                resultat[1]--;
                indicateur++;
            }
            if (indicateur == 2)
                resultat[2]--;
        }
    }
}


// function renvoie la différence entre le nombre de chiffres des premier et deuxième joueurs
// ce f n'est utilisé que dans la première étape du jeu est dans lequel on ne voit que le nombre de micros
// alors que le nombre de souris ouvertes ne nous intéresse pas actuellement
// pour l'efficacité dans la deuxième étape du nombre de souris de jeu (c.-à-d. le chiffre chez la souris), souris ouvertes
// et le marqueur est réalisé dans la route pour boucle

int nbr_fig_U_premiere_phase(int Table[24]) {
    int resultat = 0;
    int i;

    for (i = 0; i < 24; i++)
        if (Table[i] == 1 && isTrio(Table, i)) // trio chez joueur en position i
            resultat++;
        else if (Table[i] == -1 && isTrio(Table, i)) // trio chez machine en position i
            resultat--;

    return resultat;
}

/*
Il vérifie si le chiffre est dans la configuration 2 et renvoie 1 si c'est le cas et 0 s'il n'est pas trouvé
si cette figure est dans la configuration 3, alors f est retourné 2
*/
int deux_tri_configuracija(int Table[24], int position) {
  int indicateurTriKonf = 0;

  switch (position) {
    case 0:
      if ((Table[0] == Table[1] && Table[2] == 0) || (Table[0] == Table[2] && Table[1] == 0))
          indicateurTriKonf++;
      if ((Table[0] == Table[9] && Table[21] == 0) || (Table[0] == Table[21] && Table[9] == 0))
          indicateurTriKonf++;
      return indicateurTriKonf;

    case 1:
      if ((Table[1] == Table[4] && Table[7] == 0) || (Table[1] == Table[7] && Table[4] == 0))
          indicateurTriKonf++;
      if ((Table[1] == Table[0] && Table[2] == 0) || (Table[1] == Table[2] && Table[0] == 0))
          indicateurTriKonf++;
      return indicateurTriKonf;

    case 2:
      if ((Table[2] == Table[1] && Table[0] == 0) || (Table[2] == Table[0] && Table[1] == 0))
          indicateurTriKonf++;
      if ((Table[2] == Table[14] && Table[23] == 0) || (Table[2] == Table[23] && Table[14] == 0))
          indicateurTriKonf++;
      return indicateurTriKonf;

    case 3:
      if ((Table[3] == Table[4] && Table[5] == 0) || (Table[3] == Table[5] && Table[4] == 0))
          indicateurTriKonf++;
      if ((Table[3] == Table[10] && Table[18] == 0) || (Table[3] == Table[18] && Table[10] == 0))
          indicateurTriKonf++;
      return indicateurTriKonf;

    case 4:
      if ((Table[4] == Table[1] && Table[7] == 0) || (Table[4] == Table[7] && Table[1] == 0))
          indicateurTriKonf++;
      if ((Table[4] == Table[3] && Table[5] == 0) || (Table[4] == Table[5] && Table[3] == 0))
          indicateurTriKonf++;
      return indicateurTriKonf;

    case 5:
      if ((Table[5] == Table[4] && Table[3] == 0) || (Table[5] == Table[3] && Table[4] == 0))
          indicateurTriKonf++;
      if ((Table[5] == Table[13] && Table[20] == 0) || (Table[5] == Table[20] && Table[13] == 0))
          indicateurTriKonf++;
      return indicateurTriKonf;

    case 6:
      if ((Table[6] == Table[7] && Table[8] == 0) || (Table[6] == Table[8] && Table[7] == 0))
          indicateurTriKonf++;
      if ((Table[6] == Table[11] && Table[15] == 0) || (Table[6] == Table[15] && Table[11] == 0))
          indicateurTriKonf++;
      return indicateurTriKonf;

    case 7:
      if ((Table[7] == Table[6] && Table[8] == 0) || (Table[7] == Table[8] && Table[6] == 0))
          indicateurTriKonf++;
      if ((Table[7] == Table[4] && Table[1] == 0) || (Table[7] == Table[1] && Table[4] == 0))
          indicateurTriKonf++;
      return indicateurTriKonf;

    case 8:
      if ((Table[8] == Table[7] && Table[6] == 0) || (Table[8] == Table[6] && Table[7] == 0))
          indicateurTriKonf++;
      if ((Table[8] == Table[12] && Table[17] == 0) || (Table[8] == Table[17] && Table[12] == 0))
          indicateurTriKonf++;
      return indicateurTriKonf;

    case 9:
      if ((Table[9] == Table[0] && Table[21] == 0) || (Table[9] == Table[21] && Table[0] == 0))
          indicateurTriKonf++;
      if ((Table[9] == Table[10] && Table[11] == 0) || (Table[9] == Table[11] && Table[10] == 0))
          indicateurTriKonf++;
      return indicateurTriKonf;

    case 10:
      if ((Table[10] == Table[9] && Table[11] == 0) || (Table[10] == Table[11] && Table[9] == 0))
          indicateurTriKonf++;
      if ((Table[10] == Table[3] && Table[18] == 0) || (Table[10] == Table[18] && Table[3] == 0))
          indicateurTriKonf++;
      return indicateurTriKonf;

    case 11:
      if ((Table[11] == Table[9] && Table[10] == 0) || (Table[11] == Table[10] && Table[9] == 0))
          indicateurTriKonf++;
      if ((Table[11] == Table[6] && Table[15] == 0) || (Table[11] == Table[15] && Table[6] == 0))
          indicateurTriKonf++;
      return indicateurTriKonf;

    case 12:
      if ((Table[12] == Table[8] && Table[17] == 0) || (Table[12] == Table[17] && Table[8] == 0))
          indicateurTriKonf++;
      if ((Table[12] == Table[13] && Table[14] == 0) || (Table[12] == Table[14] && Table[13] == 0))
          indicateurTriKonf++;
      return indicateurTriKonf;

    case 13:
      if ((Table[13] == Table[12] && Table[14] == 0) || (Table[13] == Table[14] && Table[12] == 0))
          indicateurTriKonf++;
      if ((Table[13] == Table[5] && Table[20] == 0) || (Table[13] == Table[20] && Table[5] == 0))
          indicateurTriKonf++;
      return indicateurTriKonf;

    case 14:
      if ((Table[14] == Table[12] && Table[13] == 0) || (Table[14] == Table[13] && Table[12] == 0))
          indicateurTriKonf++;
      if ((Table[14] == Table[2] && Table[23] == 0) || (Table[14] == Table[23] && Table[2] == 0))
          indicateurTriKonf++;
      return indicateurTriKonf;

    case 15:
      if ((Table[15] == Table[11] && Table[6] == 0) || (Table[15] == Table[6] && Table[11] == 0))
          indicateurTriKonf++;
      if ((Table[15] == Table[16] && Table[17] == 0) || (Table[15] == Table[17] && Table[16] == 0))
          indicateurTriKonf++;
      return indicateurTriKonf;

    case 16:
      if ((Table[16] == Table[15] && Table[17] == 0) || (Table[16] == Table[17] && Table[15] == 0))
          indicateurTriKonf++;
      if ((Table[16] == Table[19] && Table[22] == 0) || (Table[16] == Table[22] && Table[19] == 0))
          indicateurTriKonf++;
      return indicateurTriKonf;

    case 17:
      if ((Table[17] == Table[15] && Table[16] == 0) || (Table[17] == Table[16] && Table[15] == 0))
          indicateurTriKonf++;
      if ((Table[17] == Table[12] && Table[8] == 0) || (Table[17] == Table[8] && Table[12] == 0))
          indicateurTriKonf++;
      return indicateurTriKonf;

    case 18:
      if ((Table[18] == Table[10] && Table[3] == 0) || (Table[18] == Table[3] && Table[10] == 0))
          indicateurTriKonf++;
      if ((Table[18] == Table[19] && Table[20] == 0) || (Table[18] == Table[20] && Table[19] == 0))
          indicateurTriKonf++;
      return indicateurTriKonf;

    case 19:
      if ((Table[19] == Table[18] && Table[20] == 0) || (Table[19] == Table[20] && Table[18] == 0))
          indicateurTriKonf++;
      if ((Table[19] == Table[16] && Table[22] == 0) || (Table[19] == Table[22] && Table[16] == 0))
          indicateurTriKonf++;
      return indicateurTriKonf;

    case 20:
      if ((Table[20] == Table[18] && Table[19] == 0) || (Table[20] == Table[19] && Table[18] == 0))
          indicateurTriKonf++;
      if ((Table[20] == Table[13] && Table[5] == 0) || (Table[20] == Table[5] && Table[13] == 0))
          indicateurTriKonf++;
      return indicateurTriKonf;

    case 21:
      if ((Table[21] == Table[9] && Table[0] == 0) || (Table[21] == Table[0] && Table[9] == 0))
          indicateurTriKonf++;
      if ((Table[21] == Table[22] && Table[23] == 0) || (Table[21] == Table[23] && Table[22] == 0))
          indicateurTriKonf++;
      return indicateurTriKonf;

    case 22:
      if ((Table[22] == Table[21] && Table[23] == 0) || (Table[22] == Table[23] && Table[21] == 0))
          indicateurTriKonf++;
      if ((Table[22] == Table[19] && Table[16] == 0) || (Table[22] == Table[16] && Table[19] == 0))
          indicateurTriKonf++;
      return indicateurTriKonf;

    case 23:
      if ((Table[23] == Table[21] && Table[22] == 0) || (Table[23] == Table[22] && Table[21] == 0))
          indicateurTriKonf++;
      if ((Table[23] == Table[14] && Table[2] == 0) || (Table[23] == Table[2] && Table[14] == 0))
          indicateurTriKonf++;
      return indicateurTriKonf;

  }
}


/*
Le résultat [0] entrera dans la configuration Différence 2 de deux joueurs
Dans le résultat [1], la différence entre 3 joueurs de conférence et 2 joueurs est entrée
Un chiffre à 3 chiffres existe s'il existe une figure appartenant à deux configurations à 2
Par conséquent, ces résultats peuvent être directement multipliés par le coefma dans f-ji evaluaciCest*/

void N__figures(int Table[24], int resultat[2]) {
  int i;

  for (i = 0; i < 24; i++) {
      if (Table[i] == 1) {  // case joueur
          if (deux_tri_configuracija(Table, i) == 1)
              resultat[0]++;
          else if (deux_tri_configuracija(Table, i) == 2) {
              resultat[0]++;
              resultat[1]++;
          }
      }
      else if (Table[i] == -1) { // case machine
          if (deux_tri_configuracija(Table, i) == 1)
              resultat[0]--;
          else if (deux_tri_configuracija(Table, i) == 2) {
              resultat[0]--;
              resultat[1]--;
          }
      }
  }
}


int libres_autour_position(int Table[24], int position) {
    int nombre = 0;

    switch (position) {
        case 0:
            if (Table[1] == 0)
                nombre++;
            if (Table[9] == 0)
                nombre++;
            return nombre;

        case 1:
            if (Table[0] == 0)
                nombre++;
            if (Table[4] == 0)
                nombre++;
            if (Table[2] == 0)
                nombre++;
            return nombre;

        case 2:
            if (Table[1] == 0)
                nombre++;
            if (Table[14] == 0)
                nombre++;
            return nombre;

        case 3:
            if (Table[10] == 0)
                nombre++;
            if (Table[4] == 0)
                nombre++;
            return nombre;

        case 4:
            if (Table[1] == 0)
                nombre++;
            if (Table[3] == 0)
                nombre++;
            if (Table[7] == 0)
                nombre++;
            if (Table[5] == 0)
                nombre++;
            return nombre;

        case 5:
            if (Table[4] == 0)
                nombre++;
            if (Table[13] == 0)
                nombre++;
            return nombre;

        case 6:
            if (Table[7] == 0)
                nombre++;
            if (Table[11] == 0)
                nombre++;
            return nombre;

        case 7:
            if (Table[6] == 0)
                nombre++;
            if (Table[4] == 0)
                nombre++;
            if (Table[8] == 0)
                nombre++;
            return nombre;

        case 8:
            if (Table[7] == 0)
                nombre++;
            if (Table[12] == 0)
                nombre++;
            return nombre;

        case 9:
            if (Table[0] == 0)
                nombre++;
            if (Table[10] == 0)
                nombre++;
            if (Table[21] == 0)
                nombre++;
            return nombre;

        case 10:
            if (Table[3] == 0)
                nombre++;
            if (Table[9] == 0)
                nombre++;
            if (Table[18] == 0)
                nombre++;
            if (Table[11] == 0)
                nombre++;
            return nombre;

        case 11:
            if (Table[6] == 0)
                nombre++;
            if (Table[10] == 0)
                nombre++;
            if (Table[15] == 0)
                nombre++;
            return nombre;

        case 12:
            if (Table[8] == 0)
                nombre++;
            if (Table[13] == 0)
                nombre++;
            if (Table[17] == 0)
                nombre++;
            return nombre;

        case 13:
            if (Table[5] == 0)
                nombre++;
            if (Table[12] == 0)
                nombre++;
            if (Table[20] == 0)
                nombre++;
            if (Table[14] == 0)
                nombre++;
            return nombre;

        case 14:
            if (Table[2] == 0)
                nombre++;
            if (Table[13] == 0)
                nombre++;
            if (Table[23] == 0)
                nombre++;
            return nombre;

        case 15:
            if (Table[11] == 0)
                nombre++;
            if (Table[16] == 0)
                nombre++;
            return nombre;

        case 16:
            if (Table[15] == 0)
                nombre++;
            if (Table[19] == 0)
                nombre++;
            if (Table[17] == 0)
                nombre++;
            return nombre;

        case 17:
            if (Table[16] == 0)
                nombre++;
            if (Table[12] == 0)
                nombre++;
            return nombre;

        case 18:
            if (Table[10] == 0)
                nombre++;
            if (Table[19] == 0)
                nombre++;
            return nombre;

        case 19:
            if (Table[16] == 0)
                nombre++;
            if (Table[18] == 0)
                nombre++;
            if (Table[22] == 0)
                nombre++;
            if (Table[20] == 0)
                nombre++;
            return nombre;

        case 20:
            if (Table[19] == 0)
                nombre++;
            if (Table[13] == 0)
                nombre++;
            return nombre;

        case 21:
            if (Table[9] == 0)
                nombre++;
            if (Table[22] == 0)
                nombre++;
            return nombre;

        case 22:
            if (Table[21] == 0)
                nombre++;
            if (Table[19] == 0)
                nombre++;
            if (Table[23] == 0)
                nombre++;
            return nombre;

        case 23:
            if (Table[22] == 0)
                nombre++;
            if (Table[14] == 0)
                nombre++;
            return nombre;
    }

}
// places libres autour des figures qui peuvent être jouées dans la deuxième phase. Il peut être utilisé immédiatement dans f-ji eval.
int liberer(int Table[24]) {
    int resultat = 0;
    int nombre;

    for (nombre = 0; nombre < 24; nombre++)
          if (Table[nombre] == 1)
            resultat = resultat + libres_autour_position(Table, nombre);
        else if (Table[nombre] == -1)
            resultat = resultat - libres_autour_position(Table, nombre);


    return resultat;
}

