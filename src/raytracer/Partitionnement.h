
#ifndef PARTITIONNEMENT_H_
#define PARTITIONNEMENT_H_

#include "Base.h"
#include "Vecteur3.h"
#include "Intersection.h"
#include "Primitive.h"
#include "Rayon.h"

/// \brief Partitionnement des primitives.
///
class Partitionnement
{
public:
	/// \brief Destructeur
	///
	virtual ~Partitionnement();

	/// \brief Initialise la structure de partitionnement.
	///
	/// Cette fonction doit etre appelee avant d'utiliser les fonctions pointsVisibles et intersection.
	///
	virtual void initialiser(AutoSet<Primitive>::const_iterator itDebut,
			AutoSet<Primitive>::const_iterator itFin) = 0;

	/// \brief Retourne vrai si le rayon n'est pas interrompu sur une certaine distance.
	///
	/// La structure de partitionnement doit avoir ete initialisee.
	///
	virtual bool visibilite(const Rayon &rayon, reel distance) const = 0;

	/// \brief Determine l'intersection la plus proche.
	/// La structure de partitionnement doit avoir ete initialisee.
	///
	virtual bool intersection(const Rayon &rayon, Intersection &intersection) const = 0;
};


class PartitionnementUnitaire : public Partitionnement
{
	AutoSet<Primitive>::const_iterator _itDebut;
	AutoSet<Primitive>::const_iterator _itFin;

public:

	/// \brief Initialise la structure de partitionnement.
	///
	/// Cette fonction doit etre appelee avant d'utiliser les fonctions pointsVisibles et intersection.
	///
	void initialiser(AutoSet<Primitive>::const_iterator itDebut,
			AutoSet<Primitive>::const_iterator itFin);

	/// \brief Retourne vrai si le rayon n'est pas interrompu sur une certaine distance.
	///
	/// La structure de partitionnement doit avoir ete initialisee.
	///
	bool visibilite(const Rayon &rayon, reel distance) const;

	/// \brief Determine l'intersection la plus proche.
	/// La structure de partitionnement doit avoir ete initialisee.
	///
	bool intersection(const Rayon &rayon, Intersection &intersection) const;
};


#endif /* PARTITIONNEMENT_H_ */
