#include "manipFichier.h"

/*
======================================================================================================
Definitions des fonctions de lecture et d'ecriture
======================================================================================================

Un fichier .ppm peut être ouvert soit par un éditeur de texte, soit par un visionneur (gimp par exemple).
Il est de la forme suivante :
P3 (ou P6) : format : P3 indique un codage en ASCII
longueur
largeur
max : valeur du pixel maximal (255)
données de l'image : chaque pixel est donné de la forme suivante R G B

par exemple :
P3
2
2
255
255 0 0   100 125 120
0 0 255   255 255 0

Un fichier au format ppm contient donc des entiers séparés soit par ' ' ou bien \n ou bien \t
*/


// loadPicture : prend le nom d'un fichier contenant une image au format ppm,
// remplit 3 tableaux 2D avec les données de cette image, et renvoie la taille
// effective de ces tableaux (identique pour les 3 tableaux).
// paramètres (D) image : chaîne de caractères
//  	      (R) tabR, tabB, tabG : tableaux [0,MAX-1][0,MAX-1] d'entiers
//	      (R) taille : entier;
void loadPicture(string picture, int red[][MAX], int green[][MAX], int blue[][MAX], int & taille)
{
    // Déclaration des variables
    string line; // pour récupérer les lignes du fichier image au format .ppm, qui est codé en ASCII.
    string format; //pour récupérer le format de l'image : celui-ci doit être de la forme P3
    string name; // au cas où l'utilisateur se trompe dans le nom de l'image à charger, on redemande le nom.
    // Allocation dynamique du tableau mypixels, vous verrez ces notions plus tard dans l'année
    // on procède de cette manière pour des raisons de mémoire (vous verrez toutes ces notions plus tard dans l'année)
    int *mypixels = new int[3*MAX*MAX]; // pour récupérer les données du fichier de manière linéaire. On répartira ensuite ces données dans les tableaux correspondants
    ifstream in; // Déclaration d'un "flux" qui permettra ensuite de lire les données de l'image.
    streambuf* oldbuf; // déclaration d'un "buffer" qui permettra de rediriger les entrées standard (cin) sur le fichier image portant le nom picture
    int hauteur; // pour bien vérifier que l'image est carrée, et de taille respectant les conditions fixées par l'énoncé
    // Initialisation des variables
    name = picture;
    // Permet d'ouvrir le fichier portant le nom picture et de rediriger l'entrée standard sur le fichier portant le nom picture :
    // ouverture du fichier portant le nom picture
    in.open(name.c_str( ));
    // redirection de l'entrée standard (cin) vers le fichier image.
    oldbuf = cin.rdbuf(in.rdbuf());

    // On vérifie que le fichier a bien été ouvert. Si ça n'est pas le cas, on redemande un nom de fichier valide
    while (!in)
    {
        cin.rdbuf(oldbuf);
        cerr << "Erreur! Impossible de lire de fichier " << name << " ! " << endl;
        cerr << "Redonnez le nom du fichier a ouvrir SVP. Attention ce fichier doit avoir un nom du type nom.ppm." << endl;
        cin >> name;
        in.open(name.c_str( )); // relance
        oldbuf = cin.rdbuf(in.rdbuf());
    }

    // Lecture du nombre définissant le format (ici P3)
    //getline(cin, format);
    cin >> format;
    // on finit de lire la ligne (caractère d'espacement)
    getline(cin, line);

    // Lecture du commentaire
    getline(cin, line);

    //lecture des dimensions
    cin >> taille >> hauteur;
    getline(cin, line); // on finit de lire la ligne (caractère d'espacement)

    // On vérifie que l'image a une taille qui vérifie bien les conditions requises par l'énoncé.
    // Si ça n'est pas le cas, on redemande un fichier valide, et ce, tant que necessaire.
    while (taille != hauteur || taille > MAX || format != "P3")
    {
        if (format != "P3")
        {
            cerr << "Erreur! L'image que vous nous avez donnee a un format ne verifiant pas les conditions requises." << endl;
            cerr << "L'image que vous nous avez donnee doit etre codee en ASCII et non en brut." << endl;
        }

        if (taille != hauteur)
            cerr << "Erreur! L'image que vous nous avez donne n'est pas carree." << endl;

        if (taille > MAX || hauteur > MAX)
            cerr << "L'image que vous nous avez donnee est trop grande. Elle doit etre carree de cote inferieur a " << MAX << " pixels." << endl;

        in.close();

        // On va redemander un nom de fichier valide.
        do
        {
            cin.rdbuf(oldbuf);
            cerr << "Veuillez redonner un nom de fichier qui respecte les conditions de format et de taille. Attention, ce nom doit etre de la forme nom.ppm." << endl;
            cin >> name;
            in.open(name.c_str( )); // relance
            oldbuf = cin.rdbuf(in.rdbuf());
        }while(!in);

         // Lecture du nombre définissant le format (ici P3)
       // getline(cin, format);
         cin >> format;
         getline(cin, line); // on finit de lire la ligne (caractère d'espacement)

        // Lecture du commentaire
        getline(cin, line);

        //lecture des dimensions
        cin >> taille >> hauteur; // relance
        getline(cin, line); // on finit de lire la ligne (caractère d'espacement)
    }

    //Lecture de la valeur max
    getline(cin, line);

    //Lecture des donnees et écriture dans les tableaux :
    // Pour plus de simplicité, on stocke d'abord toutes les données dans mypixels
    // dans l'ordre de lecture puis ensuite on les répartira dans les différents tableaux.
    //Les données stockées dans mypixels sont de la forme RGB RGB RGB ....
    // Il faudra donc répartir les valeurs R correspondant à la composante rouge de l'image
    // dans le tableau red, de même pour G et B.

    for (int i = 0; i < 3*taille*taille; i++)
    {
        cin >> mypixels[i];
    }

    // Remplissage des 3 tableaux : on répartit maintenant les valeurs dans les bonnes composantes
    // Comme dans mypixels, les données sont stockées de la manière suivante : RGB RGB RGB, il faut mettre
    // les valeurs correspondant à la composante rouge dans red, ...
    // Ainsi, les valeurs de la composante rouge correspondent aux valeurs stockes aux indices
    // congrus à 0 mod 3 dans mypixels, que les valeurs de la composante verte correspond aux valeurs
    // stockes aux indices sont congrus à 1 mod 3, ...
    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < taille; j++)
        {
            red[i][j] = mypixels[3*j + 3*taille*i];
            green[i][j] = mypixels[3*j + 1 + 3*taille*i];
            blue[i][j] = mypixels[3*j + 2 + 3*taille*i];
        }
    }

    // Informations à l'utilisateur pour dire que tout s'est bien passé
    cout << " L'image " << name << " a bien ete chargee dans les tableaux ." << endl;

    // On libère la mémoire que l'on avait attribué à mypixels : vous verrez ces notions plus tard dans l'année
    delete mypixels;
    // On ferme le fichier que l'on vient de lire
    in.close();
    // On remet à nouveau l'entrée standard sur la console
    cin.rdbuf(oldbuf);
}

