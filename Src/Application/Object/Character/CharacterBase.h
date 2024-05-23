#pragma once

//ステータス==============================
struct Status
{
	int Hp;   //体力
	int Atk;  //攻撃力
	int Def;  //防御力
	int Spd;  //素早さ
};
//========================================

class CharacterBase :public KdGameObject
{
public:
	 CharacterBase() { Init(); }
	 ~CharacterBase()override{}

	 virtual void Update()override;
	 virtual void DrawLit()override;
	virtual void Init() override;

protected:
	bool m_bFlg;
	std::shared_ptr<KdSquarePolygon> m_polygon;
	Status status;
	Math::Vector3 m_pos;
};