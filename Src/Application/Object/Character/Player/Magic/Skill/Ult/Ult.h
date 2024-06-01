#pragma once

#define SIZEMAX   3.0f   //最大サイズ
#define SIZEUP    0.01f  //サイズ増加量
#define SPEED     1.0f   //速さ
#define ALIVETIME 5*60   //生存時間
#define DEFAULTPOS 4     //プレイヤーの少し前

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

	void SetPos(Math::Vector3 a_pos);
	void SetAngle(float a_angle) { m_angle = a_angle; }

	const float GetSize()const { return m_size; }

private:
	std::shared_ptr<KdModelData> m_model;
	
	Math::Vector3                m_pos;
	int                          m_AliveTime;  //生存時間
	float                        m_size;
	float                        m_angle;
};