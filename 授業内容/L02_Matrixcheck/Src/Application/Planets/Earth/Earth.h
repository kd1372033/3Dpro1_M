#pragma once

#include "../../../Framework/GameObject/KdGameObject.h"

class Sun;

class Earth :public KdGameObject
{
public:
	Earth(){}
	~Earth(){}

	void Update() override;
	void DrawLit() override;
	void Init() override;


private:
	std::shared_ptr<KdModelData> m_earth = nullptr;
	std::shared_ptr<Sun> sun = nullptr;
};