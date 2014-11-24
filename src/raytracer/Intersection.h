
#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include "Vecteur2.h"
#include "Vecteur3.h"

struct Materiau;
struct Objet;

/// \brief Definit une intersection rayon-primitive.
///
struct Intersection
{
	/// \brief Distance parcourue sur le rayon avant l'intersection.
	///
	reel _distance;

	/// \brief Position de l'intersection.
	///
	Vecteur3 _position;

	/// \brief Normale a la surface au point rencontre.
	///
	Vecteur3 _normale;

	/// \brief Vecteur incident (oriente vers l'objet).
	///
	Vecteur3 _incidence;

	/// \brief Vecteur reflechi (oriente vers l'exterieur).
	///
	Vecteur3 _reflexion;

	/// \brief Coordonnees de texture au point d'intersection.
	///
	Vecteur2 _texcoords;

	/// \brief Materiau au point d'intersection.
	///
	Materiau *_materiau;

	int _rebond;
};

#endif /* INTERSECTION_H_ */
