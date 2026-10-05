#include "GameScene.h"
#include"../SceneManager.h"

#include "../../GameObject/Stage/Stage01/Stage01.h"
#include "../../GameObject/Character/Player/Player.h"
#include "../../GameObject/Stage/Stage01/Water/Water.h"
#include "../../GameObject/Character/Weapon/Tanto/Tanto.h"

#include "../../GameObject/Camera/TPSCamera/TPSCamera.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}
}

void GameScene::Init()
{
	//===================================================================
	// ステージ初期化
	//===================================================================
	std::shared_ptr<Stage01> _stage01 = std::make_shared<Stage01>();
	_stage01->Init();
	AddObject(_stage01);

	////水
	//std::shared_ptr<Water> _water = std::make_shared<Water>();
	//_water->Init();
	//AddObject(_water);
	
	//===================================================================
	// キャラクター初期化
	//===================================================================
	std::shared_ptr<Player> _player = std::make_shared<Player>();
	_player->Init();
	_player->RegistHitObject(_stage01);
	AddObject(_player);

	//短刀
	std::shared_ptr<Tanto> _tanto = std::make_shared<Tanto>();
	_tanto->Init();
	//あなたが私の持ち主です　宣言
	_tanto->SetOwner(_player);
	AddObject(_tanto);

	//===================================================================
	// カメラ初期化
	//===================================================================
	m_Camera = std::make_unique<TPSCamera>();
	m_Camera->Init();
	m_Camera->SetTarget(_player);
	AddObject(m_Camera);

	// プレイヤーにカメラ情報をセット
	_player->SetCamera(m_Camera);
}
