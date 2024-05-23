#pragma once

#include"../CharacterBase.h"

#define SPDCORREC 0.05  //スピード補正

class Player :public CharacterBase
{
public:
	Player() { Init(); }
	~Player()override{}

	void Update()override;
	void DrawLit()override;
	void Init()override;

private:

};