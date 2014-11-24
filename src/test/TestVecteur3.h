#ifndef TESTVECTEUR3_H_
#define TESTVECTEUR3_H_

#include "../raytracer/Vecteur3.h"

BEGIN_TEST(TestVecteur3_constructeur_1)
{
	Vecteur3 v;
	TESTLIB_ASSERT_EQUAL(v._x, 0);
	TESTLIB_ASSERT_EQUAL(v._y, 0);
	TESTLIB_ASSERT_EQUAL(v._z, 0);
}
END_TEST(TestVecteur3_constructeur_1)

BEGIN_TEST(TestVecteur3_constructeur_2)
{
	Vecteur3 v(0, 4, 3);
	TESTLIB_ASSERT_EQUAL(v._x, 0);
	TESTLIB_ASSERT_EQUAL(v._y, 4);
	TESTLIB_ASSERT_EQUAL(v._z, 3);
}
END_TEST(TestVecteur3_constructeur_2)

BEGIN_TEST(TestVecteur3_operateur_moins)
{
	Vecteur3 u(0, -4, 3);
	Vecteur3 v(-u);
	TESTLIB_ASSERT_EQUAL(v._x, 0);
	TESTLIB_ASSERT_EQUAL(v._y, 4);
	TESTLIB_ASSERT_EQUAL(v._z, -3);
}
END_TEST(TestVecteur3_operateur_moins)

BEGIN_TEST(TestVecteur3_produit_vectoriel)
{
	Vecteur3 u(1, 2, 3);
	Vecteur3 v(2, 3, 4);
	Vecteur3 w(ProduitVectoriel(u, v));
	TESTLIB_ASSERT_EQUAL(w._x, -1);
	TESTLIB_ASSERT_EQUAL(w._y, 2);
	TESTLIB_ASSERT_EQUAL(w._z, -1);
}
END_TEST(TestVecteur3_produit_vectoriel)

BEGIN_TEST(TestVecteur3_plus_egal_vecteur3)
{
	Vecteur3 u(1, 2, -4);
	Vecteur3 v(2, 3, 4);
	u += v;
	TESTLIB_ASSERT_EQUAL(u._x, 3);
	TESTLIB_ASSERT_EQUAL(u._y, 5);
	TESTLIB_ASSERT_EQUAL(u._z, 0);
}
END_TEST(TestVecteur3_plus_egal_vecteur3)

BEGIN_TEST(TestVecteur3_operateur_div_egal)
{
	Vecteur3 u(1, 2, -4);
	reel k = 0.5;
	u *= k;
	TESTLIB_ASSERT_EQUAL(u._x, 0.5);
	TESTLIB_ASSERT_EQUAL(u._y, 1);
	TESTLIB_ASSERT_EQUAL(u._z, -2);
}
END_TEST(TestVecteur3_operateur_div_egal)

BEGIN_TEST(TestVecteur3_normecarree_1)
{
	Vecteur3 u(3, 4, 5);
	reel n = u.calculerNormeCarree();
	TESTLIB_ASSERT_EQUAL(n, 50);
}
END_TEST(TestVecteur3_normecarree_1)

BEGIN_TEST(TestVecteur3_norme_1)
{
	Vecteur3 u(3, 4, 0);
	reel n = u.calculerNorme();
	TESTLIB_ASSERT_EQUAL(n, 5);
}
END_TEST(TestVecteur3_norme_1)

BEGIN_TEST(TestVecteur3_norme_2)
{
	Vecteur3 u(0, 0, 1);
	reel n = u.calculerNorme();
	TESTLIB_ASSERT_EQUAL(n, 1);
}
END_TEST(TestVecteur3_norme_2)

BEGIN_TEST(TestVecteur3_normaliser)
{
	Vecteur3 u(2, 3, 4);
	u.normer();
	TESTLIB_ASSERT_ALMOST_EQUAL(u._x, 0.37, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(u._y, 0.55, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(u._z, 0.74, 0.01);
}
END_TEST(TestVecteur3_normaliser)

BEGIN_TEST(TestVecteur3_produit_scalaire)
{
	Vecteur3 u(1, 2, 6);
	Vecteur3 v(2, -3, 4);
	reel n = ProduitScalaire(u, v);
	TESTLIB_ASSERT_EQUAL(n, 20);
}
END_TEST(TestVecteur3_produit_scalaire)

BEGIN_TEST(TestVecteur3_fois_double)
{
	Vecteur3 u(2, 3, -4);
	reel k=3;
	Vecteur3 v = u*k;
	TESTLIB_ASSERT_EQUAL(v._x, 6);
	TESTLIB_ASSERT_EQUAL(v._y, 9);
	TESTLIB_ASSERT_EQUAL(v._z, -12);
}
END_TEST(TestVecteur3_fois_double)

BEGIN_TEST(TestVecteur3_moins_vecteur3)
{
	Vecteur3 u(1, 2, 6);
	Vecteur3 v(2, 3, 4);
	Vecteur3 w = u-v;
	TESTLIB_ASSERT_EQUAL(w._x, -1);
	TESTLIB_ASSERT_EQUAL(w._y, -1);
	TESTLIB_ASSERT_EQUAL(w._z, 2);
}
END_TEST(TestVecteur3_moins_vecteur3)

BEGIN_TEST(TestVecteur3_fois_vecteur3)
{
	Vecteur3 u(1, 2, 6);
	Vecteur3 v(2, 3, 4);
	Vecteur3 w = u*v;
	TESTLIB_ASSERT_EQUAL(w._x, 2);
	TESTLIB_ASSERT_EQUAL(w._y, 6);
	TESTLIB_ASSERT_EQUAL(w._z, 24);
}
END_TEST(TestVecteur3_fois_vecteur3)

BEGIN_TEST(TestVecteur3_plus_vecteur3)
{
	Vecteur3 u(1, 2, -6);
	Vecteur3 v(2, 3, 4);
	Vecteur3 w = u+v;
	TESTLIB_ASSERT_EQUAL(w._x, 3);
	TESTLIB_ASSERT_EQUAL(w._y, 5);
	TESTLIB_ASSERT_EQUAL(w._z, -2);
}
END_TEST(TestVecteur3_plus_vecteur3)

BEGIN_TEST(TestVecteur3_VecteurReflechi)
{
	Vecteur3 u(1, 0, -1);
	Vecteur3 v(0, 0, 1);
	Vecteur3 w = VecteurReflechi(u, v);
	TESTLIB_ASSERT_EQUAL(w._x, 1);
	TESTLIB_ASSERT_EQUAL(w._y, 0);
	TESTLIB_ASSERT_EQUAL(w._z, 1);
}
END_TEST(TestVecteur3_VecteurReflechi)

#endif /* TESTVECTEUR3_H_ */
