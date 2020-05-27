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
	}

}

#endif // !_MYMATH_H_
