#pragma once
#include "SceneGraph.h"

template<class T>
class SingleSpriteRenderable;
class Container;
class Button;
class ButtonEventHandler;

class DescriptionScene:public IScene
{
	ButtonEventHandler* _buttonEventHandle;
	class Container* _descriptionContainer;
	struct DescriptionComponents
	{
		SingleSpriteRenderable<DescriptionComponents>* background;
		Button* entryButton;
	}_descriptionComps;
public:
	DescriptionScene();
	~DescriptionScene(){};
	void Update(double deltaTime)override;
	void Draw()override;
	void InitScene()override;
	void EndScene()override;
};
//TODO :  png �Ѿ���´�� entry�� ��ư. description�� 1920 1080 �̹��� ����.
