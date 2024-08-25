#include "WeaponStats.h"
#include "../../Font.h"
#include "raymath.h"

static const char* statsJsonName = "WeaponStats";
static const float tolerance = 0.1f;


StatFloatMulti& StatFloatMulti::operator+=(const StatFloatMulti& stat)
{
	value += stat.value;
	multiplier += stat.multiplier;
	return *this;
}
StatFloatMulti& StatFloatMulti::operator-=(const StatFloatMulti& stat)
{
	value -= stat.value;
	multiplier -= stat.multiplier;
	return *this;
}

StatFloat& StatFloat::operator+=(const StatFloat& stat)
{
	value += stat.value;
	return *this;
}
StatFloat& StatFloat::operator-=(const StatFloat& stat)
{
	value -= stat.value;
	return *this;
}

StatInt& StatInt::operator+=(const StatInt& stat)
{
	value += stat.value;
	return *this;
}

StatInt& StatInt::operator-=(const StatInt& stat)
{
	value -= stat.value;
	return *this;
}

#pragma region readFromJson
static void getJsonData(nlohmann::json& json,float* stat,float* statMul)
{
	if (stat)
	{
		if (json.contains("Min") && json.contains("Max"))
		{
			float min = json["Min"];
			float max = json["Max"];
			float procent = (rand() % 100) / 100.0f;
			(*stat) = (min + (max - min) * procent);
		}
		else if (json.contains("Value"))
		{
			(*stat) = json["Value"];
		}
		else if (json.is_number())
		{
			(*stat) = json;
		}
	}
	if (statMul)
	{
		if (json.contains("MulMin") && json.contains("MulMax"))
		{
			float min = json["MulMin"];
			float max = json["MulMax"];
			float procent = (rand() % 1000) / 1000.0f;
			(*statMul) = (min + (max - min) * procent);
		}
		else if (json.contains("MulValue"))
		{
			(*statMul) = json["MulValue"];
		}
	}
}

static void getJsonData(nlohmann::json& json,int tier, float* stat, float* statMul)
{
	if (!json.is_array())
	{
		getJsonData(json, stat, statMul);
		return;
	}
	if (json.size() <= 0)
		return;
	int tiers = (int)Clamp(tier, 0, json.size() - 1.0f);
	
	getJsonData(json[tiers], stat, statMul);
}

static void readStatFromWeapon(nlohmann::json& json, const char* statProperty, int tier, float* stat, float* statMultiplier = nullptr)
{
	if (!json.contains(statProperty))
		return;
	if (json[statProperty].is_number())
	{
		if (stat)
			*stat = json[statProperty];
		return;
	}
	getJsonData(json[statProperty], tier, stat, statMultiplier);
}

static void readStatFromWeapon(nlohmann::json& json, const char* statProperty, int tier, int* stat)
{
	if (!json.contains(statProperty))
		return;
	float data = 0.0f;
	readStatFromWeapon(json, statProperty, tier, &data);
	*stat = (int)data;
}
#pragma endregion readFromJson

void WeaponStats::readStatsFromWeapon(nlohmann::json json, int tier)
{
	if (!json.contains(statsJsonName))
		return;

	readStatFromWeapon(json[statsJsonName], "Damage",		tier, &damage.value,		&damage.multiplier);
	readStatFromWeapon(json[statsJsonName], "UseTime",		tier, &useTime.value,		&useTime.multiplier);
	readStatFromWeapon(json[statsJsonName], "ReloadTime",	tier, &reloadTime.value,	&reloadTime.multiplier);
	readStatFromWeapon(json[statsJsonName], "Speed",		tier, &speed.value,			&speed.multiplier);
	readStatFromWeapon(json[statsJsonName], "Range",		tier, &range.value,			&range.multiplier);
	readStatFromWeapon(json[statsJsonName], "Knockback",	tier, &knockback.value,		&knockback.multiplier);
	readStatFromWeapon(json[statsJsonName], "Angle",		tier, &angle.value);
	readStatFromWeapon(json[statsJsonName], "CountOfUse",	tier, &countOfUse.value);
	readStatFromWeapon(json[statsJsonName], "Bounce",		tier, &bounce.value);
	readStatFromWeapon(json[statsJsonName], "Pirce"     ,	tier, &pirce.value);
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
	readStat(json, "Damage",		damage.value,		damage.multiplier);
	readStat(json, "UseTime",		useTime.value,		useTime.multiplier);
	readStat(json, "ReloadTime",	reloadTime.value,	reloadTime.multiplier);
	readStat(json, "Speed",			speed.value,		speed.multiplier);
	readStat(json, "Range",			range.value,		range.multiplier);
	readStat(json, "Knockback",		knockback.value,	knockback.multiplier);
	if (json[statsJsonName].contains("Angle"))
		angle.value = json[statsJsonName]["Angle"];
	if (json[statsJsonName].contains("CountOfUse"))
		countOfUse.value = json[statsJsonName]["CountOfUse"];
	if (json[statsJsonName].contains("Bounce"))
		bounce.value = json[statsJsonName]["Bounce"];
	if (json[statsJsonName].contains("Pirce"))
		pirce.value = json[statsJsonName]["Pirce"];
}

