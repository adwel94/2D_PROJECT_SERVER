#include "MyMath2D.h"
#include"Vector2D.h"


sMatrix2X2 operator*(float _n, const sMatrix2X2& _m)
{
	sMatrix2X2 m;	
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			//if (_m.e[i][j] == 0)
			//{
			//	m.e[i][j] = 0;
			//	continue;
			//}

			m.e[i][j] = _m.e[i][j] * _n;

		}
	}

	return m;
}


sMatrix2X2 Matrix_Inverse(const sMatrix2X2& _m)
{
	sMatrix2X2 m = { 0,0,0,0 };
	float d = (_m.e[0][0]*_m.e[1][1]) - (_m.e[0][1]*_m.e[1][0]);
	if (d == 0) return m;
	float n = 1 / d;
	m = { _m.e[1][1], (-1)*_m.e[0][1] , (-1)*_m.e[1][0],_m.e[0][0] };
	return n * m;
}

sMatrix4X4 Matrix_Unit()
{
	sMatrix4X4 m = { 1,0,0,0,
							0,1,0,0,
							0,0,1,0,
							0,0,0,1 };
	return m;
}

sMatrix4X4 Matrix_Translation(float _x, float _y, float _z)
{
	sMatrix4X4 m = { 1,	0,	0,	0,
							0,	1,	0,	0,
							0,	0,	1,	0,
							_x,	_y,	_z,	1 };
	return m;
}

sMatrix4X4 Matrix_RoatationX(float _angle)
{
	sMatrix4X4 m = { 1,0,0,0,
							0,cos(_angle),sin(_angle),0,
							0,-sin(_angle),cos(_angle),0,
							0,0,0,1 };
	return m;
}

sMatrix4X4 Matrix_RoatationY(float _angle)
{
	sMatrix4X4 m = { cos(_angle),-sin(_angle),0,0,
							0,1,0,0,
							sin(_angle),0,cos(_angle),0,
							0,0,0,1 };
	return m;
}


sMatrix4X4 Matrix_RoatationZ(float _angle)
{
	sMatrix4X4 m = { cos(_angle),sin(_angle),0,0,
							-sin(_angle),cos(_angle),0,0,
							0,0,1,0,
							0,0,0,1 };
	return m;
}
