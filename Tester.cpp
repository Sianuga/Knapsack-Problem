#include "Tester.h"

void Tester::testUnit()
{
	CGeneticAlgorithm genTest;
	CKnapsackProblem knapsackTest, knapsackTest2, knapsackTest3;

	knapsackTest.configureProblem(5, 50,
		new double[5] {42.0, 54.0, 11.0, 12.0, 13.0},
		new double[5] {1.0, 11.0, 23.0, 21.0, 33.0	});


	knapsackTest2.configureProblem("testLong.txt");

	knapsackTest3.configureProblem("testExample.txt");

	genTest.configureRun(10000, 0.1, 0.7, &knapsackTest);
	genTest.run(10);
	genTest.printBestResult();



	genTest.configureRun(1000, 0.15, 0.55, &knapsackTest2);
	genTest.run(50);
	genTest.printBestResult();

	genTest.configureRun(100, 0.2, 0.6, &knapsackTest3);
	genTest.run(1000);
	genTest.printBestResult();


}