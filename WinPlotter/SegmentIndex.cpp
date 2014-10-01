#include "SegmentIndex.h"

CSegmentIndex::CSegmentIndex(int first , int second):
First(first), Second(second)
{
	// ��������� ������������ ���������� ��������
	if (first < 0 || second < 0 || first == second)
	{
		throw CSegmentIndex::IncorrectIndex();
	}
}