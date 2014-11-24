#ifndef TESTBASE_H_
#define TESTBASE_H_

#include "../raytracer/Base.h"
#include "../raytracer/Vecteur2.h"


BEGIN_TEST(TestBase_interpoler)
{
	Vecteur2 A(1, 2);
	Vecteur2 B(3, -2);
	Vecteur2 I = interpoler(A, B, 0.25);
	TESTLIB_ASSERT_ALMOST_EQUAL(I._u, 1.5, 0.001);
	TESTLIB_ASSERT_ALMOST_EQUAL(I._v, 1, 0.001);
}
END_TEST(TestBase_interpoler)

BEGIN_TEST(TestBase_autoset)
{
	AutoSet<TestlibAlloc> *autoset = new AutoSet<TestlibAlloc>();
	TestlibAlloc::reset();
	TESTLIB_ASSERT_EQUAL(TestlibAlloc::getCompteur(), 0);

	AutoSet<TestlibAlloc>::const_iterator it;
	int valeur1, valeur2;

	autoset->ajouter(new TestlibAlloc(2));
	TESTLIB_ASSERT_EQUAL(TestlibAlloc::getCompteur(), 1);
	TESTLIB_ASSERT_EQUAL(autoset->size(), 1);
	it = autoset->begin();
	valeur1 = (*it)->_valeur;
	TESTLIB_ASSERT_EQUAL(valeur1, 2);

	autoset->ajouter(new TestlibAlloc(1));
	TESTLIB_ASSERT_EQUAL(TestlibAlloc::getCompteur(), 2);
	TESTLIB_ASSERT_EQUAL(autoset->size(), 2);
	it = autoset->begin();
	valeur1 = (*it)->_valeur;
	++it;
	valeur2 = (*it)->_valeur;
	TESTLIB_ASSERT_TRUE(((valeur1==2 && valeur2==1) || (valeur1==1 && valeur2==2)));

	delete autoset;
	TESTLIB_ASSERT_EQUAL(TestlibAlloc::getCompteur(), 0);
}
END_TEST(TestBase_autoset)


BEGIN_TEST(TestBase_automap)
{
	AutoMap<TestlibAlloc> *automap = new AutoMap<TestlibAlloc>();
	TestlibAlloc::reset();
	TESTLIB_ASSERT_EQUAL(TestlibAlloc::getCompteur(), 0);

	TestlibAlloc *p1 = automap->trouver("a");
	TESTLIB_ASSERT_EQUAL(p1, 0);
	TESTLIB_ASSERT_EQUAL(TestlibAlloc::getCompteur(), 0);

	TestlibAlloc *p2 = new TestlibAlloc(2);
	automap->ajouter("a", p2);
	TestlibAlloc *p3 = automap->trouver("a");
	TESTLIB_ASSERT_EQUAL(p3, p2);
	TESTLIB_ASSERT_EQUAL(TestlibAlloc::getCompteur(), 1);

	TestlibAlloc *p4 = new TestlibAlloc(1);
	automap->ajouter("b", p4);
	TestlibAlloc *p5 = automap->trouver("b");
	TESTLIB_ASSERT_EQUAL(p5, p4);
	TESTLIB_ASSERT_EQUAL(TestlibAlloc::getCompteur(), 2);

	delete automap;

	TESTLIB_ASSERT_EQUAL(TestlibAlloc::getCompteur(), 0);
}
END_TEST(TestBase_automap)


#endif /* TESTBASE_H_ */
