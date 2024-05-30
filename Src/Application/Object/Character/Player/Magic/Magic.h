#pragma once

#include"../PlayerBase.h"

class Magic :public PlayerBase
{
public:
	Magic() { Init(); }
	~Magic()override{}

	void Update()override;
	void Draw()override;
	void Init()override;

private:

};