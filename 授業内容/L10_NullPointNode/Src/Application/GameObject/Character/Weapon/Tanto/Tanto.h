#pragma once

class Tanto : public KdGameObject
{
public:
	Tanto() {}
	~Tanto()			override {}

	void Init()			override;
	void Update()		override;
	void DrawLit()		override;
	void GenerateDepthMapFromLight()		override;

	void SetOwner(const std::shared_ptr<KdGameObject>& owner)
	{
		m_wpOwner = owner;
	}
private:

	std::shared_ptr<KdModelData>	m_spModel = nullptr;
	
	//装備者
	std::weak_ptr< KdGameObject>	m_wpOwner;

};