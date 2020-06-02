#include "Matrix.h"
#include <math.h>


using namespace Utilities::MY_Math;

cMatrix2x2 Utilities::MY_Math::operator*(float _n, const cMatrix2x2& _m)
{
	cMatrix2x2 m;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			m.e[i][j] = _m.e[i][j] * _n;
		}
	}
	return m;
}

cMatrix2x2 Utilities::MY_Math::Matrix_Inverse(const cMatrix2x2& _m)
{
	cMatrix2x2 m = { 0,0,0,0 };
	float d = (_m.e[0][0] * _m.e[1][1]) - (_m.e[0][1] * _m.e[1][0]);
	if (d == 0) return m;
	float n = 1 / d;
	m = { _m.e[1][1], (-1) * _m.e[0][1] , (-1) * _m.e[1][0],_m.e[0][0] };
	return n * m;
}

cMatrix4X4 Utilities::MY_Math::Matrix_Unit()
{
	cMatrix4X4 m = { 1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1 };
	return m;
}

cMatrix4X4 Utilities::MY_Math::Matrix_Translation(float _x, float _y, float _z)
{
	cMatrix4X4 m = { 1,	0,	0,	0,
				0,	1,	0,	0,
				0,	0,	1,	0,
				_x,	_y,	_z,	1 };
	return m;
}

cMatrix4X4 Utilities::MY_Math::Matrix_RoatationX(float _rad)
{
	cMatrix4X4 m = { 1,0,0,0,
							0,cos(_rad),sin(_rad),0,
							0,-sin(_rad),cos(_rad),0,
							0,0,0,1 };
	return m;
}

cMatrix4X4 Utilities::MY_Math::Matrix_RoatationY(float _rad)
{
	cMatrix4X4 m = { cos(_rad),-sin(_rad),0,0,
							0,1,0,0,
							sin(_rad),0,cos(_rad),0,
							0,0,0,1 };
	return m;
}

cMatrix4X4 Utilities::MY_Math::Matrix_RoatationZ(float _rad)
{
	cMatrix4X4 m = { cos(_rad),sin(_rad),0,0,
				-sin(_rad),cos(_rad),0,0,
				0,0,1,0,
				0,0,0,1 };
	return m;
}