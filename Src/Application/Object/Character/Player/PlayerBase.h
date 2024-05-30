#pragma once

#include"../CharacterBase.h"

class PlayerBase :public CharacterBase
{
public:
	PlayerBase() { Init(); }
	~PlayerBase()override{}

	virtual void Update()override = 0;
	virtual void Draw()override = 0;
	virtual void Init()override = 0;

protected:

};