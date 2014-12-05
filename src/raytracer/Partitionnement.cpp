#include "Partitionnement.h"
#include <stdlib.h>

#define EPSILON 1e-6

Partitionnement::~Partitionnement()
{}

void PartitionnementUnitaire::initialiser(AutoSet<Primitive>::const_iterator itDebut,
		AutoSet<Primitive>::const_iterator itFin)
{
	_itDebut = itDebut;
	_itFin = itFin;
}

bool PartitionnementUnitaire::visibilite(const Rayon &rayon, reel distanceMax) const
{
	// parcourt toutes les primitives de la scene
	AutoSet<Primitive>::const_iterator it;
	for (it = _itDebut; it != _itFin; ++it)
	{
		// teste si le rayon touche la primitive courante
		Primitive *primitive = *it;
		reel distance;
		if (primitive->calculerIntersection(rayon, distance) && distance < distanceMax)
		{
			return false;
		}
	}
	return true;
}

bool PartitionnementUnitaire::intersection(const Rayon &rayon, Intersection &intersection) const
{
	bool trouve = false;

	// parcourt toutes les primitives de la scene
	AutoSet<Primitive>::const_iterator it;
	for (it = _itDebut; it != _itFin; ++it)
	{
		// teste si le rayon touche la primitive courante
		Primitive *primitive = *it;
		Intersection intersectionCourante;
		if (primitive->calculerIntersection(rayon, intersectionCourante))
		{
			// retient l'intersection la plus proche
			if (!trouve || intersectionCourante._distance < intersection._distance )
			{
				trouve = true;
				intersection = intersectionCourante;
			}
		}
	}
	return trouve;
}





















/// [PartitionnementGrille]
PartitionnementGrille::PartitionnementGrille()
{
	_dimension = 1;
	_tailleCase = 4;
	_offset = -2.0;
	_caseData = new Case[_dimension*_dimension*_dimension];
}
PartitionnementGrille::~PartitionnementGrille()
{
	delete[] _caseData;
}

void PartitionnementGrille::initialiser( AutoSet<Primitive>::const_iterator itDebut,
	AutoSet<Primitive>::const_iterator itFin)
{
	_itDebut = itDebut;
	_itFin = itFin;

	//[TODO] initialiser le tableau de case a 3 dimensions
	for(int x = 0; x < _dimension; x++)
	{
		for(int y = 0; y < _dimension; y++)
		{
			for(int z = 0; z < _dimension; z++)
			{
				int num = x * (_dimension*_dimension) + y * (_dimension) + z;
				if( num >= (_dimension*_dimension*_dimension) )
					printf("Overranged !");
				else
				{
					_caseData[num].InitialiserCase( Vecteur3(x*_tailleCase+_offset, y*_tailleCase+_offset, z*_tailleCase+_offset), Vecteur3(_tailleCase, _tailleCase, _tailleCase) );
					AutoSet<Primitive>::iterator it;
					for(it = _itDebut; it != _itFin; it++)
					{
						if( (*it)->intersectionCube(_caseData[num]._boite->_sommetMin, _caseData[num]._boite->_sommetMax) )
						{
							_caseData[num].AjouterPrimitive(*it);
						}
					}
				}
			}
		}
	}
}
bool PartitionnementGrille::visibilite(const Rayon &rayon, reel distanceMax) const
{
	//[TODO] - parcourir les cases
	//       - pour chacune d'elle verifier les primitives intégrées dans la case
	
	reel distanceCaseMax = 1000;
	reel distaneCase = 1000;

	for(int x = 0; x < _dimension; x++)
	{
		for(int y = 0; y < _dimension; y++)
		{
			for(int z = 0; z < _dimension; z++)
			{
				int num = x * (_dimension*_dimension) + y * (_dimension) + z;
				if( num >= (_dimension*_dimension*_dimension) )
					printf("Overranged !");
				else
				{
					reel distance;
					//// IF RENDER SCENE
					if( _caseData[num]._boite->calculerIntersection(rayon, distaneCase))
						if( _caseData[num].calculerIntersection(rayon, distance) && distance < distanceMax )
								return false;
					//// IF RENDER GRID
					/*if( _caseData[num]._boite->calculerIntersection(rayon, distance) && distance < distanceMax )
						return false;*/
				}
			}
		}
	}
	return true;
}

bool PartitionnementGrille::intersection(const Rayon &rayon, Intersection &intersection) const
{
	bool trouve = false;

	//[TODO] - parcourir les cases
	//       - pour chacune d'elle verifier les primitives intégrées dans la case

	for(int x = 0; x < _dimension; x++)
	{
		for(int y = 0; y < _dimension; y++)
		{
			for(int z = 0; z < _dimension; z++)
			{
				int num = x * (_dimension*_dimension) + y * (_dimension) + z;
				Intersection intersectionCourante;
				//// IF RENDER SCENE
				if( _caseData[num]._boite->calculerIntersection(rayon, intersectionCourante))
					if (_caseData[num].calculerIntersection(rayon, intersectionCourante))
					{
						// retient l'intersection la plus proche
						if (!trouve || intersectionCourante._distance < intersection._distance )
						{
							trouve = true;
							intersection = intersectionCourante;
						}
					}
				//// IF RENDER GRID
				/*if( _caseData[num]._boite->calculerIntersection(rayon, intersectionCourante))
				{
					// retient l'intersection la plus proche
					if (!trouve || intersectionCourante._distance < intersection._distance )
					{
						trouve = true;
						intersection = intersectionCourante;
					}
				}*/
			}
		}
	}
	return trouve;
}

/// [PartitionnementGrille]

