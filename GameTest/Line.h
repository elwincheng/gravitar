#pragma once
class Line
{
public:
	Line(float sx, float sy, float ex, float ey, float r, float g, float b, float originX, float originY);
	void Draw();
	void Update(float dt);

	void GetPoints(float& sx, float& sy, float& ex, float& ey) { sx = m_sx; sy = m_sy; ex = m_ex; ey = m_ey; }

	void SetPos(float x, float y) { m_originX = x; m_originY = y; }

	void Rotate(float thetaDot);

	bool Intersects(Line line);

private:
	float m_sx = 0.0F;
	float m_sy = 0.0F;
	float m_ex = 0.0F;
	float m_ey = 0.0F;
	float m_r;
	float m_g;
	float m_b;
	float m_originX = 0.0f;
	float m_originY = 0.0f;
	float m_animTime = 0.0F;
};

