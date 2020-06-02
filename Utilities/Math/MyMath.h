#pragma once
#ifndef _MYMATH_H_
#define _MYMATH_H_

namespace Utilities
{

	namespace MY_Math
	{
		//����
		inline double SQUARE(double _x)
		{
			return ((_x) * (_x));
		}
		//rad to degree
		inline double RAD2DEG(double _x)
		{
			return ((_x) * (180 / 3.14159265));
		}

		//degree to rad
		inline double DEG2RAD(double  _x)
		{
			return ((_x) * (3.14159265 / 180));
		}

		//���밪
		inline double ABS(double  _x)
		{
			return (((_x) < 0) ? -(_x) : (_x));
		}

		//�ݿø�
		inline long ROUND(double _x)
		{
			return ((_x) >= 0 ? (long)((_x)+0.5) : (long)((_x)-0.5));
		}

		//�ִ�
		inline double MAX(double _x, double _y)
		{
			return (((_x) >= (_y)) ? (_x) : (_y));
		}

		inline double MIN(double _x, double _y)
		{
			return (((_x) < (_y)) ? (_x) : (_y));
		}
	}

}

#endif // !_MYMATH_H_
