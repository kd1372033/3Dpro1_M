#include "Water.h"

void Water::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelData>();
		m_spModel->Load("Asset/Data/LessonData/Stage/Water/Water.gltf");
	}

	SetPos({ 0.0f, 0.5f, 0.0f });
}

void Water::Update()
{
	// 基礎編　UVアニメーション
	m_UVOffset.x += 0.0005f;
	m_UVOffset.y += 0.0005f;
}

void Water::DrawTransParent()
{
	if (!m_spModel) return;
	KdShaderManager::Instance().m_StandardShader.SetUVOffset(m_UVOffset);
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

