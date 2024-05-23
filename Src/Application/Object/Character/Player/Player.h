#pragma once

#include"../CharacterBase.h"

//アニメーション===================
#define UP    3  //上
#define LEFT  1  //左
#define RIGHT 2  //右
#define DOWN  0  //下
//=================================

class Player :public CharacterBase
{
public:
	Player() { Init(); }
	~Player()override{}

	void Update()override;
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;
	void Init()override;

private:
	float size;
};