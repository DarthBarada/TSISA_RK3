#pragma once
#include <cmath>

/**
* @brief Функция f(x,y), написанная согласно варианту 10
* 
* @param[in] x Координата x 
* @param[in] y Координата у
* 
* @return Значение функции f(x,y)
*
*/
double F(double x,double y)
	{
		return pow(sin(x),2.0)/(1+pow(x,2.0)+pow(y,2.0));
	}