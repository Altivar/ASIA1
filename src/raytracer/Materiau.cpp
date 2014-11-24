#include "Materiau.h"
#include "Scene.h"
#include "Eclairement.h"
#include "Rendu.h"

#include <cmath>

MateriauPhong::MateriauPhong(Texture *Ca, Texture *Cd, Texture *Cs, reel Ns):
_Ca(Ca), _Cd(Cd), _Cs(Cs), _Ns(Ns)
{}

Couleur MateriauPhong::calculerReflexion(const Rendu *, Intersection &intersection, Scene &scene) const
{
	// calcule les composantes du materiau
	Couleur Cd;
	Couleur Cs;

	// calcule la reflexion de la lumiere issue des differentes sources
	for (AutoSet<Lumiere>::const_iterator it=scene.lumieresBegin(); it!=scene.LumieresEnd(); ++it)
	{
		// teste si la lumiere est visible
		Lumiere *lumiere = *it;
		Eclairement eclairement;
		bool visible = lumiere->calculerEclairement(intersection, scene, eclairement);
		if (visible)
		{
			// calcule l'eclairement issue de la source
			reel cosTheta = std::max<reel>(0, ProduitScalaire(intersection._normale, eclairement._incidence));
			Cd += eclairement._couleur*cosTheta;
			reel cosAlpha = std::max<reel>(0, ProduitScalaire(intersection._reflexion, eclairement._incidence));
			reel cosAlphaNs = pow(cosAlpha, _Ns);
			Cs += eclairement._couleur*cosAlphaNs;
		}
	}

	// retourne la lumiere reflechie totale
	return _Ca->calculerCouleur(intersection._texcoords)
			+ _Cd->calculerCouleur(intersection._texcoords)*Cd
			+ _Cs->calculerCouleur(intersection._texcoords)*Cs;
}


MateriauMiroir::MateriauMiroir(Texture *Ca, Texture *Cd, Texture *Cs, reel Ns, Texture *Cr):
MateriauPhong(Ca, Cd, Cs, Ns), _Cr(Cr)
{}

Couleur MateriauMiroir::calculerReflexion(const Rendu *rendu, Intersection &intersection, Scene &scene) const
{
	// calcule la luminance correspondant au materiau de base
	Couleur C = MateriauPhong::calculerReflexion(rendu, intersection, scene);

	// calcule la luminance correspondant a la reflexion ideale
	Rayon rayonReflechi(intersection._position, intersection._reflexion, intersection._rebond);
	rayonReflechi.avancer();
	Couleur Cr = rendu->calculerLuminance(scene, rayonReflechi);

	return C + _Cr->calculerCouleur(intersection._texcoords)*Cr;
}
