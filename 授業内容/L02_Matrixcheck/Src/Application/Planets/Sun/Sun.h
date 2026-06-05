#pragma once
#include "../../../Framework/GameObject/KdGameObject.h"

class Sun :public KdGameObject
{
public:
	Sun(){}
	~Sun(){}

	void Update() override;
	void DrawLit() override;
	void Init() override;

private:
	std::shared_ptr<KdModelData> m_sun = nullptr;

};