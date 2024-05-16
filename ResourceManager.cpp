#pragma once

#include <unordered_map>



namespace lz {

using namespace Gdiplus;

class ResourceManager {
  using ImageName = std::wstring;
  std::unordered_map<ImageName, Image*> _images;

	static ResourceManager* _instance;

public:
  ResourceManager() {}
	ResourceManager(const ResourceManager&) = delete;
  ResourceManager(ResourceManager&&) noexcept = delete;
  ResourceManager& operator=(const ResourceManager&) = delete;
  ResourceManager& operator=(ResourceManager&&) noexcept = delete;
  ~ResourceManager() {}


  bool LoadImageFromFile(const wchar_t* path, const ImageName& name) {
    Image* pImage = Image::FromFile(path); 

		if (!pImage) return false;
		
		_images[name] = pImage;

		return true;
  }

  Image* GetImage(const ImageName& name) { 
    auto it = _images.find(name);
    if (it == _images.end()) return nullptr;
    return it->second;
  }
};



}