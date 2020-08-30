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

class RuleAlienMission;
class AlienDeployment;

/**
 * Represents an alien mission site on the world.
 */
class MissionSite final : public Target
{
private:
	const RuleAlienMission *_rules;
	const AlienDeployment *_deployment;
	const AlienDeployment *_missionCustomDeploy;
	int _texture;
	size_t _secondsRemaining;
	std::string _race, _city;
	bool _inBattlescape, _detected;
public:
	/// Creates a mission site.
	MissionSite(const RuleAlienMission *rules, const AlienDeployment *deployment, const AlienDeployment *alienWeaponDeploy) noexcept;
	/// Cleans up the mission site.
	~MissionSite() = default;
	/// Loads the mission site from YAML.
	void load(const YAML::Node& node) override;
	/// Saves the mission site to YAML.
	YAML::Node save() const override;
	/// Gets the waypoint's type.
	std::string getType() const override;
	const RuleAlienMission* getRules() const { return _rules; } /// @return Pointer to ruleset for the mission's type.
	const AlienDeployment* getDeployment() const { return _deployment; } /// @return Pointer to mission site's deployment rules.
	const AlienDeployment* getMissionCustomDeploy() const { return _missionCustomDeploy; } /// @return mission's optional custom deployment of weapons.
	/// Gets the mission site's marker name.
	std::string getMarkerName() const override;
	/// Gets the mission site's marker sprite.
	int getMarker() const override;
	size_t getSecondsRemaining() const { return _secondsRemaining; } /// @return number of seconds remaining, until this mission site expires.
	void setSecondsRemaining(size_t seconds) { _secondsRemaining = seconds; } /// @param seconds until this mission site expires.
	/// Gets the mission site's alien race.
	std::string getAlienRace() const;
	/// Sets the mission site's alien race.
	void setAlienRace(const std::string &race);
	void setInBattlescape(bool inbattle) { _inBattlescape = inbattle; } /// @param inbattle True if and only if it's in battle.
	bool isInBattlescape() const  { return _inBattlescape; } /// @return Is the mission currently in battle?
	int getTexture() const { return _texture; } /// @return mission site's Texture ID.
	void setTexture(int texture) { _texture = texture; } /// @param texture mission site's new Texture ID.
	/// Gets the mission site's city.
	std::string getCity() const;
	/// Sets the mission site's city.
	void setCity(const std::string &city);
	/// used for popups of sites spawned directly, rather than by UFOs.
	bool getDetected() const { return _detected; } /// @return whether or not this site has been detected.
	void setDetected(bool detected) { _detected = detected; } /// @param detected whether we want this site to show on the geoscape or not.
};

}
