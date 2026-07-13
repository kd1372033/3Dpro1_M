#pragma once

class CameraBase;

#include "../CharacterBase.h"

class Player : public CharacterBase
{
public:
	Player()						{}
	~Player()			override	{}

	void Init()			override;
	void Update()		override;

	void SetTarGet(const std::shared_ptr<KdGameObject>& target);

private:
	std::weak_ptr<CameraBase> m_wpCamera;

};