
#ifndef ECLAIREMENT_H_
#define ECLAIREMENT_H_

#include "Couleur.h"
#include "Vecteur3.h"

/// \brief Definit l'eclairement d'un point par une source de lumiere.
///
struct Eclairement
{
	/// \brief Couleur de la lumiere incidente.
	///
	Couleur _couleur;

	/// \brief Direction d'incidence, du point vers la source.
	///
	/// Vecteur unitaire.
	///
	Vecteur3 _incidence;
};

#endif /* ECLAIREMENT_H_ */
