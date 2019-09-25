#include "Mat3.h"
#include <math.h>

Mat3::Mat3(const Vec3& first, const Vec3& second, const Vec3& third) {
	this->first = first;
	this->second = second;
	this->third = third;
}

const Vec3& Mat3::operator[](int index) const {
	switch(index) {
		case 0: return first; break;
		case 1: return second; break;
		case 2: return third; break;
	}
	throw std::invalid_argument("Matrix index out of bounds");
}

Vec3 Mat3::operator*(const Vec3& other) {
	return {
		Vec3::dot(first, other),
		Vec3::dot(second, other),
		Vec3::dot(third, other)
	};
}

Mat3 Mat3::identity() {
	return {
		{1,0,0},
		{0,1,0},
		{0,0,1}
	};
}

//each of these rotates a vector counter-clockwise when the axis of rotation is 
//pointing towards the observer.

Mat3 Mat3::rotation_around_x(float theta) {
	float cos_theta = cos(theta);
	float sin_theta = sin(theta);
	return {
		{1,			0,			  0},
		{0,	cos_theta, -1*sin_theta},
		{0,	sin_theta, 	  cos_theta}
	};
}

Mat3 Mat3::rotation_around_y(float theta) {
	float cos_theta = cos(theta);
	float sin_theta = sin(theta);
	return {
		{   cos_theta, 0, sin_theta},
		{   		0, 1, 0		   },
		{-1*sin_theta, 0, cos_theta}
	};
}

Mat3 Mat3::rotation_around_z(float theta) {
	float cos_theta = cos(theta);
	float sin_theta = sin(theta);
	return {
		{cos_theta, -1*sin_theta, 0},
		{sin_theta,    cos_theta, 0},
		{	 	 0,			   0, 1}
	};
}
