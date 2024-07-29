#include "WeaponStats.h"
#include "../../Font.h"

static const char* statsJsonName = "Stats";
static const float tolerance = 0.1f;

void readStatFromWeapon(nlohmann::json& json, const char* statProperty, int tier, int& stat)
{
	if (!json[statsJsonName].contains(statProperty))
		return;
	int statsSize = (int)json[statsJsonName][statProperty].size();
	if (statsSize <= 0)
		return;
	if (tier >= statsSize)
		tier = statsSize - 1;
	if (json[statsJsonName][statProperty][tier].size() > 1)
	{
		int min = json[statsJsonName][statProperty][tier][0];
		int max = json[statsJsonName][statProperty][tier][1];
		float procent = (rand() % 1000) / 1000.0f;
		stat = (int)(min + (max - min) * procent);
	}
	else if (json[statsJsonName][statProperty][tier].size() > 0)
	{
		stat = json[statsJsonName][statProperty][tier];
	}


}

void readStatFromWeapon(nlohmann::json& json, const char* statProperty, int tier, float& stat)
{
	if (!json[statsJsonName].contains(statProperty))
		return;
	int statsSize = (int)json[statsJsonName][statProperty].size();
	if (statsSize <= 0)
		return;
	if (tier >= statsSize)
		tier = statsSize - 1;

	if (json[statsJsonName][statProperty][tier].size() > 1)
	{
		float min = json[statsJsonName][statProperty][tier][0];
		float max = json[statsJsonName][statProperty][tier][1];
		float procent = (rand() % 1000) / 1000.0f;
		stat = min + (max - min) * procent;
	}
	else if (json[statsJsonName][statProperty][tier].size() > 0)
	{
		stat = json[statsJsonName][statProperty][tier];
	}
}

void readStatFromWeapon(nlohmann::json& json, const char* statProperty, int tier, float& stat, float& statMultiplier)
{
	if (!json[statsJsonName].contains(statProperty))
		return;
	int statsSize = (int)json[statsJsonName][statProperty].size();
	if (statsSize <= 0)
		return;
	if (tier >= statsSize)
		tier = statsSize - 1;
	if (json[statsJsonName][statProperty][tier][0].size() > 1)
	{
		float min = json[statsJsonName][statProperty][tier][0][0];
		float max = json[statsJsonName][statProperty][tier][0][1];
		float procent = (rand() % 1000) / 1000.0f;
		stat = min + (max - min) * procent;
	}
	else if (json[statsJsonName][statProperty][tier][0].size() > 0)
	{
		stat = json[statsJsonName][statProperty][tier][0];
	}
	if (json[statsJsonName][statProperty][tier][1].size() > 1)
	{
		float min = json[statsJsonName][statProperty][tier][1][0];
		float max = json[statsJsonName][statProperty][tier][1][1];
		float procent = (rand() % 1000) / 1000.0f;
		statMultiplier = min + (max - min) * procent;
	}
	else if (json[statsJsonName][statProperty][tier][1].size() > 0)
	{
		statMultiplier = json[statsJsonName][statProperty][tier][1];
	}

}

void WeaponStats::readStatsFromWeapon(nlohmann::json json, int tier)
{
	if (!json.contains(statsJsonName))
		return;

	readStatFromWeapon(json, "Damage"    ,tier, damage, damageMultiplier);
	readStatFromWeapon(json, "UseTime"   , tier, useTime, useTimeMultiplier);
	readStatFromWeapon(json, "ReloadTime", tier, reloadTime, reloadTimeMultiplier);
	readStatFromWeapon(json, "Speed"     , tier, speed, speedMultiplier);
	readStatFromWeapon(json, "Range"     , tier, range, rangeMultiplier);
	readStatFromWeapon(json, "Knockback" , tier, knockback, knockbackMultiplier);
	readStatFromWeapon(json, "Angle"     , tier, angle);
	readStatFromWeapon(json, "CountOfUse", tier, countOfUse);
	readStatFromWeapon(json, "Bounce"    , tier, bounce);
	readStatFromWeapon(json, "Pirce"     , tier, pirce);
}

void readStat(nlohmann::json& json,const char* statProperty,float& stat,float& statMultiplier)
{
	if (!json[statsJsonName].contains(statProperty))
		return;
	stat = json[statsJsonName][statProperty][0];
	statMultiplier = json[statsJsonName][statProperty][1];
}

