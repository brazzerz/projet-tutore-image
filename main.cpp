#include <iostream>
#include <cstdlib>
#include "Image.h"

using namespace std;

int main(int argc, char const *argv[])
{
	string input;
	cout<<"Entrez une image en entrée."<<endl;
	cin>>input;
	Image image(input);
	string output;
	cout<<"Entrez le nom du fichier de sortie"<<endl;
	cin>>output;
	int choix;
	cout<<"1\tCopie identique de l'image\n2\tConserve uniquement le rouge\n3\t... le vert\n4\t... le bleu\n5\tPresence rouge\n6\tSupprimer rouge si présent\n7\tNegatif\n8\tNoir et blanc\n9\tLuminosite\n10\tSymetrie vertical\n11\tSymetrie horizontal\n12\tRotation\n13\tFlou\n14\tSymetrie centrale\n15\tMeliMelo\n16\tRotation a 270\n17-18\tSobel\n19\tSobel final\nChoix : ";
	cin>>choix;
	switch(choix){
		case 1: image.write(output);break;
		case 2: image.redOnly();image.write(output);break;
		case 3: image.greenOnly();image.write(output);break;
		case 4: image.blueOnly();image.write(output);break;
		case 5: if (image.presRouge())
		{
			cout<<"La couleur rouge est présente dans l'image."<<endl;
		}
		else
		{
			cout<<"La couleur rouge n'est pas présente dans l'image."<<endl;
		}
		case 6: if (image.presRouge())
		{
			image.rmRouge();image.write(output);break;
		}
		else
		{
			cout<<"La couleur rouge n'est pas présente dans l'image."<<endl;
		}
		case 7: image.negatif();image.write(output);break;
		case 8: image.binarisation();image.write(output);break;
		case 9:	image.luminosite();image.write(output);break;
		case 10: image.inversevert();image.write(output);break;
		case 11: image.inversehor();image.write(output);break;
		case 12: image.rotation90();image.write(output);break;
		case 13: image.flou();image.write(output);break;
		case 14: image.symetriecentrale();image.write(output);break;
		case 15: image.melimelo();image.write(output);break;
		case 16: image.rotation270();image.write(output);break;
		case 17: image.sobel1();image.write(output);break;
		case 18: image.sobel2();image.write(output);break;
		case 19: image.sobel3();image.write(output);break;
		default: cout<<"Choix invalide."<<endl;break;
	}
	return 0;
}
