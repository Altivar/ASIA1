#include "Scene.h"

#include <cassert>
#include <iostream>

Scene::Scene():
_partitionnement(0)
{}

Scene::Scene(const Scene &)
{
	// La scene ne doit pas etre recopiee sinon les donnees seront detruites plusieurs fois.
	assert(false);
}

Scene::~Scene()
{
	if (_partitionnement)
	{
		delete _partitionnement;
		_partitionnement = 0;
	}
}

Image * Scene::enregistrerImage(const String &nomImage)
{
	// si l'image est deja enregistree, retourne son pointeur
	Image *image = _images.trouver(nomImage);
	if (image)
	{
		return image;
	}

	// sinon ouvre et enregistre une nouvelle image
	image = new Image;
	if (!image->charger(nomImage))
	{
		std::cerr << "Scene::enregistrerImage : erreur au chargement de " << nomImage << std::endl;
		return 0;
	}
	_images.ajouter(nomImage, image);
	return image;
}

void Scene::enregistrerMateriau(Materiau *materiau)
{
	_materiaux.ajouter(materiau);
}

void Scene::enregistrerPrimitive(Primitive *primitive)
{
	_primitives.ajouter(primitive);
}

void Scene::enregistrerTexture(Texture *texture)
{
	_textures.ajouter(texture);
}

void Scene::enregistrerCamera(Camera *camera)
{
	_cameras.ajouter(camera);
}

void Scene::enregistrerLumiere(Lumiere *lumiere)
{
	_lumieres.ajouter(lumiere);
}

AutoSet<Camera>::const_iterator Scene::camerasBegin() const
{
	return _cameras.begin();
}

AutoSet<Camera>::const_iterator Scene::camerasEnd() const
{
	return _cameras.end();
}

AutoSet<Lumiere>::const_iterator Scene::lumieresBegin() const
{
	return _lumieres.begin();
}

AutoSet<Lumiere>::const_iterator Scene::LumieresEnd() const
{
	return _lumieres.end();
}

AutoSet<Primitive>::const_iterator Scene::primitivesBegin() const
{
	return _primitives.begin();
}

AutoSet<Primitive>::const_iterator Scene::primitivesEnd() const
{
	return _primitives.end();
}

int Scene::nbCameras() const
{
	return _cameras.size();
}

int Scene::nbLumieres() const
{
	return _lumieres.size();
}


int Scene::nbPrimitives() const
{
	return _primitives.size();
}

void Scene::valider(TypePartitionnement typePartionnement)
{
	if (_partitionnement)
	{
		delete _partitionnement;
		_partitionnement = 0;
	}

	switch (typePartionnement)
	{
	case PARTIONNEMENT_UNITAIRE :
		_partitionnement = new PartitionnementUnitaire();
		break;
	case PARTITIONNEMENT_GRILLE :
		_partitionnement = new PartitionnementUnitaire();
		break;

	default:
		std::cerr << "Scene::valider : type de partitionnement invalide.\n";
	}

	assert(_partitionnement);

	_partitionnement->initialiser(primitivesBegin(), primitivesEnd());
}

bool Scene::visibilite(const Rayon &rayon, reel distance) const
{
	return _partitionnement->visibilite(rayon, distance);
}

bool Scene::intersection(const Rayon &rayon, Intersection &intersection) const
{
	return _partitionnement->intersection(rayon, intersection);
}


