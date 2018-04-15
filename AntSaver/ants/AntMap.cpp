#include "antMap.h"

AntMap::~AntMap()
{
	delete(colours);
	delete(directions);
}
