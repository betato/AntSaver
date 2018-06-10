#include "AntMap.h"

AntMap::~AntMap()
{
	delete(colours);
	delete(directions);
}
