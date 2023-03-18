#include "CIndividual.h"


std::random_device CIndividual::rd;
std::mt19937 CIndividual::gen(CIndividual::rd());
std::uniform_int_distribution<> CIndividual::disTF(0,1);
std::uniform_int_distribution<> CIndividual::disRand(0);


CIndividual::CIndividual()
{
	_fitnessLevel = 0;
}

CIndividual::CIndividual(int genotypeLength)
{

	_genotype.resize(genotypeLength);
	_fitnessLevel = 0;
	
	for (int i = 0; i < genotypeLength; i++)
	{

		_genotype[i] = disTF(gen);
	}	
}

CIndividual::CIndividual(CIndividual* parent1, CIndividual* parent2, int cutIndex)
{
	_genotype.resize(parent1->_genotype.size());
	_fitnessLevel = 0;

	for (int i = 0; i < _genotype.size(); i++)
	{
		if (i<=cutIndex)
		{
			_genotype[i] = parent1->_genotype[i];
		}
		else
		{
			_genotype[i] = parent2->_genotype[i];
		}
	}
}

CIndividual::CIndividual(CIndividual* other)
{
	_genotype.resize(other->_genotype.size());
	_fitnessLevel = 0;

	for (int i = 0; i < _genotype.size(); i++)
	{
		_genotype[i] = other->_genotype[i];
	}
}

void CIndividual::calculateFitness(GAProblem* problem)
{
	_fitnessLevel = problem->calculateQuality(_genotype);
}


void CIndividual::printGenotype()
{
	for (int i = 0; i < _genotype.size(); i++)
	{
		std::cout << _genotype[i];
	}
	
	std::cout << std::endl;
}

void CIndividual::mutate(double* mutationProbability)
{

	double randomChance;

	
	for (int i = 0; i < _genotype.size(); i++)
	{
		randomChance = (1.0) / (double)((disRand(gen)) % 1000);

		
		if ( randomChance <= *mutationProbability)
		{
			_genotype[i] = !_genotype[i];
		}
		
	}

}

std::pair<CIndividual*,CIndividual*> CIndividual::crossOver(CIndividual* other)
{
	int cutIndex;
	cutIndex = disRand(gen) % _genotype.size();

	CIndividual* childVariantA = new CIndividual(this, other, cutIndex);
	CIndividual* childVariantB = new CIndividual(other, this, cutIndex);
	
	return std::make_pair(childVariantA, childVariantB);
}

int CIndividual::getGenotypeSize()
{
	return (int)_genotype.size();
}


std::vector<bool> CIndividual::getGenotype()
{
	return _genotype;
}


bool CIndividual::operator>=(CIndividual* other)
{
	return _fitnessLevel >= other->_fitnessLevel;
}
