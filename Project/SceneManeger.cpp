#include "SceneManeger.h"
#include"GameDefine.h"
#include<Mof.h>

//�e�V�[���̃C���N���[�h
#include"TitleScene.h"
#include"GameScene.h"
namespace Game
{
	Game::SceneManeger::SceneManeger()
		:currentScene(nullptr),
		nextScene(nullptr),
		effectInStart(false),
		effectOutStart(true),
		effectcount(0),
		waitcount(30)
	{
	}

	Game::SceneManeger::~SceneManeger()
	{
	}

	void Game::SceneManeger::Initialize(int sceneNo,int wait)
	{
		//�e�����o�[�ŏ�����
		Release();
		waitcount = wait;
		effectcount = wait / 2;
		effectInStart = false;
		effectOutStart = true;

		//�����V�[���̍쐬
		currentScene = Create(sceneNo);
		if(currentScene == nullptr)
		{
			MOF_PRINTLOG("SceneCreate failured\n");
			return;
		}
		//�ǂݍ��ݎ��s�����ꍇ
		if (!currentScene->Load())
		{
			MOF_PRINTLOG("SceneCreate failured\n");
			return;
		}
		currentScene->Initialize();
	}

	void Game::SceneManeger::Update()
	{
		//�V�[���̐������ł��ĂȂ��ꍇ�X�V���Ȃ�
		if (!currentScene) {
			return;
		}
		if (effectInStart)
		{
			effectcount++;
			if (effectcount >= waitcount / 2)
			{
				effectInStart = false;
				effectOutStart = true;
			}
		}
		else if (effectOutStart)
		{
			effectcount++;
			if (effectcount >= waitcount)
			{
				effectcount = 0;
				effectOutStart = false;
			}
		}
		else if(effectStart)
		{
			effectStart = false;
		}
		//�V�[���̍X�V
		currentScene->Update();
		//�V�[���̕ύX
		if (currentScene->IsChange())
		{
			if (!effectStart)
			{
				effectStart = true;
				effectInStart = true;
				effectOutStart = false;
			}
			if (effectOutStart)
			{
				int next = currentScene->GetNextScene();
				nextScene = Create(next);
				//���̃V�[���̎擾
				if (nextScene)
				{
					//�V�[���̓ǂݍ���
					nextScene->Load();
					//�V�[���̏�����
					nextScene->Initialize();
				}
				//�V�[���̃��Z�b�g
				currentScene->Release();
				currentScene.reset();
				//���̃V�[����p��
				currentScene = nextScene;
				nextScene = nullptr;
				effectStart = false;
			}
		}
	}

	void Game::SceneManeger::Render()
	{
		//�V�[���̐������ł��ĂȂ��ꍇ�`�悵�Ȃ�
		if (!currentScene) {
			return;
		}
		//�V�[���̍X�V
		currentScene->Render();
		CRectangle fadeRecr(0, 0, g_pGraphics->GetTargetWidth(),
			g_pGraphics->GetTargetHeight());

		if (effectInStart)
		{
			float alpha = effectcount / (waitcount / 0.5f);
			CGraphicsUtilities::RenderFillRect(fadeRecr, MOF_ALPHA_BLACK((int)(255 * alpha)));
		}
		if (effectOutStart)
		{
			float alpha = (effectcount - (waitcount / 0.5f)) / (waitcount * 0.5f);
			CGraphicsUtilities::RenderFillRect(fadeRecr, MOF_ALPHA_BLACK((int)(255 * (1.0f - alpha))));
		}
	}

	void Game::SceneManeger::Release()
	{
		if (currentScene)
		{
			currentScene->Release();
			currentScene.reset();
		}
		if (nextScene)
		{
			nextScene->Release();
			nextScene.reset();
		}

	}
	//�V�[���̐���
	ScebePtr Game::SceneManeger::Create(int sceneNo)
	{
		switch (sceneNo)
		{
		case SceneName_Title:
			return std::make_shared<TitleScene>();
		case SceneName_Game:
			return std::make_shared<GameScene>();
		default:
			break;
		}
		return nullptr;
	}
}