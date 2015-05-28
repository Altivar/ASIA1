#ifndef SCENE_H_
#define SCENE_H_

#include "Base.h"
#include "Image.h"
#include "Camera.h"
#include "Lumiere.h"
#include "Texture.h"
#include "Materiau.h"
#include "Primitive.h"
#include "Partitionnement.h"

/// \brief Definit une scene.
///
class Scene
{
	AutoMap<Image> _images;
	AutoSet<Materiau> _materiaux;
	AutoSet<Texture> _textures;

	AutoSet<Camera> _cameras;
	AutoSet<Lumiere> _lumieres;
	AutoSet<Primitive> _primitives;

	Partitionnement *_partitionnement;

public:

	/// \brief Constructeur.
	///
	/// Une scene ne doit pas etre copiee (a cause de la destruction automatique des objets pointes).
	///
	Scene();

	// Ne pas utiliser : la recopie de scene est interdite (a cause de la destruction automatique des objets pointes).
	Scene(const Scene &);

	/// \brief Destructeur
	///
	~Scene();

	/// \brief Enregistre une image dans la scene.
	///
	/// Si l'image est deja enregistree dans la scene, retourne un pointeur vers l'objet correspondant.
	/// Si l'image n'est pas deja dans la scene, charge le fichier dans un objet image et retourne un pointeur.
	/// l'objet est detruit automatiquement lors de la destruction de la scene
	///
	Image * enregistrerImage(const String &nomImage);

	/// \brief Enregistre un materiau dans la scene.
	///
	/// Le materiau doit etre alloue dynamiquement;
	/// la desallocation est realisee automatiquement a la destruction de la scene.
	///
	void enregistrerMateriau(Materiau *materiau);

	/// \brief Enregistre une primitive dans la scene.
	///
	/// La primitive doit etre allouee dynamiquement;
	/// la desallocation est realisee automatiquement a la destruction de la scene.
	///
	void enregistrerPrimitive(Primitive *primitive);

	/// \brief Enregistre une texture dans la scene.
	///
	/// La texture doit etre allouee dynamiquement;
	/// la desallocation est realisee automatiquement a la destruction de la scene.
	///
	void enregistrerTexture(Texture *texture);

	/// \brief Enregistre une camera dans la scene.
	///
	/// La camera doit etre allouee dynamiquement;
	/// la desallocation est realisee automatiquement a la destruction de la scene.
	///
	void enregistrerCamera(Camera *camera);

	/// \brief Enregistre une lumiere dans la scene.
	///
	/// La lumiere doit etre allouee dynamiquement;
	/// la desallocation est realisee automatiquement a la destruction de la scene.
	///
	void enregistrerLumiere(Lumiere *lumiere);



	/// \brief Iterateur de debut sur les cameras de la scene.
	///
	AutoSet<Camera>::const_iterator camerasBegin() const;

	/// \brief Iterateur de fin sur les cameras de la scene.
	///
	AutoSet<Camera>::const_iterator camerasEnd() const;

	/// \brief Iterateur de debut sur les lumieres de la scene.
	///
	AutoSet<Lumiere>::const_iterator lumieresBegin() const;

	/// \brief Iterateur de fin sur les lumieres de la scene.
	///
	AutoSet<Lumiere>::const_iterator LumieresEnd() const;

	/// \brief Iterateur de debut sur les primitives de la scene.
	///
	AutoSet<Primitive>::const_iterator primitivesBegin() const;

	/// \brief Iterateur de fin sur les primitives de la scene.
	///
	AutoSet<Primitive>::const_iterator primitivesEnd() const;

	/// \brief Nombre de cameras dans la scene.
	///
	int nbCameras() const;

	/// \brief Nombre de lumieres dans la scene.
	///
	int nbLumieres() const;

	/// \brief Nombre de primitives dans la scene.
	///
	int nbPrimitives() const;


	/// \brief Type de partitionnement de scene.
	///
	/// Unitaire : parcourt toutes les primitives.
	///
	enum TypePartitionnement {PARTITIONNEMENT_UNITAIRE, PARTITIONNEMENT_GRILLE};

	/// \brief Calcule le partitionnement de scene.
	///
	/// Leve une assertion si le type de partitionnement n'existe pas ou si probleme d'allocation.
	///
	void valider(TypePartitionnement typePartionnement);

	/// \brief Retourne vrai si le rayon n'est pas interrompu sur une certaine distance.
	///
	bool visibilite(const Rayon &rayon, reel distance) const;

	/// \brief Determine l'intersection la plus proche.
	///
	bool intersection(const Rayon &rayon, Intersection &intersection) const;

	// retourne le partitionnement pour avoir accès aux cases du partitionnement grille (pour le rendu de l'armature)
	Partitionnement* GetPatitionnement() { return _partitionnement; }

	// retourne le type de partitionnement choisi
	TypePartitionnement _typePartitionnement;

};

#endif



