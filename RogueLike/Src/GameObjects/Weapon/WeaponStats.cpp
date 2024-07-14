#include "WeaponStats.h"
#include "../../Font.h"

static const char* statsJsonName = "Stats";

void readStatFromWeapon(nlohmann::json& json, const char* statProperty, int tier, int& stat)
{
	if (!json[statsJsonName].contains(statProperty))
		return;
	int statsSize = (int)json[statsJsonName][statProperty].size();
	if (statsSize <= 0)
		return;
	if (tier >= statsSize)
		tier = statsSize - 1;
	int min = json[statsJsonName][statProperty][tier][0];
	int max = json[statsJsonName][statProperty][tier][1];
	float procent = (rand() % 1000) / 1000.0f;
	stat = (int)(min + (max - min) * procent);
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
	float min = json[statsJsonName][statProperty][tier][0];
	float max = json[statsJsonName][statProperty][tier][1];
	float procent = (rand() % 1000) / 1000.0f;
	stat = min + (max - min) * procent;
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
	float min = json[statsJsonName][statProperty][tier][0][0];
	float max = json[statsJsonName][statProperty][tier][0][1];
	float procent = (rand() % 1000) / 1000.0f;
	stat = min + (max - min) * procent;
	min = json[statsJsonName][statProperty][tier][1][0];
	max = json[statsJsonName][statProperty][tier][1][1];
	procent = (rand() % 1000) / 1000.0f;
	statMultiplier = min + (max - min) * procent;
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
	readStat(json, "Damage", damage, damageMultiplier);
	readStat(json, "UseTime", useTime, useTimeMultiplier);
	readStat(json, "ReloadTime", reloadTime, reloadTimeMultiplier);
	readStat(json, "Speed", speed, speedMultiplier);
	readStat(json, "Range", range, rangeMultiplier);
	readStat(json, "Knockback", useTime, useTimeMultiplier);
	readStat(json, "UseTime", useTime, useTimeMultiplier);
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
	json[statsJsonName]["Damage"] = { damage ,damageMultiplier };
	json[statsJsonName]["UseTime"] = { useTime ,useTimeMultiplier };
	json[statsJsonName]["ReloadTime"] = { reloadTime ,reloadTimeMultiplier };
	json[statsJsonName]["Speed"] = { speed ,speedMultiplier };
	json[statsJsonName]["Range"] = { range ,rangeMultiplier };
	json[statsJsonName]["Angle"] = angle;
	json[statsJsonName]["Knockback"] = { knockback ,knockbackMultiplier };
	json[statsJsonName]["CountOfUse"] = countOfUse;
	json[statsJsonName]["Bounce"] = bounce;
	json[statsJsonName]["Pirce"] = pirce;
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
	damage -= ws.damage;
	damageMultiplier -= ws.damageMultiplier;
	useTime -= ws.useTime;
	useTimeMultiplier -= ws.useTimeMultiplier;
	reloadTime -= ws.reloadTime;
	reloadTimeMultiplier -= ws.reloadTimeMultiplier;
	speed -= ws.speed;
	speedMultiplier -= ws.speedMultiplier;
	range -= ws.range;
	rangeMultiplier -= ws.rangeMultiplier;
	angle -= ws.angle;
	knockback -= ws.knockback;
	knockbackMultiplier -= ws.knockbackMultiplier;
	countOfUse -= ws.countOfUse;
	bounce -= ws.bounce;
	pirce -= ws.pirce;
	return *this;
}

void addToStringData(std::string& data, float value, std::string name, bool icon = false, int ID = 0)
{
	std::string dataValue = std::to_string(value);
	dataValue.erase(dataValue.size() - 5, 5);
	if (icon)
		data += std::string("{Icon:") + std::to_string(ID) + std::string("}");
	data += "{" + name + "}: " + dataValue + std::string("\n");
}

void addToStringData(std::string& data, int value, std::string name, bool icon = false, int ID = 0)
{
	if (icon)
		data += std::string("{Icon:") + std::to_string(ID) + std::string("}");
	data += "{" + name + "}: " + std::to_string(value) + std::string("\n");
}

std::string WeaponStats::toString()
{
	std::string data="";
	addToStringData(data, damage		, "Damage"		, true, 0);
	addToStringData(data, useTime		, "UseTime"		, true, 1);
	addToStringData(data, reloadTime	, "ReloadTime"	, true, 2);
	addToStringData(data, speed			, "Speed"		, true, 3);
	addToStringData(data, range			, "Range"		, true, 4);
	addToStringData(data, angle			, "Angle"		, true, 5);
	addToStringData(data, knockback		, "Knockback"	, true, 6);
	addToStringData(data, countOfUse	, "CountOfUse"	, true, 7);
	addToStringData(data, bounce		, "Bounce"		, true, 8);
	addToStringData(data, pirce			, "Pirce"		, true, 9);
	return data;
}

void WeaponStats::draw(Rectangle pos, float textSize,bool flexRec,bool frame)
{
	std::string desc = toString();
	const char* cDesc = desc.c_str();
	Vector2 size = MyFont::TextSize(cDesc, textSize, 0);
	const float border = 20.0f;
	Rectangle rec = { pos.x - border, pos.y - border,pos.height + 2 * border, pos.height + 2 * border };
	if (flexRec)
	{
		rec.width = size.x + 2 * border;
		rec.height = size.y + 2 * border;
	}
	else
	{
		BeginScissorMode((int)pos.x, (int)pos.y, (int)pos.width, (int)pos.height);
	}
	if (frame)
	{
		DrawRectangleRounded(rec, 0.2f, 1, RED);
		DrawRectangleRoundedLines({ rec.x + 1,rec.y + 1,rec.width - 2,rec.height - 2 }, 0.2f, 1, 5, BLACK);
	}
	//DrawRectangleRec(pos, BLUE);
	MyFont::DrawTextWithOutline(cDesc, pos.x, pos.y, textSize, WHITE, BLACK);
	if (!flexRec)
	{
		EndScissorMode();
	}

}