#include "GameScene.h"
#include"../SceneManager.h"

#include "../../GameObject/Stage/Stage01/Stage01.h"
#include "../../GameObject/Character/Player/Player.h"
#include "../../GameObject/Stage/Lift/Lift.h"

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

	//===================================================================
	// リフト初期化
	//===================================================================
	std::shared_ptr<Lift> _lift = std::make_shared<Lift>();
	_lift->Init();
	AddObject(_lift);

	//===================================================================
	// キャラクター初期化
	//===================================================================
	std::shared_ptr<Player> _player = std::make_shared<Player>();
	_player->Init();
	_player->RegistHitObject(_stage01);
	_player->RegistHitObject(_lift);
	AddObject(_player);

	//===================================================================
	// カメラ初期化
	//===================================================================
	m_Camera = std::make_unique<TPSCamera>();
	m_Camera->Init();
	m_Camera->SetTarget(_player);
	AddObject(m_Camera);

}
