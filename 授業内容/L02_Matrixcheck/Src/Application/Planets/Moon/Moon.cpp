#include "Moon.h"
#include "../Earth/Earth.h"

void Moon::Update()
{
	static int _yAng = 0;
	Math::Matrix _mRotationY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(_yAng));
	_yAng += 3.0f;
	Math::Matrix _mTrans = Math::Matrix::CreateTranslation(0.0f, 0.0f, -3.0f);

	// 行列の合成　ワールド行列 = 大きさ * 回転 * 位置
	m_mWorld = (_mRotationY * _mTrans);
}

void Moon::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_moon, m_mWorld);
}

void Moon::Init()
{
	earth = std::make_shared<Earth>();

	m_moon = std::make_shared<KdModelData>();
	m_moon->Load("Asset/Data/LessonData/Planets/moon.gltf");

	Math::Matrix m_mTrans = Math::Matrix::CreateTranslation(0, 0, -1.5f);

}
