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
		//エフェクト発生フラグ
		bool effectStart;
		//エフェクト発生フラグ
		bool effectInStart;
		//エフェクト発生フラグ
		bool effectOutStart;
		//シーンエフェクト実行フレーム
		int waitcount;
		//シーンエフェクトカウンタ
		int effectcount;
	public:
		//コンストラクタ
		SceneManeger();
		//デストラクタ
		~SceneManeger();
		//初期化
		void Initialize(int sceneNo,int wait);
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
