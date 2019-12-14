#pragma once
#include <cmath>

/**
* @brief ������� f(x,y), ���������� �������� �������� 10
* 
* @param[in] x ���������� x 
* @param[in] y ���������� �
* 
* @return �������� ������� f(x,y)
*
*/
double F(double x,double y)
	{
		return pow(sin(x),2.0)/(1+pow(x,2.0)+pow(y,2.0));
	}