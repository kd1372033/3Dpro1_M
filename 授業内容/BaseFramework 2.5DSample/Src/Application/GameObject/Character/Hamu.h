#pragma once

class Hamu : public KdGameObject
{
public:
	Hamu();
	~Hamu()				override;

	void Init()			override;
	void Update()		override;
	void DrawLit()		override;

	void DrawSprite()	override;

private:

	void Release();

	// 授業用リソース
	std::shared_ptr<KdSquarePolygon> m_spPoly = nullptr;
};