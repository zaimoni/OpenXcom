#pragma once
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
#include "Target.h"

namespace OpenXcom
{

class AlienDeployment;

/**
 * Represents an alien base on the world.
 */
class AlienBase final : public Target
{
private:
	std::string _pactCountry;
	std::string _race;
	bool _inBattlescape, _discovered;
	AlienDeployment *_deployment;
	int _startMonth;
	int _minutesSinceLastHuntMissionGeneration;
	int _genMissionCount;
public:
	/// Creates an alien base.
	AlienBase(AlienDeployment *deployment, int startMonth);
	/// Cleans up the alien base.
	~AlienBase() = default;
	/// Loads the alien base from YAML.
	void load(const YAML::Node& node) override;
	/// Saves the alien base to YAML.
	YAML::Node save() const override;
	/// Gets the alien base's type.
	std::string getType() const override;
	/// Gets the alien base's marker sprite.
	int getMarker() const override;
	const std::string &getPactCountry() const { return _pactCountry; } /// @return alien base's pact Country ID.
	/// Sets the alien base's pact country.
	void setPactCountry(const std::string &pactCountry);
	/// Gets the alien base's amount of active hours.
	std::string getAlienRace() const;
	/// Sets the alien base's alien race.
	void setAlienRace(const std::string &race);
	void setInBattlescape(bool inbattle) { _inBattlescape = inbattle; } /// @param inbattle True if and only if it's in battle.
	bool isInBattlescape() const { return _inBattlescape; } /// @return Is the base on the battlescape?
	bool isDiscovered() const { return _discovered; } /// @return Has the base been discovered?
	void setDiscovered(bool discovered) { _discovered = discovered; } /// @param discovered True if and only if the base been discovered.
	AlienDeployment *getDeployment() const { return _deployment; } /// @return Pointer to alien base's deployment rules.

	void setDeployment(AlienDeployment *deployment);

	/// Gets the month on which the base spawned.
	int getStartMonth() const { return _startMonth; }
	int getMinutesSinceLastHuntMissionGeneration() const { return _minutesSinceLastHuntMissionGeneration; } /// @return Number of minutes since the last hunt mission was generated.
	void setMinutesSinceLastHuntMissionGeneration(int newValue) { _minutesSinceLastHuntMissionGeneration = newValue; } /// @param newValue Number of minutes, since the last hunt mission was generated.
	int getGenMissionCount() const { return _genMissionCount; } /// @return Number of missions generated so far by this base.
	void setGenMissionCount(int newValue) { _genMissionCount = newValue; } /// @param newValue Number of missions.


};

}
