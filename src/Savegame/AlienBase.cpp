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
#include "AlienBase.h"
#include "../Engine/Language.h"
#include "../Mod/AlienDeployment.h"

namespace OpenXcom
{

/**
 * Initializes an alien base
 */
AlienBase::AlienBase(AlienDeployment *deployment, int startMonth) : Target(), _inBattlescape(false), _discovered(false), _deployment(deployment), _startMonth(startMonth), _genMissionCount(0)
{
	// allow spawning hunt missions immediately after the base is created, i.e. no initial delay
	_minutesSinceLastHuntMissionGeneration = _deployment->getHuntMissionMaxFrequency();
}

/**
 * Loads the alien base from a YAML file.
 * @param node YAML node.
 */
void AlienBase::load(const YAML::Node &node)
{
	Target::load(node);
	_pactCountry = node["pactCountry"].as<std::string>(_pactCountry);
	_race = node["race"].as<std::string>(_race);
	_inBattlescape = node["inBattlescape"].as<bool>(_inBattlescape);
	_discovered = node["discovered"].as<bool>(_discovered);
	_startMonth = node["startMonth"].as<int>(_startMonth);
	_minutesSinceLastHuntMissionGeneration = node["minutesSinceLastHuntMissionGeneration"].as<int>(_minutesSinceLastHuntMissionGeneration);
	_genMissionCount = node["genMissionCount"].as<int>(_genMissionCount);
}

/**
 * Saves the alien base to a YAML file.
 * @return YAML node.
 */
YAML::Node AlienBase::save() const
{
	YAML::Node node = Target::save();
	node["pactCountry"] = _pactCountry;
	node["race"] = _race;
	if (_inBattlescape)
		node["inBattlescape"] = _inBattlescape;
	if (_discovered)
		node["discovered"] = _discovered;
	node["deployment"] = _deployment->getType();
	node["startMonth"] = _startMonth;
	node["minutesSinceLastHuntMissionGeneration"] = _minutesSinceLastHuntMissionGeneration;
	node["genMissionCount"] = _genMissionCount;
	return node;
}

/**
 * Returns the alien base's unique type used for
 * savegame purposes.
 * @return ID.
 */
std::string AlienBase::getType() const
{
	return _deployment->getMarkerName();
}

/**
 * Returns the globe marker for the alien base.
 * @return Marker sprite, -1 if none.
 */
int AlienBase::getMarker() const
{
	if (!_discovered)
		return -1;
	return _deployment->getMarkerIcon();
}

/**
 * Changes the country that has a pact with this alien base.
 * @param pactCountry Country ID.
 */
void AlienBase::setPactCountry(const std::string &pactCountry)
{
	_pactCountry = pactCountry;
}

/**
 * Returns the alien race currently residing in the alien base.
 * @return Alien race.
 */
std::string AlienBase::getAlienRace() const
{
	return _race;
}

/**
 * Changes the alien race currently residing in the alien base.
 * @param race Alien race.
 */
void AlienBase::setAlienRace(const std::string &race)
{
	_race = race;
}

void AlienBase::setDeployment(AlienDeployment *deployment)
{
	_deployment = deployment;

	// allow spawning hunt missions immediately after the base is upgraded, i.e. no initial delay
	_minutesSinceLastHuntMissionGeneration = _deployment->getHuntMissionMaxFrequency();
}

}
