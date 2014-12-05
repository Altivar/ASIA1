
#ifndef MATERIAU_H_
#define MATERIAU_H_

#include "Base.h"
#include "Texture.h"
#include "Couleur.h"
#include "Intersection.h"
#include "Primitive.h"
#include "Lumiere.h"

class Rendu;
class Scene;

/// \brief Definit un materiau.
///
/// Classe abstraite a deriver.
///
struct Materiau
{
	/// \brief Nom du materiau.
	///
	String _nom;

	/// \brief Calcule de reflectance.
	///
	virtual Couleur calculerReflexion(const Rendu *rendu, Intersection &intersection, Scene &scene) const = 0;
};

/// \brief Definit un materiau de type Phong.
///
struct MateriauPhong : Materiau
{
	/// \brief Texture ambiante.
	///
	Texture *_Ca;
	/// \brief Texture diffuse.
	///
	Texture *_Cd;

	/// \brief Texture speculaire.
	///
	Texture *_Cs;

	/// \brief Indice speculaire.
	///
	reel _Ns;

	/// \brief Constructeur.
	///
	MateriauPhong(Texture *Ca, Texture *Cd, Texture *Cs, reel Ns);

	/// \brief Calcul d'eclairement.
	///
	virtual Couleur calculerReflexion(const Rendu *rendu, Intersection &intersection, Scene &scene) const;
};

/// \brief Definit un materiau de type reflexion.
///
struct MateriauMiroir : MateriauPhong
{
	/// \brief Texture reflexion.
	///
	Texture *_Cr;

	/// \brief Constructeur.
	///
	MateriauMiroir(Texture *Ca, Texture *Cd, Texture *Cs, reel Ns, Texture *Cr);

	/// \brief Calcul d'eclairement.
	///
	Couleur calculerReflexion(const Rendu *rendu, Intersection &intersection, Scene &scene) const;
};

struct MateriauFilDeFer : Materiau
{
	MateriauFilDeFer(Couleur coul);
	Couleur* _couleur;
	Couleur calculerReflexion(const Rendu *rendu, Intersection &intersection, Scene &scene) const;
};

#endif /* MATERIAU_H_ */


