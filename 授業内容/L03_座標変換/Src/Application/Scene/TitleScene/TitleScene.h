#pragma once

#include"../BaseScene/BaseScene.h"

class TitleScene : public BaseScene
{
public :

	TitleScene()  {}
	~TitleScene() { Release(); }

private :

	void Event()	override;
	void Init()		override;
	void Release()  override;
};
