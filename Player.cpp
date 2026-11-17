#include <DxLib.h>
#include <cmath>
#include <algorithm>
#include "Player.h"
#include "Gun.h"
#include "PlayerInput.h"
#include "Camera.h"
#include "Neon.h"
#include "DebugDisplay.h"
#include "Score.h"

void Player::InitializePlayer()
{
	//初期化(ここで各数値を調整)
	m_playerPosX = 5000;
	m_playerPosY = 2400;
	m_playerW = static_cast<int>(DRAW_SIZE * 2);
	m_playerH = static_cast<int>(DRAW_SIZE * 2);

	m_playerState = PlayerState::Alive;

	m_hitPoint.Initialize(MAX_HP);
	m_invincibleTimer = 0;

	m_gun.InitializeGun(BULLET_COUNT);
	m_playerObj = { { m_playerPosX,m_playerPosY },m_playerW,m_playerH};
};

Player::PlayerState Player::GetPlayerState() const
{
	return m_playerState;
}

void Player::SetPlayerState(PlayerState state)
{
	m_playerState = state;
};

Vector2 Player::GetPosition() const 
{
	Vector2 position =
	{ static_cast<float>(m_playerObj.position.x),static_cast<float>(m_playerObj.position.y) };

	return position;
}

float Player::GetRadius() const 
{
	return DRAW_SIZE;
}

void Player::DrawPlayer(Camera camera)
{
	if (DebugDisplay::IsVisible())
	{
		DrawFormatString(20, 60, GetColor(255, 255, 0), L"PlayerPos X = %.0f Y = %.0f", m_playerObj.position.x, m_playerObj.position.y);
		DrawFormatString(20, 140, GetColor(255, 255, 0), L"PlayerState = %s", GetStateName());
		DrawFormatString(20, 180, GetColor(255, 255, 0), L"HP = %d", m_hitPoint.GetHp());
	}

	if (m_playerState == PlayerState::Dead) return;

	m_gun.DrawBullet(camera,Neon::MAGENTA);
	m_gun.DrawSight();

	//光る三角形で描く(先端がマウスの方向を向く)
	float centerX = static_cast<float>(m_playerObj.position.x - camera.m_x);
	float centerY = static_cast<float>(m_playerObj.position.y - camera.m_y);

	float tipX = centerX + cosf(m_angle) * DRAW_SIZE;
	float tipY = centerY + sinf(m_angle) * DRAW_SIZE;
	float leftX = centerX + cosf(m_angle - BACK_ANGLE) * DRAW_SIZE * 0.8f;
	float leftY = centerY + sinf(m_angle - BACK_ANGLE) * DRAW_SIZE * 0.8f;
	float rightX = centerX + cosf(m_angle + BACK_ANGLE) * DRAW_SIZE * 0.8f;
	float rightY = centerY + sinf(m_angle + BACK_ANGLE) * DRAW_SIZE * 0.8f;

	//プレイヤーの状態による表示切替
	switch (m_playerState)
	{
	case PlayerState::Alive:
	{
		Neon::DrawGlowTriangle(tipX, tipY, leftX, leftY, rightX, rightY, Neon::CYAN, 3.0f);
		Neon::DrawGlowCircle(centerX, centerY, 4.0f, Neon::CYAN, 2.0f);
	}
	break;

	case PlayerState::Damage:
	{
		if (m_invincibleTimer / 5 % 2 == 0)
		{
			Neon::DrawGlowTriangle(tipX, tipY, leftX, leftY, rightX, rightY, Neon::RED, 3.0f);
			Neon::DrawGlowCircle(centerX, centerY, 4.0f, Neon::RED, 2.0f);
		}
		else
		{
			Neon::DrawGlowTriangle(tipX, tipY, leftX, leftY, rightX, rightY, Neon::CYAN, 3.0f);
			Neon::DrawGlowCircle(centerX, centerY, 4.0f, Neon::CYAN, 2.0f);
		}
	}
	break;

	}
}

void Player::UpdatePlayer(int stageWidth,int stageHeight ,Camera camera) 
{
	if (m_playerState == PlayerState::Dead) return;

	Score::AddSurviveFrame();

	UpdateAim(camera);
	PlayerControl(stageWidth, stageHeight);
	m_gun.UpdateBullet(stageWidth, stageHeight);

	//プレイヤーの状態管理
	switch (m_playerState)
	{
	case PlayerState::Alive:
	{
	}
	break;

	case PlayerState::Damage:
	{
		m_invincibleTimer -= 1;

		if (m_invincibleTimer <= 0)
			m_playerState = PlayerState::Alive;
	}
	break;

	}
}

bool Player::CheckBulletHit(Vector2 targetPos, float targetRadius) 
{
	return m_gun.CheckHit(targetPos, targetRadius);
}

void Player::PlayerControl(int stageWidth, int stageHeight)
{
	if (m_playerState == PlayerState::Dead) return;

	//左クリックで発射
	if (PlayerInput::GetMouseClick(PlayerInput::Input::LeftClick))
		m_gun.Shoot(m_aimDirection, m_playerObj.position);

	if (PlayerInput::GetInput(PlayerInput::Input::Left))  m_playerObj.position.x -= MOVE_SPEED;
	if (PlayerInput::GetInput(PlayerInput::Input::Right)) m_playerObj.position.x += MOVE_SPEED;
	if (PlayerInput::GetInput(PlayerInput::Input::Up))    m_playerObj.position.y -= MOVE_SPEED;
	if (PlayerInput::GetInput(PlayerInput::Input::Down))  m_playerObj.position.y += MOVE_SPEED;

	// ステージの外に出ないように範囲内に収める
	m_playerObj.position.x = std::clamp(m_playerObj.position.x, 0.0f, static_cast<float>(stageWidth - m_playerObj.width));
	m_playerObj.position.y = std::clamp(m_playerObj.position.y, 0.0f, static_cast<float>(stageHeight - m_playerObj.height));
}

void Player::UpdateAim(Camera camera) 
{
	Vector2 mouse = PlayerInput::GetMousePos();

	//マウスの座標をワールド座標に変換
	float worldMouseX = mouse.x + camera.m_x;
	float worldMouseY = mouse.y + camera.m_y;

	//プレイヤーからマウスへの方向ベクトルを計算
	//  (プレイヤーの向き計算に使用、弾の発射方向計算にも使うためgunにもそのまま使用)
	m_aimDirection.x =
		worldMouseX -
		(m_playerObj.position.x);

	m_aimDirection.y =
		worldMouseY -
		(m_playerObj.position.y);

	//方向ベクトルから角度を計算
	m_angle = atan2f(m_aimDirection.y, m_aimDirection.x);
}

void Player::TakeDamage(int amount) 
{
	if (m_playerState == PlayerState::Damage
		|| m_playerState == PlayerState::Dead)
		return;

	m_hitPoint.Damage(amount);

	if (m_hitPoint.IsDead())
	{
		m_playerState = PlayerState::Dead;
	}
	else
	{
		m_playerState = PlayerState::Damage;
		m_invincibleTimer = INVINCIBLE_TIME;
	}
}

int Player::GetMoveSpeed()
{
	return MOVE_SPEED;
}

const TCHAR* Player::GetStateName() const
{
	switch (m_playerState)
	{
	case PlayerState::Alive:  return L"Alive";
	case PlayerState::Damage: return L"Damage";
	case PlayerState::Dead:   return L"Dead";
	}
	return L"Unknown";
}