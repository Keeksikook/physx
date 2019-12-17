#pragma once
#include "System.h"
class IntersectData
{
public:
	IntersectData(const bool& collides, const px::Vector2f& distToOther);
	~IntersectData();
	const bool Collision;
	const px::Vector2f distToOther;

};

