#pragma once

template <typename Derived, typename T>
class ResourceManager
{
public:
    ResourceManager(const std::string &pathsFile);
    virtual ~ResourceManager();

    T* getResource(const std::string& id);
private:
    std::unordered_map<std::string, std::pair<T*, unsigned>> resources;
    std::unordered_map<std::string, std::string> paths;
};
