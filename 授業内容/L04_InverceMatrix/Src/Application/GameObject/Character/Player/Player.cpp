#include "Player.h"

void Player::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}

	SetPos({ -12.0f, 2.5f, 1.5f });
}

void Player::Update()
{
	// キャラクターには常に重力がかかる
	m_Gravity += 0.01f;
	m_mWorld._42 -= m_Gravity;
}
