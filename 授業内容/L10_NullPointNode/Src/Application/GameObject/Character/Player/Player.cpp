#include "Player.h"
#include "../../Camera/CameraBase.h"

void Player::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Data/LessonData/Character/Robot/Robot.gltf");
		m_spAnimator = std::make_shared<KdAnimator>();
		m_spAnimator->SetAnimation(m_spModel->GetAnimation("Walk"));

		//m_spModel = std::make_shared<KdModelWork>();
		//m_spModel->SetModelData("Asset/Data/LessonData/Character/SkinMeshMan/SkinMeshMan.gltf");
		//m_spAnimator = std::make_shared<KdAnimator>();
		//m_spAnimator->SetAnimation(m_spModel->GetAnimation("Walk"));
	}

	SetPos({ 0.0f, 0.0f, 0.0f });
}

void Player::Update()
{
	// キャラクターには常に重力がかかる
	m_Gravity += 0.01f;
	m_mWorld._42 -= m_Gravity;

	// 移動処理復活
	float _moveSpd = 0.05f;
	m_worldPos = GetPos();

	m_moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState('D')) { m_moveVec.x = 1.0f; }
	if (GetAsyncKeyState('A')) { m_moveVec.x = -1.0f; }
	if (GetAsyncKeyState('W')) { m_moveVec.z = 1.0f; }
	if (GetAsyncKeyState('S')) { m_moveVec.z = -1.0f; }

	const std::shared_ptr<CameraBase> _spCamera = GetCamera().lock();
	if (_spCamera)
	{
		m_moveVec = m_moveVec.TransformNormal(m_moveVec, _spCamera->GetRotationYMatrix());
	}

	m_moveVec.Normalize();
	m_moveVec *= _moveSpd;
	m_worldPos += m_moveVec;

	// 親クラスのUpdate()を呼び出し
	// ↓中でやってることは行列の更新処理
	CharacterBase::Update();
}

void Player::DrawLit()
{
	//1体目は普通に描画して２体目はおっきく表示して内部を消している
		//だからアウトラインみたいに見える
	if (m_spModel)
	{
		//↓これを書いていないと真っ黒ロボットが表示される
		CharacterBase::DrawLit();

		KdShaderManager::Instance().
			m_StandardShader.SetEnableOutLineDraw(true);

		//↓これを書いていないとロボットはちゃんと表示されるが
		// なぜか川が真っ黒になる
		KdShaderManager::Instance().
			m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
	//m_spModel　今はロボットのモデルデータ
}
