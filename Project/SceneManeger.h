#pragma once
#include "SceneBase.h"
//シーン管理クラス
namespace Game
{
	class SceneManeger
	{
	private:
		//現在実行されているシーン
		ScebePtr currentScene;
		//変更後実行されるシーン
		ScebePtr nextScene;
	public:
		//コンストラクタ
		SceneManeger();
		//デストラクタ
		~SceneManeger();
		//初期化
		void Initialize(int sceneNo);
		//更新
		void Update();
		//描画
		void Render();
		//解放
		void Release();

		//シーンの生成
		ScebePtr Create(int sceneNo);
	};
}
