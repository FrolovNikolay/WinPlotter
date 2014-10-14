//Борин Павел

#pragma once
class IStm {
public:
	virtual void Destruct() = 0;
	virtual void Execute() = 0;
	virtual ~IStm() {};
};

class IExp {
public:
	virtual void Destruct() = 0;
	virtual double Execute() = 0;
	virtual ~IExp() {};
};