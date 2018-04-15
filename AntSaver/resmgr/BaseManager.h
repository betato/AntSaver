#pragma once

#include <map>

template<typename Enum, typename Resource>
class BaseManager
{
public:
	const Resource& get(Enum name) const
	{
		return resources.at(name);
	}
protected:
	void addResource(Enum name, const std::string& file)
	{
		Resource res;
		res.loadFromFile(file);
		resources.insert(std::make_pair(name, res));
	}
private:
	std::map<Enum, Resource> resources;
};
