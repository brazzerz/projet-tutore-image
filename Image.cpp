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

void Image::clone1(){ // Clone l'image chargé dans un tableau alternatif.
    for (int i = 0; i < taille_; ++i)
    {
        for (int j = 0; j < taille_; ++j)
        {
            red_1[i][j]=red_[i][j];
            green_1[i][j]=green_[i][j];
            blue_1[i][j]=blue_[i][j];
        }
    }
}

void Image::clone2(){ // Clone l'image chargé dans un tableau alternatif.
    for (int i = 0; i < taille_; ++i)
    {
        for (int j = 0; j < taille_; ++j)
        {
            red_2[i][j]=red_[i][j];
            green_2[i][j]=green_[i][j];
            blue_2[i][j]=blue_[i][j];
        }
    }
    
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

//Réalisé par SALVATO Lucas
//Méthode de rotation à 270°
void Image::rotation270(){
    //On prend des tableau pour stocker les valeurs temporaire
    int red[MAX][MAX];
    int green[MAX][MAX];
    int blue[MAX][MAX];
    //Parcour des lignes
    for(int i=0;i<taille_;i++){
        //Parcour des colonnes
        for(int j=0;j<taille_;j++){
            red[j][taille_-i]=red_[i][j];
            green[j][taille_-i]=green_[i][j];
            blue[j][taille_-i]=blue_[i][j];
        }
    }
    //On remplis de nouveau les attributs
    for(int i=0;i<taille_;i++){
        for(int j=0;j<taille_;j++){
            red_[i][j]=red[i][j];
            green_[i][j]=green[i][j];
            blue_[i][j]=blue[i][j];
        }
    }
}

//Réaltisé par Shuishan WANG
// Filtre 1, flou.
void Image::flou()
{
    clone1();
    for(int i = 0 ; i < taille_ ; i++)
    {

        for(int j = 0 ; j < taille_ ; j++)
        {
           if(i == 0 || j == 0 || i == taille_ - 1 || j == taille_ - 1)
           {
                red_[i][j] = 0;
                blue_[i][j] = 0;
                green_[i][j] = 0;

           }
           else {
                int mRouge;
                int mVert;
                int mBleu;
                red_[i][j] = (red_1[i][j] +red_1[i][j-1] +red_1[i][j+1] +red_1[i-1][j] +red_1[i-1][j+1] +red_1[i-1][j-1] +red_1[i+1][j-1] +red_1[i+1][j] +red_1[i+1][j+1])/9;

                green_[i][j] =  (green_1[i][j] +green_1[i][j-1] +green_1[i][j+1] +green_1[i-1][j] +green_1[i-1][j+1] +green_1[i-1][j-1] +green_1[i+1][j-1] +green_1[i+1][j] +green_1[i+1][j+1])/9;

                blue_[i][j] = (blue_1[i][j] +blue_1[i][j-1] +blue_1[i][j+1] +blue_1[i-1][j] +blue_1[i-1][j+1] +blue_1[i-1][j-1] +blue_1[i+1][j-1] +blue_1[i+1][j] +blue_1[i+1][j+1])/9;
           }

        }
    }
}

//Réaltisé par Shuishan WANG
// Filtre 2, créer un noir ?
void Image::noir()
{
    for(int i = 0 ; i < taille_ ; i++)
    {

        for(int j = 0 ; j < taille_ ; j++)
        {
            if(i == 0 || j == 0 || i == taille_ - 1 || j == taille_ - 1)
           {
                red_[i][j] = 0;
                blue_[i][j] = 0;
                green_[i][j] = 0;

           }
           else
           {
            red_[i][j] = (red_1[i][j]*0 +red_1[i][j-1]*2 +red_1[i][j+1]*-2 +red_1[i-1][j]*0 +red_1[i-1][j+1]*-1 +red_1[i-1][j-1]*1 +red_1[i+1][j-1]*1 +red_1[i+1][j]*0 +red_1[i+1][j+1]*-1);
            green_[i][j] = (green_1[i][j]*0 +green_1[i][j-1]*2 +green_1[i][j+1]*-2 +green_1[i-1][j]*0 +green_1[i-1][j+1]*-1 +green_1[i-1][j-1]*1 +green_1[i+1][j-1]*1 +green_1[i+1][j]*0 +green_1[i+1][j+1]*-1);
            blue_[i][j] = (blue_1[i][j]*0 +blue_1[i][j-1]*2 +blue_1[i][j+1]*-2 +blue_1[i-1][j]*0 +blue_1[i-1][j+1]*-1 +blue_1[i-1][j-1]*1 +blue_1[i+1][j-1]*1 +blue_1[i+1][j]*0 +blue_1[i+1][j+1]*-1);
            if(red_[i][j] > 255 )red_[i][j] = 255;
            if (red_[i][j] < 0)red_[i][j] = 0;
            if(green_[i][j] > 255 )green_[i][j] = 255;
            if (green_[i][j] < 0)green_[i][j] = 0;
            if(blue_[i][j] > 255 )blue_[i][j] = 255;
            if (blue_[i][j] < 0)blue_[i][j] = 0;

           }
        }
    }
}

void Image::filtre3()
{
for(int i = 0 ; i < taille_ ; i++)
    {

        for(int j = 0 ; j < taille_ ; j++)
        {
            if(i == 0 || j == 0 || i == taille_ - 1 || j == taille_ - 1)
           {
                red_[i][j] = 0;
                blue_[i][j] = 0;
                green_[i][j] = 0;
           }
           else
           {
            red_[i][j] = (red_1[i][j]*0 +red_1[i][j-1]*0 +red_1[i][j+1]*0 +red_1[i-1][j]*2 +red_1[i-1][j+1]*1 +red_1[i-1][j-1]*1 +red_1[i+1][j-1]*-1 +red_1[i+1][j]*-2 +red_1[i+1][j+1]*-1);
            green_[i][j] = (green_1[i][j]*0 +green_1[i][j-1]*0 +green_1[i][j+1]*0 +green_1[i-1][j]*2 +green_1[i-1][j+1]*1 +green_1[i-1][j-1]*1 +green_1[i+1][j-1]*-1 +green_1[i+1][j]*-2 +green_1[i+1][j+1]*-1);
            blue_[i][j] = (blue_1[i][j]*0 +blue_1[i][j-1]*0 +blue_1[i][j+1]*0 +blue_1[i-1][j]*2 +blue_1[i-1][j+1]*1 +blue_1[i-1][j-1]*1 +blue_1[i+1][j-1]*-1 +blue_1[i+1][j]*-2 +blue_1[i+1][j+1]*-1);
            if(red_[i][j] > 255 )red_[i][j] = 255;
            if (red_[i][j] < 0)red_[i][j] = 0;
            if(green_[i][j] > 255 )green_[i][j] = 255;
            if (green_[i][j] < 0)green_[i][j] = 0;
            if(blue_[i][j] > 255 )blue_[i][j] = 255;
            if (blue_[i][j] < 0)blue_[i][j] = 0;
           }
        }
    }
}

// void Image::filtre4()
// {
//     for(int i = 0 ; i < taille_ ; i++)
//     {

//         for(int j = 0 ; j < taille_ ; j++)
//         {
//             if(i == 0 || j == 0 || i == taille_ - 1 || j == taille_ - 1)
//            {
//                 red_[i][j] = 0;
//                 blue_[i][j] = 0;
//                 green_[i][j] = 0;

//            }
//            else
//            {
//             red_[i][j] = (red_2[i][j]*0 +red_2[i][j-1]*0 +red_2[i][j+1]*0 +red_2[i-1][j]*2 +red_2[i-1][j+1]*1 +red_2[i-1][j-1]*1 +red_2[i+1][j-1]*-1 +red_2[i+1][j]*-2 +red_2[i+1][j+1]*-1);
//             green_[i][j] = (green_2[i][j]*0 +green_2[i][j-1]*0 +green_2[i][j+1]*0 +green_2[i-1][j]*2 +green_2[i-1][j+1]*1 +green_2[i-1][j-1]*1 +green_2[i+1][j-1]*-1 +green_2[i+1][j]*-2 +green_2[i+1][j+1]*-1);
//             blue_[i][j] = (blue_2[i][j]*0 +blue_2[i][j-1]*0 +blue_2[i][j+1]*0 +blue_2[i-1][j]*2 +blue_2[i-1][j+1]*1 +blue_2[i-1][j-1]*1 +blue_2[i+1][j-1]*-1 +blue_2[i+1][j]*-2 +blue_2[i+1][j+1]*-1);
//             red_[i][j] = red_[i][j]*red_[i][j];
//             green_[i][j] = green_[i][j]*green_[i][j];
//             blue_[i][j] = blue_[i][j]*blue_[i][j];

//              red_1[i][j] = (red_2[i][j]*0 +red_2[i][j-1]*2 +red_2[i][j+1]*-2 +red_2[i-1][j]*0 +red_2[i-1][j+1]*-1 +red_2[i-1][j-1]*1 +red_2[i+1][j-1]*1 +red_2[i+1][j]*0 +red_2[i+1][j+1]*-1);
//             green_1[i][j] = (green_2[i][j]*0 +green_2[i][j-1]*2 +green_2[i][j+1]*-2 +green_2[i-1][j]*0 +green_2[i-1][j+1]*-1 +green_2[i-1][j-1]*1 +green_2[i+1][j-1]*1 +green_2[i+1][j]*0 +green_2[i+1][j+1]*-1);
//             blue_1[i][j] = (blue_2[i][j]*0 +blue_2[i][j-1]*2 +blue_2[i][j+1]*-2 +blue_2[i-1][j]*0 +blue_2[i-1][j+1]*-1 +blue_2[i-1][j-1]*1 +blue_2[i+1][j-1]*1 +blue_2[i+1][j]*0 +blue_2[i+1][j+1]*-1);
//             red_1[i][j] = red_1[i][j]*red_1[i][j];
//             green_1[i][j] = green_1[i][j]*green_1[i][j];
//             blue_1[i][j] = blue_1[i][j]*blue_1[i][j];

//             red_[i][j] = sqrt(red_[i][j] + red_1[i][j]);
//             green_[i][j] = sqrt(green_[i][j] + green_1[i][j]);
//             blue_[i][j] = sqrt(blue_[i][j] + blue_1[i][j]);

//             if(red_[i][j] > 255 )red_[i][j] = 255;
//             if (red_[i][j] < 0)red_[i][j] = 0;
//             if(green_[i][j] > 255 )green_[i][j] = 255;
//             if (green_[i][j] < 0)green_[i][j] = 0;
//             if(blue_[i][j] > 255 )blue_[i][j] = 255;
//             if (blue_[i][j] < 0)blue_[i][j] = 0;

//            }
//         }
//     }
// }