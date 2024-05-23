#pragma once

#include"../CharacterBase.h"

//アニメーション===================
#define UP    3  //上
#define LEFT  1  //左
#define RIGHT 2  //右
#define DOWN  0  //下
//=================================
#define JUMPPOW 1.0f  //ジャンプ力

class Player :public CharacterBase
{
public:
	Player() { Init(); }
	~Player()override{}

	void Update()override;
	void Draw()override;
	void Init()override;

private:
	bool  m_jumpFlg;
	float m_jumpMove;
};