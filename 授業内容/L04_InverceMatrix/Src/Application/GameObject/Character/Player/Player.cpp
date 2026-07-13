#include "Player.h"

#include "../../Camera/CameraBase.h"

void Player::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}

	SetPos ({ -12.0f, 2.5f, 1.5f });
}

void Player::Update()
{

	std::shared_ptr<KdGameObject>_spGameObj = m_wpRiddenObject.lock();
	if (_spGameObj)
	{
		// プレイヤーから見た相対座標＊リフトの行列
		// リフトを親として、リフトから見たプレイヤーの位置
		// 乗っている乗り物の上にいれる
		m_mWorld = m_mLocalFromRideObject * _spGameObj->GetMatrix();
	}

	// キャラクターには常に重力がかかる
	m_Gravity += 0.01f;
	m_mWorld._42 -= m_Gravity;

	// 移動処理復活
	float			_moveSpd = 0.05f;
	Math::Vector3	_nowPos = GetPos();

	Math::Vector3	_moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState('D')) { _moveVec.x = 1.0f; }
	if (GetAsyncKeyState('A')) { _moveVec.x = -1.0f; }
	if (GetAsyncKeyState('W')) { _moveVec.z = 1.0f; }
	if (GetAsyncKeyState('S')) { _moveVec.z = -1.0f; }

	_moveVec.Normalize();
	_moveVec *= _moveSpd;
	_nowPos += _moveVec;

	// キャラクターのワールド行列を創る処理
	m_mWorld = Math::Matrix::CreateTranslation(_nowPos);
}
