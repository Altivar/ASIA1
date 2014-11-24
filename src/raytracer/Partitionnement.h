
#ifndef PARTITIONNEMENT_H_
#define PARTITIONNEMENT_H_

#include "Base.h"
#include "Vecteur3.h"
#include "Intersection.h"
#include "Primitive.h"
#include "Rayon.h"
#include "Case.h"

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


/// [PartitionnementGrille]
class PartitionnementGrille : public Partitionnement
{

	AutoSet<Primitive>::const_iterator _itDebut;
	AutoSet<Primitive>::const_iterator _itFin;

	// [TODO] declarer un tableau de case sur 3 dimensions
	Case*** _caseData;

public:
	
	// initialise les iterateurs
	void initialiser(AutoSet<Primitive>::const_iterator itDebut, AutoSet<Primitive>::const_iterator itFin);

	// retourne vrai si le rayon n'est pas interrompu sur une certaine distance
	bool visibilite(const Rayon& rayon, reel distance) const;

	// d�termine l'intersection la plus proche (l'initialisation doit avoir �t� effectu�e)
	bool intersection(const Rayon& rayon, Intersection& intersection) const;

};
/// [PartitionnementGrille]

#endif /* PARTITIONNEMENT_H_ */
