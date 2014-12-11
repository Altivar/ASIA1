#include "Partitionnement.h"
#include <stdlib.h>
#include <iostream>

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













enum ChoixAlgo 
{
	GRILLE_DIMENSIONS_FIXES = 0,
	GRILLE_DIMENSIONS_VARIABLES,
	GRILLE_SUBDIVISION, // inclu la dimension variable
	GRILLE_BRESENHAM
};
ChoixAlgo choix_algo = GRILLE_SUBDIVISION;
bool RenduGrille = false;






/// [PartitionnementGrille]
PartitionnementGrille::PartitionnementGrille()
{
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

	if( choix_algo == ChoixAlgo::GRILLE_DIMENSIONS_FIXES )
	{
		_3DOffset._x = -2;
		_3DOffset._y = -2;
		_3DOffset._z = -2;
		_3DDimension._x = 4;
		_3DDimension._y = 4;
		_3DDimension._z = 4;
		_3DTailleCase._x = 1;
		_3DTailleCase._y = 1;
		_3DTailleCase._z = 1;

		_nbCases = _3DDimension._x*_3DDimension._y*_3DDimension._z;
		_caseData = new Case[_nbCases];
	}
	else
	{
		// [INIT THE GRID VALUES]
		reel xmin = 9999, ymin = 9999, zmin = 9999, xmax = -9999, ymax = -9999, zmax = -9999;

		AutoSet<Primitive>::iterator it;
		for(it = _itDebut; it != _itFin; it++)
		{
			Vecteur3 vecMin = (*it)->GetMinPos();
			Vecteur3 vecMax = (*it)->GetMaxPos();

			if( xmin > vecMin._x )
				xmin = vecMin._x;
			if( ymin > vecMin._y )
				ymin = vecMin._y;
			if( zmin > vecMin._z )
				zmin = vecMin._z;

			if( xmax < vecMax._x )
				xmax = vecMax._x;
			if( ymax < vecMax._y )
				ymax = vecMax._y;
			if( zmax < vecMax._z )
				zmax = vecMax._z;
		}

		_3DOffset._x = xmin;
		_3DOffset._y = ymin;
		_3DOffset._z = zmin;
		_3DDimension._x = (int)(xmax-xmin+0.5);
		_3DDimension._y = (int)(ymax-ymin+0.5);
		_3DDimension._z = (int)(zmax-zmin+0.5);
		_3DTailleCase._x = (xmax-xmin) / _3DDimension._x;
		_3DTailleCase._y = (ymax-ymin) / _3DDimension._y;
		_3DTailleCase._z = (zmax-zmin) / _3DDimension._z;

		_nbCases = _3DDimension._x*_3DDimension._y*_3DDimension._z;
		_caseData = new Case[_nbCases];
		// [INIT THE GRID VALUES]

		
	}
	


	// [INIT 3D TABLE]
	for(int x = 0; x < _3DDimension._x; x++)
	{
		for(int y = 0; y < _3DDimension._y; y++)
		{
			for(int z = 0; z < _3DDimension._z; z++)
			{
				int num = x * (_3DDimension._y*_3DDimension._z) + y * (_3DDimension._z) + z;
				if( num >= (_3DDimension._x*_3DDimension._y*_3DDimension._z) )
					printf("Overranged !");
				else
				{
					_caseData[num].InitialiserCase( Vecteur3(x*_3DTailleCase._x+_3DOffset._x, y*_3DTailleCase._y+_3DOffset._y, z*_3DTailleCase._z+_3DOffset._z), _3DTailleCase );
					AjouterPrimitive( _caseData[num] );
					if( choix_algo == ChoixAlgo::GRILLE_SUBDIVISION )
						_caseData[num].Subdiviser();
				}
			}
		}
	}
	// [INIT 3D TABLE]

}


bool PartitionnementGrille::visibilite(const Rayon &rayon, reel distanceMax) const
{
	//[TODO] - parcourir les cases
	//       - pour chacune d'elle verifier les primitives intégrées dans la case
	
	reel distanceCaseMax = 1000;
	reel distaneCase = 1000;

	for(int num = 0; num < _nbCases; num++)
	{
		reel distance;

		if( RenduGrille )
		{
			//// IF RENDER GRID
			if( _caseData[num]._boite->calculerIntersection(rayon, distance) && distance < distanceMax )
				return false;
		}
		else
		{
			//// IF RENDER SCENE
			if( _caseData[num]._boite->calculerIntersection(rayon, distaneCase))
				//if( _caseData[num].calculerIntersection(rayon, distance) && distance < distanceMax )
				if( !_caseData[num].calculerIntersection(rayon, distance, distanceMax) )
					return false;
		}
	}
	return true;
}

bool PartitionnementGrille::intersection(const Rayon &rayon, Intersection &intersection) const
{
	bool trouve = false;

	//[TODO] - parcourir les cases
	//       - pour chacune d'elle verifier les primitives intégrées dans la case

	for(int num = 0; num < _nbCases; num++)
	{
		Intersection intersectionCourante;

		if( RenduGrille )
		{
			//// IF RENDER GRID
			if( _caseData[num]._boite->calculerIntersection(rayon, intersectionCourante))
			{
				// retient l'intersection la plus proche
				if (!trouve || intersectionCourante._distance < intersection._distance )
				{
					trouve = true;
					intersection = intersectionCourante;
				}
			}
		}
		else
		{
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
		}

	}
	return trouve;
}

void PartitionnementGrille::AjouterPrimitive( Case& c )
{
	AutoSet<Primitive>::iterator it;
	for(it = _itDebut; it != _itFin; it++)
	{
		if( (*it)->intersectionCube(c._boite->_sommetMin, c._boite->_sommetMax) )
		{
			c.AjouterPrimitive(*it);
		}
	}
}
/// [PartitionnementGrille]

