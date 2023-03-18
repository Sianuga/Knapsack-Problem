#pragma once
#include <string>
#include <vector>
#include "Item.h"

class GAProblem
{
	public:
		GAProblem();
		~GAProblem();

		
	bool isConfigured();
	int getNumberOfItems();
	double getCapacity();
	
	virtual bool configureProblem(int numberOfItems, int capacity, double* volumes, double* qualities) = 0;
	virtual bool configureProblem(std::string filePath) = 0;
	virtual double calculateQuality(std::vector<bool> genotype) = 0;
	virtual double calculateVolume(std::vector<bool> genotype) = 0;

	protected:
		
		int _numberOfItems;
		double _capacity;
		item* _items;
		bool _configured;
};