#pragma once

using namespace Gdiplus;

class ResourceManager {
  using ImageName = std::wstring;
  std::unordered_map<ImageName, Bitmap*> _images;
	std::unordered_map<ImageName, CachedBitmap*> _cachedImages;

	static std::unique_ptr<ResourceManager> _instance;

public:
  ResourceManager() {}
	ResourceManager(const ResourceManager&) = delete;
  ResourceManager(ResourceManager&&) noexcept = delete;
  ResourceManager& operator=(const ResourceManager&) = delete;
  ResourceManager& operator=(ResourceManager&&) noexcept = delete;
  ~ResourceManager() {}

  bool LoadImageFromFile(const wchar_t* path, const ImageName& name);

  Bitmap* GetImage(const ImageName& name);

public:
	static ResourceManager& Create();
	static void Destory();
	static ResourceManager& Get();
};

