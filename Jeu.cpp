#include "Jeu.h"
#include <iostream>

Jeu::Jeu() {}

// Boucle principale du jeu
void Jeu::boucleJeu() {
    char touche;
    bool mouvementOk;

    while (true) {
        _grille.afficher();

        if (_grille.aGagne()) {
            std::cout << "Félicitations ! Tu as atteint 2048 !\n";
            break;
        }

        if (!_grille.peutBouger()) {
            std::cout << "Game Over ! Aucun mouvement possible.\n";
            break;
        }

        std::cout << "Déplace (z=Haut, s=Bas, q=Gauche, d=Droite, e=Quitter) : ";
        std::cin >> touche;

        mouvementOk = false;

        switch(touche) {
            case 'z': mouvementOk = _grille.mouvementHaut(); break;
            case 's': mouvementOk = _grille.mouvementBas(); break;
            case 'q': mouvementOk = _grille.mouvementGauche(); break;
            case 'd': mouvementOk = _grille.mouvementDroite(); break;
            case 'e': return; // quitter le jeu
            default:
                std::cout << "Touche invalide !\n";
                continue;
        }

        if (mouvementOk) {
            _grille.ajouterTuileAleatoire();
        } else {
            std::cout << "Mouvement impossible ! Essaie une autre direction.\n";
        }
    }
}
