
#ifndef TESTRAYON_H_
#define TESTRAYON_H_

#include "../raytracer/Rayon.h"

BEGIN_TEST(TestRayon_constructeur)
{
	Rayon rayon(Vecteur3(1, 2, 3), Vecteur3(4, 5, 6));

	TESTLIB_ASSERT_EQUAL(rayon._origine._x, 1);
	TESTLIB_ASSERT_EQUAL(rayon._origine._y, 2);
	TESTLIB_ASSERT_EQUAL(rayon._origine._z, 3);

	TESTLIB_ASSERT_EQUAL(rayon._direction._x, 4);
	TESTLIB_ASSERT_EQUAL(rayon._direction._y, 5);
	TESTLIB_ASSERT_EQUAL(rayon._direction._z, 6);
}
END_TEST(TestRayon_constructeur)


BEGIN_TEST(TestRayon_calculerPosition)
{
	Rayon rayon(Vecteur3(1, 2, 3), Vecteur3(4, 5, 6));
	Vecteur3 p = rayon.calculerPosition(2);

	TESTLIB_ASSERT_EQUAL(p._x, 9);
	TESTLIB_ASSERT_EQUAL(p._y, 12);
	TESTLIB_ASSERT_EQUAL(p._z, 15);
}
END_TEST(TestRayon_calculerPosition)


#endif /* TESTRAYON_H_ */

