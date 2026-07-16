#pragma once
#include "../CameraBase.h"

class CharacterBase;

class CCTVCamera : public CameraBase
{
public:
	CCTVCamera() {}
	~CCTVCamera()			override {}

	void Init()				override;
	void PostUpdate()		override;

private:
	void UpdateLookAtRotate(const Math::Vector3& targetPos);

	Math::Vector3 m_targetFollowPos = Math::Vector3::Zero;
	bool          m_isInitialized = false; // 【追加】初回同期が完了したかどうかのフラグ
};