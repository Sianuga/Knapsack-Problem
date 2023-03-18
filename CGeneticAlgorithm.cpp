#include "CGeneticAlgorithm.h"




std::random_device CGeneticAlgorithm::rd;
std::mt19937 CGeneticAlgorithm::gen(CGeneticAlgorithm::rd());
std::uniform_int_distribution<> CGeneticAlgorithm::disRand(0);






CGeneticAlgorithm::CGeneticAlgorithm()
{
	_crossOverProbability = 0;
	_genotypeLength = 0;
	_mutationProbability = 0;
	_populationSize = 0;
	_bestQuality = 0;
	_GAProblem = NULL;
	_configured = false;
}

CGeneticAlgorithm::~CGeneticAlgorithm()
{

	for (int i = 0; i < _population.size(); i++)
	{
		delete _population[i];
	}

	_population.clear();
}

bool CGeneticAlgorithm::configureRun(int populationSize, double mutationProbability, double crossOverProbability, GAProblem* GAProblem)
{
	if (populationSize >= 0 > 0 && mutationProbability <= 1 && mutationProbability>=0 && crossOverProbability <= 1 && crossOverProbability>=0)
	{
		_populationSize = populationSize;
		_genotypeLength = GAProblem->getNumberOfItems();
		_mutationProbability = mutationProbability;
		_crossOverProbability = crossOverProbability;
		_GAProblem = GAProblem;
	}
	else
	{
		return false;
	}

	_configured = true;
	return true;

}

void CGeneticAlgorithm::run(int numberOfIterations)
{

	
	if(_configured && _GAProblem->isConfigured())
	{

		generatePopulation();
		_bestQuality = 0;
		_bestGenotype = std::vector<bool>(_genotypeLength, false);

		for (int i = 0; i < numberOfIterations; i++)
		{
			processSingleGeneration();
		}

		_bestGenotype = getBestGenotype();
		_bestQuality = _GAProblem->calculateQuality(_bestGenotype);
	}
	
	else
	{
		std::cout << "Genetic algorithm or problem is not configured" << std::endl;
	}

}


void CGeneticAlgorithm::generatePopulation()
{
	resetPopulation();

	for (int i = 0; i < _populationSize; i++)
	{
		CIndividual* cIndividual = new CIndividual(_genotypeLength);
		cIndividual->calculateFitness(_GAProblem);
		_population.push_back(cIndividual);
	}
}

void CGeneticAlgorithm::resetPopulation()
{
	for (int i = 0; i < _population.size(); i++)
	{
		delete _population[i];
	}

	_parents.first = NULL;
	_parents.second = NULL;
	_children.first = NULL;
	_children.second = NULL;
	
	_population.clear();
	_population.reserve(_populationSize);
}



void CGeneticAlgorithm::processSingleGeneration()
{
	std::vector<CIndividual*> newPopulation;
	
	newPopulation.reserve(_populationSize);


	
	for(int i=0;i<_populationSize;i++)
	{
		_parents.first = drawAndSelectFitterIndiv();
		_parents.second = drawAndSelectFitterIndiv();


		if (crossOverDraw())
		{
			_children = (_parents.first->crossOver(_parents.second));
		}
		else
		{
			_children.first = new CIndividual(_parents.first);
			_children.second = new CIndividual(_parents.second);
		}

		_children.first->mutate(&_mutationProbability);
		_children.second->mutate(&_mutationProbability);

		_children.first->calculateFitness(_GAProblem);
		_children.second->calculateFitness(_GAProblem);
		
	
			newPopulation.push_back(_children.first);
			newPopulation.push_back(_children.second);
		}
	




	resetPopulation();
	_population = newPopulation;
}

std::vector<bool> CGeneticAlgorithm::getBestGenotype()
{


	double individualValue;

	for (CIndividual* individual : _population)
	{
		individualValue = _GAProblem->calculateQuality (individual->getGenotype());

		if (_bestQuality < individualValue)
		{
			_bestQuality = individualValue;
			_bestGenotype = individual->getGenotype();
		}
	}

	return _bestGenotype;
}



bool CGeneticAlgorithm::crossOverDraw()
{
	double randomChance;

		randomChance = (1.0) / (double)((disRand(gen))% 1000);


		if (randomChance <= _crossOverProbability)
		{
			return true;
		}
		else
		{
			return false;
		}
	
}


CIndividual* CGeneticAlgorithm::getRandomIndiv()
{
	return _population[disRand(gen) % _populationSize];
}

CIndividual* CGeneticAlgorithm::drawAndSelectFitterIndiv()
{
	CIndividual* competitor1=getRandomIndiv();
	CIndividual* competitor2=getRandomIndiv();

	if (competitor1 >= competitor2)
	{
		return competitor1;
	}
	else
	{
		return competitor2;
	}

}

double CGeneticAlgorithm::getBestQuality()
{
	return _bestQuality;
}


bool CGeneticAlgorithm::isConfigured()
{
	return _configured;
}


void CGeneticAlgorithm::printBestResult ()
{
	std::cout << "/////////////////////////////////" << std::endl;
	std::cout << "Simulation parameters:" << std::endl;
	std::cout << "Population size: " << _populationSize << std::endl;
	std::cout << "Mutation probability: " << _mutationProbability << std::endl;
	std::cout << "Cross over probability: " << _crossOverProbability << std::endl;
	std::cout << "Problem parameters:" << std::endl;
	std::cout << "Number of items: " << _GAProblem->getNumberOfItems() << std::endl;
	std::cout << "Capacity: " << _GAProblem->getCapacity() << std::endl << std::endl;
	std::cout << "Best result:" << std::endl;
	

	
	std::cout << "Best quality: " << _bestQuality << std::endl;
	std::cout << "Best genotype: " << std::endl;

	
	for (int i = 0; i < _bestGenotype.size(); i++)
	{
		std::cout << _bestGenotype[i];
	}

	std::cout << std::endl;

	std::cout << "Capacity taken: " << _GAProblem->calculateVolume(_bestGenotype) << std::endl;
	

	std::cout << "/////////////////////////////////" << std::endl <<std::endl;
}