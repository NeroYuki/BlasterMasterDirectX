#include "ResourceImporter.h"
#define SPRITE_SECTION 1
#define ANIMATION_SECTION 2
#define TILESET_SECTION 3
#define ENTITY_LIST 4
#define PORTAL_LIST 5
#define SECTION_LIST 6
#define LADDER_LIST 7
#define SCENEPORTAL_LIST 8
#define COLLECTABLE_LIST 9
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

void ResourceImporter::spriteImport(LPCSTR filename, SpriteManager* sprManager, AnimationManager* aniManager)
{
	std::fstream fs;
	fs.open(filename);
	char res[2048];
	int parseSection = 0;
	while (fs.getline(res, 2048)) {
		std::string line(res);
		
		//TODO: improve this lmao
		if (line[0] == '#' || line.size() < 2) continue;
		
		if (line == "[SPRITE]") {
			parseSection = SPRITE_SECTION; continue;
		}
		if (line == "[ANIMATION]") {
			parseSection = ANIMATION_SECTION; continue;
		}
		if (line == "[TILESET]") {
			parseSection = TILESET_SECTION; continue;
		}
		// if (line[0] == '=') break;
		std::vector<std::string> component = split(line, " ");
		// DebugOut((line + "\n").c_str());
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
			if (component.size() < 2) {
				DebugOut("[WARNING] Not an animation chain\n");
				continue;
			}
			try {
				int ani_id = std::stoi(component[0], nullptr);
				int s_count = std::stoi(component[1], nullptr);
				if (component.size() < 2 + s_count) {
					DebugOut("[WARNING] Not enough parameter for this line\n");
					continue;
				}
				LPANIMATION entry = new Animation(100);
				for (int i = 0; i < s_count; i++) {
					entry->add(std::stoi(component[2 + i], nullptr));
				}
				aniManager->add(ani_id, entry);
			}
			catch (int er) {
				DebugOut("[ERROR] An error occured\n");
			}
			break;
		case TILESET_SECTION:
			if (component.size() < 7) {
				DebugOut("[WARNING] Not enough parameter for this line\n");
				continue;
			}
			try {
				int texture_id = std::stoi(component[0], nullptr);
				int row_num = std::stoi(component[1], nullptr);
				int column_num = std::stoi(component[2], nullptr);
				int width = std::stoi(component[3], nullptr);
				int height = std::stoi(component[4], nullptr);
				int margin = std::stoi(component[5], nullptr);
				int spacing = std::stoi(component[6], nullptr);
				int count = texture_id * 1000000;
				int x = margin; int y = margin;
				for (int i = 0; i < row_num; i++)
				{
					for (int j = 0; j < column_num; j++) {
						sprManager->add(count, y, x, y + height,x + width, TextureManager::getInstance()->get(texture_id));
						count++;
						x = x + width + spacing;
					}
					x = spacing;
					y = y + height + spacing;
				}
			}
			catch (int er) {
				DebugOut("[ERROR] An error occured\n");			
			}

			break;
		default:
			DebugOut("[WARNING] Unknown section\n");
		}
		
	}
	fs.close();
	DebugOut("[INFO] Resourced Imported\n");
	
}



void ResourceImporter::mapDataImport(LPCSTR filename, Scene* applyingScene)
{
	std::fstream fs;
	fs.open(filename);
	char res[2048];
	int row = 0;
	while (fs.getline(res, 2048)) {
		std::string line(res);
		std::vector<std::string> component = split(line, ",");
		if (component.size() >= 1) {
			//DebugOut(component[0].c_str());
			int startBlockXCoord = -1;
			int endBlockXCoord = -1;
			int startSpikeXCoord = -1;
			int endSpikeXCoord = -1;
			int startdestrucableBlockCoord = -1;
			int enddestrucableBlockCoord = -1;
			for (int i = 0; i < component.size(); i++) {
				int entry = std::stoi(component[i], nullptr);
				if (entry == 120) {
					if (startBlockXCoord == -1)
						startBlockXCoord = i * 16;
					endBlockXCoord = i * 16 + 16;
				}
				else if (startBlockXCoord != -1) {
					applyingScene->addObject(new Block(startBlockXCoord, row * 16, endBlockXCoord - startBlockXCoord, 16));
					startBlockXCoord = -1;
					endBlockXCoord = -1;
				}

				if (entry == 50) {
					if (startSpikeXCoord == -1)
						startSpikeXCoord = i * 16;
					endSpikeXCoord = i * 16 + 16;
				}
				else if (startSpikeXCoord != -1) {
					applyingScene->addObject(new Spike(startSpikeXCoord, row * 16, endSpikeXCoord - startSpikeXCoord, 16));
					startSpikeXCoord = -1;
					endSpikeXCoord = -1;
				}
				if (entry == 34) {
					if (startdestrucableBlockCoord == -1)
						startdestrucableBlockCoord = i * 16;
					enddestrucableBlockCoord = i * 16 + 16;
				}
				else if (startdestrucableBlockCoord != -1) {
					applyingScene->addObject(new DestrucableBlock(startdestrucableBlockCoord, row * 16, enddestrucableBlockCoord - startdestrucableBlockCoord, 16));
					startdestrucableBlockCoord = -1;
					enddestrucableBlockCoord = -1;
				}
				if (entry == -1) continue;
			}




			if (startBlockXCoord != -1) {
				applyingScene->addObject(new Block(startBlockXCoord, row * 16, endBlockXCoord - startBlockXCoord, 16));
			}
			if (startSpikeXCoord != -1) {
				applyingScene->addObject(new Spike(startSpikeXCoord, row * 16, endSpikeXCoord - startSpikeXCoord, 16));
			}
			if (startdestrucableBlockCoord != -1) {
				applyingScene->addObject(new DestrucableBlock(startSpikeXCoord, row * 16, endSpikeXCoord - startSpikeXCoord, 16));
			}

		}
		else {
			DebugOut("[WARNING] This row does not contain any entry\n");
		}
		row++;
	}
	fs.close();
	DebugOut("[INFO] Map Layout Imported\n");
}

