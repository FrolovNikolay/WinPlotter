#include "Model.h"

template <typename T>
void CModel<T>::AddSegment(int firstIndex, int secondIndex) {
	if (firstIndex >= Points.size || secondIndex >= Points.size) {
		throw CModel<T>::OutOfRange();
	}
	else {
		Segments.push_back(CSegmentIndex(firstIndex, secondIndex));
	}
}

/*
template <typename T>
void CModel<T>::AddTriangle(int firstIndex, int secondIndex, int thirdIndex) {
	if (firstIndex >= Points.size || secondIndex >= Points.size || thirdIndex >= Points.size) {
		throw CModel<T>::OutOfRange();
	}
	else {
		Triangles.push_back(CTriangleIndex(firstIndex, secondIndex, thirdIndex));
	}
}
*/