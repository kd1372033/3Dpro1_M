#include "GameScene.h"
#include"../SceneManager.h"

#include "../../GameObject/Stage/Stage01/Stage01.h"
#include "../../GameObject/Stage/Stage01/Water/Water.h"

#include "../../GameObject/Character/Player/Player.h"

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
	// 不透明のモデルを描画してから半透明のモデルを描画する


	//===================================================================
	// ステージ初期化
	//===================================================================
	std::shared_ptr<Stage01> _stage01 = std::make_shared<Stage01>();
	_stage01->Init();
	AddObject(_stage01);

	//===================================================================
	// 水初期化 
	// ここで描画するとプレイヤーの足が埋まる
	//	->描画順の影響で脚が隠れているため脚を描画しなくていーやーとなる
	//===================================================================
	/*std::shared_ptr<Water> _water = std::make_shared<Water>();
	_water->Init();
	AddObject(_water);*/

	//===================================================================
	// 水初期化 
	//===================================================================
	std::shared_ptr<Water> _water = std::make_shared<Water>();
	_water->Init();
	AddObject(_water);

	//===================================================================
	// キャラクター初期化
	//===================================================================
	std::shared_ptr<Player> _player = std::make_shared<Player>();
	_player->Init();
	_player->RegistHitObject(_stage01);
	AddObject(_player);

	//===================================================================
	// 水初期化 オブジェクトが増えたりすると、面倒になる
	//===================================================================
	/*std::shared_ptr<Water> _water = std::make_shared<Water>();
	_water->Init();
	AddObject(_water);*/

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
