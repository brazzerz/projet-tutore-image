#include <iostream>
#include <string>
#include "manipFichier.h"

class Image{
private:
	int red_[MAX][MAX];
	int green_[MAX][MAX];
	int blue_[MAX][MAX];
	int taille_;
	int red_1[MAX][MAX];
	int green_1[MAX][MAX];
	int blue_1[MAX][MAX];
	int red_2[MAX][MAX];
	int green_2[MAX][MAX];
	int blue_2[MAX][MAX];
public:
	Image(string);
	void clone1();
	void clone2();
	void inversevert();
	void inversehor();
	void binarisation();
	void negatif();
	void rotation90();
	void rotation270();//Bonus
	void melimelo();//Bonus
	void symetriecentrale();//Bonus
	void write(string output);
	void rotation();
	void flou();
	void noir();
	void filtre3();
	void filtre4();
};