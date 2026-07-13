#pragma once

class Lift : public KdGameObject
{
public:
	Lift() {}
	virtual ~Lift()	override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;

	// 上書きして乗り物と自己申告させる「乗り物でーす」
	bool IsRideable() const override { return true; }

private:
	std::shared_ptr<KdModelWork> m_spModel = nullptr;

	Math::Vector3 m_StartPos = Math::Vector3::Zero;
	Math::Vector3 m_EndPos	= Math::Vector3::Zero;

	float m_Progress = 0;
	float	m_Speed	= 0;

	bool m_IsReverse = false;

};
