#include "Partitionnement.h"

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


