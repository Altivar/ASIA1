#ifndef VECTEUR3_H_
#define VECTEUR3_H_

#include "Base.h"

/// \brief Vecteur 3D de flottants.
///
struct Vecteur3
{
	/// \brief Coordonnee x du vecteur.
	///
	reel _x;

	/// \brief Coordonnee y du vecteur.
	///
	reel _y;

	/// \brief Coordonnee z du vecteur.
	///
	reel _z;

	/// \brief Constructeur.
	///
	Vecteur3(reel x, reel y, reel z);

	/// \brief Constructeur par defaut.
	///
	Vecteur3();

	/// \brief Calcule le carre de la norme euclidienne du vecteur.
	///
	reel calculerNormeCarree() const;

	/// \brief Calcule la norme eucliedienne du vecteur.
	///
	reel calculerNorme() const;

	/// \brief Norme le vecteur.
	///
	void normer();

	/// \brief Norme le vecteur, connaissant la norme.
	///
	void normer(reel norme);

	/// \brief Retourne le vecteur oppose.
	///
	Vecteur3 operator-() const;

	/// \brief Retourne le vecteur multiplie par un scalaire.
	///
	Vecteur3 operator*(reel k) const;

	/// \brief Retourne le produit membre a membre des 2 vecteurs.
	///
	Vecteur3 operator*(const Vecteur3 & v) const;

	/// \brief Retourne la soustraction membre a membre des 2 vecteurs.
	///
	Vecteur3 operator-(const Vecteur3 & v) const;

	/// \brief Retourne l'addition membre a membre des 2 vecteurs.
	///
	Vecteur3 operator+(const Vecteur3 & v) const;

	/// \brief Multiplie les membres du vecteur par un scalaire.
	///
	Vecteur3 & operator*=(reel k);

	/// \brief ajoute un scalaire aux membres du vecteur.
	///
	Vecteur3 & operator+=(const Vecteur3 & v);
};

/// \brief Calcule le produit scalaire de 2 vecteurs.
///
reel ProduitScalaire(const Vecteur3 &v1, const Vecteur3 &v2);

/// \brief Calcule le produit vectoriel de 2 vecteurs.
///
Vecteur3 ProduitVectoriel(const Vecteur3 &v1, const Vecteur3 &v2);

/// \brief Calcule le vecteur reflechi d'un vecteur I incident a une surface de normale N.
///
/// I est dirige vers la surface, N et le vecteur reflechi sont diriges vers l'exterieur.
///
Vecteur3 VecteurReflechi(const Vecteur3 & I, const Vecteur3 & N);

#endif /* VECTEUR3_H_ */


