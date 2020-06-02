#pragma once
#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_

//const�� �Լ��ڿ� ���Ͻ� ��������� ���� �Ҽ� ����

namespace Utilities
{

	namespace MY_Math
	{

		class cMatrix4X4;
		
		//����2D
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

			cVector2D Round() const; //�ݿø�
			cVector2D Nomaliztion() const; //���� ����
		};

		float DotOperator(const cVector2D&, const cVector2D&); //���� ����
		cVector2D ProJ(const cVector2D&, const cVector2D&); //���� ��������
		cVector2D ProJa(const cVector2D&, const cVector2D&); //���� ��������\

		bool operator==(const cVector2D&, const cVector2D&); //������ ���
		bool operator!=(const cVector2D&, const cVector2D&);
		bool operator< (const cVector2D&, const cVector2D&);

		cVector2D operator+(const cVector2D&, const cVector2D&); //���� ��
		cVector2D operator-(const cVector2D&, const cVector2D&); //���� ��
		cVector2D operator*(const cVector2D&, float);//���� ��Į���	   
		cVector2D operator*(const cVector2D&, const cMatrix4X4&);

		float operator*(const cVector2D&, const cVector2D&);//���� ��Į���		


		float GetLength(const cVector2D& _a, const cVector2D& _b);
	}
}
#endif // !VECTOR2D
