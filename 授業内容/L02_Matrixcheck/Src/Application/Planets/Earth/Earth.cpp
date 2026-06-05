#include "Earth.h"
#include "../Sun/Sun.h"

void Earth::Update()
{
	Math::Matrix _mScale = Math::Matrix::CreateScale(1.0f);
	// 自転
	static int _yAng = 0;
	Math::Matrix _mRotationY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(_yAng));
	_yAng += 1.0f;
	Math::Matrix _mTrans = Math::Matrix::CreateTranslation(5.0f, 0.0f, 0.0f);

	// 行列の合成　ワールド行列 = 大きさ * 回転 * 位置
	m_mWorld = (_mRotationY * _mTrans);
}

void Earth::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_earth, m_mWorld);

}

void Earth::Init()
{
	m_earth = std::make_shared<KdModelData>();
	m_earth->Load("Asset/Data/LessonData/Planets/earth.gltf");
}
