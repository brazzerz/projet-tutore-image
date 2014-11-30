#include "Image.h"
#include "manipFichier.h"

// Constructeur
Image::Image(string input){
	loadPicture(input,red_,green_,blue_,taille_); // On utilise la procédure pour charger l'image en tant que constructeur.
}

void Image::write(string output){ // Ecriture du fichier.
    //Sauvegarde du résultat
    writePicture(red_,green_,blue_,taille_,output);
}

//Réaliser par SALVATO Lucas
//Inverser l'image en fonction d'un axe vertical
void Image::inversevert(){
    //Compteur inverse
    int cpt=taille_-1;
    //Variable temporaire
    int temp;
    //Boucle parcourant les lignes
    for(int i=0;i<taille_;i++){
        //Boucle parcourant les colonnes
        for(int j=0;j<=taille_/2;j++){
            //Inversion de la dernière colonne et première colonne des couleurs rouges
            temp=red_[i][j];
            red_[i][j]=red_[i][cpt];
            red_[i][cpt]=temp;
            //Inversion de la dernière colonne et première colonne des couleurs vertes
            temp=green_[i][j];
            green_[i][j]=green_[i][cpt];
            green_[i][cpt]=temp;
            //Inversion de la dernière colonne et première colonne des couleurs bleues
            temp=blue_[i][j];
            blue_[i][j]=blue_[i][cpt];
            blue_[i][cpt]=temp;
            //Diminution du compteur
            cpt--;
        }
        //Relance du compteur
        cpt=taille_-1;
    }
}

//Réalisé par SALVATO Lucas
//Mettre l'image en Noir et Blanc
void Image::binarisation (){
    int seuil;
    //Boucle du choix du seuil
    do{
        //Choix du seuil et relance de la boucle
        cout<<"Choisissez un seuil entre 0 et 765 (seuil recommandé 382)"<<endl;
        cin>>seuil;
    }while(seuil<0 || seuil>765);
    //Boucle pour parcourir les lignes
    for(int i=0;i<taille_;i++){
        //Boucle pour parcourir les colonnes
        for(int j=0;j<taille_;j++){
            //Test pour déterminer si le pixel est noir
            if((red_[i][j]+green_[i][j]+blue_[i][j])<seuil){
                red_[i][j]=0;
                green_[i][j]=0;
                blue_[i][j]=0;
            }
            //Ou blanc
            else{
                red_[i][j]=255;
                green_[i][j]=255;
                blue_[i][j]=255;
            }
        }
    }
}

//Réaliser par SALVATO Lucas
//Inverser l'image en fonction d'un axe horizontale
void Image::inversehor(){
    //Compteur inverse
    int cpt=taille_-1;
    //Variable temporaire
    int temp;
    //Boucle parcourant les lignes
    for(int j=0;j<taille_;j++){
        //Boucle parcourant les colonnes
        for(int i=0;i<=taille_/2;i++){
            //Inversion de la dernière ligne et première ligne des couleurs rouges
            temp=red_[i][j];
            red_[i][j]=red_[cpt][j];
            red_[cpt][j]=temp;
            //Inversion de la dernière ligne et première ligne des couleurs vertes
            temp=green_[i][j];
            green_[i][j]=green_[cpt][j];
            green_[cpt][j]=temp;
            //Inversion de la dernière ligne et première ligne des couleurs bleues
            temp=blue_[i][j];
            blue_[i][j]=blue_[cpt][j];
            blue_[cpt][j]=temp;
            //Diminution du compteur inverse
            cpt--;
        }
        //Relance du compteur
        cpt=taille_-1;
    }
}

//Réalisé par SALVATO Lucas
//Méthode pour rendre une photo négatif
void Image::negatif(){
    //Parcours des lignes
    for(int i=0;i<taille_;i++){
        //Parcour des colonnes
        for(int j=0;j<taille_;j++){
            //transformation négatif
            red_[i][j]=255-red_[i][j];
            green_[i][j]=255-green_[i][j];
            blue_[i][j]=255-blue_[i][j];
        }
    }
}

//Réalisé par SALVATO Lucas (Bonus)
//Méthode pour faire une symétrie en fonction de l'axecentrale
void Image::symetriecentrale(){
    for(int i=0;i<taille_;i++){
        for(int j=0;j<taille_/2;j++){
            red_[i][j]=red_[i][taille_-j];
            green_[i][j]=green_[i][taille_-j];
            blue_[i][j]=blue_[i][taille_-j];
        }
    }
}


// Réalisé par NGUYEN Duc
// séparation de l'image en 4 partie et changement de place de celles-ci
void Image::melimelo(){
    int tmpred;
    int tmpgreen;
    int tmpblue;
    for (int i = 0; i < taille_; ++i)
    {
        for (int j = 0; j < taille_/2; ++j)
        {
            tmpred = red_[i][j]; // On sauvegarde le pixel présent à l'emplacement ij
            red_[i][j] = red_[j][i]; // On remplace le pixel ij par le pixel ji.
            red_[j][i] = tmpred; // On remplace le pixel ji par le pixel ij.
            tmpgreen = green_[i][j];
            green_[i][j] = green_[j][i];
            green_[j][i] = tmpgreen;
            tmpblue = blue_[i][j];
            blue_[i][j] = blue_[j][i];
            blue_[j][i] = tmpblue;
        }
    }
}

//Réalisé par NGUYEN Duc
//Rotation à 90°
void Image::rotation90(){
    //On prend des tableaux pour stocker les valeurs temporaire
    int red[MAX][MAX];
    int green[MAX][MAX];
    int blue[MAX][MAX];
    //Parcour des lignes
    for(int i=0;i<taille_;i++){
        //Parcour des colonnes
        for(int j=0;j<taille_;j++){
            //On fait la rotation à 90°
            red[taille_-1-j][i]=red_[i][j];
            green[taille_-1-j][i]=green_[i][j];
            blue[taille_-1-j][i]=blue_[i][j];
        }
    }
    //On rempli de nouveau les attributs d'image avec les valeur temporaire
    for(int i=0;i<taille_;i++){
        for(int j=0;j<taille_;j++){
            red_[i][j]=red[i][j];
            green_[i][j]=green[i][j];
            blue_[i][j]=blue[i][j];
        }
    }
}
