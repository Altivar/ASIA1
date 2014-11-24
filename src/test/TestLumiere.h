#ifndef TESTLUMIERE_H_
#define TESTLUMIERE_H_

#include "../raytracer/Lumiere.h"

BEGIN_TEST(LumierePoint_constructeur)
{
	LumierePoint l(Vecteur3(1, 2, 3), Couleur(4, 5, 6, 7));

	TESTLIB_ASSERT_EQUAL(l._position._x, 1);
	TESTLIB_ASSERT_EQUAL(l._position._y, 2);
	TESTLIB_ASSERT_EQUAL(l._position._z, 3);

	TESTLIB_ASSERT_EQUAL(l._couleur._r, 4);
	TESTLIB_ASSERT_EQUAL(l._couleur._g, 5);
	TESTLIB_ASSERT_EQUAL(l._couleur._b, 6);
	TESTLIB_ASSERT_EQUAL(l._couleur._a, 7);
}
END_TEST(LumierePoint_constructeur)



#endif /* TESTLUMIERE_H_ */
