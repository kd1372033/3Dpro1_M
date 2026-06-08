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

	void SetCamera(std::shared_ptr<KdCamera> camera)
	{
		m_wpCamera = camera;
	}

private:

	void Release();

	// 授業用リソース
	std::shared_ptr<KdSquarePolygon> m_spPoly = nullptr;

	// 座標変換に必要な為のカメラの情報
	std::weak_ptr<KdCamera> m_wpCamera;

};