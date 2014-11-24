#include "Image.h"

#include <QColor>

bool Image::creer(int largeur, int hauteur)
{
	// cree l'image 32 bits
	_qimage = QImage(largeur, hauteur, QImage::Format_ARGB32);

	if (estValide())	// creation ok
	{
		// initialise les donnees
		_largeur = _qimage.width();
		_hauteur = _qimage.height();
		_qimage.fill(0x00000000);
		return true;
	}
	else	// creation hs
	{
		return false;
	}
}

bool Image::charger(const String &nom)
{
	// lit le fichier specifie
	_qimage.load(nom.c_str());

	if (estValide())	// lecture ok
	{
		_largeur = _qimage.width();
		_hauteur = _qimage.height();
		return true;
	}
	else	// lecture hs
	{
		return false;
	}
}

bool Image::estValide() const
{
	return !_qimage.isNull();
}

void Image::setPixel(int x, int y, const Couleur &couleur)
{
	// convertit les composantes couleur de [0, 1] dans [|0, 255|]
	unsigned int r = 255 * std::max<reel>(0, std::min<reel>(1, couleur._r));
	unsigned int g = 255 * std::max<reel>(0, std::min<reel>(1, couleur._g));
	unsigned int b = 255 * std::max<reel>(0, std::min<reel>(1, couleur._b));
	unsigned int a = 255 * std::max<reel>(0, std::min<reel>(1, couleur._a));

	// definit le pixel aux composantes calculees
	QRgb c = qRgba(r, g, b, a);
	_qimage.setPixel(x, y, c);
}

Couleur Image::getPixel(int x, int y) const
{
	// recupere le pixel
	QRgb c = _qimage.pixel(x, y);

	// convertit les composantes de [|0, 255|] dans [0, 1]
	reel r = qRed(c)/(reel)255;
	reel g = qGreen(c)/(reel)255;
	reel b = qBlue(c)/(reel)255;
	reel a = qAlpha(c)/(reel)255;
	return Couleur(r, g, b, a);
}

void Image::enregistrer(const char *nom) const
{
	_qimage.save(nom);
}

int Image::getLargeur() const
{
	return _largeur;
}

int Image::getHauteur() const
{
	return _hauteur;
}

