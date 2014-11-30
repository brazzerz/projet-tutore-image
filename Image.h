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
	void rotation90();
	void rotation270();//Bonus
	void melimelo();//Bonus
	void symetriecentrale();//Bonus
	void write(string output);
};
