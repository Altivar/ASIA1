#include "Camera.h"

#include <cmath>

#define M_PI 3.1415926

CameraPinhole::CameraPinhole(const Vecteur3 & position, const Vecteur3 & visee, const Vecteur3 & verticale, reel fov)
{
	// memorise la position et l'angle de vue
	_position = position;
	_fov = fov;

	// calcule les matrices de changement de repere
	Vecteur3 W(visee);
	W.normer();
	Vecteur3 V0(-verticale);
	V0.normer();
	Vecteur3 U(ProduitVectoriel(V0, W)); 
	Vecteur3 V(ProduitVectoriel(W, U));
	_mondeVersCamera.remplir(U, V, W);
	_cameraVersMonde = _mondeVersCamera.transposer();
}

void CameraPinhole::setResolution(int nbX, int nbY)
{
	_invNbX = 1/(reel)nbX;
	_invNbY = 1/(reel)nbY;

	// calcule l'ecran de projection de la camera
	_dU = 2*tan(_fov*M_PI/(reel)360);
	_dV = _dU*nbY/(reel)nbX;
}

Rayon CameraPinhole::genererRayon(int x, int y) const
{
	// calcule la direction dans le repere monde
	Vecteur2 uv = imageVersEcran(x, y);
	Vecteur3 uvw = ecranVersCamera(uv);
	Vecteur3 direction = cameraVersMonde(uvw);
	direction.normer();

	// retourne le rayon
	return Rayon(_position, direction);
}

Vecteur2 CameraPinhole::imageVersEcran(int x, int y) const
{
	return Vecteur2(x*_invNbX - 0.5, y*_invNbY - 0.5);
}

Vecteur3 CameraPinhole::ecranVersCamera(const Vecteur2 &uv) const
{
	return Vecteur3(uv._u*_dU, uv._v*_dV, 1);
}

Vecteur3 CameraPinhole::cameraVersMonde(const Vecteur3 &UVW) const
{
	return _cameraVersMonde*UVW;
}


Vecteur2 CameraPinhole::mondeVersImage(const Vecteur3 &P) const
{
	// UVW : Dans le repere camera
	Vecteur3 dist = P-_position;
	Vecteur3 UVW = _mondeVersCamera*(dist);
	// Distance focale
	reel distance = 1;
	// UVW' : Projete dans le repere camera
	Vecteur3 UVW_ = Vecteur3(UVW._x*distance/UVW._z, UVW._y*distance/UVW._z, distance);
	// uv' : Projete dans le plan image
	Vecteur2 uv_ = Vecteur2(UVW_._x/_dU, UVW_._y/_dV);
	// xy : Projete dans les coordonnees image
	Vecteur2 xy = Vecteur2(int((uv_._u+0.5)*(1./_invNbX)), int((uv_._v+0.5)*(1./_invNbY)));
	return xy;
}

/*
void CameraPinhole::ecranVersImage(reel u, reel v, int &x, int &y) const;
void CameraPinhole::cameraVersEcran(const Vecteur3 &UVW, reel &u, reel &v) const;
Vecteur3 CameraPinhole::mondeVersCamera(const Vecteur3 &XYZ) const;

*/


