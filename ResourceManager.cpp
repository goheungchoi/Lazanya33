#include "ResourceManager.h"

using namespace Gdiplus;

std::unique_ptr<ResourceManager> ResourceManager::_instance(nullptr);

ResourceManager& ResourceManager::Create() { 
	if (_instance) 
		throw std::runtime_error("Recreation of ResourceManager detected!");

	_instance.reset(new ResourceManager());
	return *_instance;
}

void ResourceManager::Destory() { 
	if (!_instance) 
		throw std::runtime_error("Destruction of uninitialized ResourceManager detected!");

	_instance.release(); 
}

ResourceManager& ResourceManager::Get() { 
	if (!_instance) 
		throw std::runtime_error("Access of uninitialized ResourceManager detected!");

	return *_instance; 
}

bool ResourceManager::LoadImageFromFile(const wchar_t* path, const ImageName& name) {
  Bitmap* pImage = Bitmap::FromFile(path); 
	if (!pImage) return false;
	_images[name] = pImage;
	return true;
}

Bitmap* ResourceManager::GetImage(const ImageName& name) { 
  auto it = _images.find(name);
  if (it == _images.end()) return nullptr;
  return it->second;
}
