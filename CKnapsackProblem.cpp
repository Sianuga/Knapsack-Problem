#include "CKnapsackProblem.h"








CKnapsackProblem::CKnapsackProblem()
{

}

CKnapsackProblem::~CKnapsackProblem()
{
	

		
}

bool CKnapsackProblem::configureProblem(int numberOfItems, int knapsackCapacity, double* weights, double* values)
{
	if (numberOfItems >= 0 && knapsackCapacity >= 0)
	{
		_numberOfItems = numberOfItems;
		_capacity = knapsackCapacity;
		_items = new item[numberOfItems];
		
	
		for (int i = 0; i < numberOfItems; i++)
		{
		
				_items[i]._volume= weights[i];
				_items[i]._value = values[i];
		}
		
		_configured = true;
		return true;
		
	}




		return false;
}


double CKnapsackProblem::calculateQuality(std::vector<bool> genotype)
{
	double value = 0;
	
	for (int i = 0; i < genotype.size(); i++)
	{
		if (genotype[i])
		{
			value += _items[i]._value;
		}

	}
	
	if (calculateVolume(genotype) > _capacity)
		value = 0;
	
	return value;
}

double CKnapsackProblem::calculateVolume(std::vector<bool> genotype)
{
	double weight = 0;

	for (int i = 0; i < genotype.size(); i++)
	{
		if (genotype[i])
		{
			weight += _items[i]._volume;
		}

	}

	return weight;
}



bool CKnapsackProblem::configureProblem(std::string filepath)
{
	std::fstream file(filepath, std::fstream::in);
	
	if (file.is_open())
	{
		file >> _numberOfItems >> _capacity;

		if (_numberOfItems <= 0 || _capacity <= 0)
			return false;
		
		_items = new item[_numberOfItems];

		for (int i = 0; i < _numberOfItems; i++)
		{
			file >>_items[i]._value; 

			if (file.eof())
			{
				std::cout << "Number of items does not match number of lines in file" << std::endl;
				return false;
			}
				
			
			file >> _items[i]._volume;


		}
		file.close();
	}
	else
	{
		std::cout << "Error opening file" << std::endl;
		return false;
	}
	
	_configured = true;
	return true;
}

