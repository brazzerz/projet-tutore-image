#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char const *argv[])
{
	if (argc>1) // On regarde si des arguments ont été spécifié.
	{
		string choix = argv[1];
		if (choix == "--rouge") // On lance la fonction correspondante en fonction de l'argument.
		{
			cout<<"Cherche la présence de la couleur rouge dans l'image spécifié en argument."<<endl;
			// À l'avenir on appellera la fonction en question comme ceci : rouge(argv[2]).
		}
		else if (choix == "--rmrouge")
		{
			cout<<"Supprime la couleur rouge de l'image spécifié en argument."<<endl;
		}
		else if (choix == "--negatif")
		{
			cout<<"Créer un négatif de l'image spécifié en argument."<<endl;
		}
		else if (choix == "--nb")
		{
			cout<<"Créer un noir et blanc de l'image spécifié en argument."<<endl;
		}
		else if (choix == "--luminosite")
		{
			cout<<"Modifie la luminosité de l'image spécifié en argument."<<endl;
		}
		else if (choix == "--symetrie")
		{
			cout<<"Créer un symétrique vertical ou horizontal de l'image spécifié en argument."<<endl;
		}
		else if (choix == "--rotation")
		{
			cout<<"Effectue une rotation à 90° de l'image spécifié en argument."<<endl;
		}
		else if (choix == "--flou")
		{
			cout<<"Ajoute du flou à l'image spécifié en argument."<<endl;
		}
		else if (choix == "--help") // On affiche un message d'aide.
		{
			cout<<"Utilisation : imgsaas <OPTION> <FICHIER>\nOPTIONS :\n\t--rouge\t\tCherche la présence de la couleur rouge dans l'image spécifié en argument.\n\t--rmrouge\tSupprime la couleur rouge de l'image spécifié en argument.\n\t--negatif\tCréer un négatif de l'image spécifié en argument.\n\t--nb\tCréer un noir et blanc de l'image spécifié en argument.\n\t--luminosite\tModifie la luminosité de l'image spécifié en argument.\n\t--symetrie\tCréer un symétrique vertical ou horizontal de l'image spécifié en argument.\n\t--rotation\tEffectue une rotation à 60° de l'image spécifié en argument.\nt\t--flou\tAjoute du flou à l'image spécifié en argument.\n\t--help\tAffiche ce message."<<endl;
		}
		else{ // On affiche une erreur.
			cout<<"Syntaxe erronée.\nTapez --help pour obtenir de l'aide."<<endl;
		}
	}
	else{ // On affiche une erreur.
		cout<<"Syntaxe erronée.\nTapez --help pour obtenir de l'aide."<<endl;
	}
	return 0;
}