#include "IntersectData.h"



IntersectData::IntersectData(const bool& collides, const px::Vector2f& distToOther)
	:
	Collision(collides), distToOther(distToOther)
{
}


IntersectData::~IntersectData()
{
}
