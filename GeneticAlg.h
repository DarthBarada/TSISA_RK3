#pragma once
#include <map>
#include <random>
#include <iostream>
#include <iomanip>
#include <string>

struct point
	{
		double x; // ���������� x
		double y; // ���������� y
		double z; // ���������� z

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
		double a;	// ������ �������
		double b;	// ������� �������

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
		*	������� ������ ��� ��������� x � y			
		*/
		std::pair<borders,borders> border{{0.0,2.0},{-2.0,2.0}};
		/**
		*	��������	
		*/
		std::multimap<double,point> parents;
		/**
		*	������������� ���������
		*/
		std::multimap<double,point> intermidiate_generation;
		/**
		*	������������ ���������� ���������
		*/
		size_t max_generations;

		public:

		GeneticAlgorithm(size_t generations = 100u,std::pair<borders,borders> input_border = {{0.0,2.0},{-2.0,2.0}})
			{
				max_generations = generations;
				border = input_border;
			}
		/**
		* @brief ������� ������������ ��� ������� ����������� ������������� ���������
		*
		*/
		void pass();
		/**
		* @brief ������� ������������ ��� �������� 0 ���������
		*
		* @param[in] count_of_parents ���������� ���������
		*
		*/
		void init_gen(size_t count_of_parents = 4u);
		/**
		* @brief �������, ����������� ��������
		*
		*/
		void selection();

		/**
		* @brief �������, ����������� �������
		*
		*/
		void mutation();

		/**
		* @brief �������, ����������� ��������
		*
		*/
		void reduction();

		/**
		* @brief ������� ��� ������ multimap
		*
		* @param[in] multimap ��������� std::multimap<double,point>
		* @param[in] prefix ������� ����� �������
		* @param[in] up_border ������ ������� ������ � �����, ���� �������� true
		*
		*/
		void print(size_t genereation, std::multimap<double,point> multimap, std::string prefix = "", bool border = true);
	};