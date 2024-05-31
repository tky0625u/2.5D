#pragma once


class Ult:public KdGameObject
{
public:
	Ult() { Init(); }
	~Ult()override{}

	void Update()override;
	void Draw();
	void DrawBright()override;
	void Init();

	void SetPos(Math::Vector3 a_pos);

private:
	std::shared_ptr<KdModelData> m_model;
	
	Math::Vector3                m_pos;
	float                        m_size;
};