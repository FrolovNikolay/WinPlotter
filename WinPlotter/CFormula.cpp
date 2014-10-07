//Борин Павел
#include "StmExpRealis.h"
#include "CFormula.h"
#include <iostream>
#include <string>
#include <assert.h>

CFormula::CFormula(): epsi( 0.1 ) {};
CFormula::~CFormula() {};

CFormula::Operator::Operator( BINOP _oper, int _priority ): 
	oper(_oper),
	priority(_priority) 
{
}

/*std::map< char, std::vector< double > > CFormula::Calculate()
{
	auto iter = startPoint.begin();
	//zasipau AAAAAAAAAAAAAA SORRY
};*/

void CFormula::SetEpsilon( double _epsi ) 
{
	epsi = _epsi;
};

bool CFormula::SetFormula( const std::string& inputFormula )
{
	std::stringstream sstream;
	sstream << inputFormula;
	while( !sstream.eof() ) {
		std::string strBuffer;
		std::getline( sstream, strBuffer );
		metaData metData;
		parseFormula( strBuffer, metData );
		IExp* rval = metData.expStack[ metData.expStack.size() - 1 ];
		metData.expStack.pop_back();
		IExp* lval = metData.expStack[ metData.expStack.size() - 1 ];
		IdExp* lvalIn = static_cast< IdExp* >( lval ); //?
		analyzeDependencies( lvalIn->variable->first );
		if( lvalIn != NULL ) {
			startPoint[ lvalIn->variable->first ] = new AssignStm( lvalIn->variable, rval );//non checked zasipau
		} else {
			assert( "THERE IS A PROBLEM" );
		}
	}
	return true; // ?
}

void CFormula::analyzeDependencies( char ch )
{
	for( int i = 0; i < dependecies.size(); ++i ) {
		if( dependecies[i] != ch ) {
			bool has = false;
			for( auto iter = allDepend[ch].begin(); iter != allDepend[ch].end(); ++iter ) {
				if( (*iter) == dependecies[i] ) {
					has = true;
				}
				if( has == true ) {
					break;
				}
			}
			if( has == false ) {
				allDepend[ch].push_back( dependecies[i] );
			}
		}
	}
	dependecies.clear();
};

bool CFormula::IsVarTIn()
{
	if( variables.find( 't' ) == variables.end() ) {
		return false;
	}
	return true;
};

int CFormula::GetCountOfVariables()
{
	return variables.size();
};

char CFormula::GetNameOfVariable( int index )
{
	if( index >= variables.size() ) {
		return -1;
	}
	auto iter = variables.begin();
	for( int i = 0; i < index; ++i ) {
		++iter;
	}
	return iter->first;
};

//есть ли такая переменная в формуле
bool CFormula::IsVarCHIn( char ch )
{
	if( variables.find( ch ) != variables.end() ) {
		return true;
	}
	return false;
};

//установить диапазон для переменной по имени
void CFormula::SetDiapForVariable( char name, double min, double max )
{
	if( IsVarCHIn( name ) ) {
		diapasons[name] = std::make_pair( min, max ); ///????????????????????????????????<double, double>
	}
};


void CFormula::parseFormula( const std::string& inputFormula, metaData& metData ) 
{
	for( int i = 0; i < inputFormula.size(); ++i ) {
		bool isVar = false; //нужна для того,, чтобы в дефол лишний раз не дописывалась переменная в буффер
		char ch = inputFormula[i];
		if( ch == 'y' || ch == 'x' || ch == 'z' || ch == 't' ) {
			//если символ не является куском имени функции
			metData.buffer << ch;
			if( !checkBuffer( i, inputFormula, metData ) ) {
				isVar = true;
				//заводим переменную и устанавливаем в неё стандартный диапазон от -50 до 50
				variables[ch] = 0;
				diapasons[ch] = std::make_pair< double, double >( -50, 50 );

				dependecies.push_back( ch );//poka ne ponyatno za4em

				metData.buffer.clear();
				IExp* id = new IdExp( variables.find( ch ) );
				metData.expStack.push_back( id );
			}
		}
/*
		if( '0' <= ch && ch <= '9' ) {
			buffer << ch;
		}
*/
		switch( ch ) {
		case '+':
			checkBuffer( i, inputFormula, metData );
			binOpFunc( 1, PLUS, metData );
			break;
		case '-':
			checkBuffer( i, inputFormula, metData );
			binOpFunc( 1, MINUS, metData );
			break;
		case '=':
			metData.opStack.push_back( Operator( EQUAL, 0 ) );
			break;
		case '^':
			checkBuffer( i, inputFormula, metData );
			binOpFunc( 3, POWER, metData );
			break;
		case '/':
			checkBuffer( i, inputFormula, metData );
			binOpFunc( 2, DIV, metData );
			break;
		case '*':
			checkBuffer( i, inputFormula, metData );
			binOpFunc( 2, TIMES, metData );
			break;
		case '(':
			{
				//счетчик скобочной последовательности
				int countBrack = 1;
				for( int j = i + 1; j < inputFormula.size(); ++j ) {
					if( inputFormula[j] == '(' ) {
						countBrack++;
					} else if( inputFormula[j] == ')' ) {
						countBrack--;
					}
					//нашли соотв скобку
					if( countBrack == 0 ) {
						//строку в скобках рекурсивно разбираем
						metaData nD;
						parseFormula( inputFormula.substr( i + 1, j - i - 1 ), nD );
						metData.expStack.push_back( nD.expStack[ nD.expStack.size() - 1 ] );
						nD.expStack.pop_back();
						i = j + 1;
						break;
					}
				}
			}
		default:
			if( !isVar ) {
				metData.buffer << ch;
			}
		}
	}
	int unINT = -1;
	checkBuffer( unINT, inputFormula, metData );
	while( metData.opStack[ metData.opStack.size() - 1 ].oper != EQUAL  && !metData.opStack.empty() ) {
		Operator op = metData.opStack[ metData.opStack.size() - 1 ];
		IExp* exp1 = metData.expStack[ metData.expStack.size() - 1 ];
		metData.expStack.pop_back();
		IExp* exp2 = metData.expStack[ metData.expStack.size() - 1 ];
		metData.expStack.pop_back();
		metData.expStack.push_back( new OpExp( exp2, exp1, op.oper ) );
		metData.opStack.pop_back();
	}
}

