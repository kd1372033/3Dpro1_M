#include "Sun.h"

void Sun::Update()
{
	static int _yAng = 0;
	Math::Matrix _mRotationY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(_yAng));
	_yAng += 3.0f;

	Math::Vector3 Pos = { 0.0f, 0.0f, 0.0f };
	Math::Matrix transMat = Math::Matrix::CreateTranslation(Pos);
	m_mWorld = (_mRotationY * transMat);
}

void Sun::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_sun, m_mWorld);
}

void Sun::Init()
{
	m_sun = std::make_shared<KdModelData>();
	m_sun->Load("Asset/Data/LessonData/Planets/sun.gltf");
}
