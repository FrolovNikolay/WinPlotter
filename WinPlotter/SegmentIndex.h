#pragma once

// Структура, хранящая индексы точек начала и конца отрезка
struct CSegmentIndex
{
	int First, Second;
	CSegmentIndex(int first, int second);

	// Исключение, возникающее, когда мы хотим создать отрезок с одинаковыми или отрицательными индексами
	class IncorrectIndex
	{
	};
};

