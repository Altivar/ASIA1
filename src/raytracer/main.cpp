/// \mainpage
///
/// Moteur de rendu par lancer de rayons.
///
/// Specifications :
/// - camera : pinhole
/// - lumiere : ponctuelle omnidirectionnelle
/// - objets : sphere, triangle
/// - materiaux : Phong, reflexion
/// - textures
/// - ombres dures
/// - lissage des normales
///
/// Autres fonctionnalites :
/// - import XML
/// - gestion des images
/// - tests unitaires
/// - chronometre
///

#include "Chronometre.h"
#include "Image.h"
#include "Loader.h"
#include "Rendu.h"
#include "../test/Test.h"

#include <iostream>
#include <conio.h>

int main(int argc, char *argv[])
{
    // lance les tests unitaires
	TESTLIB_RUN

	// definit les parametres du programme
	const char cheminScene[] = ".\\scenes\\";
	const char nomScene[] = "teapot.xml";
	const char nomImage[] = "renduTeapotTest.png";
	const char nomXsd[] = "raytracer.xsd";
	int nbRebonds = 5;
	const int largeur = 800;
	const int hauteur = 600;

	// charge la scene
	Scene scene;
	Loader loader(argc, argv, nomXsd);
	bool chargerOk = loader.chargerScene(cheminScene, nomScene, scene);
	if (chargerOk)
	{
		std::cout << "Scene chargee : " << scene.nbCameras() << " camera(s), "
				<< scene.nbLumieres() << " lumiere(s), "
				<< scene.nbPrimitives() << " primitive(s).\n";
	}
	else
	{
		std::cout << "Erreur au chargement de la scene.\nAbandon.\n";
		return -1;
	}
	std::cout.flush();

	// initialise l'image
    Image image;
    image.creer(largeur, hauteur);

    // lance le rendu
    Chronometre chrono;
    RenduWhitted rendu(nbRebonds);
    chrono.start();
	std::cout << "Construction de la scene..." << std::endl;
	scene.valider(Scene::PARTITIONNEMENT_GRILLE);
	std::cout << "Rendu en cours..." << std::endl;
    rendu.calculerRendu(scene, image);
    chrono.stop();
    std::cout << "Temps de rendu : "<< chrono.elapsed() << " s.";
	
    // enregistre l'image
    image.enregistrer(nomImage);

	_getch();

    return 0;
}



