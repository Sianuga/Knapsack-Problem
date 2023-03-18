#pragma once

#include <vector>
#include <utility>
#include <random>
#include <iostream>
#include "CKnapsackProblem.h"

class CIndividual
{
	
public:

	CIndividual();
	
	CIndividual(int genotypeLength);

	CIndividual(CIndividual* parent1, CIndividual* parent2,int cutIndex);

	CIndividual(CIndividual* other);

	void calculateFitness(GAProblem* problem);

	void mutate(double* mutationProbability);

	bool operator>=(CIndividual* other);



	std::pair<CIndividual*, CIndividual*> crossOver(CIndividual* other);


	void printGenotype();
	std::vector<bool> getGenotype();
	int getGenotypeSize();

	
private:


	
	std::vector<bool> _genotype;
	double _fitnessLevel;
	
	static std::random_device rd;
	static std::mt19937 gen;
	static std::uniform_int_distribution<> disTF;
	static std::uniform_int_distribution<> disRand;
	

	
};




