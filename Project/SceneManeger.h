#pragma once
#include "SceneBase.h"
//�V�[���Ǘ��N���X
namespace Game
{
	class SceneManeger
	{
	private:
		//���ݎ��s����Ă���V�[��
		ScebePtr currentScene;
		//�ύX����s�����V�[��
		ScebePtr nextScene;
	public:
		//�R���X�g���N�^
		SceneManeger();
		//�f�X�g���N�^
		~SceneManeger();
		//������
		void Initialize(int sceneNo);
		//�X�V
		void Update();
		//�`��
		void Render();
		//���
		void Release();

		//�V�[���̐���
		ScebePtr Create(int sceneNo);
	};
}
