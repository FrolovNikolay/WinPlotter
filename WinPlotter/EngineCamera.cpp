#include "EngineCamera.h"
#include <cmath>

// ������� � ������� ��������� ��������� (���������� �� Z)
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

	// ���������� �� ������ �������� �������������� ��� �������� ������ ������
	ViewDistance = (ClientWidth - 1) / 2;

	// ����������� ����� ������� � �������
	AspectRatio = ClientWidth / ClientHeight;
}

void CEngineCamera::transform(const C3DModel& object) {
	// �������� �������� ������
	cameraModel = C3DModel(object);

	// ����������� �� ���� ��� ������ � ������������ ��� ������ ������� ��������������
	for (auto point = cameraModel.Points.begin(); point != cameraModel.Points.end(); point++) {
		*point = modifyPoint(*point);
	}
}

void CEngineCamera::filter() {
	// TODO: �������� (� �����������) ��������� ���������� ���������

	// � ������ ����������� �� ������ ����� ������� �� ������� � ������������, � ������� ���� �� ���� ������� ��������
	// ��� ������� ��������� ������ 
	std::vector<int> pointNumbersForErase; // ������� ��������� �����
	int counter = 0;
	for (auto point = cameraModel.Points.begin(); point != cameraModel.Points.end(); point++) {
		// ���� ����� ��������� ��� ������� ���������
		if (point->Z < NearZ || point->Z > FarZ || std::abs(point->X) > point->Z) {
			pointNumbersForErase.push_back(counter);
		}
		counter += 1;
	}

	// ������ �� ������� ��� ������� (�������), ������� �������� ���� �� ���� ����� �� ����������
	auto segment = cameraModel.Segments.begin();
	while (segment != cameraModel.Segments.end()) {
		// ���� �������� ��� �������, �� �������
		if (false) {
			segment = cameraModel.Segments.erase(segment);
		}
		// ����� ��������� � ���������� ��������
		else {
			segment++;
		}
	}

	// ���������� � ��� �������������
	auto triangle = cameraModel.Triangles.begin();
	while (triangle != cameraModel.Triangles.end()) {
		// ���� �������� ��� �������, �� �������
		if (false) {
			triangle = cameraModel.Triangles.erase(triangle);
		}
		// ����� ��������� � ���������� ��������
		else {
			triangle++;
		}
	}
}

void CEngineCamera::render(C2DModel& renderedObject) {
	// TODO: �������������� ��������� ��������� ����� � ��������� ������ � ���������� ���������� � ��������� ����
	renderedObject.Clear();

	// ��� ��� ���� ��������� ������� (������� � ������������) ��� �� ����������, �� �� ������ �������� ��������� �������
	renderedObject.Triangles = cameraModel.Triangles;
	renderedObject.Segments = cameraModel.Segments;

	// ��� ������ ����� ��������� � ����������������� �������������� (�� ���� ���������� �� ��������� ������ ������)
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

// ���������� ������ ��������������
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