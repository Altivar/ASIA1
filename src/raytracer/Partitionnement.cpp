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





















/// [PartitionnementGrille]
PartitionnementGrille::PartitionnementGrille()
{
	_listCases.clear();
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

	_3DOffset = Vecteur3( xmin, ymin, zmin );
	_3DDimension._x = (int)(xmax-xmin+0.5);
	_3DDimension._y = (int)(ymax-ymin+0.5);
	_3DDimension._z = (int)(zmax-zmin+0.5);
	_3DTailleCase._x = (xmax-xmin) / _3DDimension._x;
	_3DTailleCase._y = (ymax-ymin) / _3DDimension._y;
	_3DTailleCase._z = (zmax-zmin) / _3DDimension._z;

	_nbCases = _3DDimension._x*_3DDimension._y*_3DDimension._z;
	_caseData = new Case[_nbCases];
	// [INIT THE GRID VALUES]




	//[TODO] initialiser le tableau de case a 3 dimensions
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
					if( _caseData[num].GetNbPrimitive() >= 40 )
						_listCases.append( num );
				}
			}
		}
	}

	// si il y a des cases contenant trop de primitives entame la division
	if( _listCases.size() > 0 )
	{
		std::cout << "Nombre de cases subdivisées : " << _listCases.size() << "\n" << std::endl;
		try
		{
			if( !diviserCases() )
				throw 0;
		}
		catch ( int err )
		{
			std::cout << "Impossible de diviser les cases correctement..." << std::endl;
		}
	}
	else
		std::cout << "Aucune case subdivisée\n" << std::endl;

}
bool PartitionnementGrille::visibilite(const Rayon &rayon, reel distanceMax) const
{
	//[TODO] - parcourir les cases
	//       - pour chacune d'elle verifier les primitives intégrées dans la case
	
	reel distanceCaseMax = 1000;
	reel distaneCase = 1000;

	for(int num = 0; num < _nbCases; num++)
	{
		//if( num >= (_3DDimension._x*_3DDimension._y*_3DDimension._z) )
		//	printf("Overranged !");
		//else
		{
			reel distance;
			//// IF RENDER SCENE
			if( _caseData[num]._boite->calculerIntersection(rayon, distaneCase))
				if( _caseData[num].calculerIntersection(rayon, distance) && distance < distanceMax )
						return false;
			//// IF RENDER GRID
			/*if( _caseData[num]._boite->calculerIntersection(rayon, distance) && distance < distanceMax )
				return false;*/
			//// END IF
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
		//if( num >= (_3DDimension._x*_3DDimension._y*_3DDimension._z) )
		//	printf("Overranged !");
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
		//// END IF
	}
	return trouve;
}

bool PartitionnementGrille::diviserCases()
{
	Case* tempData;
	int newNbCases = _nbCases + _listCases.size() * 7;
	tempData = new Case[newNbCases];

	int currentNum = 0;

	// pour chaque case de la liste
	QList<int>::iterator it;
	for(it = _listCases.begin(); it != _listCases.end(); it++)
	{
		// crée une valeur de position et une de dimension
		Vecteur3 position( _caseData[*it]._position );
		Vecteur3 offset( 0, 0, 0 );
		Vecteur3 dimension( _3DTailleCase / 2 );

		// crée 8 cases égales
		tempData[currentNum].InitialiserCase( position + offset, dimension );
		AjouterPrimitive( tempData[currentNum] );
		currentNum++;
		
		offset = Vecteur3( dimension._x, 0, 0 );
		tempData[currentNum].InitialiserCase( position + offset, dimension );
		AjouterPrimitive( tempData[currentNum] );
		currentNum++;
		
		offset = Vecteur3( dimension._x, dimension._y, 0 );
		tempData[currentNum].InitialiserCase( position + offset, dimension );
		AjouterPrimitive( tempData[currentNum] );
		currentNum++;
		
		offset = Vecteur3( dimension._x, 0, dimension._z );
		tempData[currentNum].InitialiserCase( position + offset, dimension );
		AjouterPrimitive( tempData[currentNum] );
		currentNum++;
		
		offset = Vecteur3( dimension._x, dimension._y, dimension._z );
		tempData[currentNum].InitialiserCase( position + offset, dimension );
		AjouterPrimitive( tempData[currentNum] );
		currentNum++;

		offset = Vecteur3( 0, dimension._y, 0 );
		tempData[currentNum].InitialiserCase( position + offset, dimension );
		AjouterPrimitive( tempData[currentNum] );
		currentNum++;
		
		offset = Vecteur3( 0, 0, dimension._z );
		tempData[currentNum].InitialiserCase( position + offset, dimension );
		AjouterPrimitive( tempData[currentNum] );
		currentNum++;
		
		offset = Vecteur3( 0, dimension._y, dimension._z );
		tempData[currentNum].InitialiserCase( position + offset, dimension );
		AjouterPrimitive( tempData[currentNum] );
		currentNum++;
	}

	for( int i = 0; i < _nbCases; i++ )
	{
		if( !_listCases.contains(i) )
		{
			if( currentNum >= newNbCases )
				return false;
			tempData[currentNum].InitialiserCase( _caseData[i]._position, _caseData[i]._dimension );
			tempData[currentNum].SetPrimitives( _caseData[i]._primitiveData );
			currentNum++;
		}
	}

	// met en place les nouvelles données
	delete[] _caseData;
	_caseData = tempData;
	_nbCases = newNbCases;

	return true;
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

