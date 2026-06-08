#pragma once

class BaseScene
{
public :

	BaseScene()			 {}
	virtual ~BaseScene() {}
	
	virtual void Init();

	void PreUpdate();
	void Update();
	void PostUpdate();

	void PreDraw();
	void Draw();
	void DrawSprite();
	void DrawDebug();

	// オブジェクトリストを取得
	const std::list<std::shared_ptr<KdGameObject>>& GetObjList()
	{
		return m_objList;
	}
	
	// オブジェクトリストに追加
	void AddObject(const std::shared_ptr<KdGameObject>& _obj)
	{
		m_objList.push_back(_obj);
	}

protected :

	// 継承先シーンで必要ならオーバーライドする
	virtual void Event();

	// 解放処理の実装を強制させる書き方
	// 解放処理は丁寧に行う事！
	virtual void Release() = 0;
	
	std::unique_ptr<KdCamera> m_camera = nullptr;

	// 全オブジェクトのアドレスをリストで管理
	std::list<std::shared_ptr<KdGameObject>> m_objList;
};
