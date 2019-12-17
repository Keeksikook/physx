#pragma once
#include <string>
#include <vector>
#include "Properties.h"
#include "SFML/Graphics.hpp"
#include <assert.h>
#include "IntersectData.h"

namespace px
{	
	//Constants
	static double PI = 3.14159265358979323846;

	/*	Units:
		Angle::Unit::DEG
		Angle::Unit::RAD
	*/
	
	//Vector2
	template<typename T>
	class Vector2;
	typedef Vector2<float> Vector2f;

	class Drawable
	{
	public:
		static sf::RenderWindow* window;
	};

	template<typename T>
	class Vector2 : public Drawable
	{
	private:
	protected:
	public:
		//Members
		T x, y;
		static sf::RenderWindow* window;

		//Constructors
		Vector2<T>(T x, T y);
		Vector2<T>();
		Vector2<T>(T magnitude, Angle angle);

		//QOL functions
		const T getMagnitude() const;
		const Vector2<T> getNormalized() const;
		Vector2<T>& normalize();
		const Angle getAngle() const;
		const T dot(const Vector2<T>& other) const;
		static void drawVector(Vector2<T> vector);
		static void drawVector(const Vector2<T>& position, const Vector2<T>& vector);
		static void setWindow(sf::RenderWindow& window) { Vector2<T>::window = &window; }
		void draw(const Vector2<T>& position = {0, 0}) const;

		//Operator overloads
		bool operator==(const Vector2<T>& other)const;
		const Vector2<T> operator+(const Vector2<T>& other)const;
		Vector2<T>& operator+=(const Vector2<T>& other);
		Vector2<T>& operator=(const Vector2<T>& other);
		const Vector2<T> operator-(const Vector2<T>& other)const;
		Vector2<T>& operator-=(const Vector2<T>& other);
		const Vector2<T> operator*(const Vector2<T>& other)const;
		const Vector2<T> operator*(const T& other)const;
		Vector2<T>& operator*=(const Vector2<T>& other);
		Vector2<T>& operator*=(const T& other);
		const Vector2<T> operator/(const Vector2<T>& other)const;
		const Vector2<T> operator/(const T& other)const;
		Vector2<T>& operator/=(const Vector2<T>& other);
		Vector2<T>& operator/=(const T& other);

		template<typename E>
		friend std::ostream& operator<<(std::ostream& cout, const Vector2<E>& vector);
	
	};

	template<typename T>
	sf::RenderWindow* px::Vector2<T>::window = nullptr;

	class LineSegment : public Drawable
	{
	private:
		
	public:
		LineSegment(Vector2f start, Vector2f end): start(start), end(end) {}
		Vector2f start, end;
		void draw();
	};

	template<typename T>
	inline Vector2<T>::Vector2(T x, T y)
		:
		x(x), y(y)
	{
	}

	template<typename T>
	inline Vector2<T>::Vector2()
		:
		x(0), y(0)
	{
	}

	template<typename T>
	inline Vector2<T>::Vector2(T magnitude, Angle angle) // Construct vector from magnitude and angle
		:
		x(magnitude * cosf(angle.rad())),
		y(magnitude * sinf(angle.rad()))
	{
	}

	template<typename T>
	inline bool Vector2<T>::operator==(const Vector2<T>& other) const
	{
		return (this->x == other.x && this->y = other.y);
	}

	template<typename T>
	inline const Vector2<T> Vector2<T>::operator+(const Vector2<T>& other)const
	{
		return Vector2<T>(this->x + other.x, this->y + other.y);
	}

	template<typename T>
	inline Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& other)
	{
		*this = *this + other;
		return *this;
	}

	template<typename T>
	inline Vector2<T>& Vector2<T>::operator=(const Vector2<T>& other)
	{
		this->x = other.x;
		this->y = other.y;
		return *this;
	}

	template<typename T>
	inline const Vector2<T> Vector2<T>::operator-(const Vector2<T>& other)const
	{
		return Vector2<T>(this->x - other.x, this->y - other.y);
	}

	template<typename T>
	inline Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& other)
	{
		*this = *this - other;
		return *this;
	}

	template<typename T>
	inline const Vector2<T> Vector2<T>::operator*(const Vector2<T>& other) const
	{
		return this->dot(other);
	}

	template<typename T>
	inline const Vector2<T> Vector2<T>::operator*(const T& other) const
	{
		return Vector2<T>(this->x * other, this->y * other);
	}

	template<typename T>
	inline Vector2<T>& Vector2<T>::operator*=(const Vector2<T>& other)
	{
		*this = *this * other;
		return *this;
	}

	template<typename T>
	inline Vector2<T>& Vector2<T>::operator*=(const T & other)
	{
		*this = *this * other;
		return *this;
	}

	template<typename T>
	inline const Vector2<T> Vector2<T>::operator/(const Vector2<T>& other) const
	{
		return Vector2<T>(this->x / other.x, this->y / other.y);
	}

	template<typename T>
	inline const Vector2<T> Vector2<T>::operator/(const T& other) const
	{
		return Vector2<T>(this->x / other, this->y / other);
	}

	template<typename T>
	inline Vector2<T>& Vector2<T>::operator/=(const Vector2<T>& other)
	{
		*this = *this / other;
		return *this;
	}

	template<typename T>
	inline Vector2<T>& Vector2<T>::operator/=(const T & other)
	{
		*this = *this / other;
		return *this;
	}

	template<typename T>
	inline const T Vector2<T>::getMagnitude() const
	{
		return (sqrtf(x*x + y*y));
	}

	template<typename T>
	inline const Vector2<T> Vector2<T>::getNormalized() const
	{
		return *this / this->getMagnitude();
	}

	template<typename T>
	inline Vector2<T>& Vector2<T>::normalize()
	{
		*this = getNormalized(*this);
		return *this;
	}

	template<typename T>
	inline const Angle Vector2<T>::getAngle() const
	{
		return Angle(atan2f(this->y, this->x), Angle::Unit::RAD);
	}


	template<typename T>
	inline const T Vector2<T>::dot(const Vector2<T>& other) const
	{
		Angle angleDiff(this->getAngle().rad() - other.getAngle().rad(), Angle::Unit::RAD);
		return T(cos(angleDiff.rad())*this->getMagnitude()*other.getMagnitude());
	}

	template<typename T>
	inline void Vector2<T>::drawVector(const Vector2<T> vector)
	{
		drawVector({ 0, 0 }, vector);
	}

	template<typename T>
	inline void Vector2<T>::drawVector(const Vector2<T>& position, const Vector2<T>& vector)
	{
		assert(window);
		sf::Vertex line[3] = { sf::Vector2f(position.x, position.y), sf::Vector2f(position.x + vector.x*0.75, position.y + vector.y*0.75), sf::Vector2f(position.x + vector.x, position.y + vector.y) };
		line[0].color = sf::Color::White;
		line[1].color = sf::Color::White;
		line[2].color = sf::Color::Red;
		window->draw(line, 3, sf::LineStrip);
	}

	template<typename T>
	inline void Vector2<T>::draw(const Vector2<T>& position) const
	{
		drawVector(position,*this);
	}

	template<typename E>
	std::ostream & operator<<(std::ostream & cout, const Vector2<E>& vector)
	{
		cout << '{' << vector.x << ',' << vector.y << '}';
		return cout;
	}
}