void ResourceImporter::mapObjImport(LPCSTR filename, Scene* applyingScene)
{
	std::fstream fs;
	fs.open(filename);
	char res[2048];
	int parseSection = 0;
	while (fs.getline(res, 2048)) {
		std::string line(res);
		std::vector<std::string> component = split(line, " ");

		if (line[0] == '#' || line.size() < 2) continue;

		if (line == "[ENTITY]") {
			parseSection = ENTITY_LIST; continue;
		}
		if (line == "[PORTAL]") {
			parseSection = PORTAL_LIST; continue;
		}
		if (line == "[SECTION]") {
			parseSection = SECTION_LIST; continue;
		}
		if (line == "[LADDER]") {
			parseSection = LADDER_LIST; continue;
		}
		if (line == "[ScenePortal]") {
			parseSection = SCENEPORTAL_LIST; continue;
		}
		if (line == "[COLLECTABLE]") {
			parseSection = COLLECTABLE_LIST; continue;
		}
		switch (parseSection) {
		case ENTITY_LIST:
			if (component.size() < 3) {
				DebugOut("[WARNING] Not enough parameter for this line\n");
				continue;
			}
			try {
				int id = std::stof(component[0], nullptr);
				float x = std::stof(component[1], nullptr);
				float y = std::stof(component[2], nullptr);
				switch (id)
				{
				case 1: applyingScene->addObject(new Worm(x, y, 10)); break;
				//case 2: applyingScene->addObject(new Dome(x, y, 10)); break;
				case 3: applyingScene->addObject(new Floater(x, y, 10)); break;
				case 4: applyingScene->addObject(new Jumper(x, y, 10)); break;
				case 5: applyingScene->addObject(new Insect(x, y, 10)); break;
				case 6: applyingScene->addObject(new Orb(x, y, 10)); break;
				case 7: applyingScene->addObject(new Skull(x, y, 10)); break;
				case 8: applyingScene->addObject(new Mine(x, y, 10)); break;
				case 9:applyingScene->addObject(new Teleporter(x, y, 10)); break;
				case 10:applyingScene->addObject(new Cannon(x, y, 10)); break;
				case 11:applyingScene->addObject(new Eyeball(x, y, 10)); break;
				default:
					break;
				}
			}
			catch (int er) {
				DebugOut("[ERROR] An error occured\n");
			}
			break;
		case PORTAL_LIST:
			if (component.size() < 8) {
				DebugOut("[WARNING] Not enough parameter for this line\n");
				continue;
			}
			try {
				float x = std::stof(component[0], nullptr);
				float y = std::stof(component[1], nullptr);
				int w = std::stoi(component[2], nullptr);
				int h = std::stoi(component[3], nullptr);
				float lx = std::stof(component[4], nullptr);
				float ly = std::stof(component[5], nullptr);
				int sectionStart = std::stoi(component[6], nullptr);
				int sectionEnd = std::stoi(component[7], nullptr);
				applyingScene->addPortal(new Portal(x, y, w, h, lx, ly, sectionStart, sectionEnd));
			}
			catch (int er) {
				DebugOut("[ERROR] An error occured\n");
			}
			break;
		case SECTION_LIST:
			if (component.size() < 4) {
				DebugOut("[WARNING] Not enough parameter for this line\n");
				continue;
			}
			try {
				int t = std::stoi(component[0], nullptr);
				int l = std::stoi(component[1], nullptr);
				int b = std::stoi(component[2], nullptr);
				int r = std::stoi(component[3], nullptr);
				applyingScene->addSection(new SceneSection(t, l, b, r));
			}
			catch (int er) {
				DebugOut("[ERROR] An error occured\n");
			}
			break;
		case LADDER_LIST:
			if (component.size() < 4) {
				DebugOut("[WARNING] Not enough parameter for this line\n");
				continue;
			}
			try {
				int t = std::stoi(component[0], nullptr);
				int l = std::stoi(component[1], nullptr);
				int b = std::stoi(component[2], nullptr);
				int r = std::stoi(component[3], nullptr);
				applyingScene->addObject(new Ladder(t, l, b, r));
			}
			catch (int er) {
				DebugOut("[ERROR] An error occured\n");
			}
		case SCENEPORTAL_LIST:
			if (component.size() < 9) {
				DebugOut("[WARNING] Not enough parameter for this line\n");
				continue;
			}
			try {
				float x = std::stof(component[0], nullptr);
				float y = std::stof(component[1], nullptr);
				int w = std::stoi(component[2], nullptr);
				int h = std::stoi(component[3], nullptr);
				float lx = std::stof(component[4], nullptr);
				float ly = std::stof(component[5], nullptr);
				int sectionStart = std::stoi(component[6], nullptr);
				int sectionEnd = std::stoi(component[7], nullptr);
				int isChangeScene = std::stoi(component[8], nullptr);
				applyingScene->addObject(new ScenePortal(x, y, w, h, lx, ly, sectionStart, sectionEnd,isChangeScene));
			}
			catch (int er) {
				DebugOut("[ERROR] An error occured\n");
			}
			break;
		case COLLECTABLE_LIST:
			if (component.size() < 4) {
				DebugOut("[WARNING] Not enough parameter for this line\n");
				continue;
			}
			try {
				float x = std::stof(component[0], nullptr);
				float y = std::stof(component[1], nullptr);
				int w = std::stoi(component[2], nullptr);
				int h = std::stoi(component[3], nullptr);
				applyingScene->addObject(new Collectable(x, y, w, h));
			}
			catch (int er) {
				DebugOut("[ERROR] An error occured\n");
			}
			break;
		default:
			DebugOut("[WARNING] Unknown section\n");
		}

	}
}

