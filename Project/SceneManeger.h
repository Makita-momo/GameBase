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
		//�G�t�F�N�g�����t���O
		bool effectStart;
		//�G�t�F�N�g�����t���O
		bool effectInStart;
		//�G�t�F�N�g�����t���O
		bool effectOutStart;
		//�V�[���G�t�F�N�g���s�t���[��
		int waitcount;
		//�V�[���G�t�F�N�g�J�E���^
		int effectcount;
	public:
		//�R���X�g���N�^
		SceneManeger();
		//�f�X�g���N�^
		~SceneManeger();
		//������
		void Initialize(int sceneNo,int wait);
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
