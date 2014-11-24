
#ifndef TESTVECTEUR2_H_
#define TESTVECTEUR2_H_

#include "../raytracer/Vecteur2.h"


BEGIN_TEST(TestVecteur2_constructeur_1)
{
	Vecteur2 v;
	TESTLIB_ASSERT_EQUAL(v._u, 0);
	TESTLIB_ASSERT_EQUAL(v._v, 0);
}
END_TEST(TestVecteur2_constructeur_1)

BEGIN_TEST(TestVecteur2_constructeur_2)
{
	Vecteur2 v(4, 3);
	TESTLIB_ASSERT_EQUAL(v._u, 4);
	TESTLIB_ASSERT_EQUAL(v._v, 3);
}
END_TEST(TestVecteur2_constructeur_2)


BEGIN_TEST(TestVecteur2_fois_reel)
{
	Vecteur2 u(2, -4);
	reel k=3;
	Vecteur2 v = u*k;
	TESTLIB_ASSERT_EQUAL(v._u, 6);
	TESTLIB_ASSERT_EQUAL(v._v, -12);
}
END_TEST(TestVecteur2_fois_reel)


BEGIN_TEST(TestVecteur2_plus_vecteur2)
{
	Vecteur2 u(1, -6);
	Vecteur2 v(2, 3);
	Vecteur2 w = u+v;
	TESTLIB_ASSERT_EQUAL(w._u, 3);
	TESTLIB_ASSERT_EQUAL(w._v, -3);
}
END_TEST(TestVecteur2_plus_vecteur2)




BEGIN_TEST(TestVecteur2_moins_vecteur2)
{
	Vecteur2 u(1, -6);
	Vecteur2 v(2, 3);
	Vecteur2 w = u-v;
	TESTLIB_ASSERT_EQUAL(w._u, -1);
	TESTLIB_ASSERT_EQUAL(w._v, -9);
}
END_TEST(TestVecteur2_moins_vecteur2)



#endif /* TESTVECTEUR2_H_ */
