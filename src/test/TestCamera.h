#ifndef TESTCAMERA_H_
#define TESTCAMERA_H_

#include "../raytracer/Camera.h"

BEGIN_TEST(TestCameraPinhole_constructeur)
{
	Vecteur3 position(0, 0, 0);
	Vecteur3 visee(0, 0, 1);
	Vecteur3 verticale(0, -1, 0);
	reel fov = 60;
	CameraPinhole camera(position, visee, verticale, fov);

	TESTLIB_ASSERT_EQUAL(camera._position._x, 0);
	TESTLIB_ASSERT_EQUAL(camera._position._y, 0);
	TESTLIB_ASSERT_EQUAL(camera._position._z, 0);

	TESTLIB_ASSERT_EQUAL(camera._fov, 60);

	TESTLIB_ASSERT_EQUAL(camera._mondeVersCamera._00, 1);
	TESTLIB_ASSERT_EQUAL(camera._mondeVersCamera._01, 0);
	TESTLIB_ASSERT_EQUAL(camera._mondeVersCamera._02, 0);
	TESTLIB_ASSERT_EQUAL(camera._mondeVersCamera._10, 0);
	TESTLIB_ASSERT_EQUAL(camera._mondeVersCamera._11, 1);
	TESTLIB_ASSERT_EQUAL(camera._mondeVersCamera._12, 0);
	TESTLIB_ASSERT_EQUAL(camera._mondeVersCamera._20, 0);
	TESTLIB_ASSERT_EQUAL(camera._mondeVersCamera._21, 0);
	TESTLIB_ASSERT_EQUAL(camera._mondeVersCamera._22, 1);

	TESTLIB_ASSERT_EQUAL(camera._cameraVersMonde._00, 1);
	TESTLIB_ASSERT_EQUAL(camera._cameraVersMonde._01, 0);
	TESTLIB_ASSERT_EQUAL(camera._cameraVersMonde._02, 0);
	TESTLIB_ASSERT_EQUAL(camera._cameraVersMonde._10, 0);
	TESTLIB_ASSERT_EQUAL(camera._cameraVersMonde._11, 1);
	TESTLIB_ASSERT_EQUAL(camera._cameraVersMonde._12, 0);
	TESTLIB_ASSERT_EQUAL(camera._cameraVersMonde._20, 0);
	TESTLIB_ASSERT_EQUAL(camera._cameraVersMonde._21, 0);
	TESTLIB_ASSERT_EQUAL(camera._cameraVersMonde._22, 1);
}
END_TEST(TestCameraPinhole_constructeur)



