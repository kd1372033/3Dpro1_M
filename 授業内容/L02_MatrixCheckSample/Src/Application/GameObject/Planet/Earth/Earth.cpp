#include "Earth.h"

Earth::Earth()
{
}

Earth::~Earth()
{
	Release();
}

void Earth::Init()
{
	PlanetBase::Init();

	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelData>();
		m_spModel->Load("Asset/Planets/earth.gltf");

		// 原点(回転させたい中心点)からどれだけ離れた位置にいるか
		m_mTrans = Math::Matrix::CreateTranslation(0, 0, -4.0f);
	}
}

void Earth::Update()
{
	Math::Matrix parentTrans = Math::Matrix::Identity;
	const std::shared_ptr<PlanetBase> spParent = m_wpParent.lock();
	if (spParent)	// 親惑星(太陽)を持っているなら親の座標を取得する
	{
		parentTrans =
			Math::Matrix::CreateTranslation(spParent->GetPos());
		// 欲しいのは親の行列ではなくて親の座標
	}

	// 自転
	m_mRotation *=
		Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(2.0f));

	// 公転(移動してから回転)T*R	原点の座標を保持しながら
	m_mTrans *=
		Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(0.5f));

	// 行列の合成（最後に親の行列を合成する！） = 行列の親子関係
	m_mWorld = (m_mRotation * m_mTrans) * parentTrans;
	//										↑親惑星がいなかった場合は0になるので行の短縮になる
}

void Earth::Release()
{
}
