#include "Hamu.h"

Hamu::Hamu()
{
}

Hamu::~Hamu()
{
	Release();
}

void Hamu::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}
}

void Hamu::Update()
{
	// キャラ制御
	{
		float			_moveSpd = 0.1f;
		Math::Vector3	_nowPos = m_mWorld.Translation();

		Math::Vector3	_moveVec = Math::Vector3::Zero;
		if (GetAsyncKeyState('W'))_moveVec.z = 1.0f;
		if (GetAsyncKeyState('D'))_moveVec.x = 1.0f;
		if (GetAsyncKeyState('A'))_moveVec.x = -1.0f;
		if (GetAsyncKeyState('S'))_moveVec.z = -1.0f;
		// 正規化(あらゆる矢印の長さを「1.0」にする)
		_moveVec.Normalize();
		_nowPos += _moveVec * _moveSpd;

		// キャラクターのワールド行列を求める
		m_mWorld = Math::Matrix::CreateTranslation(_nowPos);
	}
}

void Hamu::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void Hamu::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawCircle(GetPos().x, GetPos().z, 10, &kRedColor);
}

void Hamu::Release()
{
}
