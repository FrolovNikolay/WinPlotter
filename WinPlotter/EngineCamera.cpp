#include "EngineCamera.h"
#include <cmath>
#include <set>

// Ближняя и дальная плоскости отсечения (координаты по Z)
const double CEngineCamera::NearZ = 1;
const double CEngineCamera::FarZ = 100;

CEngineCamera::CEngineCamera(int clientWidth, int clientHeight) :
AngleX(0), AngleY(0), AngleZ(1), ViewDistance(1), ClientHeight(clientHeight), ClientWidth(clientWidth)
{
	Position = C3DPoint(10, 10, 10);
	UpdateInverseRotateMatrixX(0);
	UpdateInverseRotateMatrixY(0);
	UpdateInverseRotateMatrixZ(1);
	UpdateTransformMatrix();
}

void CEngineCamera::Render(const C3DModel& object, C2DModel& renderedObject) {
	transform(object);
	filter();
	render(renderedObject);
}

void CEngineCamera::SetWindowSize(int clientWidth_, int clientHeight_) {
	if (clientWidth_ <= 0 || clientHeight_ <= 0) {
		throw CEngineCamera::IncorrectWindowSize();
	}
	ClientWidth = clientWidth_;
	ClientHeight = clientHeight_;

	// Расстояние до экрана проекции устанавлиается как половина ширины экрана
	ViewDistance = (ClientWidth - 1) / 2;

	// Соотношение между шириной и высотой
	AspectRatio = ClientWidth / ClientHeight;
}

void CEngineCamera::transform(const C3DModel& object) {
	// Копируем исходный объект
	cameraModel = C3DModel(object);

	// Пробегаемся по всем его точкам и модифицируем при помощи матрицы преобразований
	for (auto point = cameraModel.Points.begin(); point != cameraModel.Points.end(); point++) {
		*point = modifyPoint(*point);
	}
}

void CEngineCamera::filter() {
	// TODO: удаление (и модификация) элементов внутренней структуры

	// В первом приближении мы просто будем удалять те отрезки и треугольники, у которых хотя бы одна вершина попадает
	// вне области видимости камеры 
	std::set<int> pointNumbersForErase; // индексы удаляемых точек
	int counter = 0;
	for (auto point = cameraModel.Points.begin(); point != cameraModel.Points.end(); point++) {
		// Если точка находится вне области видимости
		if (point->Z < NearZ || point->Z > FarZ || std::abs(point->X) > point->Z) {
			pointNumbersForErase.insert(counter);
		}
		counter += 1;
	}

	// Теперь мы удаляем все объекты (индексы), которые содержат хотя бы одну точку из отсечённых
	auto segment = cameraModel.Segments.begin();
	while (segment != cameraModel.Segments.end()) {
		// Если попадает под условие (один из концов находится среди удаляемых точек), то удаляем
		if (pointNumbersForErase.find(segment->First) != pointNumbersForErase.end() ||
			pointNumbersForErase.find(segment->Second) != pointNumbersForErase.end()) {
			segment = cameraModel.Segments.erase(segment);
		}
		// Иначе переходим к следующему элементу
		else {
			segment++;
		}
	}

	// Аналогично и для треугольников
	auto triangle = cameraModel.Triangles.begin();
	while (triangle != cameraModel.Triangles.end()) {
		// Если попадает под условие (одна из вершин треугольника попадает в точки), то удаляем
		if (pointNumbersForErase.find(triangle->First) != pointNumbersForErase.end() ||
			pointNumbersForErase.find(triangle->Second) != pointNumbersForErase.end() ||
			pointNumbersForErase.find(triangle->Third) != pointNumbersForErase.end()) {
			triangle = cameraModel.Triangles.erase(triangle);
		}
		// Иначе переходим к следующему элементу
		else {
			triangle++;
		}
	}
}

void CEngineCamera::render(C2DModel& renderedObject) {
	// TODO: преобразование трёхмерных координат точек в контексте камеры в двухмерные координаты в контексте окна
	renderedObject.Clear();

	// Так как сама структура объекта (отрезки и треугольники) уже не поменяется, то мы просто копируем имеющиеся индексы
	renderedObject.Triangles = cameraModel.Triangles;
	renderedObject.Segments = cameraModel.Segments;

	// Для каждой точки выполняем её аксонометрическое преобразование (то есть проецируем на плоскость обзора камеры)
	for (auto point = cameraModel.Points.begin(); point != cameraModel.Points.end(); point++) {
		C2DPoint newPoint;
		newPoint.X = ViewDistance * point->X / point->Z + (0.5 * ClientWidth - 0.5);
		newPoint.Y = - ViewDistance * point->Y * AspectRatio / point->Z + (0.5 * ClientHeight - 0.5);
		renderedObject.AddPoint(newPoint); 
	}
}

C3DPoint CEngineCamera::modifyPoint(C3DPoint originPoint) const {
	return TransfromMatrix.ProjectPoint(originPoint);
}



void CEngineCamera::SetPosition(C3DPoint point) {
	Position = point;
	MovingMatrix = CMatrix44(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-Position.X, -Position.Y, -Position.Z, 1
	);
}

// Обновления матриц преобразования
void CEngineCamera::UpdateInverseRotateMatrixX(double angle) {
	inverseRotateMatrixX = CMatrix44(
		1, 0, 0, 0,
		0, cos(-angle), sin(-angle), 0,
		0, -sin(-angle), cos(-angle), 0,
		0, 0, 0, 1
	);
}

void CEngineCamera::UpdateInverseRotateMatrixY(double angle) {
	inverseRotateMatrixX = CMatrix44(
		cos(-angle), 0, -sin(-angle), 0,
		0, 1, 0, 0,
		sin(-angle), 0, cos(-angle), 0,
		0, 0, 0, 1
		);
}

void CEngineCamera::UpdateInverseRotateMatrixZ(double angle) {
	inverseRotateMatrixX = CMatrix44(
		cos(-angle), sin(-angle), 0, 0,
		-sin(-angle), cos(-angle), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
}

void CEngineCamera::UpdateTransformMatrix() {
	TransfromMatrix = CMatrix44();
	TransfromMatrix.MultiplyRight(MovingMatrix);
	TransfromMatrix.MultiplyRight(inverseRotateMatrixY);
	TransfromMatrix.MultiplyRight(inverseRotateMatrixX);
	TransfromMatrix.MultiplyRight(inverseRotateMatrixZ);
}