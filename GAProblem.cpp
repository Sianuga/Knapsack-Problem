#include "GAProblem.h"


GAProblem::GAProblem()
{
	_capacity = 0;
	_numberOfItems = 0;
	_items = NULL;
	_configured = false;
}


GAProblem::~GAProblem()
{
	if (_items != NULL)
	{
		delete[] _items;
	}
}

bool GAProblem::isConfigured()
{
	return _configured;
}

int GAProblem::getNumberOfItems()
{
	return _numberOfItems;
}

double GAProblem::getCapacity()
{
	return _capacity;
}