#include "ResourceImporter.h"
#define SPRITE_SECTION 1
#define ANIMATION_SECTION 2

std::vector<std::string> split(std::string line, std::string delimeter)
{
	std::vector<std::string> tokens;
	size_t last = 0; size_t next = 0;
	while ((next = line.find(delimeter, last)) != std::string::npos)
	{
		tokens.push_back(line.substr(last, next - last));
		last = next + 1;
	}
	tokens.push_back(line.substr(last));

	return tokens;
}

void ResourceImporter::spriteImport(LPCSTR filename, SpriteManager* sprManager)
{
	std::fstream fs;
	fs.open(filename);
	char res[2048];
	int parseSection = 0;
	while (fs.getline(res, 2048)) {
		std::string line(res);
		
		//TODO: improve this lmao
		if (line[0] == '#') continue;
		std::vector<std::string> component = split(line, " ");
		if (line == "[SPRITE]") {
			parseSection = SPRITE_SECTION; continue;
		}
		if (line == "[ANIMATION]") {
			parseSection = ANIMATION_SECTION; continue;
		}
		if (line[0] == '=') break;
		DebugOut((line + "\n").c_str());
		switch (parseSection) {
		case SPRITE_SECTION:
			if (component.size() < 6) {
				DebugOut("[WARNING] Not enough parameter for this line\n");
				continue;
			}
			try {
				sprManager->add(std::stoi(component[0], nullptr), std::stoi(component[1], nullptr), std::stoi(component[2], nullptr), std::stoi(component[3], nullptr), std::stoi(component[4], nullptr), TextureManager::getInstance()->get(std::stoi(component[5], nullptr)));
			}
			catch (int er) {
				DebugOut("[ERROR] An error occured\n");
			}
			break;
		case ANIMATION_SECTION:

			break;
		default:
			DebugOut("[WARNING] Unknown section");
		}
		
	}
	fs.close();
	DebugOut("[INFO] Importing\n");
	
}

void ResourceImporter::mapDataImport(LPCSTR filename)
{
}
