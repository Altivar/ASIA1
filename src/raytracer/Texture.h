#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "Base.h"
#include "Couleur.h"
#include "Image.h"
#include "Vecteur2.h"

/// \brief Definit une texture.
///
/// Ici, une texture represente une composante d'un materiau, par exemple une couleur ou une image.
/// Classe abstraite
///
struct Texture
{
	/// \brief Nom de la texture.
	///
	String _nom;

	/// \brief Fonction de calcul de la couleur de la texture.
	///
	virtual Couleur calculerCouleur(const Vecteur2 &texcoords) const = 0;
};

/// \brief Texture constante i.e. une couleur.
///
struct TextureCouleur : Texture
{
	Couleur _couleur;

	/// \brief Constructeur.
	///
	TextureCouleur(const Couleur &couleur);

	/// \brief Fonction de calcul de la couleur de la texture.
	///
	Couleur calculerCouleur(const Vecteur2 &texcoords) const;
};

/// \brief Texture de type image.
///
struct TextureImage : Texture
{
	Image *_image;
	reel _largeur, _hauteur;

	/// \brief Constructeur.
	///
	TextureImage(Image *image);

	/// \brief Fonction de calcul de la couleur de la texture.
	///
	/// \param texcoords coordonnees de texture dans [0, 1]^2
	Couleur calculerCouleur(const Vecteur2 &texcoords) const;
};

#endif /* TEXTURE_H_ */
