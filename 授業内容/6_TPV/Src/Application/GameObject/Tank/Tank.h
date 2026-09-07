#pragma once

class TPSCamera;

class Tank : public KdGameObject
{
public:

	Tank() { Init(); };
	~Tank() {};

	void Update()  override;
	void DrawLit() override;

	void SetCamera(const std::shared_ptr<TPSCamera>& camera)
	{
		m_camera = camera;
	}

private:
	void Init() override;


	std::shared_ptr<KdModelData> m_model;

	float m_angle = 0;
	Math::Vector3 m_pos;

	// カメラのポインタを用意
	std::weak_ptr<TPSCamera> m_camera;
};
