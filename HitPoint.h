#pragma once

class HitPoint
{
public:
	void Initialize(int maxHp);

	void Damage(int amount);
	void Heal(int amount);

	int GetHp() const;
	int GetMaxHp() const;

	bool IsDead() const;
private:
	int m_hp = 0;
	int m_maxHp = 0;
};