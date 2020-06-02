#pragma once
#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_

//const를 함수뒤에 붙일시 멤버변수를 변경 할수 없다

namespace Utilities
{

	namespace MY_Math
	{

		class cMatrix4X4;
		
		//벡터2D
		class cVector2D
		{
		public:
			float mX;
			float mY;

			cVector2D();
			cVector2D(const cVector2D&);
			cVector2D(float, float);
			~cVector2D();

			void SetXY(float, float);
			float GetSize() const;

			cVector2D Round() const; //반올림
			cVector2D Nomaliztion() const; //고유 벡터
		};

		float DotOperator(const cVector2D&, const cVector2D&); //벡터 내적
		cVector2D ProJ(const cVector2D&, const cVector2D&); //벡터 프로젝션
		cVector2D ProJa(const cVector2D&, const cVector2D&); //벡터 프로젝션\

		bool operator==(const cVector2D&, const cVector2D&); //벡터의 상등
		bool operator!=(const cVector2D&, const cVector2D&);
		bool operator< (const cVector2D&, const cVector2D&);

		cVector2D operator+(const cVector2D&, const cVector2D&); //벡터 합
		cVector2D operator-(const cVector2D&, const cVector2D&); //백터 차
		cVector2D operator*(const cVector2D&, float);//벡터 스칼라곱	   
		cVector2D operator*(const cVector2D&, const cMatrix4X4&);

		float operator*(const cVector2D&, const cVector2D&);//벡터 스칼라곱		


		float GetLength(const cVector2D& _a, const cVector2D& _b);
	}
}
#endif // !VECTOR2D
