#include "Model.h"

template <typename T>
CModel<T>::CModel<T>() {
}

template <typename T>
void CModel<T>::AddPoint(T point) {
	points.push_back(point);
}

template <typename T>
void CModel<T>::AddSegment(int firstIndex, int secondIndex) {
	if (firstIndex >= points.size || secondIndex >= points.size) {
		throw CModel<T>::OutOfRange();
	}
	else {
		segments.push_back(CSegmentIndex(firstIndex, secondIndex));
	}
}

template <typename T>
void CModel<T>::AddTriangle(int firstIndex, int secondIndex, int thirdIndex) {
	if (firstIndex >= points.size || secondIndex >= points.size || thirdIndex >= points.size) {
		throw CModel<T>::OutOfRange();
	}
	else {
		triangles.push_back(CTriangleIndex(firstIndex, secondIndex, thirdIndex));
	}
}