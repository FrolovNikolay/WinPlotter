#include "Engine.h"
#include <set>

CEngine::CEngine() {

}

CEngine::CEngine( int windowWidthInPixels, int windowHeightInPixels )
{
	camera.SetWindowSize( windowWidthInPixels, windowHeightInPixels );
}

void CEngine::Render( const C3DModel& object, C2DModel& renderedObject )
{
	transform( object );
	filter();
	render( renderedObject );
}

CCamera& CEngine::getCamera()
{
	return camera;
}

void CEngine::transform( const C3DModel& object )
{
	// Копируем исходный объект
	cameraModel = C3DModel( object );

	// Пробегаемся по всем его точкам и модифицируем при помощи матрицы преобразований
	for ( auto point = cameraModel.Points.begin(); point != cameraModel.Points.end(); point++ ) {
		camera.TransformPoint(*point, *point);
	}
}

void CEngine::filter() {
	// TODO: удаление (и модификация) элементов внутренней структуры

	// В первом приближении мы просто будем удалять те отрезки и треугольники, у которых хотя бы одна вершина попадает
	// вне области видимости камеры 
	std::set<int> pointNumbersForErase; // индексы удаляемых точек
	int counter = 0;
	for ( auto point = cameraModel.Points.cbegin(); point != cameraModel.Points.cend(); point++ ) {
		// Если точка находится вне области видимости
		if ( !camera.IsPointInFieldOfView(*point) ) {
			pointNumbersForErase.insert( counter );
		}
		counter += 1;
	}

	// Теперь мы удаляем все объекты (индексы), которые содержат хотя бы одну точку из отсечённых
	auto segment = cameraModel.Segments.begin();
	while ( segment != cameraModel.Segments.end() ) {
		// Если попадает под условие (один из концов находится среди удаляемых точек), то удаляем
		if ( pointNumbersForErase.find( segment->First ) != pointNumbersForErase.end() &&
			pointNumbersForErase.find( segment->Second ) != pointNumbersForErase.end() ) {
			segment = cameraModel.Segments.erase( segment );
		}
		// Иначе переходим к следующему элементу
		else {
			segment++;
		}
	}

	// Аналогично и для треугольников
	auto triangle = cameraModel.Triangles.begin();
	while ( triangle != cameraModel.Triangles.end() ) {
		// Если попадает под условие (одна из вершин треугольника попадает в точки), то удаляем
		if ( pointNumbersForErase.find( triangle->First ) != pointNumbersForErase.end() &&
			pointNumbersForErase.find( triangle->Second ) != pointNumbersForErase.end() &&
			pointNumbersForErase.find( triangle->Third ) != pointNumbersForErase.end() ) {
			triangle = cameraModel.Triangles.erase( triangle );
		}
		// Иначе переходим к следующему элементу
		else {
			triangle++;
		}
	}
}

void CEngine::render( C2DModel& renderedObject ) {
	// TODO: преобразование трёхмерных координат точек в контексте камеры в двухмерные координаты в контексте окна
	renderedObject.Clear();

	// Так как сама структура объекта (отрезки и треугольники) уже не поменяется, то мы просто копируем имеющиеся индексы
	renderedObject.Triangles = cameraModel.Triangles;
	renderedObject.Segments = cameraModel.Segments;

	// Для каждой точки выполняем её аксонометрическое преобразование (то есть проецируем на плоскость обзора камеры)
	for ( auto point = cameraModel.Points.cbegin(); point != cameraModel.Points.cend(); point++ ) {
		C2DPoint newPoint;
		camera.ProjectPoint( *point, newPoint );
		renderedObject.AddPoint( newPoint );
	}
}


