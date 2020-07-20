#pragma once

#include "pugixml.hpp"
#include "Logger.h"

typedef unsigned int GLuint;

class Settings
{
public:
	static GLuint gl_version_major;
	static GLuint gl_version_minor;
	static unsigned int window_width;
	static unsigned int window_height;
	static unsigned int antiailising_level;
	static unsigned int anisotropic_filtering_level;
	static bool fullscreen;

	static unsigned int render_distance;

	static pugi::xml_document load(const char* src);

	static void save(pugi::xml_document& doc, const char* dest);

private:
	Settings() {}
	Settings(const Settings&) {}
	~Settings() {}
};