void WeaponStats::readStats(nlohmann::json json)
{
	readStat(json, "Damage",		damage,		damageMultiplier);
	readStat(json, "UseTime",		useTime,	useTimeMultiplier);
	readStat(json, "ReloadTime",	reloadTime, reloadTimeMultiplier);
	readStat(json, "Speed",			speed,		speedMultiplier);
	readStat(json, "Range",			range,		rangeMultiplier);
	readStat(json, "Knockback",		knockback,	knockbackMultiplier);
	if (json[statsJsonName].contains("Angle"))
		angle = json[statsJsonName]["Angle"];
	if (json[statsJsonName].contains("CountOfUse"))
		countOfUse = json[statsJsonName]["CountOfUse"];
	if (json[statsJsonName].contains("Bounce"))
		bounce = json[statsJsonName]["Bounce"];
	if (json[statsJsonName].contains("Pirce"))
		pirce = json[statsJsonName]["Pirce"];
}

void WeaponStats::saveStats(nlohmann::json& json)
{
	json[statsJsonName]["Damage"]		= { damage ,damageMultiplier };
	json[statsJsonName]["UseTime"]		= { useTime ,useTimeMultiplier };
	json[statsJsonName]["ReloadTime"]	= { reloadTime ,reloadTimeMultiplier };
	json[statsJsonName]["Speed"]		= { speed ,speedMultiplier };
	json[statsJsonName]["Range"]		= { range ,rangeMultiplier };
	json[statsJsonName]["Angle"]		= angle;
	json[statsJsonName]["Knockback"]	= { knockback ,knockbackMultiplier };
	json[statsJsonName]["CountOfUse"]	= countOfUse;
	json[statsJsonName]["Bounce"]		= bounce;
	json[statsJsonName]["Pirce"]		= pirce;
}

WeaponStats& WeaponStats::operator+=(const WeaponStats& ws)
{
	damage					+= ws.damage;
	damageMultiplier		+= ws.damageMultiplier;
	useTime					+= ws.useTime;
	useTimeMultiplier		+= ws.useTimeMultiplier;
	reloadTime				+= ws.reloadTime;
	reloadTimeMultiplier	+= ws.reloadTimeMultiplier;
	speed					+= ws.speed;
	speedMultiplier			+= ws.speedMultiplier;
	range					+= ws.range;
	rangeMultiplier			+= ws.rangeMultiplier;
	angle					+= ws.angle;
	knockback				+= ws.knockback;
	knockbackMultiplier		+= ws.knockbackMultiplier;
	countOfUse				+= ws.countOfUse;
	bounce					+= ws.bounce;
	pirce					+= ws.pirce;
	return *this;
}

WeaponStats& WeaponStats::operator-=(const WeaponStats& ws)
{
	damage					-= ws.damage;
	damageMultiplier		-= ws.damageMultiplier;
	useTime					-= ws.useTime;
	useTimeMultiplier		-= ws.useTimeMultiplier;
	reloadTime				-= ws.reloadTime;
	reloadTimeMultiplier	-= ws.reloadTimeMultiplier;
	speed					-= ws.speed;
	speedMultiplier			-= ws.speedMultiplier;
	range					-= ws.range;
	rangeMultiplier			-= ws.rangeMultiplier;
	angle					-= ws.angle;
	knockback				-= ws.knockback;
	knockbackMultiplier		-= ws.knockbackMultiplier;
	countOfUse				-= ws.countOfUse;
	bounce					-= ws.bounce;
	pirce					-= ws.pirce;
	return *this;
}
void addToStringData(std::string& data, float value, float valueMulti, std::string name, bool icon = false,
	int ID = 0, bool skip = false, bool showProcent = true, char separator = '+')
{
	if (skip && fabs(value) < tolerance && fabs(valueMulti) < tolerance)
		return;
	
	std::string dataValue = std::to_string(value);
	std::string dataValueMulti = std::to_string(valueMulti*100);
	dataValue.erase(dataValue.size() - 5, 5);
	dataValueMulti.erase(dataValueMulti.size() - 4, 5);
	if (icon)
		data += std::string("{Icon:") + std::to_string(ID) + std::string("}");
	data += "{" + name + "}: " ;
	if (showProcent)
	{
		if (separator == '*')
		{
			std::string dataV = std::to_string(value * valueMulti);
			dataV.erase(dataV.size() - 5, 5);
			data += dataV + " = " + dataValue + ' ' + separator + ' ' + dataValueMulti + '%';
		}
		else
			data += dataValue + ' ' + separator + ' ' + dataValueMulti + '%';
	}

	else
		data += dataValue;
	data += std::string("\n");
}

