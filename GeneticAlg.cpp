#include"GeneticAlg.h"
#include "Function.h"
#include <iterator>
#include <algorithm>

std::random_device rd;
std::mt19937 gen(rd());

void draw_hat()
	{
		std::cout<<std::left<<std::setprecision(4)<<"|"<<std::setw(9)<<"genereation"<<"|"<<std::setw(6)<<"prefix"<<" | "<<std::setw(10)<<"X"<<" | "<<std::setw(10)<<"Y"<<" | "<<std::setw(10)<<"FIT"<<" |"<<std::setw(10)<<"max element"<<" |  "<<std::setw(9)<<"average"<<" |\n";
	}

void GeneticAlgorithm::init_gen(size_t count_of_parents)
	{
		std::uniform_real_distribution<double> x_border (border.first.a,border.first.b);
		std::uniform_real_distribution<double> y_border (border.second.a,border.second.b);
		
		parents.clear();

		point temp_point;

		for (size_t count = 0u;count < count_of_parents;++count)
			{
				temp_point.x = x_border(gen);
				temp_point.y = y_border(gen);
				temp_point.z = F(temp_point.x,temp_point.y);

				parents.insert({temp_point.z,temp_point});
			}
	}

void GeneticAlgorithm::selection()
	{
		intermidiate_generation.clear();

		point temp_point;

		for(auto index = parents.begin();index != parents.end();++index)
			{
				/* 
					“ак как потомок может иметь что-то от каждого из радителей, то € сделал следующее:
					у 2 родителей могут быть 2 потомка с координитами (x1,y2,f(x1,y2)) и (x2,y1,f(x2,y1)),
					где (x1,y1) - координаты 1 родител€, (x2,y2) - координаты 2 родител€.
				*/
				for(auto index_2 = std::next(index);index_2 != parents.end();++index_2)
					{
						// 1)
						temp_point.x = index->second.x;
						temp_point.y = index_2->second.y;
						temp_point.z = F(temp_point.x,temp_point.y);

						intermidiate_generation.insert({temp_point.z,temp_point});
						// 2)
						temp_point.x = index_2->second.x;
						temp_point.y = index->second.y;
						temp_point.z = F(temp_point.x,temp_point.y);

						intermidiate_generation.insert({temp_point.z,temp_point});
					}
			}
	}

void GeneticAlgorithm::reduction()
	{
		for (auto temp : intermidiate_generation)
			{
				parents.insert(temp);	
			}
		intermidiate_generation.clear();

		size_t temp = parents.size() - 4;
		for (size_t index = 0u;index < temp;++index)
			{
				parents.erase(parents.begin());	
			}
	}

void GeneticAlgorithm::mutation()
	{
		/*
			«аметка:
			ћутаци€ в данной реализации генного алгоритма выгл€дит следующим образом:
			беретс€ координата точки x и рандомно сдвигаетс€ и также с y координатой.
		*/
		std::uniform_real_distribution<double> delta(-0.3,0.3);

		std::multimap<double, point> temp_multimap;

		for (auto parent = parents.begin();parent != parents.end();++parent)
			{
				parent->second.x += delta(gen);
				parent->second.y += delta(gen);

				if (parent->second.x < border.first.a)
					{
						parent->second.x = border.first.a;
					}
				else if (parent->second.x > border.first.b)
					{
						parent->second.x = border.first.b;
					}
				if (parent->second.y < border.second.a)
					{
						parent->second.y = border.second.a;
					}
				else if (parent->second.y > border.second.b)
					{
						parent->second.y = border.second.b;
					}
				parent->second.z = F(parent->second.x,parent->second.y);
				temp_multimap.insert({parent->second.z,parent->second});
			}
		parents = temp_multimap;
		temp_multimap.clear();

		for (auto child = intermidiate_generation.begin();child != intermidiate_generation.end();++child)
			{
				child->second.x += delta(gen);
				child->second.y += delta(gen);
				if (child->second.x < border.first.a)
					{
						child->second.x = border.first.a;
					}
				else if (child->second.x > border.first.b)
					{
						child->second.x = border.first.b;
					}
				if (child->second.y < border.second.a)
					{
						child->second.y = border.second.a;
					}
				else if (child->second.y > border.second.b)
					{
						child->second.y = border.second.b;
					}
				child->second.z = F(child->second.x,child->second.y);
				temp_multimap.insert({child->second.z,child->second});
			}
		intermidiate_generation = temp_multimap;
		temp_multimap.clear();
	}

void GeneticAlgorithm::pass()
	{
		double P = 0.0;
		std::uniform_real_distribution<double> Probability(0.0,0.1);

		draw_hat();
		init_gen();
		print(0u,parents,"p");
		selection();
		reduction();
		std::cout<<"\n";
		
		for (size_t iteration = 1u;iteration <= max_generations - 1u ;++iteration)
			{
				P += Probability(gen);
				// std::cout<<P<<"\n"; // Debug
				selection();
				if (P > 0.5)
					{
						mutation();
						P = 0.0;
					}
				print(iteration, parents,"p");
				print(iteration, intermidiate_generation, "ig",true);
				reduction();
				std::cout<<"\n";
			}
		print(max_generations,parents,"result");
	}

void GeneticAlgorithm::print(size_t genereation,std::multimap<double,point> multimap, std::string prefix,bool border)
	{
		if (border)
			{
				std::cout<<" ";
				for (int index = 1;index < 85;++index)
					{
						std::cout<<"-";
					}
				std::cout<<"\n";
			}

		double average = 0.0;

		for (auto tochka: multimap)
			{
				average +=tochka.second.z;
			}

		average=average/multimap.size();	

		auto max_element = std::max_element(multimap.begin(),multimap.end(),
											 [](std::pair<double,point> var1,std::pair<double,point> var2)
												 {
													return var1.first < var2.first;
												 }
		);

		for (auto tochka = multimap.begin();tochka != multimap.end();++tochka)
			{
				std::cout<<std::left<<std::setprecision(4)<<"|  "<<std::setw(9)<<genereation<<"|"<<std::setw(6)<<' '+prefix<<" | "<<std::setw(10)<<tochka->second.x<<" | "<<std::setw(10)<<tochka->second.y<<" | "<<std::setw(10)<<tochka->second.z;
				if (tochka == std::prev(multimap.end()))
					{
						std::cout<<" | "<<std::setw(10)<<max_element->first<<" | "<<std::setw(10)<<average<<" |";
					}
				else
					{
						std::cout<<" | "<<std::setw(10)<<"          "<<" | "<<std::setw(10)<<"          "<<" |";
					}
				std::cout<<"\n";
			}

		if (border)
			{
				std::cout<<" ";
				for (int index = 1;index < 85;++index)
					{
						std::cout<<"-";
					}
				std::cout<<"\n";
			}
	}