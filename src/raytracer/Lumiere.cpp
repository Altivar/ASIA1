#include "Lumiere.h"
#include "Intersection.h"
#include "Scene.h"
#include "Eclairement.h"


LumierePoint::LumierePoint(const Vecteur3 &position, const Couleur &couleur):
_position(position), _couleur(couleur)
{}

bool LumierePoint::calculerEclairement(const Intersection &intersection, const Scene &scene, Eclairement &eclairement) const
{
	// calcule la direction de la lumiere
	Vecteur3 L = _position - intersection._position;
	reel distance = L.calculerNorme();
	L.normer(distance);

	// teste si la lumiere est visible
	Rayon rayonLumiere(intersection._position, L);
	rayonLumiere.avancer();
	bool visible = scene.visibilite(rayonLumiere, distance);

	// initialise l'eclairement
	if (visible)
	{
		eclairement._couleur = _couleur;
		eclairement._incidence = L;
	}

	return visible;
}

