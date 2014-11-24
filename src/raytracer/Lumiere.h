
#ifndef LUMIERE_H_
#define LUMIERE_H_

#include "Base.h"
#include "Couleur.h"
#include "Vecteur3.h"

class Scene;
struct Intersection;
struct Eclairement;

/// \brief Definit une souce de lumiere virtuelle.
///
/// Classe abstraite.
///
struct Lumiere
{
	/// \brief Nom de la source.
	///
	String _nom;

	/// \brief Calcule l'eclairement apporte par la source de lumiere au point d'intersection.
	///
	/// Retourne true si la source est visible depuis le point d'intersection.
	///
	virtual bool calculerEclairement(const Intersection &intersection,
			const Scene &scene, Eclairement &eclairement) const = 0;
};

/// \brief Definit une souce de lumiere virtuelle.
///
/// Source de lumiere ponctuelle omnidirectionnelle.
///
struct LumierePoint : Lumiere
{
	/// \brief Position de la source.
	///
	Vecteur3 _position;

	/// \brief Couleur de la source.
	///
	Couleur _couleur;

	/// \brief Constructeur.
	///
	LumierePoint(const Vecteur3 &position, const Couleur &couleur);

	/// \brief Calcule l'eclairement apporte par la source de lumiere au point d'intersection.
	///
	/// Retourne true si la source est visible depuis le point d'intersection.
	///
	bool calculerEclairement(const Intersection &intersection,
			const Scene &scene, Eclairement &eclairement) const;
};


#endif /* LUMIERE_H_ */

