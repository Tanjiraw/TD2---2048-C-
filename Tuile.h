#ifndef TUILE_H
#define TUILE_H

class Tuile {
private:
    int _valeur;   

public:
Tuile(int val = 0); //constructeur
int GetValeur() const; //getters
bool EstVide() const; 
void SetValeur(int val);
void Vider();
};

#endif