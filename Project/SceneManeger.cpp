#include "SceneManeger.h"
#include"GameDefine.h"
#include<Mof.h>

//各シーンのインクルード
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
		//初期シーンの作成
		currentScene = Create(sceneNo);
		if(currentScene == nullptr)
		{
			MOF_PRINTLOG("SceneCreate failured\n");
			return;
		}
		//読み込み失敗した場合
		if (!currentScene->Load())
		{
			MOF_PRINTLOG("SceneCreate failured\n");
			return;
		}
		currentScene->Initialize();
	}

	void Game::SceneManeger::Update()
	{
		//シーンの生成ができてない場合更新しない
		if (!currentScene) {
			return;
		}
		//シーンの更新
		currentScene->Update();
	}

	void Game::SceneManeger::Render()
	{
		//シーンの生成ができてない場合描画しない
		if (!currentScene) {
			return;
		}
		//シーンの更新
		currentScene->Render();
	}

	void Game::SceneManeger::Release()
	{
	}
	//シーンの生成
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