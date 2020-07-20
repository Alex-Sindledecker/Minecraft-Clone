#include "pch.h"
#include "Settings.h"

GLuint Settings::gl_version_major;
GLuint Settings::gl_version_minor;
unsigned int Settings::window_width;
unsigned int Settings::window_height;
unsigned int Settings::antiailising_level;
unsigned int Settings::anisotropic_filtering_level;
bool Settings::fullscreen;

unsigned int Settings::render_distance;

pugi::xml_document Settings::load(const char* src)
{
	{
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(src);
		if (!result)
		{
			CONSOLE_LOG_ERROR("Game.cpp", result.description());
			return doc;
		}

		pugi::xml_node root = doc.child("Settings");
		pugi::xml_node gameplay = root.child("GameplaySettings");
		pugi::xml_node graphics = root.child("GraphicsSettings");

		render_distance = graphics.child("RenderDistance").attribute("value").as_int();

		window_width = graphics.child("WindowSize").attribute("width").as_int();
		window_height = graphics.child("WindowSize").attribute("height").as_int();
		fullscreen = graphics.child("WindowSize").attribute("fullscreen").as_bool();
		anisotropic_filtering_level = graphics.child("AnisotropicFiltering").attribute("level").as_int();
		gl_version_major = graphics.child("GLVersion").attribute("major").as_int();
		gl_version_minor = graphics.child("GLVersion").attribute("minor").as_int();

		return doc;
	}
}

void Settings::save(pugi::xml_document& doc, const char* dest)
{
	pugi::xml_node root = doc.child("Settings");
	pugi::xml_node gameplay = root.child("GameplaySettings");
	pugi::xml_node graphics = root.child("GraphicsSettings");

	graphics.child("RenderDistance").attribute("value").set_value(render_distance);

	graphics.child("WindowSize").attribute("width").set_value(window_width);
	graphics.child("WindowSize").attribute("height").set_value(window_height);
	graphics.child("WindowSize").attribute("fullscreen").set_value(fullscreen);

	doc.save_file(dest);
}
