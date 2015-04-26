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



void Image::tracerDroiteBresenham(Vecteur2 a, Vecteur2 b, std::list<Vecteur2> &pixels)
{
	
	std::list<Vecteur2> pixelsTraces;
	
	int x1 = a._u, x2 = b._u;
	int y1 = a._v, y2 = b._v;
	
	int xbas, ybas, xhaut, yhaut, dx, dy;
	
	if (y1 < y2)
	{
		xbas = x1;
		ybas = y1;
		xhaut = x2;
		yhaut = y2;
	}
	else
	{
		xbas = x2;
		ybas = y2;
		xhaut = x1;
		yhaut = y1;
	}
	
	int deltaE, deltaNE, incEx, incEy, incNEx, incNEy, N, di;
	deltaE = deltaNE = incEx = incEy = incNEx = incNEy = N = di = 0;
	if (xbas <= xhaut)
	{
		// cas 1
		dx = xhaut - xbas;
		dy = yhaut - ybas;
		if (dx >= dy)
		{
			// cas 1.a
			di = 2*dy - dx;
			deltaE = 2*dy;
			deltaNE = 2*(dy - dx);
			incEx = 1;
			incEy = 0;
			incNEx = 1;
			incNEy = 1;
			N = dx;
		}
		else
		{
			// cas 1.b
			di = 2*dx - dy;
			deltaE = 2*dx;
			deltaNE = 2*(dx - dy);
			incEx = 0;
			incEy = 1;
			incNEx = 1;
			incNEy = 1;
			N = dy;
		}
	}
	else
	{
		// cas 2
		dx = xbas - xhaut;
		dy = yhaut - ybas;
		if (dx >= dy)
		{
			// cas 2.a
			di = 2*dy - dx;
			deltaE = 2*dy;
			deltaNE = 2*(dy - dx);
			incEx = -1;
			incEy = 0;
			incNEx = -1;
			incNEy = 1;
			N = dx;
		}
		else
		{
			// cas 2.b
			di = 2*dx - dy;
			deltaE = 2*dx;
			deltaNE = 2*(dx - dy);
			incEx = 0;
			incEy = 1;
			incNEx = -1;
			incNEy = 1;
			N = dy;
		}
	}
	
	int x = xbas;
	int y = ybas;
	
	int i;
	for (i = 0; i < N; ++i)
	{
		if (di <= 0)
		{
			di += deltaE;
			x += incEx;
			y += incEy;
		}
		else
		{
			di += deltaNE;
			x += incNEx;
			y += incNEy;
		}
		pixels.push_back(Vecteur2(x,y));
	}

}