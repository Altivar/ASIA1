#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_

#include "Intersection.h"
#include "Rayon.h"
#include "Base.h"
#include "Vecteur2.h"
#include "Materiau.h"

/// \brief Primitive geometrique.
///
/// Classe abstraite a deriver.
///
struct Primitive
{
	/// \brief Materiau de la primitive.
	///
	Materiau *_materiau;

	/// \brief Contructeur.
	///
	Primitive(Materiau *materiau);

	/// \brief Fonction de calcul d'intersection rayon-primitive a redefinir.
	///
	/// Si une intersection est detectee, remplit la structure Intersection et retourne true.
	///
	virtual bool calculerIntersection(const Rayon &, Intersection &) const = 0;

	/// \brief Fonction de calcul d'intersection rayon-primitive a redefinir.
	///
	/// Si une intersection est detectee, retourne true sans calculer tous les parametres de l'intersection.
	/// Si une intersection est detectee, distance est initialise.
	///
	virtual bool calculerIntersection(const Rayon &, reel &distance) const = 0;
};

struct Sommet
{
	/// \brief Position du sommet dans le repere monde.
	///
	Vecteur3 _position;

	/// \brief Normale au sommet.
	///
	/// Doit etre norme.
	///
	Vecteur3 _normale;

	/// \brief Coordonnees de texture du sommet.
	///
	/// Doit appartenir a [0, 1]^2
	///
	Vecteur2 _texcoords;

	/// \brief Constructeur.
	///
	/// Norme la normale et clampe les coordonnees de texture.
	///
	Sommet(const Vecteur3 &position, const Vecteur3 &normale, const Vecteur2 &texcoords);
};

/// \brief Definit une primitive geometrique de type triangle.
///
struct PrimitiveTriangle : Primitive
{
	/// \brief Normale du triangle.
	///
	/// Moyenne des normales des sommets. Calculee automatiquement a la construction.
	///
	Vecteur3 _normale;

	/// \brief Sommet du triangle.
	///
	Sommet _A;

	/// \brief Sommet du triangle.
	///
	Sommet _B;

	/// \brief Sommet du triangle.
	///
	Sommet _C;

	/// \brief Constructeur.
	///
	PrimitiveTriangle(Materiau *materiau, const Sommet &A, const Sommet &B, const Sommet &C);

	/// \brief Fonction de calcul d'intersection rayon-triangle.
	///
	///  pas d'intersection si le rayon sort du triangle
	///
	bool calculerIntersection(const Rayon &rayon, Intersection &intersection) const;

	/// \brief Fonction de calcul rapide d'intersection rayon-triangle.
	///
	/// Pas d'intersection si le rayon sort du triangle
	/// Si une intersection est detectee, distance est initialise.
	///
	bool calculerIntersection(const Rayon &, reel &distance) const;
};

/// \brief Definit une primitive geometrique de type sphere.
///
struct PrimitiveSphere : Primitive
{
	/// \brief Centre de la sphere.
	///
	Vecteur3 _centre;

	/// \brief rayon de la sphere.
	///
	reel _rayon;

	/// \brief Constructeur.
	///
	PrimitiveSphere(Materiau *materiau, const Vecteur3 &centre, reel rayon);

	/// \brief Fonction de calcul d'intersection rayon-sphere.
	///
	bool calculerIntersection(const Rayon &rayon, Intersection &intersection) const;

	/// \brief Fonction de calcul rapide d'intersection rayon-sphere.
	///
	/// Si une intersection est detectee, distance est initialise.
	///
	bool calculerIntersection(const Rayon &, reel &distance) const;
};

#endif /* PRIMITIVE_H_ */