void addToStringData(std::string& data, float value, std::string name, bool icon = false, int ID = 0, bool skip = false)
{
	if (skip && fabs(value) < tolerance)
		return;
	std::string dataValue = std::to_string(value);
	dataValue.erase(dataValue.size() - 5, 5);
	if (icon)
		data += std::string("{Icon:") + std::to_string(ID) + std::string("}");
	data += "{" + name + "}: " + dataValue + std::string("\n");
}

void addToStringData(std::string& data, int value, std::string name, bool icon = false, int ID = 0, bool skip = false)
{
	if (labs(value) < 0)
		return;
	if (icon)
		data += std::string("{Icon:") + std::to_string(ID) + std::string("}");
	data += "{" + name + "}: " + std::to_string(value) + std::string("\n");
}


std::string WeaponStats::toString(bool skipZero,bool showProcent,char separator)
{
	std::string data="";

	addToStringData(data, damage		, damageMultiplier		, "Damage"		, true, 0, skipZero, showProcent, separator);
	addToStringData(data, useTime		, useTimeMultiplier		, "UseTime"		, true, 1, skipZero, showProcent, separator);
	addToStringData(data, reloadTime	, reloadTimeMultiplier	, "ReloadTime"	, true, 2, skipZero, showProcent, separator);
	addToStringData(data, speed			, speedMultiplier		, "Speed"		, true, 3, skipZero, showProcent, separator);
	addToStringData(data, range			, rangeMultiplier		, "Range"		, true, 4, skipZero, showProcent, separator);
	addToStringData(data, angle									, "Angle"		, true, 5, skipZero);
	addToStringData(data, knockback		, knockbackMultiplier	, "Knockback"	, true, 6, skipZero, showProcent, separator);
	addToStringData(data, countOfUse							, "CountOfUse"	, true, 7, skipZero);
	addToStringData(data, bounce								, "Bounce"		, true, 8, skipZero);
	addToStringData(data, pirce									, "Pirce"		, true, 9, skipZero);
	return data;
}

void WeaponStats::draw(Rectangle pos, float textSize,bool flexRec,bool frame,std::string title,
	bool skipZero,bool colorStats, bool showProcent, char separator)
{
	std::string desc = title + toString(skipZero, showProcent, separator);
	const char* cDesc = desc.c_str();
	Vector2 size = MyFont::TextSize(cDesc, textSize, 0);

	if (flexRec)
	{
		pos.width = size.x;
		pos.height = size.y;
	}
	else
		BeginScissorMode((int)pos.x, (int)pos.y, (int)pos.width, (int)pos.height);
	if (frame)
		DrawFrameRounded(pos, BLUE, BLACK);

	if (colorStats)
	{
		int lines = (int)std::count(title.begin(), title.end(), '\n');
		MyFont::DrawTextWithOutline(title.c_str(), pos.x, pos.y, textSize, WHITE, BLACK);
		drawColorStats(pos.x, pos.y + lines * textSize, textSize, RED, GREEN, BLACK);
	}
	else
		MyFont::DrawTextWithOutline(cDesc, pos.x, pos.y, textSize, WHITE, BLACK);

	if (!flexRec)
		EndScissorMode();

}

void isLineEgsist(int& lines,int v)
{
	if (abs(v) <= 0)
		return;
	lines++;
}

void isLineEgsist(int& lines,float v)
{
	if (abs(v) < tolerance)
		return;
	lines++;
}

void isLineEgsist(int& lines, float v, float vMultiplier)
{
	if (abs(v) < tolerance && abs(vMultiplier) < tolerance)
		return;
	lines++;
}

