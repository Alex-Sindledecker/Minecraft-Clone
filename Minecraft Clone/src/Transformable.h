#pragma once

#include "glm/glm.hpp"

class Transformable
{
public:
	Transformable();
	virtual ~Transformable() {}
	virtual void move(glm::vec3 offset);
	virtual void rotate(glm::vec3 angles);
	virtual void scale(glm::vec3 factor);
	virtual void setPosition(glm::vec3 pos);
	virtual void setRotation(glm::vec3 angles);
	virtual void setScale(glm::vec3 scale);
	virtual glm::vec3 getPosition() const;
	virtual glm::vec3 getRotation() const;
	virtual glm::vec3 getScale() const;

protected:
	glm::vec3 m_pos;
	glm::vec3 m_angles;
	glm::vec3 m_scale;
};

