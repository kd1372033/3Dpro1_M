#include "CCTVCamera.h"
#include "../../Character/Player/Player.h"

void CCTVCamera::Init()
{
	CameraBase::Init();

	// カメラのローカル相対位置（注視点から後ろに10、上に6離す）
	m_mLocalPos = Math::Matrix::CreateTranslation(0.0f, 6.0f, -10.0f);

	m_targetFollowPos = Math::Vector3::Zero;
	m_isInitialized = false;
}

void CCTVCamera::PostUpdate()
{
	// ターゲット（自機）の取得
	const std::shared_ptr<const KdGameObject> _spTarget = m_wpTarget.lock();
	if (!_spTarget) return;

	Math::Vector3 playerPos = _spTarget->GetPos();

	// -------------------------------------------------------------
	// 【初回フレーム同期】自機の位置に追従座標を合わせる
	// -------------------------------------------------------------
	if (!m_isInitialized)
	{
		m_targetFollowPos = playerPos;
		m_isInitialized = true;
	}

	// -------------------------------------------------------------
	// 1. 3D空間上でのデッドゾーン（追従枠）の計算
	// -------------------------------------------------------------
	// 自機が注視点（m_targetFollowPos）からこの距離（limit）以上離れたら、
	// 注視点が引っ張られて動くようにします。
	const float limitX = 5.5f; // 左右の許容範囲（小さいほどカメラがすぐ動く）
	const float limitY = 3.0f; // 上下の許容範囲
	const float limitZ = 7.0f; // 【追加】前後の許容範囲（斜め移動や奥への移動用）

	// 現在の注視点から見た、自機の相対位置
	Math::Vector3 relativePos = playerPos - m_targetFollowPos;

	// --- 左右（X軸）のハミ出しをチェックし、注視点をずらす ---
	if (relativePos.x > limitX)
	{
		m_targetFollowPos.x += (relativePos.x - limitX);
	}
	else if (relativePos.x < -limitX)
	{
		m_targetFollowPos.x += (relativePos.x + limitX);
	}

	// --- 上下（Y軸）のハミ出しをチェックし、注視点をずらす ---
	// ※ジャンプや落下などの上下動に対応します
	if (relativePos.y > limitY)
	{
		m_targetFollowPos.y += (relativePos.y - limitY);
	}
	else if (relativePos.y < -limitY)
	{
		m_targetFollowPos.y += (relativePos.y + limitY);
	}

	// --- 前後（Z軸）のハミ出しをチェックし、注視点をずらす ---
	// ※以前は `m_targetFollowPos.z = playerPos.z;` と直接同期していましたが、
	//  これだと「前後だけはデッドゾーンを無視して即座についていく」状態になり、
	//  斜めカメラの構造上、上下方向の遊び（limitY）の挙動を邪魔してしまうことがあります。
	//  前後（Z軸）も同様にデッドゾーンで制御することで、上下左右すべてのスクロールが滑らかに連動します。
	if (relativePos.z > limitZ)
	{
		m_targetFollowPos.z += (relativePos.z - limitZ);
	}
	else if (relativePos.z < -limitZ)
	{
		m_targetFollowPos.z += (relativePos.z + limitZ);
	}

	// -------------------------------------------------------------
	// 2. 元々完全に動いていた「行列の掛け算方式」でカメラのワールド行列を作成
	// -------------------------------------------------------------
	// 45度の下向き回転
	Math::Matrix _rot = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));

	// 補正された「注視目標点」の平行移動行列を作る
	Math::Matrix targetTrans = Math::Matrix::CreateTranslation(m_targetFollowPos);

	// 【重要】元々動いていたコードと全く同じ順序で掛け合わせる
	// これにより、バグる原因になっていた LookAt や Invert() を完全に排除します
	m_mWorld = _rot * m_mLocalPos * targetTrans;

	// 3. 親クラスが持つ KdCamera オブジェクトに行列を書き戻す
	if (m_spCamera)
	{
		m_spCamera->SetCameraMatrix(m_mWorld);
	}
}