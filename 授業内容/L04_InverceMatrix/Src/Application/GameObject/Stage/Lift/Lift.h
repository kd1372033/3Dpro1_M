#pragma once

#pragma once

class Lift : public KdGameObject
{
public:
	Lift() {}
	virtual ~Lift()	override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;

private:
	std::shared_ptr<KdModelWork> m_spModel = nullptr;

};
