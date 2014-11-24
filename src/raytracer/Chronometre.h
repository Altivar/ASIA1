#ifndef CHRONOMETRE_H_
#define CHRONOMETRE_H_

#include <QTime>

/// \brief Permet de mesurer le temps d'execution d'une section de code.
///
/// Utilisation : <br>
/// <br><code>
/// Chronometre chrono; <br>
/// chrono.start(); <br>
/// ... <br>
/// chrono.stop(): <br>
/// std::cout << chrono.elapsed() <br></code>
/// <br>
///
class Chronometre
{
	QTime _qtime;
	int _elapsed;

public:
	/// \brief Demarre la mesure.
	///
	void start();

	/// \brief Arrete la mesure.
	///
	void stop();

	/// \brief Retourne le temps ecoule en seconde(s).
	///
	double elapsed();
};


#endif
