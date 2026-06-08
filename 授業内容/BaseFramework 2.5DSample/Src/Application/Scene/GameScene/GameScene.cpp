#include "GameScene.h"
#include"../SceneManager.h"

#include"../../GameObject/Character/Hamu.h"
#include"../../GameObject/Terrain/Terrain.h"

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
	// カメラの初期化
	//===================================================================
	m_camera = std::make_unique<KdCamera>();

	//===================================================================
	// キャラクターの初期化
	//===================================================================
	std::shared_ptr<Hamu> _hamu = std::make_shared<Hamu>();
	_hamu->Init();
	AddObject(_hamu);

	//===================================================================
	// ステージの初期化
	//===================================================================
	std::shared_ptr<Terrain> _terrain = std::make_shared<Terrain>();
	_terrain->Init();
	AddObject(_terrain);
}

void GameScene::Release()
{
}
