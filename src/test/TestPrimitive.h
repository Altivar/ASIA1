
#ifndef TESTPRIMITIVE_H_
#define TESTPRIMITIVE_H_

#include "../raytracer/Primitive.h"


BEGIN_TEST(TestPrimitiveSphere_calculerIntersection_1)
{
	PrimitiveSphere sphere(0, Vecteur3(1, 2, 3), 2);
	Rayon rayon(Vecteur3(4, 2, 3), Vecteur3(-1, 0, 0));
	reel distance;
	bool r = sphere.calculerIntersection(rayon, distance);

	TESTLIB_ASSERT_TRUE(r);
}
END_TEST(TestPrimitiveSphere_calculerIntersection_1)


BEGIN_TEST(TestPrimitiveSphere_calculerIntersection_2)
{
	PrimitiveSphere sphere(0, Vecteur3(1, 2, 3), 2);
	Rayon rayon(Vecteur3(4, 2, 3), Vecteur3(1, 0, 0));
	reel distance;
	bool r = sphere.calculerIntersection(rayon, distance);

	TESTLIB_ASSERT_TRUE(!r);
}
END_TEST(TestPrimitiveSphere_calculerIntersection_2)


BEGIN_TEST(TestPrimitiveSphere_calculerIntersection_22)
{
	PrimitiveSphere sphere(0, Vecteur3(1, 2, 3), 2);
	Rayon rayon(Vecteur3(2, 2, 3), Vecteur3(1, 0, 0));
	reel distance;
	bool r = sphere.calculerIntersection(rayon, distance);

	TESTLIB_ASSERT_TRUE(r);
}
END_TEST(TestPrimitiveSphere_calculerIntersection_22)


BEGIN_TEST(TestPrimitiveSphere_calculerIntersection_3)
{
	PrimitiveSphere sphere(0, Vecteur3(1, 2, 3), 2);
	Rayon rayon(Vecteur3(4, 2, 3), Vecteur3(-1, 0, 0));
	Intersection intersection;
	bool r = sphere.calculerIntersection(rayon, intersection);

	TESTLIB_ASSERT_EQUAL(r, true);

	TESTLIB_ASSERT_EQUAL(intersection._distance, 1);

	TESTLIB_ASSERT_EQUAL(intersection._position._x, 3);
	TESTLIB_ASSERT_EQUAL(intersection._position._y, 2);
	TESTLIB_ASSERT_EQUAL(intersection._position._z, 3);

	TESTLIB_ASSERT_EQUAL(intersection._normale._x, 1);
	TESTLIB_ASSERT_EQUAL(intersection._normale._y, 0);
	TESTLIB_ASSERT_EQUAL(intersection._normale._z, 0);

	TESTLIB_ASSERT_EQUAL(intersection._incidence._x, -1);
	TESTLIB_ASSERT_EQUAL(intersection._incidence._y, 0);
	TESTLIB_ASSERT_EQUAL(intersection._incidence._z, 0);

	TESTLIB_ASSERT_EQUAL(intersection._reflexion._x, 1);
	TESTLIB_ASSERT_EQUAL(intersection._reflexion._y, 0);
	TESTLIB_ASSERT_EQUAL(intersection._reflexion._z, 0);
}
END_TEST(TestPrimitiveSphere_calculerIntersection_3)


BEGIN_TEST(TestPrimitiveSphere_calculerIntersection_4)
{
	PrimitiveSphere sphere(0, Vecteur3(1, 2, 3), 2);
	Rayon rayon(Vecteur3(4, 2, 3), Vecteur3(1, 0, 0));
	Intersection intersection;
	bool r = sphere.calculerIntersection(rayon, intersection);

	TESTLIB_ASSERT_TRUE(!r);
}
END_TEST(TestPrimitiveSphere_calculerIntersection_4)




