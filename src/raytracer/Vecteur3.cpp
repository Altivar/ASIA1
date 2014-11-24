#include "Vecteur3.h"

#include <cmath>

Vecteur3::Vecteur3(reel x, reel y, reel z):
_x(x), _y(y), _z(z)
{}

Vecteur3::Vecteur3():
_x(0), _y(0), _z(0)
{}

Vecteur3 Vecteur3::operator-() const {
  return Vecteur3(-_x, -_y, -_z);
}

reel Vecteur3::calculerNormeCarree() const {
  return _x*_x + _y*_y + _z*_z;
}

reel Vecteur3::calculerNorme() const {
  return sqrt(_x*_x + _y*_y + _z*_z);
}

void Vecteur3::normer() {
  operator*=(1/calculerNorme());
}

void Vecteur3::normer(reel norme) {
  operator*=(1/norme);
}

Vecteur3 & Vecteur3::operator+=(const Vecteur3 & v) {
  _x += v._x;
  _y += v._y;
  _z += v._z;
  return *this;
}

Vecteur3 & Vecteur3::operator*=(reel k) {
  _x *= k;
  _y *= k;
  _z *= k;
  return *this;
}

Vecteur3 ProduitVectoriel(const Vecteur3 & v1, const Vecteur3 & v2){
  return Vecteur3(v1._y*v2._z -v1._z*v2._y,  v1._z*v2._x -v1._x*v2._z,  v1._x*v2._y -v1._y*v2._x);
}

reel ProduitScalaire(const Vecteur3 & v1, const Vecteur3 & v2) {
  return v1._x*v2._x + v1._y*v2._y + v1._z*v2._z;
}

Vecteur3 Vecteur3::operator*(reel k) const {
  return Vecteur3(_x*k, _y*k, _z*k);
}

Vecteur3 Vecteur3::operator*(const Vecteur3 & v) const {
  return Vecteur3(_x*v._x, _y*v._y, _z*v._z);
}

Vecteur3 Vecteur3::operator-(const Vecteur3 & v) const {
  return Vecteur3(_x-v._x, _y-v._y, _z-v._z);
}

Vecteur3 Vecteur3::operator+(const Vecteur3 & v) const {
  return Vecteur3(_x+v._x, _y+v._y, _z+v._z);
}

Vecteur3 VecteurReflechi(const Vecteur3 & I, const Vecteur3 & N) {
  return I - N*ProduitScalaire(N, I)*2;
}

