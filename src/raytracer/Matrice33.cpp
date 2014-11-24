#include "Matrice33.h"

#include <cmath>

void Matrice33::remplir(reel coefs[9])
{
	_00 = coefs[0]; _01 = coefs[1]; _02 = coefs[2];
	_10 = coefs[3]; _11 = coefs[4]; _12 = coefs[5];
	_20 = coefs[6]; _21 = coefs[7]; _22 = coefs[8];
}

Matrice33 Matrice33::transposer() const
{
	Matrice33 T;
	T._00 = _00;	T._01 = _10;	T._02 = _20;
	T._10 = _01;	T._11 = _11;	T._12 = _21;
	T._20 = _02;	T._21 = _12;	T._22 = _22;
	return T;
}

Matrice33 Matrice33::operator*(double k) const
{
	Matrice33 A;

	A._00 = _00*k;		A._01 = _01*k;		A._02 = _02*k;
	A._10 = _10*k;		A._11 = _11*k;		A._12 = _12*k;
	A._20 = _20*k;		A._21 = _21*k;		A._22 = _22*k;

	return A;
}

Vecteur3 Matrice33::operator*(const Vecteur3& v) const
{
	double x(_00*v._x + _01*v._y + _02*v._z);
	double y(_10*v._x + _11*v._y + _12*v._z);
	double z(_20*v._x + _21*v._y + _22*v._z);
	return Vecteur3(x, y, z);
}


void Matrice33::remplir(const Vecteur3 & vx, const Vecteur3 & vy, const Vecteur3 & vz)
{
	_00 = vx._x; _01 = vx._y; _02 = vx._z;
	_10 = vy._x; _11 = vy._y; _12 = vy._z;
	_20 = vz._x; _21 = vz._y; _22 = vz._z;
}

#define EPSILON 1e-6


reel calculerDeterminant(const Vecteur3 &u, const Vecteur3 &v, const Vecteur3 &w)
{
	return u._x*v._y*w._z + v._x*w._y*u._z + w._x*u._y*v._z
			- w._x*v._y*u._z - u._x*w._y*v._z - v._x*u._y*w._z;
}

bool resoudreSysteme(const Vecteur3 &a0, const Vecteur3 &a1, const Vecteur3 &a2,
		Vecteur3 &x, const Vecteur3 &b)
{
	// applique la methode de Cramer (pas efficace mais assez robuste)
	reel d = calculerDeterminant(a0, a1, a2);
	if (fabs(d)<EPSILON)
		return false;
	x._x = calculerDeterminant(b, a1, a2);
	x._y = calculerDeterminant(a0, b, a2);
	x._z = calculerDeterminant(a0, a1, b);
	x *= 1/d;
	return true;
}


