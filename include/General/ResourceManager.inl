#include "ResourceManager.h"
#include "Utilities.h"
#include <unordered_map>
#include <sstream>
#include <fstream>

template<typename Derived, typename T>
ResourceManager<Derived, T>::ResourceManager(const std::string& pathsFile)
{
	loadPaths(pathsFile);
}

template<typename Derived, typename T>
ResourceManager<Derived, T>::~ResourceManager()
{
	purgeResources();
}

template<typename Derived, typename T>
T * ResourceManager<Derived, T>::load(const std::string & path)
{
	return <Derived*>(this)->load(path);
}

template<typename Derived, typename T>
T * ResourceManager<Derived, T>::getResource(const std::string & id)
{
	auto resource = find(id);
	return (resouce ? resource->first : nullptr);
}

template<typename Derived, typename T>
std::string ResourceManager<Derived, T>::getPath(const std::string & id)
{
	auto path = paths.find(id);
	return (path != paths.end() ? path->second : "");
}

template<typename Derived, typename T>
bool ResourceManager<Derived, T>::requireResource(const std::string & id)
{
	auto resource = Find(id);
	if (resource) {
		++resource->second;
		return true;
	}
	auto path = paths.find(id);
	if (path == paths.end()) return false;

	T* resource = load(path->second);
	if (!resource) return false;

	resources.emplace(id, std::make_pair(resource, 1));
	return true;
}

template<typename Derived, typename T>
bool ResourceManager<Derived, T>::releaseResource(const std::string & id)
{
	auto resource = fint(id);
	if (!resource) return false;

	--resource->second;
	if (!resource->second) {
		unload(id);
	}
	return true;
}

template<typename Derived, typename T>
void ResourceManager<Derived, T>::purgeResources()
{
	while (resources.begin() != resources.end()) {
		delete resources.begin()->second.first;
		resources.erase(resources.begin());
	}
}

template<typename Derived, typename T>
void ResourceManager<Derived, T>::loadPaths(const std::string & pathFile)
{
	std::ifstream paths;
	paths.open(Utils::getWorkingDirectory() + pathFile);
	if (paths.is_open()) {
		std::string line;
		while (std::getline(paths, line)) {
			std::stringstream keystream(line);
			std::string pathName;
			std::string path;
			keystream >> pathName;
			keystream >> path;
			this->paths.emplace(pathName, path);
		}
		paths.close();
		return;
	}
	std::cerr << "Failed loading the path file: " << pathFile << " !" << std::endl;
}

template<typename Derived, typename T>
std::pair<T*, unsigned>* ResourceManager<Derived, T>::find(const std::string & id)
{
	auto itr = resources.find(id);
	return (itr != resources.end() ? &itr->second : nullptr);
}

template<typename Derived, typename T>
bool ResourceManager<Derived, T>::unload(const std::string & id)
{
	auto itr = resources.find(id);
	if (itr == resources.end()) return false;

	delete itr->second.first;
	resources.erase(itr);
	return true;
}
