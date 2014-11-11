#pragma once 

#include <iostream>
#include <vector>
#include "3DPoint.h"
#include "CFormula.h"
#include "FormulaParser.h"
#include <cassert>

class CGraphBuilder {
public:
	//eps-точность шага сетки
	CGraphBuilder() : eps( 1 ),
	 	leftBound( -10. ), rightBound( 10. ) { }
	bool buildPointGrid( const std::string& data );
	const std::vector< C3DPoint >& GetPoints() const { return points; }
	const std::vector< std::pair< int, int > >& GetSegments() const { return segments; }
private:
	double eps;
	//если выяснится, что функция параметрическая, то можно выставить диапазон параметров.
	double leftBound; 
	double rightBound; 
	std::vector< C3DPoint > points;
	std::vector< std::pair< int, int > > segments;
};