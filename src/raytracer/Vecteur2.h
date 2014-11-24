
#ifndef VECTEUR2_H_
#define VECTEUR2_H_

#include "Base.h"

/// \brief Vecteur 2D de flottants.
///
struct Vecteur2
{
	/// \brief Coordonnee u du vecteur.
	///
	reel _u;

	/// \brief Coordonnee v du vecteur.
	///
	reel _v;

	/// \brief Constructeur.
	///
	Vecteur2(reel u, reel v);

	/// \brief Constructeur par defaut.
	///
	Vecteur2();

	/// \brief Addition de deux vecteurs.
	///
	Vecteur2 operator+(const Vecteur2 &v) const;

	/// \brief Soustraction de deux vecteurs.
	///
	Vecteur2 operator-(const Vecteur2 &v) const;

	/// \brief Produit par un scalaire.
	///
	Vecteur2 operator*(reel k)const;

};

#endif /* VECTEUR2_H_ */
