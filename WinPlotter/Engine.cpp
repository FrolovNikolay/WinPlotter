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
	// �������� �������� ������
	cameraModel = C3DModel( object );

	// ����������� �� ���� ��� ������ � ������������ ��� ������ ������� ��������������
	for ( auto point = cameraModel.Points.begin(); point != cameraModel.Points.end(); point++ ) {
		camera.TransformPoint(*point, *point);
	}
}

void CEngine::filter() {
	// TODO: �������� (� �����������) ��������� ���������� ���������

	// � ������ ����������� �� ������ ����� ������� �� ������� � ������������, � ������� ���� �� ���� ������� ��������
	// ��� ������� ��������� ������ 
	std::set<int> pointNumbersForErase; // ������� ��������� �����
	int counter = 0;
	for ( auto point = cameraModel.Points.cbegin(); point != cameraModel.Points.cend(); point++ ) {
		// ���� ����� ��������� ��� ������� ���������
		if ( !camera.IsPointInFieldOfView(*point) ) {
			pointNumbersForErase.insert( counter );
		}
		counter += 1;
	}

	// ������ �� ������� ��� ������� (�������), ������� �������� ���� �� ���� ����� �� ����������
	auto segment = cameraModel.Segments.begin();
	while ( segment != cameraModel.Segments.end() ) {
		// ���� �������� ��� ������� (���� �� ������ ��������� ����� ��������� �����), �� �������
		if ( pointNumbersForErase.find( segment->First ) != pointNumbersForErase.end() &&
			pointNumbersForErase.find( segment->Second ) != pointNumbersForErase.end() ) {
			segment = cameraModel.Segments.erase( segment );
		}
		// ����� ��������� � ���������� ��������
		else {
			segment++;
		}
	}

	// ���������� � ��� �������������
	auto triangle = cameraModel.Triangles.begin();
	while ( triangle != cameraModel.Triangles.end() ) {
		// ���� �������� ��� ������� (���� �� ������ ������������ �������� � �����), �� �������
		if ( pointNumbersForErase.find( triangle->First ) != pointNumbersForErase.end() &&
			pointNumbersForErase.find( triangle->Second ) != pointNumbersForErase.end() &&
			pointNumbersForErase.find( triangle->Third ) != pointNumbersForErase.end() ) {
			triangle = cameraModel.Triangles.erase( triangle );
		}
		// ����� ��������� � ���������� ��������
		else {
			triangle++;
		}
	}
}

void CEngine::render( C2DModel& renderedObject ) {
	// TODO: �������������� ��������� ��������� ����� � ��������� ������ � ���������� ���������� � ��������� ����
	renderedObject.Clear();

	// ��� ��� ���� ��������� ������� (������� � ������������) ��� �� ����������, �� �� ������ �������� ��������� �������
	renderedObject.Triangles = cameraModel.Triangles;
	renderedObject.Segments = cameraModel.Segments;

	// ��� ������ ����� ��������� � ����������������� �������������� (�� ���� ���������� �� ��������� ������ ������)
	for ( auto point = cameraModel.Points.cbegin(); point != cameraModel.Points.cend(); point++ ) {
		C2DPoint newPoint;
		camera.ProjectPoint( *point, newPoint );
		renderedObject.AddPoint( newPoint );
	}
}