void WeaponStats::saveStats(nlohmann::json& json)
{
	json[statsJsonName]["Damage"]		= { damage.value ,damage.multiplier };
	json[statsJsonName]["UseTime"]		= { useTime.value ,useTime.multiplier };
	json[statsJsonName]["ReloadTime"]	= { reloadTime.value ,reloadTime.multiplier };
	json[statsJsonName]["Speed"]		= { speed.value ,speed.multiplier };
	json[statsJsonName]["Range"]		= { range.value ,range.multiplier };
	json[statsJsonName]["Angle"]		=   angle.value;
	json[statsJsonName]["Knockback"]	= { knockback.value ,knockback.multiplier };
	json[statsJsonName]["CountOfUse"]	=   countOfUse.value;
	json[statsJsonName]["Bounce"]		=   bounce.value;
	json[statsJsonName]["Pirce"]		=   pirce.value;
}

WeaponStats& WeaponStats::operator+=(const WeaponStats& ws)
{
	damage					+= ws.damage;
	useTime					+= ws.useTime;
	reloadTime				+= ws.reloadTime;
	speed					+= ws.speed;
	range					+= ws.range;
	angle					+= ws.angle;
	knockback				+= ws.knockback;
	countOfUse				+= ws.countOfUse;
	bounce					+= ws.bounce;
	pirce					+= ws.pirce;
	return *this;
}

