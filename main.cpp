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
	cout<<"1\tPresence rouge\n2\tSupprimer rouge\n3\tNegatif\n4\tNoir et blanc\n5\tLuminosite\n6\tSymetrie vertical\n7\tSymetrie horizontal\n8\tRotation\n9\tFlou\n10\tSymetrie centrale\n11\tMeliMelo\n12\tRotation a 270\nChoix : ";
	cin>>choix;
	switch(choix){
		case 1:
		case 2:
		case 3: image.negatif();image.write(output);break;
		case 4: image.binarisation();image.write(output);break;
		case 5:	
		case 6: image.inversevert();image.write(output);break;
		case 7: image.inversehor();image.write(output);break;
		case 8: image.rotation90();image.write(output);break;
		case 9:
		case 10: image.symetriecentrale();image.write(output);break;
		case 11: image.melimelo();image.write(output);break;
		case 12: image.rotation270();image.write(output);break;
		default: cout<<"Choix invalide."<<endl;break;
	}
	return 0;
}
