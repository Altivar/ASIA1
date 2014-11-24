#include "Primitive.h"
#include "Matrice33.h"

#include <cmath>


Primitive::Primitive(Materiau *materiau): _materiau(materiau)
{}

PrimitiveSphere::PrimitiveSphere(Materiau *materiau, const Vecteur3 &centre, reel rayon):
Primitive(materiau), _centre(centre), _rayon(rayon)
{}

bool PrimitiveSphere::calculerIntersection(const Rayon &rayon, reel &distance) const
{
	Vecteur3 COr = rayon._origine - _centre;
	reel b = 2*ProduitScalaire(COr, rayon._direction);
	reel c = COr.calculerNormeCarree() - _rayon*_rayon;
	reel delta = b*b - 4*c;

	if (delta < 0)		// pas d'intersection
		return false;

	reel rdelta = sqrt(delta);

	if (rdelta < -b)		// 1 intersection devant + 1 derriere (origine du rayon dans la sphere)
	{
		distance = -0.5 *(b + rdelta);
		return true;
	}

	if (rdelta > b)		// 2 intersections devant : prendre la plus proche
	{
		distance = -0.5 *(b - rdelta);
		return true;
	}

	return false;
}

bool PrimitiveSphere::calculerIntersection(const Rayon &rayon, Intersection &intersection) const
{
	Vecteur3 COr = rayon._origine - _centre;
	reel b = 2*ProduitScalaire(COr, rayon._direction);
	reel c = COr.calculerNormeCarree() - _rayon*_rayon;
	reel delta = b*b - 4*c;
	if (delta > 0)
	{
		reel rdelta = sqrt(delta);
		if (rdelta < -b)		// 1 intersection devant + 1 derriere (origine du rayon dans la sphere)
		{
			intersection._distance = -0.5 *(b + rdelta);
		}
		else
		{
			if (rdelta > b)		// 2 intersections devant : prendre la plus proche
			{

				intersection._distance = -0.5 *(b - rdelta);
			}
			else
			{
				return false;
			}
		}

		intersection._incidence = rayon._direction;
		intersection._position = rayon.calculerPosition(intersection._distance);
		intersection._normale = intersection._position - _centre;
		intersection._normale.normer();
		intersection._reflexion = VecteurReflechi(intersection._incidence, intersection._normale);
		intersection._texcoords._u = 0;
		intersection._texcoords._v = 0;
		intersection._materiau = _materiau;

		return true;
	}
	return false;
}

Sommet::Sommet(const Vecteur3 &position, const Vecteur3 &normale, const Vecteur2 &texcoords):
_position(position), _normale(normale)
{
	_normale.normer();
	_texcoords._u = std::max<reel>(0, std::min<reel>(1, texcoords._u));
	_texcoords._v = std::max<reel>(0, std::min<reel>(1, texcoords._v));
}


PrimitiveTriangle::PrimitiveTriangle(Materiau *materiau, const Sommet &A, const Sommet &B, const Sommet &C):
		Primitive(materiau), _A(A), _B(B), _C(C)
{
	_normale = (_A._normale+_B._normale+_C._normale)*(1.0/3.0);
}

bool PrimitiveTriangle::calculerIntersection(const Rayon &rayon, Intersection &intersection) const
{
	// pas d'intersection si le rayon sort du triangle
	if (ProduitScalaire(rayon._direction, _normale) > 0)
		return false;

	Vecteur3 AOr = rayon._origine - _A._position;
	Vecteur3 AB = _B._position - _A._position;
	Vecteur3 AC = _C._position - _A._position;
	Vecteur3 mDr = - rayon._direction;

	Vecteur3 vI;
	if (!resoudreSysteme(AB, AC, mDr, vI, AOr))
		return false;
	if (vI._z<=0 || vI._x<0 || vI._x>1 || vI._y<0 || vI._y>1 || (vI._x+vI._y)>1)
		return false;

	reel up = vI._x/(1.0-vI._y);

	// interpolation des normales
	Vecteur3 Nac = interpoler<Vecteur3>(_A._normale, _C._normale, vI._y);
	Vecteur3 Nbc = interpoler<Vecteur3>(_B._normale, _C._normale, vI._y);
	intersection._normale = interpoler<Vecteur3>(Nac, Nbc, up);

	// interpolation des coordonnees de texture
	Vecteur2 Tac = interpoler<Vecteur2>(_A._texcoords, _C._texcoords, vI._y);
	Vecteur2 Tbc = interpoler<Vecteur2>(_B._texcoords, _C._texcoords, vI._y);
	intersection._texcoords = interpoler<Vecteur2>(Tac, Tbc, up);

	intersection._distance = vI._z;
	intersection._position = rayon.calculerPosition(intersection._distance);
	intersection._incidence = rayon._direction;
	intersection._reflexion = VecteurReflechi(intersection._incidence, intersection._normale);
	intersection._materiau = _materiau;

	return true;
}


bool PrimitiveTriangle::calculerIntersection(const Rayon &rayon, reel &distance) const
{
	// pas d'intersection si le rayon sort du triangle
	if (ProduitScalaire(rayon._direction, _normale) > 0)
		return false;

	Vecteur3 AOr = rayon._origine - _A._position;
	Vecteur3 AB = _B._position - _A._position;
	Vecteur3 AC = _C._position - _A._position;
	Vecteur3 mDr = - rayon._direction;

	Vecteur3 vI;
	if (!resoudreSysteme(AB, AC, mDr, vI, AOr))
		return false;
	if (vI._z<=0 || vI._x<0 || vI._x>1 || vI._y<0 || vI._y>1 || (vI._x+vI._y)>1)
		return false;

	distance = vI._z;
	return true;
}

/// [PrimitiveBoite]
PrimitiveBoite::PrimitiveBoite(Materiau* materiau, const Vecteur3& origine, const Vecteur3& dimensions)
	: Primitive(materiau)
	, _origine(origine)
	, _dimensions(dimensions)
{
}

bool PrimitiveBoite::calculerIntersection(const Rayon& rayon, Intersection& intersection) const
{
	// [TODO] - editer l'intersection
	//        - return true en cas d'intersection, sinon false
	return true;
}

bool PrimitiveBoite::calculerIntersection(const Rayon& rayon, reel& distance) const
{
	// [TODO] - editer la distance
	//        - return true en cas d'intersection, sinon false
	return true;
}
/// [PrimitiveBoite]
