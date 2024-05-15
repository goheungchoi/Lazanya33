#include "pch.h"
#include "PlayScene.h"
#include "BrickGenerationSystem.h"
PlayScene::PlayScene()
{
	_renderSystem->RegisterRenderableObject(_walls);
	_renderSystem->RegisterRenderableObject(dynamic_cast<IRenderable*>(_player));
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
	//TODO: �������.->�÷��̾�� �긯�� �簢������ �������ؼ� ���� ���� �۵��ϴ��� Ȯ��.
	/*
	* �긯�� 3ĭ ���� �ö󰡸� ���� �������ֱ�.
	* player�� ��ĭ ������ �� ���� �긯 ��ĭ�� �ø���
	* �긯�� ȭ�� ������ ������ popfront�ϱ�
	*/
}

void PlayScene::Draw()
{
	_renderSystem->Render();
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
