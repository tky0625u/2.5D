#pragma once

//必殺技=========================================
#define SIZEMAX   3.0f   //最大サイズ
#define SIZEUP    0.01f  //サイズ増加量
#define SPEED     1.0f   //速さ
#define DEFAULTPOS 4     //プレイヤーの少し前
//===============================================

//魔法陣=========================================
#define CicleSizeUP   0.1f  //魔法陣増加量
#define CicleSizeDown 0.2f  //魔法陣減少量
//===============================================

class Ult:public KdGameObject
{
public:
	Ult() { Init(); }
	~Ult()override{}

	void Update()override;
	void Draw();
	void DrawLit()override;
	void DrawBright()override;
	void Init();

	void SetPos(Math::Vector3 a_pos);  //必殺技座標
	void SetCirclePos(Math::Vector3 a_pos) { m_CirclePos = { a_pos.x,a_pos.y + 0.1f,a_pos.z }; }  //魔法陣座標
	void SetAngle(float a_angle) { m_angle = a_angle; }
	void SetAtk(int a_Atk){}

	const float GetSize()const { return m_size; }
	const int   GetDamage()const { return m_Atk * m_PlayerAtk; }

private:
	//必殺技===================================================================
	std::shared_ptr<KdModelData> m_model;
	Math::Vector3                m_pos;
	int                          m_AliveTime;  //生存時間
	int                          m_Atk;        //攻撃力
	int                          m_PlayerAtk;  //プレイヤー攻撃力
	float                        m_size;
	float                        m_angle;
	//=========================================================================
	
	//魔法陣===================================================================
	std::shared_ptr<KdSquarePolygon> m_polygon;
	Math::Vector3                    m_CirclePos;
	Math::Matrix                     m_CircleMat;
	float                            m_CirecleSize;
	int                              m_CirecleAngle;
	//=========================================================================
};