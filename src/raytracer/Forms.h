#include "Vecteur3.h"

struct Triangle
{
	
	Vecteur3 _A, _B, _C;

	Triangle()
	{
		_A = Vecteur3(0,0,0);
		_B = Vecteur3(0,0,0);
		_C = Vecteur3(0,0,0);
	}

	Triangle(Vecteur3 a, Vecteur3 b, Vecteur3 c)
	{
		_A = a;
		_B = b;
		_C = c;
	}

};

struct Plane
{
	float _a, _b, _c, _d;

	Plane()
	{
		_a = 0;
		_b = 0;
		_c = 0;
		_d = 0;
	}

	Plane(float a, float b, float c, float d)
	{
		_a = a;
		_b = b;
		_c = c;
		_d = d;
	}

	Plane(Triangle tri)
	{
		
		Vecteur3 vec1 = tri._B - tri._A;
		Vecteur3 vec2 = tri._C - tri._A;
		Vecteur3 n = ProduitVectoriel( vec1, vec2 );

		_a = n._x;
		_b = n._y;
		_c = n._z;

		_d = _a*tri._A._x;
		_d += _b*tri._A._y;
		_d += _c*tri._A._z;
		_d = -_d;

	}

};

struct Line
{
	
	Vecteur3 _A, _B;

	Line()
	{
		_A = Vecteur3(0,0,0);
		_B = Vecteur3(0,0,0);
	}

	Line(Vecteur3 a, Vecteur3 b)
	{
		_A = a;
		_B = b;
	}

};

struct Complex
{
	float _n, _c;

	Complex()
	{
		_n = 0;
		_c = 0;
	}

	Complex(float n, float c)
	{
		_n = n;
		_c = c;
	}

	Complex operator+(Complex com)
	{
		return Complex(_n+com._n, _c+com._c);
	}

	Complex operator-(Complex com)
	{
		return Complex(_n-com._n, _c-com._c);
	}

	Complex operator+(float f)
	{
		return Complex(_n+f, _c);
	}

	Complex operator-(float f)
	{
		return Complex(_n-f, _c);
	}

	Complex operator+=(Complex com)
	{
		_n += com._n;
		_c += com._c;
		return (*this);
	}

	Complex operator-=(Complex com)
	{
		_n -= com._n;
		_c -= com._c;
		return (*this);
	}

	Complex operator+=(float f)
	{
		_n += f;
		return (*this);
	}

	Complex operator-=(float f)
	{
		_n -= f;
		return (*this);
	}

	Complex operator*(float f)
	{
		return Complex(this->_n*f, this->_c*f);
	}

	Complex operator/(float f)
	{
		return Complex(this->_n/f, this->_c/f);
	}

	Complex operator*=(float f)
	{
		_n *= f;
		_c *= f;
		return (*this);
	}

	Complex operator/=(float f)
	{
		_n /= f;
		_c /= f;
		return (*this);
	}

};