// writePicture : prend 3 tableaux 2D, leur taille effective (identique pour les 3),
// crée une image au format ppm à partir des données de ces tableaux, et l’enregistre
// dans un fichier.
// paramètres (D) tabR, tabB, tabG : tableaux [0,MAX-1][0,MAX-1] d’entiers
//		 (D) taille : entier
//		 (D) image : chaîne de caractères
void writePicture(const int red[][MAX], const int green[][MAX], const int blue[][MAX], int taille, string name)
{
    // Déclaration des variables
    ofstream out;
    streambuf* oldbuf;

    // Initialisation des variables
    /*On redirige la sortie standard sur le fichier portant le nom name.
    De cette manière, lorsque l'on fera appel à cout, la sortie sera écrite dans le fichier portant le nom name et non pas sur la console */
    // ouverture (voire création) du fichier portant le nom name pour écrire les données
    out.open(name.c_str( ));
    // redirection de la sortie standard (cout) vers le fichier image.
    oldbuf = std::cout.rdbuf(out.rdbuf());

    // On vérifie que le fichier a bien été crée
    if (!out)
    {
        cerr << "Impossible de creer le fichier " << name << " ! " << endl;
    }

    else
    {
        // Créer le format, la largeur (les paramètres qui ne sont pas dans le tableau
        // Ecriture du nombre définissant le format. On n'utilise que le codage ASCII
        cout << "P3" << endl;
        // Ecriture d'un commentaire (pour calquer au format de Gimp)
        cout << "# Created by IUT d'Informatique d'Orsay Team" << endl;
        // Ecriture des dimensions
        cout << taille << ' ' << taille << endl;
        // Ecriture de la valeur maximale : cette valeur vaut toujours 255 avec le codage RGB
        cout << 255 << endl;

        // Ecriture des données, qui se trouvent dans les tableaux fournis par l'utilisateur
        for (int i = 0; i < taille; i++)
        {
            for (int j = 0; j < taille; j++)
            {
                cout << red[i][j] << endl;
                cout << green[i][j] << endl;
                cout << blue[i][j] << endl;
            }
        }

        // Fermeture du fichier une fois que l'on a plus besoin de travailler dessus
        out.close();
        // Redirection de la sortie standard sur la console
        cout.rdbuf(oldbuf);

        // Informations à l'utilisateur pour dire que tout s'est déroulé correctement
        cout << "L'image " << name << " a bien ete cree sur votre disque. " << endl;
    }
}
//Réaliser par SALVATO Lucas
//Inverser l'image en fonction d'un axe vertical
void inversevert(int red[][MAX],int green[][MAX],int blue[][MAX],int taille){
    //Compteur inverse
    int cpt=taille-1;
    //Variable temporaire
    int temp;
    //Boucle parcourant les lignes
    for(int i=0;i<taille;i++){
        //Boucle parcourant les colonnes
        for(int j=0;j<=taille/2;j++){
            //Inversion de la dernière colonne et première colonne des couleurs rouges
            temp=red[i][j];
            red[i][j]=red[i][cpt];
            red[i][cpt]=temp;
            //Inversion de la dernière colonne et première colonne des couleurs vertes
            temp=green[i][j];
            green[i][j]=green[i][cpt];
            green[i][cpt]=temp;
            //Inversion de la dernière colonne et première colonne des couleurs bleues
            temp=blue[i][j];
            blue[i][j]=blue[i][cpt];
            blue[i][cpt]=temp;
            //Diminution du compteur
            cpt--;
        }
        //Relance du compteur
        cpt=taille-1;
    }
    //Sauvegarde du résultat
    string name="XX-symetrieVerticale.ppm";
    writePicture(red,green,blue,taille,name);
}

