//Борин Павел

#pragma once
class IStm {
public:
	virtual void Execute() = 0;
	virtual ~IStm() {};
};

class IExp {
public:
	virtual double Execute() = 0;
	virtual ~IExp() {};
};