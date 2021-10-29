#include "SceneManeger.h"
#include"GameDefine.h"
#include<Mof.h>

//各シーンのインクルード
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
		//各メンバーで初期化
		Release();
		waitcount = wait;
		effectcount = wait / 2;
		effectInStart = false;
		effectOutStart = true;

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
		//シーンの更新
		currentScene->Update();
		//シーンの変更
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
				//次のシーンの取得
				if (nextScene)
				{
					//シーンの読み込み
					nextScene->Load();
					//シーンの初期化
					nextScene->Initialize();
				}
				//シーンのリセット
				currentScene->Release();
				currentScene.reset();
				//次のシーンを用意
				currentScene = nextScene;
				nextScene = nullptr;
				effectStart = false;
			}
		}
	}

	void Game::SceneManeger::Render()
	{
		//シーンの生成ができてない場合描画しない
		if (!currentScene) {
			return;
		}
		//シーンの更新
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