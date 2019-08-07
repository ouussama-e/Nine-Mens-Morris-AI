#include "heuristike.h"
#include "pravila.h"
#include "alphabeta.h"

#include <iostream>




//semblable à max
int min(int Table[24], int alpha, int beta, int Dernier_retour_positif, int Dernier_deploreur_negatif,
        int profondeur, int nbr_epuiseurs, int coef[19])
{
    int victoire;
    int resultat[4] = {0, 0, 0, 0};
    nbrBlockee(Table, resultat);

    int minimalnavaleur = 32000;
    int valeur = 0;
    int nombre;

    if (resultat[3] == 2 || resultat[3] == resultat[1])
        victoire = 1;
    else
        if (resultat[2] == 2 || resultat[2] == resultat[0])
            victoire = -1;
        else
            victoire = 0;

    if (nbr_epuiseurs < 18) {
        //jos uvek jeprva faza igre

        if (profondeur == 0) {
            //izlaz iz rekurziCest
            int deux_tri_conf[2] = {0, 0};
            N__figures(Table, deux_tri_conf);



            return (coef[0] * (Dernier_deploreur_negatif + Dernier_retour_positif)) + (coef[1] * nbr_fig_U_premiere_phase(Table)) +
                   (coef[2] * (resultat[0] - resultat[1])) + (coef[3] * (resultat[2] - resultat[3])) +
                   (coef[4] * deux_tri_conf[0]) + (coef[5] * deux_tri_conf[1]) + (coef[6] * liberer(Table));
        }

        // nous ne sortons toujours pas de la récursion, mais nous cherchons le meilleur déplaceur pour le négatiffor (nombre = 0; nombre < 24; nombre++) {
         for (nombre = 0; nombre < 24; nombre++) {
            if (Table[nombre] == 0) {
                Table[nombre] = -1; // depuis que nous sommes en min nous savons que le négatif sur déplaceur

                if (isTrio(Table, nombre)) {
                    Dernier_deploreur_negatif = 1;
                    int j;

                    for (j = 0; j < 24; j++) {
                        if (Table[j] == 1 && !port_legal(Table, -1, j)) {
                            Table[j] = 0; // on enlève la figure de l'adversaire
                            valeur = max(Table, alpha, beta, nullptr, Dernier_retour_positif,
                                           Dernier_deploreur_negatif, profondeur - 1, nbr_epuiseurs + 1, coef);
                            Table[j] = 1; // on retourne tel quel après avoir évalué ce déploreur
                            if (valeur < minimalnavaleur)
                                minimalnavaleur = valeur;
                            if (minimalnavaleur <= alpha) {
                                Table[nombre] = 0;
                                return minimalnavaleur;
                            }
                            if(minimalnavaleur < beta)
                                beta = minimalnavaleur;
                        }
                    }

                }
                else {// joué déplaceur n'a pas fait une souris

                    Dernier_deploreur_negatif = 0;
                    valeur = max(Table, alpha, beta, nullptr, Dernier_retour_positif,
                                   Dernier_deploreur_negatif, profondeur - 1, nbr_epuiseurs + 1, coef);
                    if (valeur < minimalnavaleur)
                        minimalnavaleur = valeur;
                    if (minimalnavaleur <= alpha) {
                        Table[nombre] = 0;
                        return minimalnavaleur;
                    }
                if (minimalnavaleur < beta)
                        beta = minimalnavaleur;
                }
            Table[nombre] = 0;
            }
        }
       return minimalnavaleur;
    }

    else {

        if (profondeur == 0 || victoire != 0) {
            if (resultat[2] > 3 && resultat[3] > 3) {
                //evaluacija prema heuristikama za drugu fazu igre
                int brMicaIOtvorenih[3] = {0, 0, 0};
                deplacemnt_sourie_ouverte(Table, brMicaIOtvorenih);

                return (coef[7] * (Dernier_deploreur_negatif + Dernier_retour_positif)) +
                       (coef[8] * brMicaIOtvorenih[0]) + (coef[9] * (resultat[0] - resultat[1])) +
                       (coef[10] * (resultat[2] - resultat[3])) + (coef[11] * brMicaIOtvorenih[1]) +
                       (coef[12] * brMicaIOtvorenih[2]) + (coef[13] * liberer(Table)) + (coef[14] * victoire);
            }
            else {// Evaluation par heuristique pour la troisième phase du jeu
                int deux_tri_conf[2] = {0, 0};
                N__figures(Table, deux_tri_conf);

                return (coef[15] * deux_tri_conf[0]) + (coef[16] * deux_tri_conf[1]) + (coef[17] * (Dernier_deploreur_negatif + Dernier_retour_positif)) +
                       (coef[18] * victoire);
            }


       // ne sort toujours pas de la récursivité mais nous jouons certains des déplacers if (resultat[3] > 3) {
            //negativni ima vise od 3 figure i igra po pravilima druge faze
            for (nombre = 0; nombre < 24; nombre++) {
                if (Table[nombre] == -1) {
                    // nous avons trouvé un chiffre négatif et nous regardons quelle position nous pouvons jouerint deplaceri[4] = {-101, -101, -101, -101};
                    int deplaceri[4] = {-101, -101, -101, -101};
                    deplacemnt_legal_deuxieme_phase(Table, nombre, deplaceri);
                    int j;
                    for (j = 0; j < 4; j++)
                        if (deplaceri[j] != -101) {
                                // on joue avec le compteur sur la masse salariale [j]
                            Table[nombre] = 0;
                            Table[deplaceri[j]] = -1;

                            if (isTrio(Table, deplaceri[j])) {
                                Dernier_deploreur_negatif = 1;
                                int k;
                                for (k = 0; k < 24; k++) {
                                    if (Table[k] == 1 && !port_legal(Table, -1, k)) {
                                        Table[k] = 0;
                                        valeur = max(Table, alpha, beta, nullptr, Dernier_retour_positif,
                                                       Dernier_deploreur_negatif, profondeur - 1, nbr_epuiseurs + 1, coef);
                                        Table[k] = 1; // on retourne tel quel après avoir évalué ce déploreur
                                        if (valeur < minimalnavaleur)
                                            minimalnavaleur = valeur;
                                        if (minimalnavaleur <= alpha) {
                                            Table[deplaceri[j]] = 0;
                                            Table[nombre] = -1;
                                            return minimalnavaleur;
                                        }
                                        if(minimalnavaleur < beta)
                                            beta = minimalnavaleur;
                                    }
                                }
                            }
                            else {// quand on joue avec le compteur sur les gains [j] on ne fabrique pas de souris
                                Dernier_deploreur_negatif = 0;
                                valeur = max(Table, alpha, beta, nullptr, Dernier_retour_positif,
                                               Dernier_deploreur_negatif, profondeur - 1, nbr_epuiseurs + 1, coef);
                                if (valeur < minimalnavaleur)
                                    minimalnavaleur = valeur;
                                if (minimalnavaleur <= alpha) {
                                    Table[deplaceri[j]] = 0;
                                    Table[nombre] = -1;
                                    return minimalnavaleur;
                                }
                                if(minimalnavaleur < beta)
                                    beta = minimalnavaleur;
                            }
                            Table[deplaceri[j]] = 0;
                            Table[nombre] = -1;
                        }
                }
         }
            return minimalnavaleur;
       }

        else {
            // Negative a 3 figures et un jeu selon les règles de la troisième étape
            for (nombre = 0; nombre < 24; nombre++) {
                if (Table[nombre] == -1) {
                    int j;
                    for (j = 0; j < 24; j++) {
                        if (Table[j] == 0) {
                            // on peut sauter en position j car c'est libre
                            Table[nombre] = 0;
                            Table[j] = -1;

                            if (isTrio(Table, j)) {
                                    // on vient de sauter sur le mica en sautant
                                Dernier_deploreur_negatif = 1;
                                int k;
                                for (k = 0; k < 24; k++) {
                                    if (Table[k] == 1 && port_legal(Table, -1, k)) {
                                        Table[k] = 0;
                                        valeur = max(Table, alpha, beta, nullptr, Dernier_retour_positif,
                                                       Dernier_deploreur_negatif, profondeur - 1, nbr_epuiseurs + 1, coef);
                                        Table[k] = 1;
                                        if (valeur < minimalnavaleur)
                                            minimalnavaleur = valeur;
                                        if (minimalnavaleur <= alpha) {
                                            Table[j] = 0;
                                            Table[nombre] = -1;
                                            return minimalnavaleur;
                                        }
                                        if(minimalnavaleur < beta)
                                            beta = minimalnavaleur;
                                    }
                                }
                            }
                            else {
                                // saute à j on ne fabrique pas de souris
                                Dernier_deploreur_negatif = 0;
                                valeur = max(Table, alpha, beta, nullptr, Dernier_retour_positif,
                                               Dernier_deploreur_negatif, profondeur - 1, nbr_epuiseurs + 1, coef);
                                if (valeur < minimalnavaleur)
                                    minimalnavaleur = valeur;
                                if (minimalnavaleur <= alpha) {
                                    Table[j] = 0;
                                    Table[nombre] = -1;
                                    return minimalnavaleur;
                                }
                                if(minimalnavaleur < beta)
                                    beta = minimalnavaleur;
                            }
                            Table[j] = 0;
                            Table[nombre] = -1;
                        }
                    }
                }
            }
            return minimalnavaleur;
        }
    }
}


