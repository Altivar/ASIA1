#ifndef RENDU_H_
#define RENDU_H_

#include "Image.h"
#include "Scene.h"


/// \brief Definit un algorithme de rendu par lancer de rayons.
///
/// Classe abstraite a deriver.
///
struct Rendu
{
	/// \brief Calcule la luminance correspondant a un rayon.
	///
	virtual Couleur calculerLuminance(Scene &scene, Rayon &rayon) const = 0;

	/// \brief Calcule le rendu de la scene dans l'image.
	///
	/// La scene doit avoir ete validee.
	///
	virtual void calculerRendu(Scene &scene, Image &image) const = 0;
};

/// \brief Algorithme de rendu par lancer de rayons de type Whitted.
///
struct RenduWhitted : Rendu
{
	/// \brief Nombre de rebonds max des rayons.
	///
	int _nbRebonds;

	/// \brief Constructeur.
	///
	RenduWhitted(int nbRebonds): _nbRebonds(nbRebonds) {}

	/// \brief Calcule la luminance correspondant a un rayon.
	///
	Couleur calculerLuminance(Scene &scene, Rayon &rayon) const;

	/// \brief Calcule le rendu de la scene dans l'image.
	///
	/// La scene doit avoir ete validee.
	///
	void calculerRendu(Scene &scene, Image &image) const;

	/// \brief Calcule le rendu fil de fer de la scene dans l'image.
	///
	/// La scene doit avoir ete validee.
	///
	void calculerProjectionPrimitives(Scene &scene, Image &image) const;
	void calculerProjectionPartition(Scene &scene, Image &image) const;
	void calculerProjectionBoite(Scene &scene, Image &image, Case &c_case, CameraPinhole* camera) const;
};

#endif


