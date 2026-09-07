#pragma once
class Ground : public KdGameObject
{
public:

	Ground() { Init(); };
	~Ground() {};

	void DrawLit() override;

private:
	void Init() override;

	std::shared_ptr<KdModelData> m_model;
};