BEGIN_TEST(TestPrimitiveTriangle_constructeur)
{
	Sommet A(Vecteur3(1, 2, 3), Vecteur3(4, 0, 0), Vecteur2(0.7, 0.8));
	Sommet B(Vecteur3(9, 10, 11), Vecteur3(0, 13, 0), Vecteur2(0.15, 0.16));
	Sommet C(Vecteur3(17, 18, 19), Vecteur3(0, 0, 22), Vecteur2(0.23, 0.24));

	PrimitiveTriangle triangle(0, A, B, C);

	TESTLIB_ASSERT_EQUAL(triangle._A._position._x, 1);
	TESTLIB_ASSERT_EQUAL(triangle._A._position._y, 2);
	TESTLIB_ASSERT_EQUAL(triangle._A._position._z, 3);
	TESTLIB_ASSERT_EQUAL(triangle._A._normale._x, 1);
	TESTLIB_ASSERT_EQUAL(triangle._A._normale._y, 0);
	TESTLIB_ASSERT_EQUAL(triangle._A._normale._z, 0);
	TESTLIB_ASSERT_EQUAL(triangle._A._texcoords._u, 0.7);
	TESTLIB_ASSERT_EQUAL(triangle._A._texcoords._v, 0.8);

	TESTLIB_ASSERT_EQUAL(triangle._B._position._x, 9);
	TESTLIB_ASSERT_EQUAL(triangle._B._position._y, 10);
	TESTLIB_ASSERT_EQUAL(triangle._B._position._z, 11);
	TESTLIB_ASSERT_EQUAL(triangle._B._normale._x, 0);
	TESTLIB_ASSERT_EQUAL(triangle._B._normale._y, 1);
	TESTLIB_ASSERT_EQUAL(triangle._B._normale._z, 0);
	TESTLIB_ASSERT_EQUAL(triangle._B._texcoords._u, 0.15);
	TESTLIB_ASSERT_EQUAL(triangle._B._texcoords._v, 0.16);

	TESTLIB_ASSERT_EQUAL(triangle._C._position._x, 17);
	TESTLIB_ASSERT_EQUAL(triangle._C._position._y, 18);
	TESTLIB_ASSERT_EQUAL(triangle._C._position._z, 19);
	TESTLIB_ASSERT_EQUAL(triangle._C._normale._x, 0);
	TESTLIB_ASSERT_EQUAL(triangle._C._normale._y, 0);
	TESTLIB_ASSERT_EQUAL(triangle._C._normale._z, 1);
	TESTLIB_ASSERT_EQUAL(triangle._C._texcoords._u, 0.23);
	TESTLIB_ASSERT_EQUAL(triangle._C._texcoords._v, 0.24);
}
END_TEST(TestPrimitiveTriangle_constructeur)



BEGIN_TEST(TestPrimitiveTriangle_calculerIntersection_1)
{
	Sommet A(Vecteur3(1, 0, 0), Vecteur3(), Vecteur2());
	Sommet B(Vecteur3(0, 1, 0), Vecteur3(), Vecteur2());
	Sommet C(Vecteur3(0, 0, 1), Vecteur3(), Vecteur2());
	PrimitiveTriangle triangle(0, A, B, C);

	Rayon r1(Vecteur3(1, 1, 1), Vecteur3(-1, -1, -1));
	Rayon r2(Vecteur3(1, 1, 1), Vecteur3(1, 1, 1));
	Rayon r3(Vecteur3(1, 1, 0), Vecteur3(-1, -1, -1));
	reel distance;

	TESTLIB_ASSERT_EQUAL(triangle.calculerIntersection(r1, distance), true);
	TESTLIB_ASSERT_EQUAL(triangle.calculerIntersection(r2, distance), false);
	TESTLIB_ASSERT_EQUAL(triangle.calculerIntersection(r3, distance), false);
}
END_TEST(TestPrimitiveTriangle_calculerIntersection_1)




#endif /* TESTPRIMITIVE_H_ */

