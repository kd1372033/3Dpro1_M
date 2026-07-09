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
	SetPos({ -12.0f, 1.0f, 1.0f });
}

void Lift::Update()
{

}

void Lift::DrawLit()
{
	if (!m_spModel) return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel,m_mWorld);
}

