
#ifndef COULEUR_H_
#define COULEUR_H_

#include "Base.h"

/// \brief Definit une couleur sur 4 canaux (RGBA) en flottants normalises (sur [0, 1]).
///
struct Couleur
{
	/// \brief Canal rouge.
	///
	reel _r;

	/// \brief Canal vert.
	///
	reel _g;

	/// \brief Canal bleu.
	///
	reel _b;

	/// \brief Canal alpha.
	///
	reel  _a;

	/// \brief Constructeur permettant d'initialiser les canaux.
	///
	Couleur(reel r, reel g, reel b, reel a);

	/// \brief Constructeur par defaut. Initialise tous les canaux a 0.
	///
	Couleur();

	/// \brief Addition de deux couleurs.
	///
	Couleur operator+(const Couleur &c) const;

	/// \brief Produit couleur-scalaire.
	///
	/// Ne modifie pas le canal alpha.
	///
	Couleur operator*(reel k) const;

	/// \brief Produit membre a membre de deux couleurs.
	///
	Couleur operator*(const Couleur &c) const;

	/// \brief Addition de deux couleurs.
	///
	Couleur & operator+=(const Couleur &c) ;
};

#endif

