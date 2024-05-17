#pragma once

#include "Renderer.h"
#include "IRenderable.h"

#include "ResourceManager.h"

using namespace Gdiplus;

/**
 * @brief 랜더링 시스템. 
 * 사용방법) 렌더러블 오브젝트를 시스템에 등록후 Render() 함수를
 * 호출한다.
 */
class RenderSystem {
  GDIRenderer* _renderer;
  std::vector<IRenderable*> _renderableObjects;

public:
  RenderSystem(GDIRenderer* renderer)
  : _renderer(renderer) {}

  /**
   * @brief 렌더러블 오브젝트를 드로우 할 오브젝트 목록에 등록한다.
   * @param renderableObject 드로우 할 오브젝트
   */
  void RegisterRenderableObject(IRenderable* renderableObject) {
    _renderableObjects.push_back(renderableObject);
  }

  void ClearRenderableRegistry() {
    _renderableObjects.clear();
  }

	void CacheDataInRegistry() {
		for (auto& it : _renderableObjects) {
      it->CacheData(*_renderer->GetGraphics());
		}
	}

  /**
   * @brief 렌더러블 오브젝트 목록을 렌더한 후, 렌더러의 
   * 드로우 함수를 호출한다.
   */
  void Render() {
    _renderer->Clear();

    for (auto& renderable : _renderableObjects) {
      renderable->Render(*_renderer->GetGraphics());
    }

    _renderer->Draw();
  }
};

