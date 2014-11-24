#include "Rendu.h"

#include <iostream>

Couleur RenduWhitted::calculerLuminance(Scene &scene, Rayon &rayon) const
{
	if (rayon._rebond < _nbRebonds)
	{
		Intersection intersection;
		bool trouve = scene.intersection(rayon, intersection);
		if (trouve)
		{
			intersection._rebond = rayon._rebond+1;
			return intersection._materiau->calculerReflexion(this, intersection, scene);
		}
	}
	return Couleur(0, 0, 0, 0);
}

void RenduWhitted::calculerRendu(Scene &scene, Image &image) const
{
	// teste si la scene contient une camera
	AutoSet<Camera>::const_iterator camerasBegin = scene.camerasBegin();
	AutoSet<Camera>::const_iterator camerasEnd = scene.camerasEnd();
	if (camerasBegin == camerasEnd)
	{
		std::cerr << "Pas de camera dans la scene.\n";
		return;
	}

	// recupere la premiere camera de la scene pour calculer le rendu
	Camera *camera = *camerasBegin;
	int largeur = image.getLargeur();
	int hauteur = image.getHauteur();
	camera->setResolution(largeur, hauteur);

	// effectue le lancer de rayon pour chaque pixel
#pragma omp parallel for
	for (int x=0; x<largeur; x++)
	{
		for (int y=0; y<hauteur; y++)
		{
			// generer le rayon camera
			Rayon rayon = camera->genererRayon(x, y);

			// calculer la luminance du rayon
			Couleur couleur = calculerLuminance(scene, rayon);

			// remplit l'image
			image.setPixel(x, y, couleur);
		}
	}
}




