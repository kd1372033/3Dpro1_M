#pragma once

class Terrain : public KdGameObject
{
public:
	Terrain();
	~Terrain()			override;

	void Init()			override;
	void DrawLit()		override;

private:

	void Release();

	// 授業用リソース
	std::shared_ptr<KdModelData> m_spModel = nullptr;
};