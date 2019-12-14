#pragma once
#include <map>
#include <random>
#include <iostream>
#include <iomanip>
#include <string>

struct point
	{
		double x; // Координата x
		double y; // Координата y
		double z; // Координата z

		point()
			{
				x = 0.0;
				y = 0.0;
				z = 0.0;
			}
		point(double xval,double yval,double zval = 0.0)
			{
				x = xval;y = yval;z=zval;
			} 
		bool operator!=( point point_2 )
			{
				if ((x != point_2.x) && (y != point_2.y))
					{
						return true;
					}
				return false;
			}
		bool operator==( point point_2 )
			{
				if ((x == point_2.x) && (y == point_2.y))
					{
						return true;
					}
				return false;
			}
	};

struct borders
	{
		double a;	// Нижняя граница
		double b;	// Верхняя граница

		borders()
			{
				a = 0.0;
				b = 0.0;
			}
		borders(double a2,double b2)
			{
				a=a2;
				b=b2;
			}
	};

class GeneticAlgorithm
	{
		protected:
		/**
		*	Область поиска для координат x и y			
		*/
		std::pair<borders,borders> border{{0.0,2.0},{-2.0,2.0}};
		/**
		*	Родители	
		*/
		std::multimap<double,point> parents;
		/**
		*	Промежуточная популяция
		*/
		std::multimap<double,point> intermidiate_generation;
		/**
		*	Максимальное количество поколений
		*/
		size_t max_generations;

		public:

		GeneticAlgorithm(size_t generations = 100u,std::pair<borders,borders> input_border = {{0.0,2.0},{-2.0,2.0}})
			{
				max_generations = generations;
				border = input_border;
			}
		/**
		* @brief Функция используется для полного прохождения генетического алгоритма
		*
		*/
		void pass();
		/**
		* @brief Функция используется для создания 0 генерации
		*
		* @param[in] count_of_parents Количество родителей
		*
		*/
		void init_gen(size_t count_of_parents = 4u);
		/**
		* @brief Функция, описывающая селекцию
		*
		*/
		void selection();

		/**
		* @brief Функция, описывающая мутацию
		*
		*/
		void mutation();

		/**
		* @brief Функция, описывающая селекцию
		*
		*/
		void reduction();

		/**
		* @brief Функция для печати multimap
		*
		* @param[in] multimap Контейнер std::multimap<double,point>
		* @param[in] prefix Префикс перед строкой
		* @param[in] up_border Рисует границу сверху и снизу, если значение true
		*
		*/
		void print(size_t genereation, std::multimap<double,point> multimap, std::string prefix = "", bool border = true);
	};