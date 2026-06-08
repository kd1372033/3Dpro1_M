#pragma once
#include"../PlanetBase.h"

class Sky : public PlanetBase
{
public:
	Sky();
	~Sky()				override;

	void Init()			override;
	void Update()		override;
	void DrawLit() override;

	void DrawUnLit() override;
private:

	void Release();
};