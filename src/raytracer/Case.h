#pragma once

#include "Vecteur3.h"
#include "Primitive.h"
#include "Materiau.h"
#include <vector>

struct Case
{

	Case(void);
	~Case(void);


	//[Methods]
	void InitialiserCase(Vecteur3 &position, Vecteur3 &dimension);
	void AjouterPrimitive(Primitive* primitive);
	bool calculerIntersection(const Rayon &rayon, Intersection &intersection);
	bool calculerIntersection(const Rayon &rayon, reel &distance, reel distanceMax);
	int GetNbPrimitive() { return _primitiveData.size(); }
	void SetPrimitives( std::vector<Primitive*>& data );
	void Subdiviser();
	//[Methods]



	// primitive boite
	PrimitiveBoite* _boite;
	// tableau de cases (dans le cas d'une subdivision)
	Case* _caseData;
	// tableau de primitives
	std::vector<Primitive*> _primitiveData;

	// egal true si la case a été subdivisée
	bool _subdivise;

	// position de la case
	Vecteur3 _position;
	// dimension de la case
	Vecteur3 _dimension;

	
	
	// materiau fil de fer
	MateriauFilDeFer* _materiau_fil_de_fer;

};

