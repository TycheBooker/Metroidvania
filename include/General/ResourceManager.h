#pragma once

template <typename Derived, typename T>
class ResourceManager
{
public:
    ResourceManager(const std::string &pathsFile);
    virtual ~ResourceManager();

	T* load(const std::string& path);

    T* getResource(const std::string& id);
	std::string getPath(const std::string& id);

	bool requireResource(const std::string& id);
	bool releaseResource(const std::string& id);
	void purgeResources();
private:
	void loadPaths(const std::string& pathFile);

	std::pair<T*, unsigned>* find(const std::string& id);
	bool unload(const std::string& id);

    std::unordered_map<std::string, std::pair<T*, unsigned>> resources;
    std::unordered_map<std::string, std::string> paths;
};

#include "ResourceManager.inl"
