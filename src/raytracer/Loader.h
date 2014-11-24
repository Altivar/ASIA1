#ifndef LOADER_H_
#define LOADER_H_

#include "Scene.h"

#include <QCoreApplication>

/// \brief Loader de fichiers XML.
///
/// Schema XML donne par raytracer.xsd.
///
class Loader
{
public:
	/// \brief Constructeur.
	///
	/// Necessite les arguments de ligne de commande
	/// (creation d'un QCoreApplication pour la validation XML+XSD).
	///
	Loader(int argc, char **argv, const char *fichierXsd);

	/// \brief Charge une scene d'un fichier 3DS.
	///
	/// \return true si le chargement a reussi.
	///
	bool chargerScene(const String &chemin, const String &nomFichier, Scene &scene);

private:
	/// \brief Validation XML+XSD du fichier de scene.
	///
	bool validerFichier(const String &nomFichierComplet) const;

	QCoreApplication _application;

	String _fichierXsd;
};

#endif
