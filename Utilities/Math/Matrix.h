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

		cMatrix2x2 operator* (float _n, const cMatrix2x2& _m);

		//역행렬
		cMatrix2x2 Matrix_Inverse(const cMatrix2x2& _m);


		class cMatrix4X4
		{
		public:
			union
			{
				struct
				{
					float _00, _01, _02, _03;
					float _10, _11, _12, _13;
					float _20, _21, _22, _23;
					float _30, _31, _32, _33;
				};
				float e[4][4];
			};
		};

		cMatrix4X4 Matrix_Unit();
		cMatrix4X4 Matrix_Translation(float _x, float _y, float _z);


		cMatrix4X4 Matrix_RoatationX(float _rad);
		cMatrix4X4 Matrix_RoatationY(float _rad);
		cMatrix4X4 Matrix_RoatationZ(float _rad);
	}
}
#endif // !_MATRIX_H_
