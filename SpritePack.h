#pragma once

using namespace Gdiplus;

template <class T>
class SpritePack {
	using Tag = std::wstring;

  static std::unordered_map<Tag, Bitmap*> _pSpriteRegister;
  static std::unordered_map<Tag, CachedBitmap*> _pSpriteCacheData;

public:

	static void AddSprite(Bitmap* pSprite, const Tag& tag, Graphics* g = nullptr);

	static Bitmap* GetSprite(const Tag& tag);

	static CachedBitmap* GetCachedSprite(const Tag& tag);

	static void CacheAllSprites(Graphics& g);
};

template <class T>
std::unordered_map<std::wstring, Bitmap*>
    SpritePack<T>::_pSpriteRegister;

template <class T>
std::unordered_map<std::wstring, CachedBitmap*>
    SpritePack<T>::_pSpriteCacheData;

template <class T>
void SpritePack<T>::AddSprite(
	Bitmap* pSprite, 
	const Tag& tag,
	Graphics* g) {
	if (!pSprite) {
		throw std::invalid_argument("MultiSpriteRenderable: Sprite is nullptr!");
	}
		
	_pSpriteRegister[tag] = pSprite;

	if (g) _pSpriteCacheData[tag] = new CachedBitmap(pSprite, g);
}

template <class T>
Bitmap* SpritePack<T>::GetSprite(const Tag& tag) {
	// Check if the sprite with this tag exists
	auto it = _pSpriteRegister.find(tag);
	if (it == _pSpriteRegister.end())
    return nullptr;

	return it->second;
}

template <class T>
CachedBitmap* SpritePack<T>::GetCachedSprite(const Tag& tag) {
	// Check if the cached sprite exists
	auto cacheIt = _pSpriteCacheData.find(tag);
	if (cacheIt == _pSpriteCacheData.end()) 
		return nullptr; 

	return cacheIt->second;
}

template <class T>
void SpritePack<T>::CacheAllSprites(Graphics& g) {
	for (auto& it : _pSpriteRegister) {
    _pSpriteCacheData[it.first] = new CachedBitmap(it.second, &g);
	}
}
