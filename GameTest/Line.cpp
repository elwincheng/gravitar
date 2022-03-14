#include "stdafx.h"
#include "Line.h"
#include "App/app.h"
#include <math.h>

Line::Line(float sx, float sy, float ex, float ey, float r, float g, float b, float originX, float originY) 
	: m_sx(sx), m_sy(sy), m_ex(ex), m_ey(ey), m_r(r), m_g(g), m_b(b), m_originX(originX), m_originY(originY) {};

void Line::Draw() 
{
	App::DrawLine(m_sx + m_originX, m_sy + m_originY, m_ex + m_originX, m_ey + m_originY, m_r, m_g, m_b);
}

bool Line::Intersects(Line line)
{
	float sx, sy, ex, ey;
	line.GetPoints(sx, sy, ex, ey);
	float m1 = (m_ey - m_sy) / (m_ex - m_sx);
	float m2 = (ey - sy) / (ex - sx);

}

void Line::Rotate(float thetaDot)
{
	float angle = -thetaDot * m_animTime;

	float c = cosf(angle);
	float s = sinf(angle);

	/*
	float sx = c * (m_sx - m_originX) + s * (m_sy - m_originY);
	float sy = -s * (m_sx - m_originX) + c * (m_sy - m_originY);

	float ex = c * (m_ex - m_originX) + s * (m_ey - m_originY);
	float ey = -s * (m_ex - m_originX) + c * (m_ey - m_originY);
	*/

	// Rotation matrix
	float sx = c * (m_sx) + s * (m_sy);
	float sy = -s * (m_sx) + c * (m_sy);

	float ex = c * (m_ex) + s * (m_ey);
	float ey = -s * (m_ex) + c * (m_ey);

	m_sx = sx;
	m_sy = sy;
	m_ex = ex;
	m_ey = ey;
}

void Line::Update(float dt)
{
	m_animTime = dt / 1000.0f;
}



