
#include "Rayon.h"

Rayon::Rayon(const Vecteur3 &origine, const Vecteur3 &direction, int rebond):
_origine(origine), _direction(direction), _rebond(rebond)
{}

Vecteur3 Rayon::calculerPosition(reel t) const
{
	return _origine + _direction*t;
}

void Rayon::avancer(reel distance)
{
	_origine +=  _direction*distance;
}

