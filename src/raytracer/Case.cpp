#include "Case.h"

Case::Case(void)
{
}

Case::~Case(void)
{
	delete _boite;
	delete _materiau_fil_de_fer;
}

void Case::InitialiserCase(Vecteur3 &position, Vecteur3 &dimension)
{
	_position = position;
	_dimension = dimension;

	//[TODO] initialiser le materiau fil de fer
	_materiau_fil_de_fer = new MateriauFilDeFer(Couleur(position._x*0.2+0.5, position._y*0.2+0.5, position._z*0.2+0.5, 1.0));
	//[TODO] initialiser la primitive boite
	_boite = new PrimitiveBoite(_materiau_fil_de_fer, _position, _position+_dimension);
}

void Case::AjouterPrimitive(Primitive* primitive)
{
	_primitiveData.push_back(primitive);
}

bool Case::calculerIntersection(const Rayon &rayon, Intersection &intersection)
{
	if(_primitiveData.size() <= 0 )
		return false;

	bool result = false;

	std::vector<Primitive*>::iterator it;
	for(it = _primitiveData.begin(); it != _primitiveData.end(); it++)
	{
		if( (*it)->calculerIntersection(rayon, intersection) )
			result = true;
	}
	return result;
}
	
bool Case::calculerIntersection(const Rayon &rayon, reel &distance)
{
	if(_primitiveData.size() <= 0 )
		return false;

	bool result = false;

	std::vector<Primitive*>::iterator it;
	for(it = _primitiveData.begin(); it != _primitiveData.end(); it++)
	{
		if( (*it)->calculerIntersection(rayon, distance) )
			result = true;
	}
	return result;
}
	
