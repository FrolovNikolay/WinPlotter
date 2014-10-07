//Борин Павел
#include <string>
#include "IStmExp.h"
#include "Enums.h"
#include <map>
#include <math.h>


//Exp = Exp
class AssignStm: public IStm {
public:
	AssignStm( std::map< const char, double >::iterator _lval, IExp* _rval ): lval( _lval ), rval( _rval ) {};
	void Execute() 
	{
		lval->second = rval->Execute();
	}
private:
	IExp *rval;
	std::map< const char, double >::iterator lval;
};

//Exp BinOp Exp
class OpExp: public IExp {
public:
	OpExp( IExp* _lval, IExp* _rval, BINOP _mval ):
		lval( _lval ), rval( _rval ), oper( _mval ) 
	{};
	double Execute() 
	{
		switch( oper ) {
		case PLUS:
			return lval->Execute() + rval->Execute();
		case MINUS:
			return lval->Execute() - rval->Execute();
		case TIMES:
			return lval->Execute() * rval->Execute();
		case DIV:
			return lval->Execute() / rval->Execute();
		case POWER:
			return std::pow( lval->Execute(), rval->Execute() );
		}
	};
private:
	IExp *lval, *rval;
	BINOP oper;
};

//id
class IdExp: public IExp {
public:
	IdExp( std::map< const char, double >::iterator iter ): variable( iter ) {};
	double Execute()
	{
		return variable->second;
	}
	std::map< const char, double >::iterator variable;
private:
	
};

//num
class NumExp: public IExp {
public:
	NumExp( const double _value ): value( _value ) {}
	double Execute()
	{
		return value;
	};
private:
	double value;
};

//sin, cos ... +sqrt
class TrigonExp: public IExp {
public:
	TrigonExp( IExp* _val, FUNC _func): val( _val ), func( _func ) {};
	double Execute() 
	{
		switch( func ) {
		case SIN:
			return std::sin( val->Execute() );
		case COS:
			return std::cos( val->Execute() );
		case SQRT:
			return std::sqrt( val->Execute() );
		case TG:
			return std::tan( val->Execute() );
		case CTG:
			return 1 / std::tan( val->Execute() );
		}
		
	};
private:
	FUNC func;
	IExp* val;
};

//(Exp)
class BracketExp: public IExp {
public:
	BracketExp( IExp* _val);
	double Execute();
private:
	IExp* val;
};