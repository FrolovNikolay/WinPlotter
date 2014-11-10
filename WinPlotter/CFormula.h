//Борин Павел
//класс формулы- его представление деревом + вычисление
#include <iostream>
#include <vector>
#include <map>
#include "IStmExp.h"
#include <sstream>
#include "Enums.h"
#include <list>
#include <string>

class CFormula {
public:
	CFormula();
	~CFormula();

	//установить мелкость разбиения
	void SetEpsilon( double _epsi ) { epsi = _epsi; }
	//вычисляет что-то, будет изменено
	std::map< char, std::vector< double > > Calculate();
	//устанавливает формулу
	bool SetFormula(const std::string& inputFormula);
	//есть ли, среди переменных t
	bool IsVarTIn();
	//получить количество переменных
	int GetCountOfVariables();
	//получить имя переменной по порядку 0..GetCountOfVariables()-1
	char GetNameOfVariable(int index);
	//есть ли такая переменная в формуле
	bool IsVarCHIn(char ch);
	//установить диапазон для переменной по имени
	void SetDiapForVariable(char name, double min, double max);
	//получить все зависимости
	inline const std::vector< char >& GetDependecies() { return dependecies; };


private:

	struct Operator {
		Operator(BINOP _oper, int _priority);
		BINOP oper;
		int priority;
	};
	struct metaData {
		std::vector< IExp* > expStack;
		std::vector< const Operator > opStack;
		std::stringstream buffer;
	};
	enum { DELTA = 1 };
	//вектор зависимостей, нужен временно
	std::vector< char > dependecies;
	std::map< char, std::vector< char > > allDepend;
	//диапазоны для переменных
	std::map< char, std::pair< double, double > > diapasons;
	//вектор древосного представления для каждой формулы
	std::map< char, IStm* > startPoint;
	std::string formulaStr;
	//переменные
	std::map< char, double > variables;
	double epsi;
	//функция представляет формулу в качестве синтаксического дерева
	void parseFormula(const std::string& inputFormula, metaData& metData);
	//вспомогательная функция, созданная для проверки буффера, возвращает true, если в буффере находится полная конструкция функции или символа
	bool checkBuffer(int& index, const std::string& inputFormula, metaData& mD);
	//
	void binOpFunc(int priority, BINOP oper, metaData& mD);

	//уничтожить формулу с очисткой памяти
	void destroyTree();

	bool setIteration(const std::map< char, int >& iterCount, std::vector< int >& curIter);

	void mathFuncAdd(FUNC func, int& index, const std::string& inputFormula, metaData& mD);

	void addIndependVariables(std::map< char, std::vector< double > >& result, char variab);

	void analyzeDependencies(char ch);
};