/*
 * Copyright 2010-2016 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "MissionSite.h"
#include "../Engine/Language.h"
#include "../Mod/RuleAlienMission.h"
#include "../Mod/AlienDeployment.h"

namespace OpenXcom
{

/**
 * Initializes a mission site.
 */
MissionSite::MissionSite(const RuleAlienMission *rules, const AlienDeployment *deployment, const AlienDeployment *alienCustomDeploy)  noexcept
: Target(), _rules(rules), _deployment(deployment), _missionCustomDeploy(alienCustomDeploy), _texture(-1), _secondsRemaining(0), _inBattlescape(false), _detected(false)
{
}

/**
 * Loads the mission site from a YAML file.
 * @param node YAML node.
 */
void MissionSite::load(const YAML::Node &node)
{
	Target::load(node);
	_texture = node["texture"].as<int>(_texture);
	_secondsRemaining = node["secondsRemaining"].as<size_t>(_secondsRemaining);
	_race = node["race"].as<std::string>(_race);
	_inBattlescape = node["inBattlescape"].as<bool>(_inBattlescape);
	_detected = node["detected"].as<bool>(_detected);
	//_missionCustomDeploy loaded outside
}

/**
 * Saves the mission site to a YAML file.
 * @return YAML node.
 */
YAML::Node MissionSite::save() const
{
	YAML::Node node = Target::save();
	node["type"] = _rules->getType();
	node["deployment"] = _deployment->getType();
	if (_missionCustomDeploy)
		node["missionCustomDeploy"] = _missionCustomDeploy->getType();
	node["texture"] = _texture;
	if (_secondsRemaining)
		node["secondsRemaining"] = _secondsRemaining;
	node["race"] = _race;
	if (_inBattlescape)
		node["inBattlescape"] = _inBattlescape;
	node["detected"] = _detected;
	return node;
}

/**
 * Returns the mission's unique type used for
 * savegame purposes.
 * @return ID.
 */
std::string MissionSite::getType() const
{
	return _deployment->getMarkerName();
}

/**
 * Returns the name on the globe for the mission.
 * @return String ID.
 */
std::string MissionSite::getMarkerName() const
{
	return getType();
}

/**
 * Returns the globe marker for the mission site.
 * @return Marker sprite, -1 if none.
 */
int MissionSite::getMarker() const
{
	if (!_detected) return -1;

	int icon = _deployment->getMarkerIcon();
	return (-1 != icon) ? icon : 5;
}

/**
 * Returns the alien race currently residing in the mission site.
 * @return Alien race.
 */
std::string MissionSite::getAlienRace() const
{
	return _race;
}

/**
 * Changes the alien race currently residing in the mission site.
 * @param race Alien race.
 */
void MissionSite::setAlienRace(const std::string &race)
{
	_race = race;
}

/**
 * Gets the mission site's associated city, if any.
 * @return String ID for the city, "" if none.
 */
std::string MissionSite::getCity() const
{
	return _city;
}

/**
 * Sets the mission site's associated city, if any.
 * @param city String ID for the city, "" if none.
 */
void MissionSite::setCity(const std::string &city)
{
	_city = city;
}

}
