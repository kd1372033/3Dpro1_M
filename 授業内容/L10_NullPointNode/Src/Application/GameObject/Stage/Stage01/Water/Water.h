#pragma once

class Water : public KdGameObject
{
public:
	Water() {}
	virtual ~Water()	override {}

	void Init()				override;
	void Update()			override;
	void DrawTranceParent() ;

private:
	//モデルデータ　モデルワーク
	std::shared_ptr<KdModelData> m_spModel = nullptr;
	Math::Vector2 m_UVOffset = Math::Vector2::Zero;

};