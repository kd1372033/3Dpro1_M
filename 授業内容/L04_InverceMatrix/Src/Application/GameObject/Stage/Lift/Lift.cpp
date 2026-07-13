#include "Lift.h"

void Lift::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Data/LessonData/Stage/Lift/Lift.gltf");

		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape("Lift", m_spModel, KdCollider::TypeGround);
	}

	// 開始地点と終着地点の設定
	m_StartPos = { -12.0f, 1.0f, 1.0f };
	m_EndPos = { -6.0f, 1.0f, 1.0f };

	// ２秒で終着地点へ移動するスピード
	m_Speed = 1.0f / (60.f * 2);
}

void Lift::Update()
{
	// リフトの上下運動
	// ①進捗度の制御
	m_Progress += m_Speed * (m_IsReverse * -2 + 1);
	if (m_Progress >= 1.2f)
	{
		m_IsReverse = true;
	}
	else if (m_Progress < -0.2f)
	{
		m_IsReverse = false;
	}

	float _progress = std::clamp(m_Progress, 0.0f, 1.0f);
	Math::Vector3 towardEndVec = m_EndPos - m_StartPos;
	
	// ②進捗度を用いて座標を決定する
	Math::Matrix _trans = Math::Matrix::CreateTranslation(
		m_StartPos + towardEndVec * EaseInOutSine(_progress)
	);
	// EaseInOutSine…sin cos等のカーブで加減速をしている
	m_mWorld = _trans;
}

void Lift::DrawLit()
{
	if (!m_spModel) return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel,m_mWorld);
}

