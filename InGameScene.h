#pragma once
#include <vector>
#include "Player.h"
#include "PlayerInput.h"
#include "Enemy.h"
#include "Stage.h"
#include "Scene.h"
#include "Camera.h"

class InGameScene :public Scene
{
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;

	bool IsInGameEnd() const override;
private:
	Stage m_stage;
	Player m_player;
	Camera m_camera;
	PlayerInput m_playerInput;

	std::vector<Enemy> m_enemyPool;       //敵をプールする
	static const int MAX_ENEMY_COUNT = 5; //ステージに出現する最大敵数
	int m_activeEnemyCount = 0;             //アクティブ状態の敵の数(今のとこデバッグ用)

	int m_spawnTimer = 0;                                            //敵が出現するインターバル用のタイマー
	static const int SPAWN_SECONDS = 5;                              //インターバル(秒)
	static const int SPAWN_TIME = GameSettings::FPS * SPAWN_SECONDS; //ゲームセッティングのフレームレートを基準にする
	static const int SPAWN_DISTANCE = 1200;                          //プレイヤーから離れた場所でスポーンする
};
