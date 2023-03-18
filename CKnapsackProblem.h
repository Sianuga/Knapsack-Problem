#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Item.h"
#include "GAProblem.h"




class CKnapsackProblem :public GAProblem
{
public:
	CKnapsackProblem();
	~CKnapsackProblem();

	bool configureProblem(int numberOfItems, int knapsackCapacity, double* weights, double* values);
	bool configureProblem(std::string filepath);
	double calculateQuality(std::vector<bool> genotype); 
	double calculateVolume(std::vector<bool> genotype);


};



