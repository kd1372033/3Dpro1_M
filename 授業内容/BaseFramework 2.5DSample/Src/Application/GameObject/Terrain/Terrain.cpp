#include "Terrain.h"

Terrain::Terrain()
{
}

Terrain::~Terrain()
{
	Release();
}

void Terrain::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelData>();
		m_spModel->Load("Asset/Data/LessonData/Terrain/Terrain.gltf");
	}

	// 初期値を設定
	SetPos({0 , 0 , 0});
}

void Terrain::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel , m_mWorld);
}

void Terrain::Release()
{
}
