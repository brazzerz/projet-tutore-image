#include <iostream>
#include <string>
#include "manipFichier.h"

class Image{
private:
	int red_[MAX][MAX];
	int green_[MAX][MAX];
	int blue_[MAX][MAX];
	int taille_;
public:
	Image(string);
	void load(string input);
	void inversevert();
	void inversehor();
	void binarisation();
	void negatif();
	void symetriecentrale();//Bonus
	void write(string output);
	void rotation();
};
