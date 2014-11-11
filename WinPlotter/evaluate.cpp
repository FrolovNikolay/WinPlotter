#pragma once
#include <queue>
#include <utility>
#include "evaluate.h"
#include <sstream>
#include <regex>
#include <vector>

//первая строка формула, вторая отрезок параметров в виде аргумент 
//<var>=[<left>;<right>]'\n'
bool CGraphBuilder::buildPointGrid( const std::string& data )
{
	try {
		std::stringstream ss;
		for( auto &item : data ) {
			if( item != '\r' ) {
				ss << item;
			}
		}
		std::string strFormula, argument;
		std::map<char, std::pair< double, double > > args;
		std::getline( ss, strFormula, '\n' );
		std::regex argRegex( "(t|l|x|y|z)=\\[([\\-+]?[0-9]*\\.?[0-9]+)(;)([\\-+]?[0-9]*\\.?[0-9]+)\\]" );
		while( std::getline( ss, argument ) ) {
			if( !std::regex_match( argument, argRegex ) ) {
				return false;
			} else {
				int firstArgEnd = 3;
				while( argument[firstArgEnd] != ';' ) {
					firstArgEnd++;
				}
				int secondArgEnd = firstArgEnd;
				while( argument[secondArgEnd] != ']' ) {
					secondArgEnd++;
				}
				double lb = std::stod( argument.substr( 3, firstArgEnd - 3 ) ); //left bound from arg template
				double rb = std::stod( argument.substr( firstArgEnd + 1, secondArgEnd - firstArgEnd ) ); //right bound arg template
				args[argument[0]] = std::make_pair( lb, rb );
			}
		}

		CFormula formula = ParseFormula( strFormula );
		std::vector< char > vars = formula.GetVariables();
		for( int i = 0; i < vars.size(); i++ ) {
			if( args.find( vars[i] ) == args.end() ) {
				args[vars[i]] = std::make_pair( leftBound, rightBound );
			}
		}

		std::map< char, double > argToCount;
		if( vars.size() == 1 ) { //TODO это быдлокод надо написать без 2х if-в, т.е. просто задать обход сетки. 
			for( double gridAxis = args[vars[0]].first; gridAxis < args[vars[0]].second; gridAxis += eps ) {
				argToCount[vars[0]] = gridAxis;
				auto result = formula.Calculate( argToCount );
				points.push_back( C3DPoint( result['x'], result['y'], result['z'] ) );
				if( points.size() > 2 ) {
					segments.push_back(std::make_pair(points.size() - 1, points.size() - 2) );
				}
			}
		} else if( vars.size() == 2 ) {
			for( double gridAxis1 = args[vars[0]].first; gridAxis1 < args[vars[0]].second; gridAxis1 += eps ) {
				int iterNumber = 0;
				for( double gridAxis2 = args[vars[1]].first; gridAxis2 < args[vars[1]].second; gridAxis2 += eps ) {
					iterNumber++;
					argToCount[vars[0]] = gridAxis1;
					argToCount[vars[1]] = gridAxis2;
					auto result = formula.Calculate( argToCount );
					iterNumber++;
					points.push_back( C3DPoint( result['x'], result['y'], result['z'] ) );
					if( points.size() > 2 ) {
						//соединяем все точки, которые лежат на одной прямой, параллельной оси сетки.
						segments.push_back( std::make_pair( points.size() - 1, points.size() - 2 ) );
					}
				}
				//if( points.size() > 0 ) {
				//	for( int p = 1; p < iterNumber; p++ ) {
				//		segments.push_back( std::make_pair( points.size() - 1 - p, points.size() - 1 - p * 2) );
				//	}
				//}
			}
		} else {
			return false;
		}

	} catch( std::exception& e ) {
		return false;
	}

	return true;
}