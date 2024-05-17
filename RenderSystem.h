#pragma once

#include "Renderer.h"
#include "IRenderable.h"

#include "ResourceManager.h"

using namespace Gdiplus;

/**
 * @brief ������ �ý���. 
 * �����) �������� ������Ʈ�� �ý��ۿ� ����� Render() �Լ���
 * ȣ���Ѵ�.
 */
class RenderSystem {
  GDIRenderer* _renderer;
  std::vector<IRenderable*> _renderableObjects;

public:
  RenderSystem(GDIRenderer* renderer)
  : _renderer(renderer) {}

  /**
   * @brief �������� ������Ʈ�� ��ο� �� ������Ʈ ��Ͽ� ����Ѵ�.
   * @param renderableObject ��ο� �� ������Ʈ
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
   * @brief �������� ������Ʈ ����� ������ ��, �������� 
   * ��ο� �Լ��� ȣ���Ѵ�.
   */
  void Render() {
    _renderer->Clear();

    for (auto& renderable : _renderableObjects) {
      renderable->Render(*_renderer->GetGraphics());
    }

    _renderer->Draw();
  }
};

