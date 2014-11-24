#ifndef TESTMATERIAU_H_
#define TESTMATERIAU_H_

#include "../raytracer/Materiau.h"


BEGIN_TEST(TestMateriau_constructeur)
{
	TextureCouleur Ca(Couleur(1, 2, 3, 4));
	TextureCouleur Cd(Couleur(6, 7, 8, 9));
	TextureCouleur Cs(Couleur(11, 12, 13, 14));
	reel Ns = 16;

	MateriauPhong m(&Ca, &Cd, &Cs, Ns);

	TESTLIB_ASSERT_EQUAL(m._Ns, 16);
	TESTLIB_ASSERT_EQUAL(m._Ca, &Ca);
	TESTLIB_ASSERT_EQUAL(m._Cd, &Cd);
	TESTLIB_ASSERT_EQUAL(m._Cs, &Cs);
}
END_TEST(TestMateriau_constructeur)


#endif /* TESTMATERIAU_H_ */
