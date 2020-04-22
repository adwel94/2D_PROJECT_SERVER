#pragma once
#ifndef VECTOR2D_H
#define VECTOR2D_H
#include "MyMath2D.h"
#include <math.h>

struct sMatrix4X4;


//º¤ÅÍ2D
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
	cVector2D Round() const;
	cVector2D Nomaliztion() const;
	friend bool operator==(const cVector2D&, const cVector2D&); //º¤ÅÍÀÇ »óµî
	friend bool operator!=(const cVector2D&, const cVector2D&);
	friend cVector2D operator+(const cVector2D&, const cVector2D&); //º¤ÅÍ ÇÕ
	friend cVector2D operator-(const cVector2D&, const cVector2D&); //¹éÅÍ Â÷
	friend cVector2D operator*(const cVector2D&, float);//º¤ÅÍ ½ºÄ®¶ó°ö
	friend cVector2D operator*(const cVector2D&, const sMatrix4X4&);
	friend float operator*(const cVector2D&, const cVector2D&);//º¤ÅÍ ½ºÄ®¶ó°ö
	friend float DotOperator(const cVector2D&, const cVector2D&); //º¤ÅÍ ³»Àû
	friend bool operator< (const cVector2D&, const cVector2D&);
	friend cVector2D ProJ(const cVector2D&, const cVector2D&); //º¤ÅÍ ÇÁ·ÎÁ§¼Ç
	friend cVector2D ProJa(const cVector2D&, const cVector2D&); //º¤ÅÍ ÇÁ·ÎÁ§¼Ç
	//friend std::ostream &operator<<(std::ostream&, const cVector2D&);// º¤ÅÍ Ãâ·Â  testÇÏ±âÀ§ÇÔ

	static float GetLength(const cVector2D&, const cVector2D&);
};






#endif // !VECTOR2D
