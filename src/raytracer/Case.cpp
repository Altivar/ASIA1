#include "Case.h"

Case::Case(void)
{
}

Case::~Case(void)
{
	if( _subdivise )
		delete[] _caseData;
	delete _boite;
	delete _materiau_fil_de_fer;
}

void Case::InitialiserCase(Vecteur3 &position, Vecteur3 &dimension)
{
	_position = position;
	_dimension = dimension;

	_subdivise = false;

	//[TODO] initialiser le materiau fil de fer
	_materiau_fil_de_fer = new MateriauFilDeFer(Couleur(position._x*0.2+0.5, position._y*0.2+0.5, position._z*0.2+0.5, 1.0));
	//[TODO] initialiser la primitive boite
	_boite = new PrimitiveBoite(_materiau_fil_de_fer, _position, _position+_dimension);
}

void Case::AjouterPrimitive(Primitive* primitive)
{
	_primitiveData.push_back(primitive);
}

void Case::SetPrimitives( std::vector<Primitive*>& data )
{
	_primitiveData = data;
}

bool Case::calculerIntersection(const Rayon &rayon, Intersection &intersection)
{
	if(_primitiveData.size() <= 0 )
		return false;

	bool result = false;

	if( _subdivise )
	{
	
		for(int num = 0; num < 8; num++)
		{
			Intersection intersectionCourante;

			//// IF RENDER SCENE
			if( _caseData[num]._boite->calculerIntersection(rayon, intersectionCourante))
				if (_caseData[num].calculerIntersection(rayon, intersectionCourante))
				{
					// retient l'intersection la plus proche
					if (!result || intersectionCourante._distance < intersection._distance )
					{
						result = true;
						intersection = intersectionCourante;
					}
				}

		}
	
	}
	else
	{

		Intersection intersectionCourante;
		std::vector<Primitive*>::iterator it;
		for(it = _primitiveData.begin(); it != _primitiveData.end(); it++)
		{
			if( (*it)->calculerIntersection(rayon, intersectionCourante) )	
			{
				// retient l'intersection la plus proche
				if (!result || intersectionCourante._distance < intersection._distance )
				{
					result = true;
					intersection = intersectionCourante;
				}
			}
		}		

	}
	
	return result;
}
	
bool Case::calculerIntersection(const Rayon &rayon, reel &distance, reel distanceMax)
{
	if(_primitiveData.size() <= 0 )
		return true;


	if( _subdivise )
	{
		reel distance;
		reel distaneCase;
		for(int num = 0; num < 8; num++)
		{
			if( _caseData[num]._boite->calculerIntersection(rayon, distaneCase))
				if( !_caseData[num].calculerIntersection(rayon, distance, distanceMax) )
					return false;
		}
		return true;
	}
	else
	{
		bool result = true;
		std::vector<Primitive*>::iterator it;
		for(it = _primitiveData.begin(); it != _primitiveData.end(); it++)
		{
			if( (*it)->calculerIntersection(rayon, distance) && distance < distanceMax )
				result = false;
		}
		return result;
	}
}
	
void Case::Subdiviser()
{
	if( _primitiveData.size() < 40 )
		return;

	printf("SUB !!! \n");

	Vecteur3 dimensionSubdivision = _dimension /2;

	// initialise le tableau de case de la case
	_caseData = new Case[8];

	// crée un iterateur pour parcourir le tableau de primitives
	std::vector<Primitive*>::iterator it;

	for(int x = 0; x < 2; x++)
	{
		for(int y = 0; y < 2; y++)
		{
			for(int z = 0; z < 2; z++)
			{
				int num = x*4+y*2+z;
				// Initialise la case
				_caseData[num].InitialiserCase( 
					Vecteur3( _position._x+dimensionSubdivision._x*x, _position._y+dimensionSubdivision._y*y, _position._z+dimensionSubdivision._z*z ),
					dimensionSubdivision );
				// verifie et ajoute les primitives incluse dans la nouvelle case
				for(it = _primitiveData.begin(); it != _primitiveData.end(); it++)
				{
					if( (*it)->intersectionCube( _caseData[num]._position, _caseData[num]._position + _caseData[num]._dimension ) )
						_caseData[num].AjouterPrimitive(*it);
				}
			}
		}
	}

	_subdivise = true;
}

