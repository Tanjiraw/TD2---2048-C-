#ifndef GRILLE_H
#define GRILLE_H
#include "Tuile.h"

class Grille {
private:
    Tuile _grille[4][4];
    int _score;

    bool deplacerFusionGauche(Tuile ligne[4]);
    bool deplacerFusionDroite(Tuile ligne[4]);
    bool deplacerFusionHaut(int col);
    bool deplacerFusionBas(int col);

public:
    Grille();

    void afficher() const;
    bool ajouterTuileAleatoire();
    bool mouvementGauche();
    bool mouvementDroite();
    bool mouvementHaut();
    bool mouvementBas();

    bool peutBouger() const;
    bool aGagne() const;

    int getScore() const;
};

#endif
