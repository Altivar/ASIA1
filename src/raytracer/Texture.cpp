#include "Texture.h"

TextureCouleur::TextureCouleur(const Couleur &couleur):
_couleur(couleur)
{}

Couleur TextureCouleur::calculerCouleur(const Vecteur2 &) const
{
	return _couleur;
}


TextureImage::TextureImage(Image *image):
_image(image)
{
	if (image)
	{
		_largeur = _image->getLargeur()-1;
		_hauteur = _image->getHauteur()-1;
	}
}

Couleur TextureImage::calculerCouleur(const Vecteur2 &texcoords) const
{
	return _image->getPixel(texcoords._u*_largeur, texcoords._v*_hauteur);
}