BEGIN_TEST(TestCameraPinhole_constructeur_2)
{
	Vecteur3 position(1, 5, 6);
	Vecteur3 visee(0, -1, -1);
	Vecteur3 verticale(0, -1, 1);
	reel fov = 45;
	CameraPinhole camera(position, visee, verticale, fov);

	TESTLIB_ASSERT_EQUAL(camera._position._x, 1);
	TESTLIB_ASSERT_EQUAL(camera._position._y, 5);
	TESTLIB_ASSERT_EQUAL(camera._position._z, 6);

	TESTLIB_ASSERT_EQUAL(camera._fov, 45);

	TESTLIB_ASSERT_ALMOST_EQUAL(camera._mondeVersCamera._00, -1, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(camera._mondeVersCamera._01, 0, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(camera._mondeVersCamera._02, 0, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(camera._mondeVersCamera._10, 0, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(camera._mondeVersCamera._11, 0.7, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(camera._mondeVersCamera._12, -0.7, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(camera._mondeVersCamera._20, 0, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(camera._mondeVersCamera._21, -0.7, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(camera._mondeVersCamera._22, -0.7, 0.01);

	TESTLIB_ASSERT_ALMOST_EQUAL(camera._cameraVersMonde._00, -1, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(camera._cameraVersMonde._01, 0, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(camera._cameraVersMonde._02, 0, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(camera._cameraVersMonde._10, 0, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(camera._cameraVersMonde._11, 0.7, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(camera._cameraVersMonde._12, -0.7, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(camera._cameraVersMonde._20, 0, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(camera._cameraVersMonde._21, -0.7, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(camera._cameraVersMonde._22, -0.7, 0.01);
}
END_TEST(TestCameraPinhole_constructeur_2)



BEGIN_TEST(TestCameraPinhole_constructeur_3)
{
	Vecteur3 position(1, 5, 6);
	Vecteur3 visee(-1, 0, 0);
	Vecteur3 verticale(0, 0, 1);
	reel fov = 45;
	CameraPinhole camera(position, visee, verticale, fov);

	TESTLIB_ASSERT_EQUAL(camera._cameraVersMonde._00, 0);
	TESTLIB_ASSERT_EQUAL(camera._cameraVersMonde._01, 0);
	TESTLIB_ASSERT_EQUAL(camera._cameraVersMonde._02, -1);
	TESTLIB_ASSERT_EQUAL(camera._cameraVersMonde._10, 1);
	TESTLIB_ASSERT_EQUAL(camera._cameraVersMonde._11, 0);
	TESTLIB_ASSERT_EQUAL(camera._cameraVersMonde._12, 0);
	TESTLIB_ASSERT_EQUAL(camera._cameraVersMonde._20, 0);
	TESTLIB_ASSERT_EQUAL(camera._cameraVersMonde._21, -1);
	TESTLIB_ASSERT_EQUAL(camera._cameraVersMonde._22, 0);

	TESTLIB_ASSERT_EQUAL(camera._mondeVersCamera._00, 0);
	TESTLIB_ASSERT_EQUAL(camera._mondeVersCamera._01, 1);
	TESTLIB_ASSERT_EQUAL(camera._mondeVersCamera._02, 0);
	TESTLIB_ASSERT_EQUAL(camera._mondeVersCamera._10, 0);
	TESTLIB_ASSERT_EQUAL(camera._mondeVersCamera._11, 0);
	TESTLIB_ASSERT_EQUAL(camera._mondeVersCamera._12, -1);
	TESTLIB_ASSERT_EQUAL(camera._mondeVersCamera._20, -1);
	TESTLIB_ASSERT_EQUAL(camera._mondeVersCamera._21, 0);
	TESTLIB_ASSERT_EQUAL(camera._mondeVersCamera._22, 0);
}
END_TEST(TestCameraPinhole_constructeur_3)



BEGIN_TEST(TestCameraPinhole_setResolution)
{
	Vecteur3 position(0, 0, 0);
	Vecteur3 visee(0, 0, 1);
	Vecteur3 verticale(0, -1, 0);
	reel fov = 60;
	CameraPinhole camera(position, visee, verticale, fov);
	int nbX=400, nbY=200;
	camera.setResolution(nbX, nbY);

	TESTLIB_ASSERT_ALMOST_EQUAL(camera._dU, 1.15, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(camera._dV, 0.57, 0.01);
}
END_TEST(TestCameraPinhole_setResolution)



BEGIN_TEST(Camera_imageVersEcran)
{
	Vecteur3 position(0, 0, 0);
	Vecteur3 visee(0, 0, 1);
	Vecteur3 verticale(0, -1, 0);
	reel fov = 60;
	CameraPinhole camera(position, visee, verticale, fov);
	int nbX=400, nbY=200;
	camera.setResolution(nbX, nbY);
	Vecteur2 uv = camera.imageVersEcran(100, 150);

	TESTLIB_ASSERT_ALMOST_EQUAL(uv._u, -0.25, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(uv._v, 0.25, 0.01);
}
END_TEST(Camera_imageVersEcran)



BEGIN_TEST(Camera_ecranVersCamera)
{
	Vecteur3 position(0, 0, 0);
	Vecteur3 visee(0, 0, 1);
	Vecteur3 verticale(0, -1, 0);
	reel fov = 60;
	CameraPinhole camera(position, visee, verticale, fov);
	int nbX=400, nbY=200;
	camera.setResolution(nbX, nbY);
	Vecteur2 uv = camera.imageVersEcran(100, 150);
	Vecteur3 UVW = camera.ecranVersCamera(uv);

	TESTLIB_ASSERT_ALMOST_EQUAL(UVW._x, -0.28, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(UVW._y, 0.14, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(UVW._z, 1, 0.01);
}
END_TEST(Camera_ecranVersCamera)



BEGIN_TEST(Camera_cameraVersMonde)
{
	Vecteur3 position(0, 0, 0);
	Vecteur3 visee(0, 0, 1);
	Vecteur3 verticale(0, -1, 0);
	reel fov = 60;
	CameraPinhole camera(position, visee, verticale, fov);
	int nbX=400, nbY=200;
	camera.setResolution(nbX, nbY);
	Vecteur2 uv = camera.imageVersEcran(100, 150);
	Vecteur3 XYZ = camera.cameraVersMonde(camera.ecranVersCamera(uv));

	TESTLIB_ASSERT_ALMOST_EQUAL(XYZ._x, -0.28, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(XYZ._y, 0.14, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(XYZ._z, 1, 0.01);
}
END_TEST(Camera_cameraVersMonde)



BEGIN_TEST(Camera_GenererRayon_1)
{
	Vecteur3 position(1, 2, 3);
	Vecteur3 visee(0, 0, 1);
	Vecteur3 verticale(0, -1, 0);
	reel fov = 60;
	CameraPinhole camera(position, visee, verticale, fov);
	int nbX=400, nbY=200;
	camera.setResolution(nbX, nbY);
	Rayon rayon = camera.genererRayon(100, 150);

	TESTLIB_ASSERT_EQUAL(rayon._origine._x, 1);
	TESTLIB_ASSERT_EQUAL(rayon._origine._y, 2);
	TESTLIB_ASSERT_EQUAL(rayon._origine._z, 3);

	TESTLIB_ASSERT_ALMOST_EQUAL(rayon._direction._x, -0.27, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(rayon._direction._y, 0.13, 0.01);
	TESTLIB_ASSERT_ALMOST_EQUAL(rayon._direction._z, 0.95, 0.01);
}
END_TEST(Camera_GenererRayon_1)


#endif