WeaponStats& WeaponStats::operator-=(const WeaponStats& ws)
{
	damage					-= ws.damage;
	useTime					-= ws.useTime;
	reloadTime				-= ws.reloadTime;
	speed					-= ws.speed;
	range					-= ws.range;
	angle					-= ws.angle;
	knockback				-= ws.knockback;
	countOfUse				-= ws.countOfUse;
	bounce					-= ws.bounce;
	pirce					-= ws.pirce;
	return *this;
}
void addToStringData(std::string& data, StatFloatMulti stat, std::string name, bool icon = false,
	int ID = 0, bool skip = false, bool showProcent = true, char separator = '+')
{
	if (skip && fabs(stat.value) < tolerance && fabs(stat.multiplier) < tolerance)
		return;
	
	std::string dataValue = std::to_string(stat.value);
	std::string dataValueMulti = std::to_string(stat.multiplier*100);
	dataValue.erase(dataValue.size() - 5, 5);
	dataValueMulti.erase(dataValueMulti.size() - 4, 5);
	if (icon)
		data += std::string("{Icon:") + std::to_string(ID) + std::string("}");
	data += "{" + name + "}: " ;
	if (showProcent)
	{
		if (separator == '*')
		{
			std::string dataV = std::to_string(stat.value * stat.multiplier);
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

void addToStringData(std::string& data, StatFloat stat, std::string name, bool icon = false, int ID = 0, bool skip = false)
{
	if (skip && fabs(stat.value) < tolerance)
		return;
	std::string dataValue = std::to_string(stat.value);
	dataValue.erase(dataValue.size() - 5, 5);
	if (icon)
		data += std::string("{Icon:") + std::to_string(ID) + std::string("}");
	data += "{" + name + "}: " + dataValue + std::string("\n");
}

void addToStringData(std::string& data, StatInt stat, std::string name, bool icon = false, int ID = 0, bool skip = false)
{
	if (skip && labs(stat.value) <= 0)
		return;
	if (icon)
		data += std::string("{Icon:") + std::to_string(ID) + std::string("}");
	data += "{" + name + "}: " + std::to_string(stat.value) + std::string("\n");
}


std::string WeaponStats::toString(bool skipZero,bool showProcent,char separator)
{
	std::string data="";

	addToStringData(data, damage,		"Damage"		, true, 0, skipZero, showProcent, separator);
	addToStringData(data, useTime,		"UseTime"		, true, 1, skipZero, showProcent, separator);
	addToStringData(data, reloadTime,	"ReloadTime"	, true, 2, skipZero, showProcent, separator);
	addToStringData(data, speed,		"Speed"			, true, 3, skipZero, showProcent, separator);
	addToStringData(data, range,		"Range"			, true, 4, skipZero, showProcent, separator);
	addToStringData(data, angle,		"Angle"			, true, 5, skipZero);
	addToStringData(data, knockback,	"Knockback"		, true, 6, skipZero, showProcent, separator);
	addToStringData(data, countOfUse,	"CountOfUse"	, true, 7, skipZero);
	addToStringData(data, bounce,		"Bounce"		, true, 8, skipZero);
	addToStringData(data, pirce,		"Pirce"			, true, 9, skipZero);
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
	isLineEgsist(lines, damage.value,		damage.multiplier);
	isLineEgsist(lines, useTime.value,		useTime.multiplier);
	isLineEgsist(lines, reloadTime.value,	reloadTime.multiplier);
	isLineEgsist(lines, speed.value,		speed.multiplier);
	isLineEgsist(lines, range.value,		range.multiplier);
	isLineEgsist(lines, angle.value								);
	isLineEgsist(lines, knockback.value,	knockback.multiplier);
	isLineEgsist(lines, countOfUse.value);
	isLineEgsist(lines, bounce.value);
	isLineEgsist(lines, pirce.value);
	return lines;
}

void toStringData(int& line, int i, std::string& data, StatFloatMulti stat, std::string name, int ID,
	StatType& statType, bool reversStat = false)
{
	if (fabs(stat.value) < tolerance && fabs(stat.multiplier) < tolerance)
		return;
	if (line == i)
	{
		addToStringData(data, stat, name, true, ID);
		if (stat.value == 0.0f)
			statType = StatType::neutral;
		else if (stat.value < 0.0f)
			statType = StatType::negative;
		else
			statType = StatType::positive;

		if (statType == StatType::neutral)
		{
			if (stat.multiplier == 0.0f)
				statType = StatType::neutral;
			else if (stat.multiplier < 0.0f)
				statType = StatType::negative;
			else
				statType = StatType::positive;
		}
		else if (statType == StatType::negative)
		{
			if (stat.multiplier > 0.0f)
				statType = StatType::mix;
		}
		else
		{
			if (stat.multiplier < 0.0f)
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

void toStringData(int& line, int i, std::string& data, StatFloat stat, std::string name, int ID, StatType& statType)
{
	if (fabs(stat.value) < tolerance)
		return;
	if (line == i)
	{
		addToStringData(data, stat, name, true, ID);
		if (stat.value == 0)
			statType = StatType::neutral;
		else if (stat.value < 0.0f)
			statType = StatType::negative;
		else
			statType = StatType::positive;
	}

	line++;
}

void toStringData(int& line, int i, std::string& data, StatInt stat, std::string name, int ID, StatType& statType)
{
	if (labs(stat.value) <= 0)
		return;
	if (line == i)
	{
		addToStringData(data, stat, name, true, 0);
		if (stat.value == 0)
			statType = StatType::neutral;
		else if (stat.value < 0)
			statType = StatType::negative;
		else if (stat.value > 0)
			statType = StatType::positive;
	}

	line++;
}

std::string WeaponStats::getStringLine(int l, StatType& statType)
{
	std::string data="";
	int line = 0;
	StatType type;
	toStringData(line, l, data, damage,		"Damage"		, 0, statType);
	toStringData(line, l, data, useTime,	"UseTime"		, 1, statType);
	toStringData(line, l, data, reloadTime,	"ReloadTime"	, 2, statType);
	toStringData(line, l, data, speed,		"Speed"		, 3, statType);
	toStringData(line, l, data, range,		"Range"		, 4, statType);
	toStringData(line, l, data, angle,		"Angle"		, 5, type);
	toStringData(line, l, data, knockback,	"Knockback"	, 6, statType);
	toStringData(line, l, data, countOfUse,	"CountOfUse"	, 7, statType);
	toStringData(line, l, data, bounce,		"Bounce"		, 8, statType);
	toStringData(line, l, data, pirce,		"Pirce"		, 9, statType);
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


