//Борин Павел
//класс формулы- его представление деревом

#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include "Operators.h"
#include <list>
#include <string>
#include <memory>

// класс отвечающий за одно уравнение в системе
class CEquation {
public:
	CEquation( char name, IOperator* root );

	// вычислить значение уравнения в данной точке
	double Calculate( const std::map<char, double>& values ) const;
	// имя переменной, которая задается этим уравнением
	char GetResultVariableName() const;

private:
	std::shared_ptr<IOperator> root;

	char result;
};


class CFormula {
public:
	CFormula( int spaceDimension, int plotDimension, const std::vector<char> variables );

	// вычислить формулу в некоторой точке
	std::map<char, double> Calculate( const std::map<char, double>& values ) const;
	
	int GetSpaceDimensions() const;
	int GetPlotDimension() const;
	std::vector<char> GetVariables() const;

	// добавить уравнение к формуле
	void AddEquation( CEquation equation );

private:
	// уравнения, используемые в формуле
	std::vector<CEquation> equations;

	// размерность пространства, в котором строится график (2 - 3)
	int spaceDimension;

	// размерность графика (1 - кривая, 2 - поверхность )
	int plotDimension;

	// имена переменных, от которых зависит формула
	std::vector<char> variables;
};