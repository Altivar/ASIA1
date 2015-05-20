#ifndef CAMERA_H_
#define CAMERA_H_

#include "Rayon.h"
#include "Matrice33.h"
#include "Vecteur2.h"

#include <cmath>

/// \brief Definit une camera virtuelle pour le rendu.
///
/// Classe abstraite a deriver.
///
struct Camera
{
	/// \brief Nom de la camera.
	///
	String _nom;

	/// \brief Definit la resolution de la camera.
	///
	virtual void setResolution(int nbX, int nbY) = 0;

	/// \brief Genere un rayon passant par le pixel (x, y).
	///
	virtual Rayon genererRayon(int x, int y) const = 0;
};

/// \brief Definit une camera pinhole.
///
struct CameraPinhole : Camera
{
	/// \brief Cree la camera pinhole.
	///
	/// \param position position du point de vue
	/// \param visee direction de visee
	/// \param verticale direction verticale (up-vector)
	/// \param fov angle de vue en degres
	///
	CameraPinhole(const Vecteur3 & position, const Vecteur3 & visee, const Vecteur3 & verticale, reel fov);

	/// \brief Definit la resolution de la camera.
	///
	/// Permet de passer de l'espace image (x, y) a l'espace ecran virtuel (u, v).
	///
	void setResolution(int nbX, int nbY);

	/// \brief Genere le rayon primaire (dans l'espace monde XYZ) correspondant a un pixel (dans l'espace image xy).
	///
	Rayon genererRayon(int x, int y) const;




	// private:
	Vecteur3 _position;

	reel _fov;
	reel _invNbX, _invNbY;
	reel _dU, _dV;

	Matrice33 _cameraVersMonde;
	Matrice33 _mondeVersCamera;

	Vecteur2 imageVersEcran(int x, int y) const;
	Vecteur3 ecranVersCamera(const Vecteur2 &uv) const;
	Vecteur3 cameraVersMonde(const Vecteur3 &UVW) const;

	Vecteur2 mondeVersImage(const Vecteur3 &P) const;

	/*
	Vecteur3 mondeVersCamera(const Vecteur3 &XYZ) const;
	void cameraVersEcran(const Vecteur3 &UVW, reel &u, reel &v) const;
	void ecranVersImage(reel u, reel v, int &x, int &y) const;
	*/
};

#endif /* CAMERA_H_ */