//Réaliser par SALVATO Lucas
//Inverser l'image en fonction d'un axe horizontale
void inversehor(int red[][MAX],int green[][MAX],int blue[][MAX],int taille){
    //Compteur inverse
    int cpt=taille-1;
    //Variable temporaire
    int temp;
    //Boucle parcourant les lignes
    for(int j=0;j<taille;j++){
        //Boucle parcourant les colonnes
        for(int i=0;i<=taille/2;i++){
            //Inversion de la dernière ligne et première ligne des couleurs rouges
            temp=red[i][j];
            red[i][j]=red[cpt][j];
            red[cpt][j]=temp;
            //Inversion de la dernière ligne et première ligne des couleurs vertes
            temp=green[i][j];
            green[i][j]=green[cpt][j];
            green[cpt][j]=temp;
            //Inversion de la dernière ligne et première ligne des couleurs bleues
            temp=blue[i][j];
            blue[i][j]=blue[cpt][j];
            blue[cpt][j]=temp;
            //Diminution du compteur inverse
            cpt--;
        }
        //Relance du compteur
        cpt=taille-1;
    }
    //Sauvegarde du résultat
    string name="XX-symetrieHorizontale.ppm";
    writePicture(red,green,blue,taille,name);
}

//Réalisé par SALVATO Lucas
//Mettre l'image en Noir et Blanc
void binarisation (int red[][MAX],int green[][MAX],int blue[][MAX],int taille){
    int seuil;
    //Boucle du choix du seuil
    do{
        //Choix du seuil et relance de la boucle
        cout<<"Choisissez un seuil entre 0 et 765 (seuil recommandé 382)"<<endl;
        cin>>seuil;
    }while(seuil<0 || seuil>765);
    //Boucle pour parcourir les lignes
    for(int i=0;i<taille;i++){
        //Boucle pour parcourir les colonnes
        for(int j=0;j<taille;j++){
            //Test pour déterminer si le pixel est noir
            if((red[i][j]+green[i][j]+blue[i][j])<seuil){
                red[i][j]=0;
                green[i][j]=0;
                blue[i][j]=0;
            }
            //Ou blanc
            else{
                red[i][j]=255;
                green[i][j]=255;
                blue[i][j]=255;
            }
        }
    }
    //Sauvegarde du résultat
    string name="XX-noiretblanc.ppm";
    writePicture(red,green,blue,taille,name);
}
