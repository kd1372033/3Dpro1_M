#pragma once

#include"../BaseScene/BaseScene.h"

class GameScene : public BaseScene
{
public :
	
	GameScene()  {}
	~GameScene() { Release(); }

private:

	void Event()	override;
	void Init()		override;
	void Release()	override;
};
