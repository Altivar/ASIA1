#ifndef MATRICE33_H_
#define MATRICE33_H_

#include "Base.h"
#include "Vecteur3.h"

/// \brief Matrice 3x3 de flottants.
///
struct Matrice33
{
	/// \brief Remplit la matrice d'apres un tableau de flottants.
	///
	/// Le tableau doit contenir les 3 lignes de 3 coefficients, a la suite.
	///
	void remplir(reel coefs[9]);

	/// \brief Remplit la matrice d'apres 3 vecteurs colonnes.
	///
	void remplir(const Vecteur3 & vx, const Vecteur3 & vy, const Vecteur3 & vz);

	/// \brief Divise tous les coefficients par un scalaire.
	///
	Matrice33 operator*(double k) const;

	/// \brief Multiplie la matrice par un vecteur colonne.
	///
	Vecteur3 operator*(const Vecteur3& v) const;

	/// \brief Calcule la matrice transposee.
	///
	Matrice33 transposer() const;

	// private
	reel _00, _01, _02;
	reel _10, _11, _12;
	reel _20, _21, _22;

};

/// \brief Calcule le determinant de la matrice formee par les vecteurs colonnes a0, a1, a2.
///
reel calculerDeterminant(const Vecteur3 &u, const Vecteur3 &v, const Vecteur3 &w);

/// \brief Resoud le systeme lineaire Ax = b par calcul de detreminants.
///
/// Si le systeme n'a pas de solution, retourne false.
/// Sinon ecrit la solution dans x.
///
bool resoudreSysteme(const Vecteur3 &a0, const Vecteur3 &a1, const Vecteur3 &a2,
		Vecteur3 &x, const Vecteur3 &b);

#endif /* MATRICE33_H_ */

