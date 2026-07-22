#pragma once

class CameraBase;
class CharacterBase : public KdGameObject
{
public:
	CharacterBase();
	~CharacterBase()					override;

	void Init()							override;
	void Update()						override;
	void PostUpdate()					override;

	void DrawLit()						override;
	void GenerateDepthMapFromLight()	override;

	void RegistHitObject(const std::shared_ptr<KdGameObject>& object)
	{
		m_wpHitObjectList.push_back(object);
	}

	void SetCamera(const std::shared_ptr<CameraBase>& camera)
	{
		m_wpCamera = camera;
	}

	const std::weak_ptr<CameraBase> GetCamera() { return m_wpCamera; }

private:
	// 行列の更新
	void UpdateMatrix();
	// 回転行列の生成
	void UpdateRotate();
	// 衝突判定とそれに伴う座標の更新
	void UpdateCollision();
	// アニメーションの更新
	void UpdateAnimation();

	// 解放処理
	void Release();

	std::weak_ptr<CameraBase> m_wpCamera;

protected:
	std::shared_ptr<KdModelWork>				m_spModel	= nullptr;
	std::shared_ptr<KdAnimator>				m_spAnimator = nullptr;
	Math::Vector3								m_worldPos	= Math::Vector3::Zero;
	Math::Vector3								m_worldRot	= Math::Vector3::Zero;
	Math::Vector3								m_moveVec	= Math::Vector3::Zero;

	std::vector<std::weak_ptr<KdGameObject>>	m_wpHitObjectList{};
	float										m_Gravity	= 0;

};