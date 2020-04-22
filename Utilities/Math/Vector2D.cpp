#include "Vector2D.h"
#include "MyMath2D.h"

cVector2D::cVector2D()
{
	mX = 0;
	mY = 0;
}

cVector2D::cVector2D(float _x, float _y)
{
	mX = _x;
	mY = _y;
}

cVector2D::cVector2D(const cVector2D& v)
{
	mX = v.mX;
	mY = v.mY;
}

cVector2D::~cVector2D()
{

}


void cVector2D::SetXY(float _x, float _y)
{
	mX = _x;
	mY = _y;
}

cVector2D cVector2D::Round() const
{
	cVector2D v(ROUND(mX), ROUND(mY));
	return  v;
}

cVector2D cVector2D::Nomaliztion() const
{
	float x = (mX == 0 || GetSize() == 0) ? 0 : mX / GetSize();
	float y = (mY == 0 || GetSize() == 0) ? 0 : mY / GetSize();
	cVector2D v(x, y);
	return v;
}

float cVector2D::GetLength(const cVector2D& _a, const cVector2D& _b)
{
	return(sqrt(SQUARE(_b.mX - _a.mX) + SQUARE(_b.mY - _a.mY)));
}

float cVector2D::GetSize() const
{
	return sqrt(SQUARE(mX) + SQUARE(mY));
}


bool operator ==(const cVector2D& _v1, const cVector2D& _v2)
{
	return (_v1.mX == _v2.mX) && (_v1.mY == _v2.mY);
}

bool operator!=(const cVector2D&  _v1, const cVector2D& _v2)
{
	return (_v1.mX != _v2.mX) || (_v1.mY != _v2.mY);
}

bool operator< (const cVector2D& _v1, const cVector2D& _v2)
{
	return (_v1.mX < _v2.mX) && (_v1.mY < _v2.mY);
}
//합
cVector2D operator+(const cVector2D& _v1, const cVector2D& _v2)
{
	cVector2D v(_v1.mX + _v2.mX, _v1.mY + _v2.mY);
	return v;
}
//차
cVector2D operator-(const cVector2D& _v1, const cVector2D& _v2)
{
	cVector2D v(_v1.mX - _v2.mX, _v1.mY - _v2.mY);
	return v;
}

//곱
cVector2D operator*(const cVector2D& _v, float _scalar)
{
	cVector2D v(_scalar*_v.mX, _scalar*_v.mY);
	return v;
}

float operator*(const cVector2D& _a, const cVector2D& _b)
{
	return (_a.mX * _b.mY) - (_a.mY * _b.mX);
}

cVector2D operator*(const cVector2D& _v, const sMatrix4X4& _m)
{
	float my[4] = { _v.mX,_v.mY,0,1 };
	float result[4] = { 0,0,0,0 };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[i] += (my[j] * _m.e[j][i]);
		}
	}
	return cVector2D{ result[0], result[1] };
}
//내적
float DotOperator(const cVector2D& _v1, const cVector2D& _v2)
{
	return (_v1.mX * _v2.mX) + (_v1.mY * _v2.mY);
}

cVector2D ProJ(const cVector2D& _v, const cVector2D& _n) //벡터 프로젝
{
	//벡터의 사이의 cos 값 
	float cos = DotOperator(_v, _n) / (_n.GetSize() * _v.GetSize());
	//정규화에 곱할 스칼라 값
	float scalar = cos * _v.GetSize();
	//n을 정규화
	cVector2D v = _n.Nomaliztion();
	//결과 값
	return v * scalar;
}

cVector2D ProJa(const cVector2D& _v, const cVector2D& _n) //벡터 프로젝
{
	//벡터의 사이의 cos 값 
	float cos = ABS(DotOperator(_v, _n)) / (_n.GetSize() * _v.GetSize());
	//정규화에 곱할 스칼라 값
	float scalar = cos * _v.GetSize();
	//n을 정규화
	cVector2D v = _n.Nomaliztion();
	//결과 값
	return v * scalar;
}


//std::ostream &operator<<(std::ostream& _cout, const cVector2D& _v)
//{
//	_cout << "( " << _v.mX << ", " << _v.mY << " )";
//	return _cout;
//}