int WeaponStats::getNumberOflines()
{
	int lines = 0;
	isLineEgsist(lines, damage		, damageMultiplier		);
	isLineEgsist(lines, useTime		, useTimeMultiplier		);
	isLineEgsist(lines, reloadTime	, reloadTimeMultiplier	);
	isLineEgsist(lines, speed		, speedMultiplier		);
	isLineEgsist(lines, range		, rangeMultiplier		);
	isLineEgsist(lines, angle								);
	isLineEgsist(lines, knockback	, knockbackMultiplier	);
	isLineEgsist(lines, countOfUse							);
	isLineEgsist(lines, bounce								);
	isLineEgsist(lines, pirce								);
	return lines;
}


void toStringData(int& line, int i, std::string& data, float value, float valueMulti, std::string name, int ID,
	StatType& statType, bool reversStat = false)
{
	if (fabs(value) < tolerance && fabs(valueMulti) < tolerance)
		return;
	if (line == i)
	{
		addToStringData(data, value, valueMulti, name, true, ID);
		if (value == 0.0f)
			statType = StatType::neutral;
		else if (value < 0.0f)
			statType = StatType::negative;
		else
			statType = StatType::positive;

		if (statType == StatType::neutral)
		{
			if (valueMulti == 0.0f)
				statType = StatType::neutral;
			else if (valueMulti < 0.0f)
				statType = StatType::negative;
			else
				statType = StatType::positive;
		}
		else if (statType == StatType::negative)
		{
			if (valueMulti > 0.0f)
				statType = StatType::mix;
		}
		else
		{
			if (valueMulti < 0.0f)
				statType = StatType::mix;
		}
		if (reversStat)
		{
			if (statType == StatType::positive)
				statType = StatType::negative;
			else if (statType == StatType::negative)
				statType = StatType::positive;
		}
	}

	line++;
}

void toStringData(int& line, int i, std::string& data, float value, std::string name, int ID, StatType& statType)
{
	if (fabs(value) < tolerance)
		return;
	if (line == i)
	{
		addToStringData(data, value, name, true, ID);
		if (value == 0)
			statType = StatType::neutral;
		else if (value < 0.0f)
			statType = StatType::negative;
		else
			statType = StatType::positive;
	}

	line++;
}

void toStringData(int& line, int i, std::string& data, int value, std::string name, int ID, StatType& statType)
{
	if (labs(value) < 0)
		return;
	if (line == i)
	{
		addToStringData(data, value, name, true, 0);
		if (value == 0)
			statType = StatType::neutral;
		else if (value < 0)
			statType = StatType::negative;
		else if (value > 0)
			statType = StatType::positive;
	}

	line++;
}

std::string WeaponStats::getStringLine(int l, StatType& statType)
{
	std::string data="";
	int line = 0;
	StatType type;
	toStringData(line, l, data, damage		, damageMultiplier		, "Damage"		, 0, statType);

	toStringData(line, l, data, useTime		, useTimeMultiplier		, "UseTime"		, 1, statType);
	toStringData(line, l, data, reloadTime	, reloadTimeMultiplier	, "ReloadTime"	, 2, statType);

	toStringData(line, l, data, speed		, speedMultiplier		, "Speed"		, 3, statType);
	toStringData(line, l, data, range		, rangeMultiplier		, "Range"		, 4, statType);
	toStringData(line, l, data, angle								, "Angle"		, 5, type);
	toStringData(line, l, data, knockback	, knockbackMultiplier	, "Knockback"	, 6, statType);
	toStringData(line, l, data, countOfUse							, "CountOfUse"	, 7, statType);
	toStringData(line, l, data, bounce								, "Bounce"		, 8, statType);
	toStringData(line, l, data, pirce								, "Pirce"		, 9, statType);
	return data;
}


void WeaponStats::drawColorStats(float x, float y, float textSize, Color negative, Color positive, Color line)
{
	int n = getNumberOflines();
	for (int i = 0; i < n; i++)
	{
		StatType statType = StatType::neutral;
		std::string str = getStringLine(i, statType);
		const char *strchar = str.c_str();
		Color c = WHITE;
		switch (statType)
		{
		case StatType::positive:
			c = positive;
			break;
		case StatType::negative:
			c = negative;
			break;
		case StatType::mix:
			c = ORANGE;
			break;
		}
		MyFont::DrawTextWithOutline(strchar, x, y, textSize, c, line);
		y += textSize;
	}
}