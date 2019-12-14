#include "GeneticAlg.h"

using namespace std;

int main()
	{
		std::cout<<"\t\t\t\t10 generations:\n\n";
		GeneticAlgorithm A(10);
		A.pass();
		std::cout<<"\n\t\t\t\t100 generations:\n\n";
		GeneticAlgorithm B(100);
		B.pass();
		system("pause");
		return 0;
	}
