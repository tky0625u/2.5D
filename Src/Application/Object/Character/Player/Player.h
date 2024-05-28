#pragma once

#include"../CharacterBase.h"

class Player :public CharacterBase
{
public:
	Player() { Init(); }
	~Player()override{}

	void Update()override;
	void Draw()override;
	void Init()override;

	const float GetAngle() const { return m_angle; }

private:
};