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


void RenduWhitted::calculerProjectionPartition(Scene &scene, Image &image) const
{
	
	AutoSet<Primitive>::const_iterator itDebut = scene.primitivesBegin();
	AutoSet<Primitive>::const_iterator itFin = scene.primitivesEnd();
	AutoSet<Primitive>::iterator it;
	
	// On recupere la premiere camera de la scene pour calculer le rendu
	AutoSet<Camera>::const_iterator camerasBegin = scene.camerasBegin();
	AutoSet<Camera>::const_iterator camerasEnd = scene.camerasEnd();
	
	if (camerasBegin == camerasEnd)
	{
		std::cerr << "Pas de camera dans la scene.\n";
		return;
	}
	
	CameraPinhole *camera = (CameraPinhole *)*camerasBegin;
	int largeur = image.getLargeur();
	int hauteur = image.getHauteur();
	camera->setResolution(largeur, hauteur);
	
	// Ici on fait le test avec des primitives de type "triangle"
	PartitionnementGrille* pg = (PartitionnementGrille*)scene.GetPatitionnement();
	int nbCase = pg->GetNbCases();
	Case* cases = pg->GetCasesTable();


	Vecteur2 pointOrigine;
	Vecteur2 pointOppose;
	Vecteur2 pointOr1, pointOr2, pointOr3;
	Vecteur2 pointOp1, pointOp2, pointOp3;

	for (int i = 0; i < nbCase; i++)
	{

		calculerProjectionBoite(scene, image, cases[i], camera);

		

	}
	
}

void RenduWhitted::calculerProjectionBoite(Scene &scene, Image &image, Case &c_case, CameraPinhole* camera) const
{
	if( c_case._subdivise )
	{
		for (int i = 0; i < 8; i++)
		{
			calculerProjectionBoite(scene, image, c_case._caseData[i], camera);
		}
	}
	else
	{
		Vecteur2 pointOrigine;
		Vecteur2 pointOppose;
		Vecteur2 pointOr1, pointOr2, pointOr3;
		Vecteur2 pointOp1, pointOp2, pointOp3;

		c_case._boite->calculerProjectionSurImage(
				pointOrigine, pointOr1, pointOr2, pointOr3,
				pointOppose, pointOp1, pointOp2, pointOp3,
				*camera);

		std::list<Vecteur2> pixelsTraces;
		
		image.tracerDroiteBresenham(pointOrigine, pointOr1, pixelsTraces);
		image.tracerDroiteBresenham(pointOrigine, pointOr2, pixelsTraces);
		image.tracerDroiteBresenham(pointOrigine, pointOr3, pixelsTraces);

		image.tracerDroiteBresenham(pointOppose, pointOp1, pixelsTraces);
		image.tracerDroiteBresenham(pointOppose, pointOp2, pixelsTraces);
		image.tracerDroiteBresenham(pointOppose, pointOp3, pixelsTraces);

		image.tracerDroiteBresenham(pointOr1, pointOp2, pixelsTraces);
		image.tracerDroiteBresenham(pointOr1, pointOp3, pixelsTraces);

		image.tracerDroiteBresenham(pointOr2, pointOp1, pixelsTraces);
		image.tracerDroiteBresenham(pointOr2, pointOp3, pixelsTraces);

		image.tracerDroiteBresenham(pointOr3, pointOp1, pixelsTraces);
		image.tracerDroiteBresenham(pointOr3, pointOp2, pixelsTraces);

		
		std::list<Vecteur2>::iterator itPixels;
		for (itPixels = pixelsTraces.begin(); itPixels != pixelsTraces.end(); ++itPixels)
			image.setPixel(itPixels->_u, itPixels->_v, Couleur(0,0,0,1));
	}
}


void RenduWhitted::calculerProjectionPrimitives(Scene &scene, Image &image) const
{

	AutoSet<Primitive>::const_iterator itDebut = scene.primitivesBegin();
	AutoSet<Primitive>::const_iterator itFin = scene.primitivesEnd();
	AutoSet<Primitive>::iterator it;
	
	// On recupere la premiere camera de la scene pour calculer le rendu
	AutoSet<Camera>::const_iterator camerasBegin = scene.camerasBegin();
	AutoSet<Camera>::const_iterator camerasEnd = scene.camerasEnd();
	
	if (camerasBegin == camerasEnd)
	{
		std::cerr << "Pas de camera dans la scene.\n";
		return;
	}
	
	CameraPinhole *camera = (CameraPinhole *)*camerasBegin;
	int largeur = image.getLargeur();
	int hauteur = image.getHauteur();
	camera->setResolution(largeur, hauteur);
	
	// Ici on fait le test avec des primitives de type "triangle"
	// A remplacer avec des primitives boites !
	//
	for (it = itDebut; it != itFin; ++it)
	{
		
		PrimitiveTriangle *pTri = (PrimitiveTriangle *)*it;
		Vecteur2 a, b, c;
		// Calcul de la projection du triangle sur l'image
		pTri->calculerProjectionSurImage(a, b, c, *camera);
		// Trace de chaque arete avec Bresenham
		std::list<Vecteur2> pixelsTraces;
		image.tracerDroiteBresenham(a, b, pixelsTraces);
		image.tracerDroiteBresenham(b, c, pixelsTraces);
		image.tracerDroiteBresenham(c, a, pixelsTraces);
		std::list<Vecteur2>::iterator itPixels;
		for (itPixels = pixelsTraces.begin(); itPixels != pixelsTraces.end(); ++itPixels)
			image.setPixel(itPixels->_u, itPixels->_v, Couleur(0,0,0,1));

	}

}
