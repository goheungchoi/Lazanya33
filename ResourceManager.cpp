#include "ResourceManager.h"
#include <filesystem>

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

bool ResourceManager::LoadImages(const wchar_t* szPath)
{
  std::wstring path = szPath;

  // Tour all files in that path
  for (const auto& entry : std::filesystem::directory_iterator(path)) {
    if (entry.path().extension() == L".png") {
      // Extract File Name
      std::wstring filename = entry.path().filename().wstring();

      // Create Bitmap Object and Add to _images Map
      Bitmap* bitmap = Bitmap::FromFile(entry.path().c_str());

      //Clear .png from string to save to map
      //  -> so that only names can be retrieved from outside
      size_t extensionPos = filename.find(L".png");
      if (extensionPos != std::wstring::npos) {
        filename.erase(extensionPos, 4); 
      }

      if (bitmap) {
        _images[filename] = bitmap;
      }
    }
  }

  return !_images.empty();
}


Bitmap* ResourceManager::GetImage(const ImageName& name) { 
  auto it = _images.find(name);
  if (it == _images.end()) return nullptr;
  return it->second;
}

CachedBitmap* ResourceManager::GetCachedImage(const ImageName& name) {
	auto it = _cachedImages.find(name);
  if (it == _cachedImages.end()) return nullptr;
  return it->second;
}

bool ResourceManager::CacheAllImages(Graphics* g) {
	for (auto& p : _images) {
		_cachedImages[p.first] = new CachedBitmap(p.second, g);
	}
	return true;
}
