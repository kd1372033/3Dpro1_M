#include "Sky.h"

Sky::Sky()
{
}

Sky::~Sky()
{
	Release();
}

void Sky::Init()
{
	// 親クラスの同処理を呼び出せるよ！
	PlanetBase::Init();

	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelData>();
		m_spModel->Load("Asset/Models/Planets/Sky/Sky.gltf");
	}
}

void Sky::Update()
{
	m_mRotation *=
		Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(2.0f));

	m_mWorld =
		m_mRotation * Math::Matrix::CreateTranslation(0, 0, 8);
}

void Sky::DrawLit()
{}

void Sky::DrawUnLit()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().
			m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
}

void Sky::Release()
{
}
