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

bool PrimitiveSphere::intersectionCube(const Vecteur3& vecMin, const Vecteur3& vecMax)
{
	float dist_squared = _rayon * _rayon;
    // fonctionne seulement si les angles du cube sont dans le bon ordre
    if (_centre._x < vecMin._x) dist_squared -= (_centre._x - vecMin._x)*(_centre._x - vecMin._x);
    else if (_centre._x > vecMax._x) dist_squared -= (_centre._x - vecMax._x)*(_centre._x - vecMax._x);
    if (_centre._y < vecMin._y) dist_squared -= (_centre._y - vecMin._y)*(_centre._y - vecMin._y);
    else if (_centre._y > vecMax._y) dist_squared -= (_centre._y - vecMax._y)*(_centre._y - vecMax._y);
    if (_centre._z < vecMin._z) dist_squared -= (_centre._z - vecMin._z)*(_centre._z - vecMin._z);
    else if (_centre._z > vecMax._z) dist_squared -= (_centre._z - vecMax._z)*(_centre._z - vecMax._z);
    return dist_squared > 0;
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

bool PrimitiveTriangle::intersectionCube(const Vecteur3& vecMin, const Vecteur3& vecMax)
{
	// verifie si les sommet sont dans la case
	if(_A._position._x >= vecMin._x && _A._position._x <= vecMax._x)
		if(_A._position._y >= vecMin._y && _A._position._y <= vecMax._y)
			if(_A._position._z >= vecMin._z && _A._position._z <= vecMax._z)
				return true;

	if(_B._position._x >= vecMin._x && _B._position._x <= vecMax._x)
		if(_B._position._y >= vecMin._y && _B._position._y <= vecMax._y)
			if(_B._position._z >= vecMin._z && _B._position._z <= vecMax._z)
				return true;

	if(_C._position._x >= vecMin._x && _C._position._x <= vecMax._x)
		if(_C._position._y >= vecMin._y && _C._position._y <= vecMax._y)
			if(_C._position._z >= vecMin._z && _C._position._z <= vecMax._z)
				return true;

	// si aucun sommet ne se trouve dans la case, verifie les axes


	return false;
}

/// [PrimitiveBoite]
PrimitiveBoite::PrimitiveBoite(Materiau* materiau, const Vecteur3 posMin, const Vecteur3 posMax)
	: Primitive(materiau)
	, _sommetMin(posMin)
	, _sommetMax(posMax)
{
}

PrimitiveBoite::~PrimitiveBoite()
{
}

bool PrimitiveBoite::calculerIntersection(const Rayon& rayon, Intersection& intersection) const
{
	// [TODO] - editer l'intersection
	//        - return true en cas d'intersection, sinon false

	float tmin, tmax, tymin, tymax, tzmin, tzmax;
	
	if (rayon._direction._x >= 0)
	{
		tmin = (_sommetMin._x - rayon._origine._x) / rayon._direction._x;
		tmax = (_sommetMax._x - rayon._origine._x) / rayon._direction._x;
	}
	else 
	{
		tmin = (_sommetMax._x - rayon._origine._x) / rayon._direction._x;
		tmax = (_sommetMin._x - rayon._origine._x) / rayon._direction._x;
	}
	
	if (rayon._direction._y >= 0) 
	{
		tymin = (_sommetMin._y - rayon._origine._y) / rayon._direction._y;
		tymax = (_sommetMax._y - rayon._origine._y) / rayon._direction._y;
	}
	else
	{
		tymin = (_sommetMax._y - rayon._origine._y) / rayon._direction._y;
		tymax = (_sommetMin._y - rayon._origine._y) / rayon._direction._y;
	}

	if ( (tmin > tymax) || (tymin > tmax) )
		return false;
	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;
	if (rayon._direction._z >= 0)
	{
		tzmin = (_sommetMin._z - rayon._origine._z) / rayon._direction._z;
		tzmax = (_sommetMax._z - rayon._origine._z) / rayon._direction._z;
	}
	else
	{
		tzmin = (_sommetMax._z - rayon._origine._z) / rayon._direction._z;
		tzmax = (_sommetMin._z - rayon._origine._z) / rayon._direction._z;
	}
	if ( (tmin > tzmax) || (tzmin > tmax) )
		return false;
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;
	
	reel offset = 0.1;

	reel distance = pow( (pow((double)tmin, 2) + pow((double)tymin, 2) + pow((double)tzmin, 2)), 0.5) ;
	Vecteur3 position = rayon.calculerPosition(intersection._distance);
	/*if( position._x < _sommetMin._x - offset && position._x > _sommetMin._x + offset
		&& position._x < _sommetMax._x - offset && position._x > _sommetMin._x + offset
		&& position._y < _sommetMin._y  - offset && position._y > _sommetMin._y + offset
		&& position._y < _sommetMax._y - offset && position._y > _sommetMin._y + offset
		&& position._z < _sommetMin._z  - offset && position._z > _sommetMin._z + offset
		&& position._z < _sommetMax._z - offset && position._z > _sommetMin._z + offset)
	{
		return false;
	}*/
	//if( (int)(position._x+position._y+position._z)%2 == 1 )
	//	return false;


	// interpolation des normales
	//Vecteur3 Nac = interpoler<Vecteur3>(_A._normale, _C._normale, vI._y);
	//Vecteur3 Nbc = interpoler<Vecteur3>(_B._normale, _C._normale, vI._y);
	intersection._normale = Vecteur3(-1.0, 0.0, 0.0);

	// interpolation des coordonnees de texture
	//Vecteur2 Tac = interpoler<Vecteur2>(_A._texcoords, _C._texcoords, vI._y);
	//Vecteur2 Tbc = interpoler<Vecteur2>(_B._texcoords, _C._texcoords, vI._y);
	intersection._texcoords = Vecteur2(0.0, 0.0);

	intersection._distance = distance;
	intersection._position = position + Vecteur3(0.1, 0.5, -0.6);
	intersection._incidence = rayon._direction;
	intersection._reflexion = VecteurReflechi(intersection._incidence, intersection._normale);
	intersection._materiau = _materiau;

	return true;
}

bool PrimitiveBoite::calculerIntersection(const Rayon& rayon, reel& distance) const
{
	// [TODO] - editer la distance
	//        - return true en cas d'intersection, sinon false

	float tmin, tmax, tymin, tymax, tzmin, tzmax;
	
	if (rayon._direction._x >= 0)
	{
		tmin = (_sommetMin._x - rayon._origine._x) / rayon._direction._x;
		tmax = (_sommetMax._x - rayon._origine._x) / rayon._direction._x;
	}
	else 
	{
		tmin = (_sommetMax._x - rayon._origine._x) / rayon._direction._x;
		tmax = (_sommetMin._x - rayon._origine._x) / rayon._direction._x;
	}
	
	if (rayon._direction._y >= 0) 
	{
		tymin = (_sommetMin._y - rayon._origine._y) / rayon._direction._y;
		tymax = (_sommetMax._y - rayon._origine._y) / rayon._direction._y;
	}
	else
	{
		tymin = (_sommetMax._y - rayon._origine._y) / rayon._direction._y;
		tymax = (_sommetMin._y - rayon._origine._y) / rayon._direction._y;
	}

	if ( (tmin > tymax) || (tymin > tmax) )
		return false;
	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;
	if (rayon._direction._z >= 0)
	{
		tzmin = (_sommetMin._z - rayon._origine._z) / rayon._direction._z;
		tzmax = (_sommetMax._z - rayon._origine._z) / rayon._direction._z;
	}
	else
	{
		tzmin = (_sommetMax._z - rayon._origine._z) / rayon._direction._z;
		tzmax = (_sommetMin._z - rayon._origine._z) / rayon._direction._z;
	}
	if ( (tmin > tzmax) || (tzmin > tmax) )
		return false;
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;

	distance = pow( (pow((double)tmin, 2) + pow((double)tymin, 2) + pow((double)tzmin, 2)), 0.5) ;

	return true;
}

bool PrimitiveBoite::intersectionCube(const Vecteur3& vecMin, const Vecteur3& vecMax)
{
	if(vecMin._x >= _sommetMin._x && vecMin._x <= _sommetMax._y)
		return true;
	if(vecMin._y >= _sommetMin._y && vecMin._y <= _sommetMax._y)
		return true;
	if(vecMin._z >= _sommetMin._z && vecMin._z <= _sommetMax._z)
		return true;
	if(vecMax._x >= _sommetMin._x && vecMax._x <= _sommetMax._y)
		return true;
	if(vecMax._y >= _sommetMin._y && vecMax._y <= _sommetMax._y)
		return true;
	if(vecMax._z >= _sommetMin._z && vecMax._z <= _sommetMax._z)
		return true;

	return false;
}
/// [PrimitiveBoite]
