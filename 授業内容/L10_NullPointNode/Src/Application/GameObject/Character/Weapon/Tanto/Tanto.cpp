#include "Tanto.h"
#include "../../CharacterBase.h"

void Tanto::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelData>();
		m_spModel->Load("Asset/Data/LessonData/Weapon/Tanto/Tanto.gltf");

	}
}

void Tanto::Update()
{
	//①誰（何）にアタッチ（装備）されているか？
	//欲しい時に先にexpiredする意味ない
	//✖ if(!m_wpOwner.expired())
	//欲しいものを取ってくる時はロックだけで充分！
	std::shared_ptr<KdGameObject> _spOwner = m_wpOwner.lock();
	if (_spOwner)
	{
		// ②それがキャラクターかどうか？
		std::shared_ptr<CharacterBase> _spCharacter =
			//キャスト
			std::static_pointer_cast<CharacterBase>(_spOwner);

		if (_spCharacter)
		{
			// ③アタッチ(装備)させたい「位置」を取得する
			//FindNodeを呼び出すにはKdModelWorkが必要
			const KdModelWork::Node* _pNode =
				_spCharacter->GetModel()->FindNode("AttachPoint.001");
			//										↑ここを変えるとその位置に短刀が表示される
			if (_pNode)
			{
				// ④取得したNode位置(回転情報も含む)に自身の行列を更新
				m_mWorld =
					_pNode->m_worldTransform * _spOwner->GetMatrix();
				//↓これだけだと短刀がストーカーしてくれない
				//m_mWorld =
				//	_pNode->m_worldTransform;
			}
		}
	}
}

void Tanto::DrawLit()
{
	if (!m_spModel)return;
	{
		KdShaderManager::Instance().
			m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
	
}

void Tanto::GenerateDepthMapFromLight()
{
	if (!m_spModel)return;
	{
		KdShaderManager::Instance().
			m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
}
