#pragma once
#include <cmath>

class Vector2D {
public:
	double x = 0;
	double y = 0;

	Vector2D() = default;
	~Vector2D() = default;
	// 全参构造函数
	Vector2D(double x, double y) {
		this->x = x;
		this->y = y;
	}

	// 获取向量长度
	double length() const {
		return sqrt(this->x * this->x + this->y * this->y);
	}

	// 归一化向量
	Vector2D normalize() const {
		double len = length();
		if (len == 0) {
			return Vector2D(0, 0);
		}
		return Vector2D(this->x / len, this->y / len);
	}

	//一大批运算符重载
	Vector2D operator+(const Vector2D& other) const {
		return Vector2D(this->x + other.x, this->y + other.y);
	}

	void operator+=(const Vector2D& other) {
		this->x += other.x;
		this->y += other.y;
	}

	Vector2D operator-(const Vector2D& other) const {
		return Vector2D(this->x - other.x, this->y - other.y);
	}

	void operator-=(const Vector2D& other) {
		this->x -= other.x;
		this->y -= other.y;
	}

	Vector2D operator*(const double scalar) const {
		return Vector2D(x * scalar, y * scalar);
	}

	double operator*(const Vector2D& other) {
		return this->x * other.x + this->y * other.y;
	}

	void operator*=(const double scalar) {
		this->x *= scalar;
		this->y *= scalar;
	}

	Vector2D operator/(const double scalar) const {
		return Vector2D(x / scalar, y / scalar);
	}

	void operator/=(const  double scalar) {
		this->x /= scalar;
		this->y /= scalar;
	}

	bool operator==(const Vector2D& other) const {
		return this->x == other.x && this->y == other.y;
	}

	bool operator!=(const Vector2D& other) const {
		return this->x != other.x || this->y != other.y;
	}
};