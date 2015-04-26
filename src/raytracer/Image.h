#ifndef IMAGE_H_
#define IMAGE_H_

#include "Base.h"
#include "Couleur.h"
#include "Vecteur2.h"

#include <QImage>

/// \brief Permet de creer, lire, en enregistrer une image a 4 canaux de couleurs.
///
struct Image
{
	/// \brief Cree une image de la taille demandee et initialisee a 0.
	///
	/// \param largeur largeur de l'image
	/// \param hauteur hauteur de l'image
	/// \return true si creation ok.
	///
	bool creer(int largeur, int hauteur);

	/// \brief Charge une image a partir d'un fichier.
	///
	/// \param nom nom du fichier image
	/// \return true si chargement ok.
	///
	bool charger(const String &nom);

	/// \brief Teste si l'image est valide. (ouverture ).
	///
	/// \return true si l'image est valide (ie l'ouverture de fichier ou l'allocation memoire a reussi).
	///
	bool estValide() const;

	/// \brief Modifie la couleur d'un pixel de l'image.
	///
	void setPixel(int x, int y, const Couleur &couleur);

	/// \brief Accesseur sur l'image.
	///
	/// \return la couleur du pixel a la position (x, y).
	///
	Couleur getPixel(int x, int y) const;

	/// \brief Retourne la largeur de l'image.
	///
	int getLargeur() const;

	/// \brief Retourne la hauteur de l'image.
	///
	int getHauteur() const;

	/// \brief Enregistre l'image.
	///
	/// Le format est determine d'apres le nom du fichier.
	///
	void enregistrer(const char *nom) const;

	/// \brief Dessine un trait.
	///
	void Image::tracerDroiteBresenham(Vecteur2 a, Vecteur2 b, std::list<Vecteur2> &pixels);

	// private:
	int _largeur, _hauteur;
	QImage _qimage;

};

#endif

