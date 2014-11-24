#include "Couleur.h"

Couleur::Couleur(reel r, reel g, reel b, reel a):
_r(r), _g(g), _b(b), _a(a)
{}

Couleur::Couleur():
_r(0), _g(0), _b(0), _a(0)
{}


Couleur Couleur::operator+(const Couleur &c) const
{
	return Couleur(_r+c._r, _g+c._g, _b+c._b, _a+c._a);
}

Couleur Couleur::operator*(reel k) const
{
	return Couleur(_r*k, _g*k, _b*k, _a);
}

Couleur Couleur::operator*(const Couleur &c) const
{
	return Couleur(_r*c._r, _g*c._g, _b*c._b, _a*c._a);
}

Couleur & Couleur::operator+=(const Couleur &c)
{
	_r += c._r;
	_g += c._g;
	_b += c._b;
	_a += c._a;
	return *this;
}


