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
	const char nomScene[] = "test.xml";
	const char nomImage[] = "Rendus\\steapot_testOptions.png";
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
	std::cout << std::endl << "Construction de la scene..." << std::endl;
	scene.valider(Scene::PARTITIONNEMENT_GRILLE);
	std::cout << "Rendu en cours..." << std::endl;
    rendu.calculerRendu(scene, image);
    chrono.stop();
    std::cout << "Temps de rendu : "<< chrono.elapsed() << " s." << std::endl;
	

	// rendu en fil de fer
	int choice = 0;
	std::cout << std::endl << "Dessin en fil de fer : " << std::endl;
	std::cout << "  1    - Dessiner les primitives" << std::endl;
	std::cout << "  2    - Dessiner la grille" << std::endl;
	std::cout << "  3    - Dessiner les primitives et la grille" << std::endl;
	std::cout << " Autre - Ne rien dessiner" << std::endl;
	std::cin>>choice;
	
	if( choice == 1 || choice == 3 )
	{
		rendu.calculerProjectionPrimitives(scene, image);
	}
	if( choice == 2 || choice == 3 )
	{
		rendu.calculerProjectionPartition(scene, image);
	}
	
	
    // enregistre l'image
    image.enregistrer(nomImage);


    return 0;
}



