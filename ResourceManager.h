#pragma once

using namespace Gdiplus;

class ResourceManager {
  using ImageName = std::wstring;
  std::unordered_map<ImageName, Bitmap*> _images;
	std::unordered_map<ImageName, CachedBitmap*> _cachedImages;

	static std::unique_ptr<ResourceManager> _instance;
  PrivateFontCollection _fontCollection;

public:
  ResourceManager() {}
	ResourceManager(const ResourceManager&) = delete;
  ResourceManager(ResourceManager&&) noexcept = delete;
  ResourceManager& operator=(const ResourceManager&) = delete;
  ResourceManager& operator=(ResourceManager&&) noexcept = delete;
  ~ResourceManager() {
		for (auto p : _images) {
			delete p.second;
		}
		for (auto p : _cachedImages) {
			delete p.second;
		}
	}

  bool LoadImageFromFile(const wchar_t* path, const ImageName& name);
  bool LoadImages(const wchar_t* szPath);
 
  Bitmap* GetImage(const ImageName& name);
	CachedBitmap* GetCachedImage(const ImageName& name);

	bool CacheAllImages(Graphics* g);

public:
	static ResourceManager& Create();
	static void Destory();
	static ResourceManager& Get();
};

