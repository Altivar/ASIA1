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

Vecteur3 PrimitiveSphere::GetMaxPos()
{
	return Vecteur3( _centre._x+_rayon, _centre._y+_rayon, _centre._z+_rayon );
}

Vecteur3 PrimitiveSphere::GetMinPos()
{
	return Vecteur3( _centre._x-_rayon, _centre._y-_rayon, _centre._z-_rayon );
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

Vecteur3 PrimitiveTriangle::GetMaxPos()
{
	reel x = _A._position._x, y = _A._position._y, z = _A._position._z;
	if( x < _B._position._x )
		x = _B._position._x;
	if( x < _C._position._x )
		x = _C._position._x;
	
	if( y < _B._position._y )
		y = _B._position._y;
	if( y < _C._position._y )
		y = _C._position._y;
	
	if( z < _B._position._z )
		z = _B._position._z;
	if( z < _C._position._z )
		z = _C._position._z;

	return Vecteur3( x, y, z );
}

Vecteur3 PrimitiveTriangle::GetMinPos()
{
	reel x = _A._position._x, y = _A._position._y, z = _A._position._z;
	if( x > _B._position._x )
		x = _B._position._x;
	if( x > _C._position._x )
		x = _C._position._x;
	
	if( y > _B._position._y )
		y = _B._position._y;
	if( y > _C._position._y )
		y = _C._position._y;
	
	if( z > _B._position._z )
		z = _B._position._z;
	if( z > _C._position._z )
		z = _C._position._z;

	return Vecteur3( x, y, z );
}

void PrimitiveTriangle::calculerProjectionSurImage(Vecteur2 &a, Vecteur2 &b, Vecteur2 &c, const CameraPinhole &camera)
{
	// Projection de chaque sommet
	a = camera.mondeVersImage((const Vecteur3 &)_A);
	b = camera.mondeVersImage((const Vecteur3 &)_B);
	c = camera.mondeVersImage((const Vecteur3 &)_C);
}




/// [ALGO INTERSECTION BOITE/TRIANGLE]

bool GetIntersection( float fDst1, float fDst2, Vecteur3& P1, Vecteur3& P2)
{
	if ( (fDst1 * fDst2) >= 0.0f) return false;
	if ( fDst1 == fDst2) return false; 
	return true;
}

// returns true if line (L1, L2) intersects with the box (B1, B2)
bool CheckLineBox( Vecteur3 B1, Vecteur3 B2, Vecteur3& L1, Vecteur3& L2)
{
	if (L2._x < B1._x && L1._x < B1._x) return false;
	if (L2._x > B2._x && L1._x > B2._x) return false;
	if (L2._y < B1._y && L1._y < B1._y) return false;
	if (L2._y > B2._y && L1._y > B2._y) return false;
	if (L2._z < B1._z && L1._z < B1._z) return false;
	if (L2._z > B2._z && L1._z > B2._z) return false;
	if (L1._x > B1._x && L1._x < B2._x &&
		L1._y > B1._y && L1._y < B2._y &&
		L1._z > B1._z && L1._z < B2._z) 
		{return true;}
	if ( (GetIntersection( L1._x-B1._x, L2._x-B1._x, L1, L2))
	  || (GetIntersection( L1._y-B1._y, L2._y-B1._y, L1, L2)) 
	  || (GetIntersection( L1._z-B1._z, L2._z-B1._z, L1, L2)) 
	  || (GetIntersection( L1._x-B2._x, L2._x-B2._x, L1, L2)) 
	  || (GetIntersection( L1._y-B2._y, L2._y-B2._y, L1, L2)) 
	  || (GetIntersection( L1._z-B2._z, L2._z-B2._z, L1, L2)))
		return true;

	return false;
}


bool PrimitiveTriangle::CheckLineTriangle( Vecteur3& L1, Vecteur3& L2 )
{
	reel da, db;
	Vecteur3 x;

	da = ProduitScalaire( (L1 - _A._position), _normale);
	db = ProduitScalaire( (L2 - _A._position), _normale);
	// si les point sont du même coté du triangle return false
	if( da*db >= 0 )
		return false;

	x = (L2*da - L1*db) / (da-db);

	if( ProduitScalaire( (x-_A._position), ((_C._position-_A._position)*_normale) ) > 0
	 && ProduitScalaire( (x-_A._position), ((_B._position-_A._position)*_normale) ) > 0
	 && ProduitScalaire( (x-_B._position), ((_C._position-_B._position)*_normale) ) > 0 )
	 return true;

	return false;
}

/// [ALGO INTERSECTION BOITE/TRIANGLE]


bool PrimitiveTriangle::intersectionCube(const Vecteur3& vecMin, const Vecteur3& vecMax)
{
	
	// si aucun sommet ne se trouve dans la case, verifie si les aretes du triangle passe dans la boîte
	if( CheckLineBox(vecMin, vecMax, _A._position, _B._position) )
		return true;
	if( CheckLineBox(vecMin, vecMax, _A._position, _C._position) )
		return true;
	if( CheckLineBox(vecMin, vecMax, _B._position, _C._position) )
		return true;


	// si aucune arete du triangle ne passe dans la boite, test si le diagonales de la boite passe dans le triangle
	Vecteur3 A, B;
	A = vecMin;
	B = vecMax;
	if( CheckLineTriangle(A,B) )
		return true;
	A = Vecteur3(vecMin._x, vecMax._y, vecMin._z);
	B = Vecteur3(vecMax._x, vecMin._y, vecMax._z);
	if( CheckLineTriangle(A,B) )
		return true;
	A = Vecteur3(vecMin._x, vecMin._y, vecMax._z);
	B = Vecteur3(vecMax._x, vecMax._y, vecMin._z);
	if( CheckLineTriangle(A,B) )
		return true;
	A = Vecteur3(vecMin._x, vecMax._y, vecMax._z);
	B = Vecteur3(vecMax._x, vecMin._y, vecMin._z);
	if( CheckLineTriangle(A,B) )
		return true;

	// si toujours aucune collision, return false
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
	
	// calcul de la normale
	Vecteur3 centreCube = (_sommetMax-_sommetMin) / 2;
	Vecteur3 direction = position - centreCube;
	if( abs(direction._x) >= abs(direction._y) && abs(direction._x) >= abs(direction._z) )
	{
		if( direction._x < 0 )
			intersection._normale = Vecteur3(-1.0, 0.0, 0.0);
		if( direction._x > 0 )
			intersection._normale = Vecteur3(1.0, 0.0, 0.0);
	}
	else if( abs(direction._y) >= abs(direction._x) && abs(direction._y) >= abs(direction._z) )
	{
		if( direction._y < 0 )
			intersection._normale = Vecteur3(0.0, -1.0, 0.0);
		if( direction._y > 0 )
			intersection._normale = Vecteur3(0.0, 1.0, 0.0);
	}
	else //if( abs(direction._z) >= abs(direction._x) && abs(direction._z) >= abs(direction._y) )
	{
		if( direction._z < 0 )
			intersection._normale = Vecteur3(0.0, 0.0, -1.0);
		if( direction._z > 0 )
			intersection._normale = Vecteur3(0.0, 0.0, 1.0);
	}
	intersection._normale = Vecteur3(0.0, 0.0, 0.0);
	
	
	intersection._texcoords = Vecteur2(0.0, 0.0);
	intersection._distance = distance;
	intersection._position = position;
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

inline Vecteur3 PrimitiveBoite::GetMaxPos()
{
	return _sommetMax;
}

inline Vecteur3 PrimitiveBoite::GetMinPos()
{
	return _sommetMin;
}

void PrimitiveBoite::calculerProjectionSurImage(Vecteur2 &a, Vecteur2 &b, Vecteur2 &c, Vecteur2 &d,
												Vecteur2 &e, Vecteur2 &f, Vecteur2 &g, Vecteur2 &h,
												const CameraPinhole &camera)
{
	
	Vecteur3 A = _sommetMin;
	Vecteur3 B = Vecteur3( _sommetMax._x, _sommetMin._y, _sommetMin._z );
	Vecteur3 C = Vecteur3( _sommetMin._x, _sommetMax._y, _sommetMin._z );
	Vecteur3 D = Vecteur3( _sommetMin._x, _sommetMin._y, _sommetMax._z );
	Vecteur3 E = _sommetMax;
	Vecteur3 F = Vecteur3( _sommetMin._x, _sommetMax._y, _sommetMax._z );
	Vecteur3 G = Vecteur3( _sommetMax._x, _sommetMin._y, _sommetMax._z );
	Vecteur3 H = Vecteur3( _sommetMax._x, _sommetMax._y, _sommetMin._z );

	// Projection de chaque sommet
	a = camera.mondeVersImage((const Vecteur3 &)A);
	b = camera.mondeVersImage((const Vecteur3 &)B);
	c = camera.mondeVersImage((const Vecteur3 &)C);
	d = camera.mondeVersImage((const Vecteur3 &)D);
	e = camera.mondeVersImage((const Vecteur3 &)E);
	f = camera.mondeVersImage((const Vecteur3 &)F);
	g = camera.mondeVersImage((const Vecteur3 &)G);
	h = camera.mondeVersImage((const Vecteur3 &)H);

}

/// [PrimitiveBoite]
