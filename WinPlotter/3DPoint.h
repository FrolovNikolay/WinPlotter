#pragma once

// Структура, задающая точку в трёхмерном пространстве (вектор-строка)
struct C3DPoint
{
public:
	double X, Y, Z;

	C3DPoint(double _x = 0, double _y = 0, double _z = 0);

	// Сумма векторов
	C3DPoint operator+(C3DPoint other) const;

	// Разность векторов
	C3DPoint operator-(C3DPoint other) const;

	// Вектор на множитель
	C3DPoint operator*(double value) const;

	// Длина вектора
	double length() const;

	// Возвращает нормализованный вектор
	C3DPoint normalize() const;
	class NullLength {
	};

	// Векторное произведение
	C3DPoint cross(C3DPoint other) const;

	// Скалярное произведение
	double dot(C3DPoint other) const;
};