/*
 * C'est le meilleur déploreur que le moteur devrait jouer à la fin. NextCestmo daljei
 * le dernier (c.-à-d. juste) joué du déplaceur afin d'avoir une vérification pour la fermeture du prochain appel
 * mica. Cette heuristique est ajoutée au test pour s'assurer que le moteur va ouvrir et fermer la souris
 * Peut-on et sans cela, avec de bons coefficients pour le nombre de chiffres, le nombre de balles ouvertes et fermées, ou
 * Nous sommes tellement sûrs qu’il n’arrivera pas de faire un micro et de dire Super jecela et jamais jene pas ouvrir :)
 */
int max(int Table[24], int alpha, int beta, int deplacer[3], int Dernier_retour_positif,
        int Dernier_deploreur_negatif, int profondeur, int nbr_epuiseurs, int coef[19]) {

    if (nbr_epuiseurs == 18 || nbr_epuiseurs == 19)
        profondeur = profondeur + 1;

    if (nbr_epuiseurs == 24 || nbr_epuiseurs == 25)
        profondeur = profondeur + 1;

    int victoire;
    int resultat[4] = {0, 0, 0, 0};
    nbrBlockee(Table, resultat);


    int valeur_maximal = -32000;
    int valeur = 0;
    int nombre;


    if (resultat[3] == 2 || resultat[3] == resultat[1])
        victoire = 1;
    else
        if (resultat[2] == 2 || resultat[2] == resultat[0])
            victoire = -1;
        else
            victoire = 0;


    if (nbr_epuiseurs < 18) {
        // est toujours la première étape du jeu

        if (profondeur == 0) {
            //sortir de recursion
            int deux_tri_conf[2] = {0, 0};
            N__figures(Table, deux_tri_conf);

    return (coef[0] * (Dernier_retour_positif + Dernier_deploreur_negatif)) + (coef[1] * nbr_fig_U_premiere_phase(Table)) +
           (coef[2] * (resultat[0] - resultat[1])) + (coef[3] * (resultat[2] - resultat[3])) +
           (coef[4] * deux_tri_conf[0]) + (coef[5] * deux_tri_conf[1]) + (coef[6] * liberer(Table));
        }

        // si la profondeur reste nerveuse, on ne sort pas du regard récursif
        for (nombre = 0; nombre < 24; nombre++) {
            if (Table[nombre] == 0) {
                Table[nombre] = 1; // nous savons qu'un joueur positif est celui qui tente de maximiser

                if (isTrio(Table, nombre)) {
                    Dernier_retour_positif = 1;
                    //ako jeto sto smo odigrali zatvorilo micu, sada imamo drugi deo deplacera gde
                    //nosimo protivnikovu figuru
                    int j;

                    for (j = 0; j < 24; j++) {
                        if (Table[j] == -1 && !port_legal(Table, 1, j)) {
                            Table[j] = 0; //skidamo protivnikovu figuru
                            valeur = min(Table, alpha, beta, Dernier_retour_positif /* egal à */,
                                           Dernier_deploreur_negatif, profondeur - 1, nbr_epuiseurs + 1, coef);
                            Table[j] = -1; //vracamo kako jebilo posle evaluacijetog deplacera
                            if (valeur > valeur_maximal) {
                                valeur_maximal = valeur;
                                //posto smo nasli bolji deplacer igramo ga
                                if (deplacer) {
                                    deplacer[0] = nombre; //igramo na poziciju nombre
                                    deplacer[2] = j; //nosimo figuru sa pozicijej
                                }
                            }
                            if (valeur_maximal >= beta) {
                                Table[nombre] = 0;
                                return valeur_maximal;
                            }
                            if(valeur_maximal > alpha)
                                alpha = valeur_maximal;
                        }
                    }
                }
                else {
                    //ta posi tion na koju se igra ne pravi micu
                    Dernier_retour_positif = 0;

                    valeur = min(Table, alpha, beta, Dernier_retour_positif,
                                   Dernier_deploreur_negatif, profondeur - 1, nbr_epuiseurs + 1, coef);
                    if (valeur > valeur_maximal) {
                        valeur_maximal = valeur;
                        if (deplacer) {
                            deplacer[0] = nombre;
                            deplacer[2] = -1;
                        }
                    }
                    if (valeur_maximal >= beta) {
                        Table[nombre] = 0;
                        return valeur_maximal;
                    }
                    if (valeur_maximal > alpha)
                        alpha = valeur_maximal;
                }
                Table[nombre] = 0;
            }
            //else nijelegalan deplacer Cestr nijeslobodna position
        }

        return valeur_maximal;
    }
    else {


        if (profondeur == 0 || victoire != 0) {
            if (resultat[2] > 3 && resultat[3] > 3) {
                //
                int brMicaIOtvorenih[3] = {0, 0, 0};
                deplacemnt_sourie_ouverte(Table, brMicaIOtvorenih);

                return (coef[7] * (Dernier_deploreur_negatif + Dernier_retour_positif)) +
                       (coef[8] * brMicaIOtvorenih[0]) + (coef[9] * (resultat[0] - resultat[1])) +
                       (coef[10] * (resultat[2] - resultat[3])) + (coef[11] * brMicaIOtvorenih[1]) +
                       (coef[12] * brMicaIOtvorenih[2]) + (coef[13] * liberer(Table)) + (coef[14] * victoire);
            }
            else {
                //treca faza igre
                int deux_tri_conf[2] = {0, 0};
                N__figures(Table, deux_tri_conf);

                return (coef[15] * deux_tri_conf[0]) + (coef[16] * deux_tri_conf[1]) +
                       (coef[17] * (Dernier_deploreur_negatif + Dernier_retour_positif)) +
                       (coef[18] * victoire);
            }
        }


        //
        if (resultat[2] > 3) {
            //
            for (nombre = 0; nombre < 24; nombre++) {
                if (Table[nombre] == 1) {
                    //
                    int deplaceri[4] = {-101, -101, -101, -101};
                    deplacemnt_legal_deuxieme_phase(Table, nombre, deplaceri);
                    int j;
                    for (j = 0; j < 4; j++)
                        if (deplaceri[j] != -101) {
                            //
                            Table[nombre] = 0;
                            Table[deplaceri[j]] = 1;

                            if (isTrio(Table, deplaceri[j])) {
                                Dernier_retour_positif = 1;
                                int k;
                                for (k = 0; k < 24; k++) {
                                    if (Table[k] == -1 && !port_legal(Table, 1, k)) {
                                        Table[k] = 0;
                                        valeur =  min(Table, alpha, beta, Dernier_retour_positif,
                                                        Dernier_deploreur_negatif, profondeur - 1, nbr_epuiseurs + 1, coef);
                                        Table[k] = -1;
                                        if (valeur > valeur_maximal) {
                                            valeur_maximal = valeur;
                                            if (deplacer) {
                                                deplacer[0] = nombre;
                                                deplacer[1] = deplaceri[j];
                                                deplacer[2] = k;
                                            }
                                        }
                                        if (valeur_maximal >= beta) {
                                            Table[deplaceri[j]] = 0;
                                            Table[nombre] = 1;
                                            return valeur_maximal;
                                        }
                                        if (valeur_maximal > alpha)
                                            alpha = valeur_maximal;
                                    }
                                }
                            }
                            else {
                                //
                                Dernier_retour_positif = 0;

                                valeur =  min(Table, alpha, beta, Dernier_retour_positif,
                                                Dernier_deploreur_negatif, profondeur - 1, nbr_epuiseurs + 1, coef);
                                if (valeur > valeur_maximal) {
                                    valeur_maximal = valeur;
                                    if (deplacer) {
                                        deplacer[0] = nombre;
                                        deplacer[1] = deplaceri[j];
                                        deplacer[2] = -1;
                                    }
                                }
                                if (valeur_maximal >= beta) {
                                    Table[deplaceri[j]] = 0;
                                    Table[nombre] = 1;
                                    return valeur_maximal;
                                }
                                if (valeur_maximal > alpha)
                                    alpha = valeur_maximal;
                            }
                            Table[deplaceri[j]] = 0;
                            Table[nombre] = 1;
                        }
                }
                // sinon ce n'est pas un débogueur légal
            }
            // nous avons exécuté tous les déplaceurs possibles et maintenant nous renvoyons la valeur
            return valeur_maximal;
        }
        else {
            // positif a 3 chiffres et le jeu selon les règles de la troisième étape
            for (nombre = 0; nombre < 24; nombre++) {
                if (Table[nombre] == 1) {
                    int j;
                    for (j = 0; j < 24; j++) {
                        if (Table[j] == 0) {
                            // on peut sauter à cette position
                            Table[nombre] = 0;
                            Table[j] = 1;

                            if (isTrio(Table, j)) {
                                Dernier_retour_positif = 1;
                                int k;
                                for (k = 0; k < 24; k++) {
                                    if (Table[k] == -1 && !port_legal(Table, 1, k)) {
                                        Table[k] = 0;
                                        valeur = min(Table, alpha, beta, Dernier_retour_positif,
                                                       Dernier_deploreur_negatif, profondeur - 1, nbr_epuiseurs + 1, coef);
                                        Table[k] = -1;

                                        if (valeur > valeur_maximal) {
                                            valeur_maximal = valeur;
                                            if (deplacer) {
                                                deplacer[0] = nombre;
                                                deplacer[1] = j;
                                                deplacer[2] = k;
                                            }
                                        }
                                        if (valeur_maximal >= beta) {
                                            Table[j] = 0;
                                            Table[nombre] = 1;
                                            return valeur_maximal;
                                        }
                                        if (valeur_maximal > alpha)
                                            alpha = valeur_maximal;
                                    }
                                }
                            }
                            else {
                                // quand on joue avec un numérateur sur j, on ne surmonte pas la souris
                                Dernier_retour_positif = 0;
                                valeur =  min(Table, alpha, beta, Dernier_retour_positif,
                                                Dernier_deploreur_negatif, profondeur - 1, nbr_epuiseurs + 1, coef);
                                if (valeur > valeur_maximal) {
                                    valeur_maximal = valeur;
                                    if (deplacer) {
                                        deplacer[0] = nombre;
                                        deplacer[1] = j;
                                        deplacer[2] = -1;
                                    }
                                }
                                if (valeur_maximal >= beta) {
                                    Table[j] = 0;
                                    Table[nombre] = 1;
                                    return valeur_maximal;
                                }
                                if (valeur_maximal > alpha)
                                    alpha = valeur_maximal;
                            }
                            Table[j] = 0;
                            Table[nombre] = 1;
                        }
                    }
                }
            }
            return valeur_maximal;
        }
    }
}


void alphabeta(int Table[24], int deplacer[3], int profondeur, int nbr_epuiseurs, int coef[19]) {
    max(Table, -30000, 30000, deplacer, -1, -1, profondeur, nbr_epuiseurs, coef);
}
