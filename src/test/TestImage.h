#ifndef TESTIMAGE_H_
#define TESTIMAGE_H_

#include "../raytracer/Image.h"

BEGIN_TEST(TestImage_creer)
{
	Image image;
	image.creer(40, 30);
	TESTLIB_ASSERT_EQUAL(image._largeur, 40);
	TESTLIB_ASSERT_EQUAL(image._hauteur, 30);
	TESTLIB_ASSERT_EQUAL(image._qimage.width(), 40);
	TESTLIB_ASSERT_EQUAL(image._qimage.height(), 30);
}
END_TEST(TestImage_creer)

BEGIN_TEST(TestImage_pixel)
{
	Image image;
	image.creer(4, 3);
	Couleur c1 = image.getPixel(1,1);
	TESTLIB_ASSERT_ALMOST_EQUAL(c1._r, 0, 1e-3);
	TESTLIB_ASSERT_ALMOST_EQUAL(c1._g, 0, 1e-3);
	TESTLIB_ASSERT_ALMOST_EQUAL(c1._b, 0, 1e-3);
	TESTLIB_ASSERT_ALMOST_EQUAL(c1._a, 0, 1e-3);

	Couleur c2(0.1, 0.2, 0.3, 0.4);
	image.setPixel(1, 1, c2);
	Couleur c3 = image.getPixel(1,1);
	TESTLIB_ASSERT_ALMOST_EQUAL(c3._r, 0.1, 0.1);
	TESTLIB_ASSERT_ALMOST_EQUAL(c3._g, 0.2, 0.1);
	TESTLIB_ASSERT_ALMOST_EQUAL(c3._b, 0.3, 0.1);
	TESTLIB_ASSERT_ALMOST_EQUAL(c3._a, 0.4, 0.1);
}
END_TEST(TestImage_pixel)

BEGIN_TEST(TestImage_largeurHauteur)
{
	Image image;
	image.creer(40, 30);
	TESTLIB_ASSERT_EQUAL(image.getLargeur(), 40);
	TESTLIB_ASSERT_EQUAL(image.getHauteur(), 30);
}
END_TEST(TestImage_largeurHauteur)

#endif


