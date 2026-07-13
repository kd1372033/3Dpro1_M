#include "CharacterBase.h"

CharacterBase::CharacterBase()
{
}

CharacterBase::~CharacterBase()
{
	Release();
}

// 初期化
void CharacterBase::Init()
{
}

// 更新
void CharacterBase::Update()
{
}

void CharacterBase::PostUpdate()
{
	/*
	   座標の補正などをおこなうため、
	   すべてのオブジェクトの座標が確定してから呼んでいる
	*/
	UpdateCollision();
}

// 描画
void CharacterBase::DrawLit()
{
	if (m_spPoly)
	{
		KdShaderManager::Instance().
			m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
	}
}

void CharacterBase::UpdateCollision()
{
	// 地面判定するよ
	// ----- ----- ----- ----- -----

	// ①当たり判定(レイ判定)用の情報作成
	KdCollider::RayInfo rayInfo;
	// レイの発射位置を設定
	rayInfo.m_pos = GetPos();
	// 少し高いところから飛ばす(段差の許容範囲)
	static float enableStepHigh = 0.2f;
	rayInfo.m_pos.y += enableStepHigh;

	// レイの発射方向を設定
	rayInfo.m_dir = Math::Vector3::Down;

	// レイの長さを設定
	rayInfo.m_range = m_Gravity + enableStepHigh;
	// 当たり判定をしたいタイプを設定
	rayInfo.m_type = KdCollider::TypeGround;

	// ②HIT判定対象オブジェクトに総当たり
	m_wpRiddenObject.reset();
	for (std::weak_ptr<KdGameObject> wpGameObj : m_wpHitObjectList)
	{
		std::shared_ptr<KdGameObject> spGameObj = wpGameObj.lock();
		if (spGameObj)
		{
			std::list<KdCollider::CollisionResult> retRayList;
			spGameObj->Intersects(rayInfo, &retRayList);

			// ③ 結果を使って座標を補完する
			// レイに当たったリストから一番近いオブジェクトを検出
			float maxOverLap = 0;
			Math::Vector3 hitPos = {};
			bool hit = false;
			for (auto& ret : retRayList)
			{
				// レイを遮断しオーバーした長さが
				// 一番長いものを探す
				if (maxOverLap < ret.m_overlapDistance)
				{
					maxOverLap = ret.m_overlapDistance;
					hitPos = ret.m_hitPos;
					hit = true;
				}
			}
			if (hit)
			{
				// 地面に当たっている
				SetPos(hitPos);
				m_Gravity = 0;

				// 逆行列…行列の「今の状態」を打ち消し、「単位行列」とするもの
				// 行列A * - 行列A = 単位行列

				// 乗り物に乗っている
				// IsRideableはまだfalse(ground登録時)
				// IsRideableはtrueになる(lift登録時)
				if (spGameObj->IsRideable())
				{
					// プレイヤーが何の上に乗っているか（「乗り物から見たPlayerのローカル座標」）
					Math::Matrix _mInvertRideObject;
					spGameObj->GetMatrix().Invert(_mInvertRideObject);
					// ↑リフトのワールド行列を逆行列化して_mInvertRideObjectに代入している

					// リフトを原点としたキャラクターのローカル行列 
					//			= キャラクターのワールド行列(H) * リフトの逆行列(-L)
					// リフトの原点を強制的に(0,0,0)にして、そこから見たキャラクターの座標に変える
					m_mLocalFromRideObject = m_mWorld * _mInvertRideObject;
					m_wpRiddenObject = spGameObj;
					// 乗り物の座標を保存しておく
				}
			}
		}
	}

	// その他球による衝突判定
	// ----- ----- ----- ----- -----
	// ①当たり判定(球判定)用の情報作成
	DirectX::BoundingSphere sphere;
	sphere.Center = GetPos() + Math::Vector3(0, 0.5f, 0);
	sphere.Radius = 0.5f;
	KdCollider::SphereInfo spherInfo(KdCollider::TypeBump, sphere);

	// ②HIT判定対象オブジェクトに総当たり
	for (std::weak_ptr<KdGameObject> wpGameObj : m_wpHitObjectList)
	{
		std::shared_ptr<KdGameObject> spGameObj = wpGameObj.lock();
		if (spGameObj)
		{
			std::list<KdCollider::CollisionResult> retBumpList;
			spGameObj->Intersects(spherInfo, &retBumpList);

			// ③ 結果を使って座標を補完する
			for (auto& ret : retBumpList)
			{
				Math::Vector3 newPos = GetPos() + (ret.m_hitDir * ret.m_overlapDistance);
				SetPos(newPos);
			}
		}
	}
}

// 解放
void CharacterBase::Release()
{
	m_spPoly = nullptr;
}