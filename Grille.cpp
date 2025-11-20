#include "Grille.h"
#include <iostream>
#include <cstdlib> 

Grille::Grille() : _score(0) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            _grille[i][j].Vider();
    ajouterTuileAleatoire();
    ajouterTuileAleatoire();
}

// Affichage simple de la grille
void Grille::afficher() const {
    std::cout << "Score : " << _score << "\n";
    std::cout << "-----------------------------\n";
    for (int i = 0; i < 4; i++) {
        std::cout << "| ";
        for (int j = 0; j < 4; j++) {
            if (_grille[i][j].EstVide()) std::cout << ".\t";
            else std::cout << _grille[i][j].GetValeur() << "\t";
        }
        std::cout << "|\n";
    }
    std::cout << "-----------------------------\n";
}

// Ajouter une tuile aléatoire (2 ou 4) dans une case vide
bool Grille::ajouterTuileAleatoire() {
    int vides[16][2];
    int count = 0;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (_grille[i][j].EstVide()) {
                vides[count][0] = i;
                vides[count][1] = j;
                count++;
            }

    if (count == 0) return false;

    int r = std::rand() % count;
    int x = vides[r][0];
    int y = vides[r][1];

    int val = (std::rand() % 10 == 0) ? 4 : 2;
    _grille[x][y].SetValeur(val);

    return true;
}

bool Grille::deplacerFusionGauche(Tuile ligne[4]) {
    bool change = false;

    //compression
    for (int i = 0; i < 4; i++) {
        if (ligne[i].estVide()) {
            for (int j = i+1; j < 4; j++) {
                if (!ligne[j].EstVide()) {
                    ligne[i].SetValeur(ligne[j].getValeur());
                    ligne[j].vider();
                    change = true;
                    break;
                }
            }
        }
    }

    // Fusion
    for (int i = 0; i < 3; i++) {
        if (!ligne[i].EstVide() && ligne[i].GetValeur() == ligne[i+1].GetValeur()) {
            ligne[i].SetValeur(ligne[i].GetValeur()*2);
            _score += ligne[i].getValeur();
            ligne[i+1].Vider();
            change = true;
        }
    }

    // Compression après fusion
    for (int i = 0; i < 4; i++) {
        if (ligne[i].estVide()) {
            for (int j = i+1; j < 4; j++) {
                if (!ligne[j].estVide()) {
                    ligne[i].setValeur(ligne[j].getValeur());
                    ligne[j].vider();
                    break;
                }
            }
        }
    }

    return change;
}


bool Grille::deplacerFusionDroite(Tuile ligne[4]) {
    bool change = false;

    for (int i = 3; i >= 0; i--) {
        if (ligne[i].estVide()) {
            for (int j = i-1; j >= 0; j--) {
                if (!ligne[j].estVide()) {
                    ligne[i].setValeur(ligne[j].getValeur());
                    ligne[j].vider();
                    change = true;
                    break;
                }
            }
        }
    }

    for (int i = 3; i > 0; i--) {
        if (!ligne[i].estVide() && ligne[i].getValeur() == ligne[i-1].getValeur()) {
            ligne[i].setValeur(ligne[i].getValeur()*2);
            _score += ligne[i].getValeur();
            ligne[i-1].vider();
            change = true;
        }
    }

    for (int i = 3; i >= 0; i--) {
        if (ligne[i].estVide()) {
            for (int j = i-1; j >= 0; j--) {
                if (!ligne[j].estVide()) {
                    ligne[i].setValeur(ligne[j].getValeur());
                    ligne[j].vider();
                    break;
                }
            }
        }
    }

    return change;
}

bool Grille::deplacerFusionHaut(int col) {
    Tuile ligne[4];
    for (int i = 0; i < 4; i++) ligne[i] = _grille[i][col];

    bool change = deplacerFusionGauche(ligne);

    for (int i = 0; i < 4; i++) _grille[i][col] = ligne[i];
    return change;
}

bool Grille::deplacerFusionBas(int col) {
    Tuile ligne[4];
    for (int i = 0; i < 4; i++) ligne[i] = _grille[i][col];

    bool change = deplacerFusionDroite(ligne);

    for (int i = 0; i < 4; i++) _grille[i][col] = ligne[i];
    return change;
}

bool Grille::mouvementGauche() {
    bool change = false;
    for (int i = 0; i < 4; i++) change |= deplacerFusionGauche(_grille[i]);
    return change;
}

bool Grille::mouvementDroite() {
    bool change = false;
    for (int i = 0; i < 4; i++) change |= deplacerFusionDroite(_grille[i]);
    return change;
}

bool Grille::mouvementHaut() {
    bool change = false;
    for (int j = 0; j < 4; j++) change |= deplacerFusionHaut(j);
    return change;
}

bool Grille::mouvementBas() {
    bool change = false;
    for (int j = 0; j < 4; j++) change |= deplacerFusionBas(j);
    return change;
}


bool Grille::peutBouger() const {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (_grille[i][j].estVide()) return true;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++)
            if (_grille[i][j].getValeur() == _grille[i][j+1].getValeur()) return true;

    for (int j = 0; j < 4; j++)
        for (int i = 0; i < 3; i++)
            if (_grille[i][j].getValeur() == _grille[i+1][j].getValeur()) return true;

    return false;
}

bool Grille::aGagne() const {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (_grille[i][j].getValeur() == 2048) return true;
    return false;
}
