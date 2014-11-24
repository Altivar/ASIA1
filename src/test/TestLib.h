/// utilisation :
///
/// - TestModule.h :
/// BEGIN_TEST(TestModule_1)
/// {
/// 	...
/// TESTLIB_ASSERT_TRUE(...)
/// }
/// END_TEST(TestModule_1)
///
/// - Test.h :
/// #include "TestLib.h"
/// TESTLIB_BEGIN_TESTS
/// #include "TestModule.h
/// TESTLIB_END_TESTS
///
/// - main :
/// TESTLIB_RUN
///

#ifndef TESTLIB_H_
#define TESTLIB_H_

#include <iostream>
#include <vector>
#include <cmath>

/// Teste si les parametres sont egaux.
#define TESTLIB_ASSERT_EQUAL(A, B) if (!((A) == (B)))\
	{\
		std::cout << "obtenu : " << (A) << ", attendu : " << (B) << " -> ";\
		return false;\
	}

/// Teste si les parametres sont egaux a une precision donnee pres.
#define TESTLIB_ASSERT_ALMOST_EQUAL(A, B, C) if ((fabs((A) - (B)))>(C)) \
	{\
		std::cout << "obtenu : " << (A) << ", attendu : " << (B) << " -> ";\
		return false;\
	}

/// Teste si le parametre est vrai.
#define TESTLIB_ASSERT_TRUE(A) if (!(A)) \
	{\
		std::cout << "obtenu : " << (A) << " -> ";\
		return false;\
	}

/// commence un test unitaire
#define BEGIN_TEST(A) class A  \
	{ \
	public: \
		A(){;} \
		static bool test() \
		{


/// termine le test unitaire
#define END_TEST(A)	return true; \
		} \
	}; \
	fonctions.push_back(A::test); \
	noms.push_back(#A);


/// initialise l'ensemble des tests
#define TESTLIB_BEGIN_TESTS namespace testsUnitaires \
	{ \
		std::vector<bool(*)(void)> fonctions; \
		std::vector<std::string> noms; \
		void run() \
		{ \
			std::cout << "*** Tests unitaires ***\n";



/// termine les tests
#define TESTLIB_END_TESTS int nbSucces = 0; \
			int nbEchecs = 0; \
			int nbTests = fonctions.size(); \
			for (int i=0; i<nbTests; i++) \
			{ \
				if (fonctions[i]()) \
				{ \
					nbSucces++; \
				} \
				else \
				{ \
					nbEchecs++; \
					std::cout << "Echec de " << noms[i] << std::endl; \
				} \
			} \
			std::cout << nbTests << " test(s) : " << nbSucces << " succes, " << nbEchecs << " echec(s).\n"; \
		} \
	}


/// lance les tests
#define TESTLIB_RUN testsUnitaires::run();




// structure pour tester la gestion memoire d'ensembles de donnees
static int TestlibAlloc_compteur;
struct TestlibAlloc
{
	static void reset(){TestlibAlloc_compteur=0;}
	static int getCompteur(){return TestlibAlloc_compteur;}
	int _valeur;
	TestlibAlloc(int valeur):_valeur(valeur){TestlibAlloc_compteur++;}
	~TestlibAlloc(){TestlibAlloc_compteur--;};
};


#endif /* TESTLIB_H_ */
