#pragma once
class Scene
{
public:
	virtual ~Scene() = default;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual bool IsInGameEnd() const { return false; } //名前の通りInGameでしか使わない
private:

};