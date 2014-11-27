#include <iostream>
#include <string>
#include "manipFichier.h"
#include "rotation.h"

using namespace std;

void rotation(string input,string output){
	int red[MAX][MAX];
	int green[MAX][MAX];
	int blue[MAX][MAX];
	int taille;
	loadPicture(input,red,green,blue,taille);
	int lColone=taille;
	int lLigne=taille;
	int fLigne=0;
	int fColone=0;
	int tmp;
	for (int i = 0; i < taille/2; ++i) // On parcout toute la moitié gauche de la couleur.
	{
		for (int j = 0; j < taille/2; ++j)
		{
			tmp = red[i][j];
			red[i][j] = red[fLigne][lColone];
			fLigne++;
			fColone++;
		}
		fLigne=0;
		fColone=0;
		lLigne--;
		lColone--;
	}
	lColone=taille;
	fLigne=0;
	for (int i = 0; i < taille/2; ++i)
	{
		for (int j = 0; j < taille/2; ++j)
		{
			tmp = blue[i][j];
			blue[i][j] = blue[fLigne][lColone];
			blue[fLigne][lColone]= tmp;
			fLigne++;
			fColone++;
		}
		fLigne=0;
		fColone=0;
		lLigne--;
		lColone--;
	}
	lColone=taille;
	fLigne=0;
	for (int i = 0; i < taille/2; ++i)
	{
		for (int j = 0; j < taille/2; ++j)
		{
			tmp = green[i][j];
			green[i][j] = green[fLigne][lColone];
			green[fLigne][lColone]= tmp;
			fLigne++;
			fColone++;
		}
		fLigne=0;
		fColone=0;
		lLigne--;
		lColone--;
	}
	writePicture(red,green,blue,taille,output);
}