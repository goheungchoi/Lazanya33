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

bool ResourceManager::LoadTexture(const wchar_t* szPath)
{
	//A structure used to store file information during directory traversal.
	_wfinddata_t fd;
	//A handle used by _wfindfirst and _wfindnext to iterate over files.
	intptr_t handle;
	// A variable to store the result of _wfindnext.
	int result = 0;
	//An array to store the root path of the directory to search.
	wchar_t rootPath[256] = L"";

	lstrcpy(rootPath, szPath);
	lstrcpy(rootPath, L"/*");

	//This initializes the search and returns a handle to be used in subsequent searches.
	handle = _wfindfirst(rootPath, &fd);

	//If result is - 1, it breaks the loop, indicating no more files.
	if (-1 != handle)
	{
		int count = 0;
		while (true)
		{
			result = _wfindnext(handle, &fd);

			if (-1 == result)
				break;
			
			if (!lstrcmp(L".", fd.name) || !lstrcmp(L"..", fd.name))
				continue;

			if (0 == result && 16 == fd.attrib)
			{
				int index = 0;
				wchar_t currPath[256] = L"";

				while ('*' != rootPath[index])
				{
					currPath[index] = rootPath[index];
					index++;
				}

				lstrcat(currPath, fd.name);
				LoadTexture(currPath);
				continue;
			}

			wchar_t textureTag[64] = L"";
			wchar_t filePath[256] = L"";
			
			lstrcpy(filePath, szPath);
			lstrcat(filePath, L"/");
			lstrcat(filePath, fd.name);

			int index = 0;
			int offset = 0;
			int length = lstrlen(szPath);


		}
	}
	return true;
}

Bitmap* ResourceManager::GetImage(const ImageName& name) { 
  auto it = _images.find(name);
  if (it == _images.end()) return nullptr;
  return it->second;
}
