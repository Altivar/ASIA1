#pragma once

#include "Vecteur3.h"
#include "Primitive.h"

class Case
{

	// position de la case
	Vecteur3 _position;
	// dimension de la case
	Vecteur3 _dimension;

	// tableau de primitives
	Primitive** _primitiveData;

	// primitive boite
	PrimitiveBoite* _boite;

public:
	Case(void);
	Case(Vecteur3& position, Vecteur3& dimension);
	~Case(void);

};

