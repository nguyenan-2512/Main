// Diem.cpp - Tri?n khai l?p ?i?m
#include "Diem.h"
#include <iostream>
using namespace std;

Diem::Diem(int x, int y) : x(x), y(y) {}

Diem::~Diem() {}

int Diem::layX() const {
	return x;
}

int Diem::layY() const {
	return y;
}

void Diem::datX(int x) {
	this->x = x;
}

void Diem::datY(int y) {
	this->y = y;
}

void Diem::datXY(int x, int y) {
	this->x = x;
	this->y = y;
}

bool Diem::operator==(const Diem& khac) const {
	return (x == khac.x && y == khac.y);
}

bool Diem::operator!=(const Diem& khac) const {
	return !(*this == khac);
}