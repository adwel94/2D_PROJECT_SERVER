#pragma once
#ifndef _MATRIX_H_
#define _MATRIX_H_


namespace Utilities
{
	namespace MY_Math
	{
		class cMatrix2x2
		{
		public:
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

		cMatrix2x2 operator* (float _n, const cMatrix2x2& _m)
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

		//역행렬
		cMatrix2x2 Matrix_Inverse(const cMatrix2x2& _m)
		{
			cMatrix2x2 m = { 0,0,0,0 };
			float d = (_m.e[0][0] * _m.e[1][1]) - (_m.e[0][1] * _m.e[1][0]);
			if (d == 0) return m;
			float n = 1 / d;
			m = { _m.e[1][1], (-1) * _m.e[0][1] , (-1) * _m.e[1][0],_m.e[0][0] };
			return n * m;
		}
	}
}
#endif // !_MATRIX_H_
