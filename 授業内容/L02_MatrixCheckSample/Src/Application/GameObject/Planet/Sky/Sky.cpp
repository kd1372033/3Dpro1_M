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
	/*	何気に使っている1はどれぐらいの単位
		1 = 1mの方が好ましい(というかその方がいい)
		Blenderは1 = 1mであるため、
		Blenderで作成したモデルをそのまま読み込むと、
		1 = 1mの単位で表示される!
		175cmのプレイヤーは1.75の高さ
		50mの距離を7秒で移動する場合の１fpsあたりの移動速度は0.11m/fps
	*/

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
