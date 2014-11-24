#ifndef TESTCOULEUR_H_
#define TESTCOULEUR_H_

#include "../raytracer/Couleur.h"


BEGIN_TEST(TestCouleur_constructeur_1)
{
	Couleur couleur;

	TESTLIB_ASSERT_EQUAL(couleur._r, 0);
	TESTLIB_ASSERT_EQUAL(couleur._g, 0);
	TESTLIB_ASSERT_EQUAL(couleur._b, 0);
	TESTLIB_ASSERT_EQUAL(couleur._a, 0);
}
END_TEST(TestCouleur_constructeur_1)



BEGIN_TEST(TestCouleur_constructeur_2)
{
	Couleur couleur(1, 2, 3, 4);

	TESTLIB_ASSERT_EQUAL(couleur._r, 1);
	TESTLIB_ASSERT_EQUAL(couleur._g, 2);
	TESTLIB_ASSERT_EQUAL(couleur._b, 3);
	TESTLIB_ASSERT_EQUAL(couleur._a, 4);
}
END_TEST(TestCouleur_constructeur_2)



BEGIN_TEST(TestCouleur_couleurPlusCouleur)
{
	Couleur c1(1, 2, 3, 4);
	Couleur c2(5, 6, 7, 8);
	Couleur c3 = c1+c2;

	TESTLIB_ASSERT_EQUAL(c3._r, 6);
	TESTLIB_ASSERT_EQUAL(c3._g, 8);
	TESTLIB_ASSERT_EQUAL(c3._b, 10);
	TESTLIB_ASSERT_EQUAL(c3._a, 12);
}
END_TEST(TestCouleur_couleurPlusCouleur)



BEGIN_TEST(TestCouleur_couleurFoisScalaire)
{
	Couleur c1(1, 2, 3, 4);
	Couleur c3 = c1*4;

	TESTLIB_ASSERT_EQUAL(c3._r, 4);
	TESTLIB_ASSERT_EQUAL(c3._g, 8);
	TESTLIB_ASSERT_EQUAL(c3._b, 12);
	TESTLIB_ASSERT_EQUAL(c3._a, 4);
}
END_TEST(TestCouleur_couleurFoisScalaire)



BEGIN_TEST(TestCouleur_couleurFoisCouleur)
{
	Couleur c1(1, 2, 3, 4);
	Couleur c2(5, 6, 7, 8);
	Couleur c3 = c1*c2;

	TESTLIB_ASSERT_EQUAL(c3._r, 5);
	TESTLIB_ASSERT_EQUAL(c3._g, 12);
	TESTLIB_ASSERT_EQUAL(c3._b, 21);
	TESTLIB_ASSERT_EQUAL(c3._a, 32);
}
END_TEST(TestCouleur_couleurFoisCouleur)



BEGIN_TEST(TestCouleur_couleurPlusEgalCouleur)
{
	Couleur c1(1, 2, 3, 4);
	Couleur c2(5, 6, 7, 8);
	c1+=c2;

	TESTLIB_ASSERT_EQUAL(c1._r, 6);
	TESTLIB_ASSERT_EQUAL(c1._g, 8);
	TESTLIB_ASSERT_EQUAL(c1._b, 10);
	TESTLIB_ASSERT_EQUAL(c1._a, 12);
}
END_TEST(TestCouleur_couleurPlusEgalCouleur)




#endif /* TESTCOULEUR_H_ */

