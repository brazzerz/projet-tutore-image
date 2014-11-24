#include "manipFichier.h"

/*
======================================================================================================
Definitions des fonctions de lecture et d'ecriture
======================================================================================================

Un fichier .ppm peut �tre ouvert soit par un �diteur de texte, soit par un visionneur (gimp par exemple).
Il est de la forme suivante :
P3 (ou P6) : format : P3 indique un codage en ASCII
longueur
largeur
max : valeur du pixel maximal (255)
donn�es de l'image : chaque pixel est donn� de la forme suivante R G B

par exemple :
P3
2
2
255
255 0 0   100 125 120
0 0 255   255 255 0

Un fichier au format ppm contient donc des entiers s�par�s soit par ' ' ou bien \n ou bien \t
*/


// loadPicture : prend le nom d'un fichier contenant une image au format ppm,
// remplit 3 tableaux 2D avec les donn�es de cette image, et renvoie la taille
// effective de ces tableaux (identique pour les 3 tableaux).
// param�tres (D) image : cha�ne de caract�res
//  	      (R) tabR, tabB, tabG : tableaux [0,MAX-1][0,MAX-1] d'entiers
//	      (R) taille : entier;
void loadPicture(string picture, int red[][MAX], int green[][MAX], int blue[][MAX], int & taille)
{
    // D�claration des variables
    string line; // pour r�cup�rer les lignes du fichier image au format .ppm, qui est cod� en ASCII.
    string format; //pour r�cup�rer le format de l'image : celui-ci doit �tre de la forme P3
    string name; // au cas o� l'utilisateur se trompe dans le nom de l'image � charger, on redemande le nom.
    // Allocation dynamique du tableau mypixels, vous verrez ces notions plus tard dans l'ann�e
    // on proc�de de cette mani�re pour des raisons de m�moire (vous verrez toutes ces notions plus tard dans l'ann�e)
    int *mypixels = new int[3*MAX*MAX]; // pour r�cup�rer les donn�es du fichier de mani�re lin�aire. On r�partira ensuite ces donn�es dans les tableaux correspondants
    ifstream in; // D�claration d'un "flux" qui permettra ensuite de lire les donn�es de l'image.
    streambuf* oldbuf; // d�claration d'un "buffer" qui permettra de rediriger les entr�es standard (cin) sur le fichier image portant le nom picture
    int hauteur; // pour bien v�rifier que l'image est carr�e, et de taille respectant les conditions fix�es par l'�nonc�
    // Initialisation des variables
    name = picture;
    // Permet d'ouvrir le fichier portant le nom picture et de rediriger l'entr�e standard sur le fichier portant le nom picture :
    // ouverture du fichier portant le nom picture
    in.open(name.c_str( ));
    // redirection de l'entr�e standard (cin) vers le fichier image.
    oldbuf = cin.rdbuf(in.rdbuf());

    // On v�rifie que le fichier a bien �t� ouvert. Si �a n'est pas le cas, on redemande un nom de fichier valide
    while (!in)
    {
        cin.rdbuf(oldbuf);
        cerr << "Erreur! Impossible de lire de fichier " << name << " ! " << endl;
        cerr << "Redonnez le nom du fichier a ouvrir SVP. Attention ce fichier doit avoir un nom du type nom.ppm." << endl;
        cin >> name;
        in.open(name.c_str( )); // relance
        oldbuf = cin.rdbuf(in.rdbuf());
    }

    // Lecture du nombre d�finissant le format (ici P3)
    //getline(cin, format);
    cin >> format;
    // on finit de lire la ligne (caract�re d'espacement)
    getline(cin, line);

    // Lecture du commentaire
    getline(cin, line);

    //lecture des dimensions
    cin >> taille >> hauteur;
    getline(cin, line); // on finit de lire la ligne (caract�re d'espacement)

    // On v�rifie que l'image a une taille qui v�rifie bien les conditions requises par l'�nonc�.
    // Si �a n'est pas le cas, on redemande un fichier valide, et ce, tant que necessaire.
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

         // Lecture du nombre d�finissant le format (ici P3)
       // getline(cin, format);
         cin >> format;
         getline(cin, line); // on finit de lire la ligne (caract�re d'espacement)

        // Lecture du commentaire
        getline(cin, line);

        //lecture des dimensions
        cin >> taille >> hauteur; // relance
        getline(cin, line); // on finit de lire la ligne (caract�re d'espacement)
    }

    //Lecture de la valeur max
    getline(cin, line);

    //Lecture des donnees et �criture dans les tableaux :
    // Pour plus de simplicit�, on stocke d'abord toutes les donn�es dans mypixels
    // dans l'ordre de lecture puis ensuite on les r�partira dans les diff�rents tableaux.
    //Les donn�es stock�es dans mypixels sont de la forme RGB RGB RGB ....
    // Il faudra donc r�partir les valeurs R correspondant � la composante rouge de l'image
    // dans le tableau red, de m�me pour G et B.

    for (int i = 0; i < 3*taille*taille; i++)
    {
        cin >> mypixels[i];
    }

    // Remplissage des 3 tableaux : on r�partit maintenant les valeurs dans les bonnes composantes
    // Comme dans mypixels, les donn�es sont stock�es de la mani�re suivante : RGB RGB RGB, il faut mettre
    // les valeurs correspondant � la composante rouge dans red, ...
    // Ainsi, les valeurs de la composante rouge correspondent aux valeurs stockes aux indices
    // congrus � 0 mod 3 dans mypixels, que les valeurs de la composante verte correspond aux valeurs
    // stockes aux indices sont congrus � 1 mod 3, ...
    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < taille; j++)
        {
            red[i][j] = mypixels[3*j + 3*taille*i];
            green[i][j] = mypixels[3*j + 1 + 3*taille*i];
            blue[i][j] = mypixels[3*j + 2 + 3*taille*i];
        }
    }

    // Informations � l'utilisateur pour dire que tout s'est bien pass�
    cout << " L'image " << name << " a bien ete chargee dans les tableaux ." << endl;

    // On lib�re la m�moire que l'on avait attribu� � mypixels : vous verrez ces notions plus tard dans l'ann�e
    delete mypixels;
    // On ferme le fichier que l'on vient de lire
    in.close();
    // On remet � nouveau l'entr�e standard sur la console
    cin.rdbuf(oldbuf);
}