void ResourceImporter::enemyImport(LPCSTR filename, Scene* applyingScene)
{
	std::fstream fs;
	fs.open(filename);
	char res[2048];
	int parseSection = 0;
	while (fs.getline(res, 2048)) {
		std::string line(res);
		std::vector<std::string> component = split(line, " ");

		if (line[0] == '#' || line.size() < 2) continue;

		if (line == "[ENTITY]") {
			parseSection = ENTITY_LIST; continue;
		}
		if (line == "[PORTAL]") {
			parseSection = PORTAL_LIST; continue;
		}
		if (line == "[SECTION]") {
			parseSection = SECTION_LIST; continue;
		}
		if (line == "[LADDER]") {
			parseSection = LADDER_LIST; continue;
		}
		if (line == "[ScenePortal]") {
			parseSection = SCENEPORTAL_LIST; continue;
		}
		switch (parseSection) {
		case ENTITY_LIST:
			if (component.size() < 3) {
				DebugOut("[WARNING] Not enough parameter for this line\n");
				continue;
			}
			try {
				int id = std::stof(component[0], nullptr);
				float x = std::stof(component[1], nullptr);
				float y = std::stof(component[2], nullptr);
				switch (id)
				{
				case 1: applyingScene->addObject(new Worm(x, y, 10)); break;
			//	case 2: applyingScene->addObject(new Dome(x, y, 10)); break;
				case 3: applyingScene->addObject(new Floater(x, y, 10)); break;
				case 4: applyingScene->addObject(new Jumper(x, y, 10)); break;
				case 5: applyingScene->addObject(new Insect(x, y, 10)); break;
				case 6: applyingScene->addObject(new Orb(x, y, 10)); break;
				case 7: applyingScene->addObject(new Skull(x, y, 10)); break;
				case 8: applyingScene->addObject(new Mine(x, y, 10)); break;
				case 9:applyingScene->addObject(new Cannon(x, y, 10)); break;
				case 10:applyingScene->addObject(new Teleporter(x, y, 10)); break;
				case 11:applyingScene->addObject(new Eyeball(x, y, 10)); break;
				default:
					break;
				}
			}
			catch (int er) {
				DebugOut("[ERROR] An error occured\n");
			}
			break;
		default:
			DebugOut("[WARNING] Unknown section\n");
		}

	}
}

void ResourceImporter::tilesetImporter(LPCSTR filename)
{
}
