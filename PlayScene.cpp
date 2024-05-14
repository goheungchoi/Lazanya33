#include "pch.h"
#include "PlayScene.h"

PlayScene::PlayScene()
{
	//������ ���� ������ �ʿ��� RenderableObject ����ϱ�.
}

void PlayScene::Update(double DeltaTime)
{
#ifdef PLAYSCENE
	if (/*!�������� �����ߴ°�?*/)
	{
		//TODO: ������ ���� ������ ������Ʈ.

		_renderSystem->ClearRenderableRegistry();
		
		//���� ���۽� �ʿ���renderer���
		_renderSystem->RegisterRenderableObject(dynamic_cast<IRenderable*>(player));
	}
	else//�������� ����ٸ�
	{
		/*player=new Decorators*/
		//TODO: ���� ���� ������Ʈ
	}
#endif
}

void PlayScene::Draw()
{
#ifdef PLAYSCENE
	if (/*!�������� �����ߴ°�?*/)
	{

		_renderSystem->Render();
		//TODO: ������ ���� ������ ������Ʈ.
	}
	else//�������� ����ٸ�
	{
		_renderSystem->Render();
		//TODO: ���� ���� ����
	}
#endif
}
