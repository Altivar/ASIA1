#include "Vecteur2.h"

Vecteur2::Vecteur2(reel u, reel v):
_u(u), _v(v)
{}

Vecteur2::Vecteur2():
_u(0), _v(0)
{}

Vecteur2 Vecteur2::operator+(const Vecteur2 &v) const
{
	return Vecteur2(_u+v._u, _v+v._v);
}

Vecteur2 Vecteur2::operator-(const Vecteur2 &v) const
{
	return Vecteur2(_u-v._u, _v-v._v);
}

Vecteur2 Vecteur2::operator*(reel k)const
{
	return Vecteur2(_u*k, _v*k);
}

