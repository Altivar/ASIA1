#ifndef TESTMATRICE33_H_
#define TESTMATRICE33_H_

#include "../raytracer/Matrice33.h"

BEGIN_TEST(TestMatrice33Remplir)
{
	Matrice33 m;
	reel coefs[9] = {1,2,3,4,5,6,7,8,9};
	m.remplir(coefs);
	TESTLIB_ASSERT_EQUAL( m._00,  1 );
	TESTLIB_ASSERT_EQUAL( m._01,  2 );
	TESTLIB_ASSERT_EQUAL( m._02,  3 );
	TESTLIB_ASSERT_EQUAL( m._10,  4 );
	TESTLIB_ASSERT_EQUAL( m._11,  5 );
	TESTLIB_ASSERT_EQUAL( m._12,  6 );
	TESTLIB_ASSERT_EQUAL( m._20,  7 );
	TESTLIB_ASSERT_EQUAL( m._21,  8 );
	TESTLIB_ASSERT_EQUAL( m._22,  9 );
}
END_TEST(TestMatrice33Remplir)

BEGIN_TEST(TestMatrice33ProduitVecteur)
{
	Matrice33 m;
	reel coefs[9] = {1,2,3,4,5,6,7,8,9};
	m.remplir(coefs);
	Vecteur3 v(3, 2, 1);
	Vecteur3 r(m*v);
	TESTLIB_ASSERT_EQUAL( r._x,  10 );
	TESTLIB_ASSERT_EQUAL( r._y,  28 );
	TESTLIB_ASSERT_EQUAL( r._z,  46 );
}
END_TEST(TestMatrice33ProduitVecteur)


BEGIN_TEST(TestMatrice33_transposer)
{
	Matrice33 m;
	reel coefs[9] = {1,2,3,4,5,6,7,8,9};
	m.remplir(coefs);
	Matrice33 m2 = m.transposer();
	TESTLIB_ASSERT_EQUAL( m2._00,  1);
	TESTLIB_ASSERT_EQUAL( m2._01,  4);
	TESTLIB_ASSERT_EQUAL( m2._02,  7);
	TESTLIB_ASSERT_EQUAL( m2._10,  2);
	TESTLIB_ASSERT_EQUAL( m2._11,  5);
	TESTLIB_ASSERT_EQUAL( m2._12,  8);
	TESTLIB_ASSERT_EQUAL( m2._20,  3);
	TESTLIB_ASSERT_EQUAL( m2._21,  6);
	TESTLIB_ASSERT_EQUAL( m2._22,  9);
}
END_TEST(TestMatrice33_transposer)


BEGIN_TEST(TestMatrice33_foisScalaire)
{
	Matrice33 m;
	reel coefs[9] = {1,2,3,4,5,6,7,8,9};
	m.remplir(coefs);
	Matrice33 m2 = m*2;
	TESTLIB_ASSERT_EQUAL( m2._00,  2);
	TESTLIB_ASSERT_EQUAL( m2._01,  4);
	TESTLIB_ASSERT_EQUAL( m2._02,  6);
	TESTLIB_ASSERT_EQUAL( m2._10,  8);
	TESTLIB_ASSERT_EQUAL( m2._11,  10);
	TESTLIB_ASSERT_EQUAL( m2._12,  12);
	TESTLIB_ASSERT_EQUAL( m2._20,  14);
	TESTLIB_ASSERT_EQUAL( m2._21,  16);
	TESTLIB_ASSERT_EQUAL( m2._22,  18);
}
END_TEST(TestMatrice33_foisScalaire)



BEGIN_TEST(TestMatrice33_resoudreSysteme_2)
{
	Vecteur3 a0(-1, 3, -1);
	Vecteur3 a1(1, -1, 3);
	Vecteur3 a2(2, 1, 4);
	Vecteur3 b(2, 6, 4);
	Vecteur3 x;

	bool r = resoudreSysteme(a0, a1, a2, x, b);
	TESTLIB_ASSERT_EQUAL( r, true );
	TESTLIB_ASSERT_ALMOST_EQUAL( x._x,  1 , 0.001);
	TESTLIB_ASSERT_ALMOST_EQUAL( x._y, -1 , 0.001 );
	TESTLIB_ASSERT_ALMOST_EQUAL( x._z,  2 , 0.001 );
}
END_TEST(TestMatrice33_resoudreSysteme_2)


#endif /* TESTMATRICE33_H_ */
