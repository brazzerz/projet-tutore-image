#ifndef _MANIPFICHIER_
#define  _MANIPFICHIER_

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX = 150; 
// Prototypes des sous-programmes de lecture et d'ecriture d'une image
// (vous devez utiliser ces sous-programmes, mais pas les modifier)
void loadPicture(string picture, int red[][MAX], int green[][MAX], int blue[][MAX], int & taille);
void writePicture(const int red[][MAX], const int  green[][MAX], const int  blue[][MAX], int taille, string name);
//Procédure inversant l'image en fesant une sysmétrie verticale (SALVATO Lucas)
void inversevert(int red[][MAX],int green[][MAX],int blue[][MAX],int taille);
//Procédure inversant l'image en fesant une symétrie horizontale (SALVATO Lucas)
void inversehor(int red[][MAX],int green[][MAX],int blue[][MAX],int taille);

#endif
