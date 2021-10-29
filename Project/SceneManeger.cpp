#include "SceneManeger.h"
#include"GameDefine.h"
#include<Mof.h>

//�e�V�[���̃C���N���[�h
#include"TitleScene.h"
#include"GameScene.h"
namespace Game
{
	Game::SceneManeger::SceneManeger()
	{
	}

	Game::SceneManeger::~SceneManeger()
	{
	}

	void Game::SceneManeger::Initialize(int sceneNo)
	{
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
		//�V�[���̍X�V
		currentScene->Update();
	}

	void Game::SceneManeger::Render()
	{
		//�V�[���̐������ł��ĂȂ��ꍇ�`�悵�Ȃ�
		if (!currentScene) {
			return;
		}
		//�V�[���̍X�V
		currentScene->Render();
	}

	void Game::SceneManeger::Release()
	{
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