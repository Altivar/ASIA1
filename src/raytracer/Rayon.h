#ifndef RAYON_H_
#define RAYON_H_

#define EPSILON 1e-6

#include "Vecteur3.h"

/// \brief Definit un rayon.
///
struct Rayon
{
	/// \brief Constructeur.
	///
	Rayon(const Vecteur3 &origine, const Vecteur3 &direction, int rebond=0);

	/// \brief Avance la position sur le rayon.
	///
	void avancer(reel distance=EPSILON);

	/// \brief Calcule la position sur le rayon a l'instant t.
	///
	Vecteur3 calculerPosition(reel t) const;

	/// \brief Position d'origine du rayon.
	///
	Vecteur3 _origine;

	/// \brief Direction du rayon.
	///
	Vecteur3 _direction;

	/// \brief Numero d'iteration du rayon.
	///
	/// Permet de connaitre le nombre de rebonds realises.
	///
	int _rebond;

	/// \brief Contribution du rayon.
	///
	/// Permet de connaitre la contribution du rayon a la couleur finale.
	///
	//reel _contribution;
};

#endif /* RAYON_H_ */