// writePicture : prend 3 tableaux 2D, leur taille effective (identique pour les 3),
// cr�e une image au format ppm � partir des donn�es de ces tableaux, et l�enregistre
// dans un fichier.
// param�tres (D) tabR, tabB, tabG : tableaux [0,MAX-1][0,MAX-1] d�entiers
//		 (D) taille : entier
//		 (D) image : cha�ne de caract�res
void writePicture(const int red[][MAX], const int green[][MAX], const int blue[][MAX], int taille, string name)
{
    // D�claration des variables
    ofstream out;
    streambuf* oldbuf;

    // Initialisation des variables
    /*On redirige la sortie standard sur le fichier portant le nom name.
    De cette mani�re, lorsque l'on fera appel � cout, la sortie sera �crite dans le fichier portant le nom name et non pas sur la console */
    // ouverture (voire cr�ation) du fichier portant le nom name pour �crire les donn�es
    out.open(name.c_str( ));
    // redirection de la sortie standard (cout) vers le fichier image.
    oldbuf = std::cout.rdbuf(out.rdbuf());

    // On v�rifie que le fichier a bien �t� cr�e
    if (!out)
    {
        cerr << "Impossible de creer le fichier " << name << " ! " << endl;
    }

    else
    {
        // Cr�er le format, la largeur (les param�tres qui ne sont pas dans le tableau
        // Ecriture du nombre d�finissant le format. On n'utilise que le codage ASCII
        cout << "P3" << endl;
        // Ecriture d'un commentaire (pour calquer au format de Gimp)
        cout << "# Created by IUT d'Informatique d'Orsay Team" << endl;
        // Ecriture des dimensions
        cout << taille << ' ' << taille << endl;
        // Ecriture de la valeur maximale : cette valeur vaut toujours 255 avec le codage RGB
        cout << 255 << endl;

        // Ecriture des donn�es, qui se trouvent dans les tableaux fournis par l'utilisateur
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

        // Informations � l'utilisateur pour dire que tout s'est d�roul� correctement
        cout << "L'image " << name << " a bien ete cree sur votre disque. " << endl;
    }
}
