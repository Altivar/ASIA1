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
	bool calculerIntersection(const Rayon &rayon, reel &distance);
	int GetNbPrimitive() { return _primitiveData.size(); }
	void SetPrimitives( std::vector<Primitive*>& data );
	//[Methods]



	// primitive boite
	PrimitiveBoite* _boite;
	
	// position de la case
	Vecteur3 _position;
	// dimension de la case
	Vecteur3 _dimension;

	// tableau de primitives
	std::vector<Primitive*> _primitiveData;
	
	// materiau fil de fer
	MateriauFilDeFer* _materiau_fil_de_fer;

};

