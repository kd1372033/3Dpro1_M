#include "Hamu.h"

#include "../../main.h"

Hamu::Hamu()
{
}

Hamu::~Hamu()
{
	Release();
}

void Hamu::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}
}

void Hamu::Update()
{
	// 右クリックされたらマウス座標(2D)を3D座標へ変換しターゲット位置をブチ込む
	{
		std::shared_ptr<KdCamera> _spCamera = m_wpCamera.lock();

		if (_spCamera)
		{
			if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
			{
				// 手順①
				// マウス座標を取得
				POINT _mousePos;
				GetCursorPos(&_mousePos);
				ScreenToClient(Application::Instance().GetWindowHandle(), &_mousePos);

				// 手順②	
				// マウスの2D座標を3D座標へ変換する
				Math::Vector3 _rayPos = _spCamera->GetCameraMatrix().Translation();
				Math::Vector3 _rayDir = Math::Vector3::Zero;
				float _range = 2000.f;
				_spCamera->GenerateRayInfoFromClientPos(_mousePos, _rayPos, _rayDir, _range);

				// 手順③
				// 生成したRAY情報を基に実際にRAYを飛ばして当たり判定を取る！
				// 課題１：「瞬間移動」で構わないので、ハムスターをHITした位置に飛ばせ！
				// 課題２：「今いる地点」から「クリックした地点」まで等速で移動せよ！
				Math::Vector3 _endRayPos = _rayPos + (_rayDir * _range);
				KdCollider::RayInfo _rayInfo(
					KdCollider::TypeGround,
					_rayPos,					// RAYの始点
					_endRayPos);				// RAYの終点

				// HITした全ての結果がここに格納される！
				std::list<KdCollider::CollisionResult> _results;
				std::shared_ptr<KdGameObject> _obj = m_wpHitObj.lock();
				if (_obj)
				{
					_obj->Intersects(_rayInfo, &_results);
					if (_results.size())
					{
						for (KdCollider::CollisionResult result : _results)
						{
							m_TargetPos = result.m_hitPos;
						}
					}
				}
			}
		}
	}

	// キャラ制御
	{
		//float			_moveSpd = 0.1f;
		//Math::Vector3	_nowPos = m_mWorld.Translation();

		//Math::Vector3	_moveVec = Math::Vector3::Zero;
		//if (GetAsyncKeyState('W'))_moveVec.z = 1.0f;
		//if (GetAsyncKeyState('D'))_moveVec.x = 1.0f;
		//if (GetAsyncKeyState('A'))_moveVec.x = -1.0f;
		//if (GetAsyncKeyState('S'))_moveVec.z = -1.0f;

		//_moveVec = (m_TargetPos + Math::Vector3(0.0f, 0.5f, 0.0f)) - _nowPos;
		//// 正規化(あらゆる矢印の長さを「1.0」にする)
		//_moveVec.Normalize();
		//_nowPos += _moveVec * _moveSpd;

		//// キャラクターのワールド行列を求める
		//m_mWorld = Math::Matrix::CreateTranslation(m_TargetPos);

		// キャラ制御
		{
			float            _moveSpd = 0.1f;
			Math::Vector3    _nowPos = m_mWorld.Translation();

			//スタート地点からゴール地点への矢印　＝　ゴール地点　-　スタート地点
			Math::Vector3    _moveVec = m_TargetPos - _nowPos;
			//速度を残りの長さにする
			if (_moveVec.Length() < _moveSpd) _moveSpd = _moveVec.Length();
			//Lengthは処理が重い

			// 正規化(あらゆる矢印の長さを「1.0」にする)
			_moveVec.Normalize();
			_nowPos += _moveVec * _moveSpd;

			// キャラクターのワールド行列を求める
			m_mWorld = Math::Matrix::CreateTranslation(_nowPos);
		}
	}
}

void Hamu::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void Hamu::DrawSprite()
{
	std::shared_ptr<KdCamera> _spCamera = m_wpCamera.lock();

	if (_spCamera)
	{
		Math::Vector3 _2dPos = Math::Vector3::Zero;
		_spCamera->ConvertWorldToScreenDetail(GetPos(), _2dPos);
		// カメラの情報が必要
		KdShaderManager::Instance().m_spriteShader.DrawCircle(_2dPos.x, _2dPos.y, 10, &kRedColor);
	}
}

void Hamu::Release()
{
}
