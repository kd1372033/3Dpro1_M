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
	// 実装方法①　自力ですごい頑張る処理
	void UpdateLookAtRotateA(const Math::Vector3& targetPos);
	// 実装方法②　計算が良くわからないけどまぁなんとなく分かる処理
	void UpdateLookAtRotateB(const Math::Vector3& targetPos);
	// 実装方法②-①(true)と②-②(false)
	void UpdateLookAtRotateMethod(bool method, float pitch, float yaw);
	// 実装方法③　今までの努力が無に帰す処理
	void UpdateLookAtRotateC(const Math::Vector3& targetPos);

	Math::Vector3 m_targetFollowPos = Math::Vector3::Zero;
	bool          m_isInitialized = false; // 【追加】初回同期が完了したかどうかのフラグ
};