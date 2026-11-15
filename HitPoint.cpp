#include "HitPoint.h"
#include <algorithm>

void HitPoint::Initialize(int maxHp) 
{
	m_hp = maxHp;
	m_maxHp = maxHp;
}

void HitPoint::Damage(int amount) 
{
	m_hp = std::max(m_hp - amount, 0);
}

void HitPoint::Heal(int amount)
{
	m_hp = std::min(m_hp + amount, m_maxHp);
}

int HitPoint::GetHp() const 
{
	return m_hp;
}

int HitPoint::GetMaxHp() const 
{
	return m_maxHp;
}

bool HitPoint::IsDead() const
{
	return m_hp <= 0;
}