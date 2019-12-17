#include "Properties.h"

const double px::Mass::kg(double mass, Unit unit) const
{
	switch (unit)
	{
	case Unit::KG:
		return value;
		break;
	case Unit::G:
		return value / 1000;
		break;
	case Unit::TON:
		return value * 1000;
		break;
	}
}
