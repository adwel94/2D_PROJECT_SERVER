#pragma once
#ifndef _MYMATH_H_
#define _MYMATH_H_

namespace Utilities
{

	namespace MY_Math
	{
		//제곱
		inline double SQUARE(double _x)
		{
			return ((_x) * (_x));
		}

		//라디안을 각도로
		inline double RAD(double  _x)
		{
			return ((_x) * (3.14 / 180));
		}

		//절대값
		inline double ABS(double  _x)
		{
			return (((_x) < 0) ? -(_x) : (_x));
		}

		//반올림
		inline long ROUND(double _x)
		{
			return ((_x) >= 0 ? (long)((_x)+0.5) : (long)((_x)-0.5));
		}

		//최댓값
		inline double MAX(double _x, double _y)
		{
			return (((_x) >= (_y)) ? (_x) : (_y));
		}

		inline double MIN(double _x, double _y)
		{
			return (((_x) < (_y)) ? (_x) : (_y));
		}



		//행렬2x2
		struct sMatrix2X2
		{
			//접근을 쉽게하기 위한 공용체
			union
			{
				struct
				{
					float _00, _01;
					float _10, _11;
				};
				float e[2][2];
			};
		};

		//행렬 곱
		sMatrix2X2 operator*(float _n, const sMatrix2X2& _m)
		{
			sMatrix2X2 m;
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					m.e[i][j] = _m.e[i][j] * _n;
				}
			}
			return m;
		}

		//역행렬
		sMatrix2X2 Matrix_Inverse(const sMatrix2X2& _m)
		{
			sMatrix2X2 m = { 0,0,0,0 };
			float d = (_m.e[0][0] * _m.e[1][1]) - (_m.e[0][1] * _m.e[1][0]);
			if (d == 0) return m;
			float n = 1 / d;
			m = { _m.e[1][1], (-1) * _m.e[0][1] , (-1) * _m.e[1][0],_m.e[0][0] };
			return n * m;
		}


	}

}

#endif // !_MYMATH_H_