void CFormula::binOpFunc( int priority, BINOP oper, metaData& metData )
{
	while( true ) {
		if( metData.opStack[ metData.opStack.size() - 1 ].priority <= priority || metData.opStack.empty() ) {
			metData.opStack.push_back( Operator( oper, priority ) );
			break;
		} else {
			Operator topOper = metData.opStack[ metData.opStack.size() - 1 ];
			IExp* rval = metData.expStack[ metData.expStack.size() - 1 ];
			metData.expStack.pop_back();
			IExp* lval = metData.expStack[ metData.expStack.size() - 1 ];
			metData.expStack.pop_back();
			IExp* newExp = new OpExp( lval, rval, topOper.oper );
			metData.opStack.pop_back();
			metData.expStack.push_back( newExp );
		}
	}
};

//проверить буффер, на наличие в нем
bool CFormula::checkBuffer( int& index, const std::string& inputFormula, metaData& mD ) 
{
	if( mD.buffer.eof() ) {
		return false;
	}
	std::string strBuf;
	mD.buffer >> strBuf;
	//если записано число, считываешьего из буффера и добавляем в стек выражений
	if( strBuf[0] <= '9' && strBuf[0] >= '0' ) {
		mD.buffer.clear();
		mD.buffer << strBuf;
		double num;
		mD.buffer >> num;
		IExp* exp = new NumExp( num );
		mD.expStack.push_back( exp );
		mD.buffer.clear();
		return true;
 	}
	if( index == -1 ) {
		return false;
	}
	if( strBuf == "sin" ) {
		mathFuncAdd( SIN, index, inputFormula, mD );
		return true;
	}
	if( strBuf == "sqrt" ) {
		mathFuncAdd( SQRT, index, inputFormula, mD );
		return true;
	}
	if( strBuf == "cos" ) {
		mathFuncAdd( COS, index, inputFormula, mD );
		return true;
	}
	//tg
	if( inputFormula[index] == 't' && strBuf.size() == 1 && inputFormula[index + 1] == 'g' ) {
		index += 2;
		mathFuncAdd( SIN, index, inputFormula, mD );
		return true;
	}
	//ctg
	if( strBuf == "ct" && inputFormula[ index + 1 ] == 'g' ) {
		index += 2;
		mathFuncAdd( CTG, index, inputFormula, mD );
		return true;
	}
	mD.buffer.clear();
	return false;
}

void CFormula::mathFuncAdd( FUNC func, int& index, const std::string& inputFormula, metaData& mD ) 
{
	mD.buffer.clear();
	if( inputFormula[index] == '(' ) {
		//счетчик скобочной последовательности
		int countBrack = 1;
		for( int j = index + 1; j < inputFormula.size(); ++j ) {
			if( inputFormula[j] == '(' ) {
				countBrack++;
			} else if( inputFormula[j] == ')' ) {
				countBrack--;
			}
			//нашли соотв скобку
			if( countBrack == 0 ) {
				//строку в скобках рекурсивно разбираем
				metaData nD;
				parseFormula( inputFormula.substr( index + 1, j - index - 1 ), nD );
				mD.expStack.push_back( nD.expStack[ nD.expStack.size() - 1 ] );
				nD.expStack.pop_back();
				index = j + 1;
				break;
			}
		}
	}
	IExp* trExp = new TrigonExp( mD.expStack[ mD.expStack.size() - 1 ], func );
	mD.expStack.pop_back();
	mD.expStack.push_back( trExp );
}