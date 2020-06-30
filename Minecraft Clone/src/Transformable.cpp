#include "pch.h"
#include "Transformable.h"

Transformable::Transformable()
	: m_pos(0, 0, 0), m_angles(0, 0, 0), m_scale(1, 1, 1)
{
}

void Transformable::move(glm::vec3 offset)
{
	m_pos += offset;
}

void Transformable::rotate(glm::vec3 angles)
{
	m_angles += angles;
}

void Transformable::scale(glm::vec3 factor)
{
	m_scale *= factor;
}

void Transformable::setPosition(glm::vec3 pos)
{
	m_pos = pos;
}

void Transformable::setRotation(glm::vec3 angles)
{
	m_angles = angles;
}

void Transformable::setScale(glm::vec3 scale)
{
	m_scale = scale;
}

glm::vec3 Transformable::getPosition() const
{
	return m_pos;
}

glm::vec3 Transformable::getRotation() const
{
	return m_angles;
}

glm::vec3 Transformable::getScale() const
{
	return m_scale;
}
