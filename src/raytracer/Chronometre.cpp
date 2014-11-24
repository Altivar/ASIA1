#include "Chronometre.h"

void Chronometre::start()
{
	_qtime.start();
}

void Chronometre::stop()
{
	_elapsed = _qtime.elapsed();
}

double Chronometre::elapsed()
{
	return _elapsed * 1e-3;
}
