#pragma once
#include "../../../Framework/GameObject/KdGameObject.h"

class Earth;

class Moon :public KdGameObject
{
public:
	Moon(){}
	~Moon(){}

	void Update() override;
	void DrawLit() override;
	void Init() override;


private:
	std::shared_ptr<KdModelData> m_moon = nullptr;
	
	std::shared_ptr<Earth> earth = nullptr;
};