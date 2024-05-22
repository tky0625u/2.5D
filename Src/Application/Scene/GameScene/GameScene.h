#pragma once

#include"../BaseScene/BaseScene.h"

class GameScene : public BaseScene
{
public :

	GameScene() { Init(); }
	~GameScene() {}

private:

	void Event() override;
	void Init() override;

	//カメラ================================
	float         m_angleX;        //角度
	float         m_ViewingAngle;  //視野角
	Math::Vector3 m_pos;           //座標
	//======================================
};
