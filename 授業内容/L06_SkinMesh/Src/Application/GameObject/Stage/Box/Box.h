#pragma once

class Box : public KdGameObject
{
public:
	Box() {}
	virtual ~Box()	override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;
	void GenerateDepthMapFromLight()	override;

private:
	// アニメーションの更新
	void UpdateAnimation();
	std::shared_ptr<KdModelWork> m_spModel = nullptr;
	std::shared_ptr<KdAnimator>				m_spAnimator = nullptr;


};
