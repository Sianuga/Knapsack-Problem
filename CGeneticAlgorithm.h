#pragma once
#include <vector>
#include "CIndividual.h"
#include "GAProblem.h"

class CGeneticAlgorithm
{
public:
	CGeneticAlgorithm();
	~CGeneticAlgorithm();

	bool configureRun(int populationSize, double mutationProbability, double crossOverProbability, GAProblem* GAProblem);
	void run(int numberOfIterations);

	
	std::vector<bool> getBestGenotype();
	double getBestQuality();
	void printBestResult();

	bool isConfigured();

private:

	void generatePopulation();
	void resetPopulation();
	void processSingleGeneration();
	bool crossOverDraw();
	CIndividual* getRandomIndiv();
	CIndividual* drawAndSelectFitterIndiv();





	static std::random_device rd;
	static std::mt19937 gen;
	static std::uniform_int_distribution<> disTF;
	static std::uniform_int_distribution<> disRand;
	double _mutationProbability;

	double _crossOverProbability;
	int _genotypeLength;
	int _populationSize;
	GAProblem* _GAProblem;
	std::vector<CIndividual*> _population;


	std::pair<CIndividual*, CIndividual*> _parents;
	std::pair<CIndividual*, CIndividual*> _children;

	double _bestQuality;
	std::vector<bool> _bestGenotype;

	bool _configured;
	
};






