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

#include "MovingTarget.h"
#include "Craft.h"
#include "../Mod/RuleUfo.h"

namespace OpenXcom
{

class AlienMission;
class UfoTrajectory;
class SavedGame;
class Mod;
class Waypoint;

enum UfoDetection : int
{
	DETECTION_NONE = 0x00,
	DETECTION_RADAR = 0x01,
	DETECTION_HYPERWAVE = 0x03,
};

/**
 * Represents an alien UFO on the map.
 * Contains variable info about a UFO like
 * position, damage, speed, etc.
 * @sa RuleUfo
 */
class Ufo final : public MovingTarget
{
public:
	static const char *ALTITUDE_STRING[];
	enum UfoStatus { FLYING, LANDED, CRASHED, DESTROYED };

	/// Name of class used in script.
	static constexpr const char *ScriptName = "Ufo";
	/// Register all useful function used by script.
	static void ScriptRegister(ScriptParserBase* parser);

private:
	const RuleUfo *_rules;
	int _uniqueId;
	int _missionWaveNumber;
	int _crashId, _landId, _damage;
	std::string _direction, _altitude;
	enum UfoStatus _status;
	size_t _secondsRemaining;
	bool _inBattlescape;
	CraftId _shotDownByCraftId;
	AlienMission *_mission;
	const UfoTrajectory *_trajectory;
	size_t _trajectoryPoint;
	bool _detected, _hyperDetected, _processedIntercept;
	int _shootingAt, _hitFrame, _fireCountdown, _escapeCountdown;
	RuleUfoStats _stats;
	/// Calculates a new speed vector to the destination.
	void calculateSpeed() override;
	int _shield, _shieldRechargeHandle;
	int _tractorBeamSlowdown;
	bool _isHunterKiller, _isEscort;
	int _huntMode, _huntBehavior;
	bool _isHunting, _isEscorting;
	Waypoint *_origWaypoint;

	using MovingTarget::load;
	using MovingTarget::save;

	void backupOriginalDestination();
public:
	/// Creates a UFO of the specified type.
	Ufo(const RuleUfo *rules, int uniqueId, int hunterKillerPercentage = 0, int huntMode = 0, int huntBehavior = 0);
	/// Cleans up the UFO.
	~Ufo();
	/// Loads the UFO from YAML.
	void load(const YAML::Node& node, const Mod &ruleset, SavedGame &game);
	/// Finishes loading the UFO from YAML (called after XCOM craft are loaded).
	void finishLoading(const YAML::Node& node, SavedGame &save);
	/// Saves the UFO to YAML.
	YAML::Node save(bool newBattle) const;
	/// Saves the UFO's ID to YAML.
	YAML::Node saveId() const override;
	/// Gets the UFO's type.
	std::string getType() const override;
	const RuleUfo *getRules() const { return _rules; } /// @return Pointer to ruleset for the UFO's type.
	/// @param rules Pointer to ruleset.
	/// @warning ONLY FOR NEW BATTLE USE!
	void changeRules(const RuleUfo *rules) { _rules = rules; }
	int getUniqueId() const { return _uniqueId; } /// @return UFO's unique ID.
	/// Gets the mission wave number that created this UFO.
	int getMissionWaveNumber() const { return _missionWaveNumber; }
	/// Sets the mission wave number that created this UFO.
	void setMissionWaveNumber(int missionWaveNumber) { _missionWaveNumber = missionWaveNumber; }
	/// Gets the UFO's default name.
	std::string getDefaultName(Language *lang) const override;
	/// Gets the UFO's marker name.
	std::string getMarkerName() const override;
	/// Gets the UFO's marker ID.
	int getMarkerId() const override;
	/// Gets the UFO's marker sprite.
	int getMarker() const override;
	int getDamage() const { return _damage; } /// @return Amount of damage this UFO has taken.
	/// Sets the UFO's amount of damage.
	void setDamage(int damage, const Mod *mod);
	bool getDetected() const { return _detected; } /// @return whether this UFO has been detected by radars.
	void setDetected(bool detected) { _detected = detected; } /// @param detected whether this UFO has been detected by radars.
	size_t getSecondsRemaining() const { return _secondsRemaining; } /// @return seconds the UFO has left on the ground, before taking off or disappearing
	void setSecondsRemaining(size_t seconds) { _secondsRemaining = seconds; } /// @param seconds the UFO has left on the ground, before taking off or disappearing
	/// Gets the UFO's direction.
	std::string getDirection() const;
	/// Gets the UFO's altitude.
	std::string getAltitude() const;
	/// Gets the UFO's altitude.
	int getAltitudeInt() const;
	/// Sets the UFO's altitude.
	void setAltitude(const std::string &altitude);
	/// Gets the UFO status
	enum UfoStatus getStatus() const { return _status; }
	/// Set the UFO's status.
	void setStatus(enum UfoStatus status) {_status = status; }
	/// Gets if the UFO has crashed.
	bool isCrashed() const;
	/// Gets if the UFO has been destroyed.
	bool isDestroyed() const;
	/// Handles UFO logic.
	void think();
	/// Sets the UFO's battlescape status.
	void setInBattlescape(bool inbattle);
	bool isInBattlescape() const { return _inBattlescape; } /// @return Is the UFO currently in battle?
	/// Gets the UFO's alien race.
	const std::string &getAlienRace() const;
	/// Sets the ID of craft which shot down the UFO.
	void setShotDownByCraftId(const CraftId& craft) { _shotDownByCraftId = craft; }
	/// Gets the ID of craft which shot down the UFO.
	CraftId getShotDownByCraftId() const { return _shotDownByCraftId; }
	/// Gets the UFO's visibility.
	int getVisibility() const;
	/// Gets the UFO's Mission type.
	const std::string &getMissionType() const;
	/// Sets the UFO's mission information.
	void setMissionInfo(AlienMission *mission, const UfoTrajectory *trajectory);
	bool getHyperDetected() const { return _hyperDetected; } /// @return whether this UFO has been detected by hyper-wave.
	void setHyperDetected(bool hyperdetected) { _hyperDetected = hyperdetected; } /// @param whether this UFO has been detected by hyper-wave.
	/// Gets the UFO's progress on the trajectory track.
	size_t getTrajectoryPoint() const { return _trajectoryPoint; }
	/// Sets the UFO's progress on the trajectory track.
	void setTrajectoryPoint(size_t np) { _trajectoryPoint = np; }
	/// Gets the UFO's trajectory.
	const UfoTrajectory &getTrajectory() const { return *_trajectory; }
	/// Gets the UFO's mission object.
	AlienMission *getMission() const { return _mission; }
	/// Gets the Xcom craft targeted by this UFO.
	Craft *getTargetedXcomCraft() const;
	/// Resets the original destination if targeting the given craft.
	void resetOriginalDestination(Craft *target);
	void resetOriginalDestination(bool debugHelper);
	/// Sets the Xcom craft targeted by this UFO.
	void setTargetedXcomCraft(Craft *craft);
	/// Sets the UFO escorted by this UFO.
	void setEscortedUfo(Ufo *ufo);
	/// Sets the UFO's destination.
	void setDestination(Target *dest) override;
	int getShootingAt() const { return _shootingAt; } /// @return which interception window the UFO is active in, i.e. which interceptor this UFO is engaging.
	void setShootingAt(int target) { _shootingAt = target; } /// @param target which interception window the UFO is active in, i.e. which interceptor this UFO is engaging.
	int getLandId() const { return _landId; } /// @return UFO's landing site ID.
	void setLandId(int id) { _landId = id; } /// @param id UFO's landing site ID.
	int getCrashId() const { return _crashId; } /// @return the UFO's crash site ID.
	void setCrashId(int id) { _crashId = id; } /// @param id the UFO's crash site ID. 
	int getHitFrame() const { return _hitFrame; } /// @return the UFO's hit frame.
	void setHitFrame(int frame) { _hitFrame = frame; } /// @param frame the UFO's hit frame.
	const RuleUfoStats& getCraftStats() const { return _stats; } /// @return the UFO's stats.
	int getEscapeCountdown() const { return _escapeCountdown; } /// @return how many ticks until the UFO tries to escape the dogfight
	void setEscapeCountdown(int time) { _escapeCountdown = time; } /// @param time how many ticks until the UFO tries to escape the dogfight 
	int getFireCountdown() const { return _fireCountdown; } /// @return ticks until the UFO's weapon is ready to fire
	void setFireCountdown(int time) { _fireCountdown = time; } /// @param time ticks until the UFO's weapon is ready to fire
	bool getInterceptionProcessed() const { return _processedIntercept; } /// @return whether the ufo has had its timers decremented on this cycle of interception updates.
	/// <summary>
	/// Sets a flag denoting that this ufo has had its timers decremented.
	/// prevents multiple interceptions from decrementing or resetting an already running timer.
	/// this flag is reset in advance each time the geoscape processes the dogfights.
	/// </summary>
	void setInterceptionProcessed(bool processed) { _processedIntercept = processed; } /// @param processed whether the ufo has had its timers decremented on this cycle of interception updates.
	int getShield() const { return _shield; } /// @return UFO's remaining shield points
	/// Sets the UFO's shield
	void setShield(int shield);
	int getShieldRechargeHandle() const { return _shieldRechargeHandle; } /// @return which _interceptionNumber handles the UFO's shield recharge in a dogfight
	void setShieldRechargeHandle(int shieldRechargeHandle) { _shieldRechargeHandle = shieldRechargeHandle; } /// @param shieldRechargeHandlewhich _interceptionNumber handles the UFO's shield recharge in a dogfight

	/// Sets the number of tractor beams locked on to a UFO
	void setTractorBeamSlowdown(int tractorBeamSlowdown);
	int getTractorBeamSlowdown() const { return _tractorBeamSlowdown; } /// @return how much this UFO is being slowed down by craft tractor beams (how many there are)
	bool isHunterKiller() const { return _isHunterKiller; } /// @return True if and only if UFO is a hunter-killer.
	void setHunterKiller(bool isHunterKiller) { _isHunterKiller = isHunterKiller; } /// @param isHunterKiller True if and only if UFO is a hunter-killer.
	bool isEscort() const { return _isEscort; } /// @return True if and only if UFO is an escort.
	void setEscort(bool isEscort) { _isEscort = isEscort; } /// @param isEscort True if and only if UFO is an escort. 
	int getHuntMode() const { return _huntMode; } /// @return UFO's hunting preferences ID.
	int getHuntBehavior() const { return _huntBehavior; } /// @return UFO's hunting behavior ID.
	bool isHunting() const { return _isHunting; } /// @return True if and only if the UFO is actively hunting.
	bool isEscorting() const { return _isEscorting; } /// @return True if and only if the UFO is actively escorting.

	/// Checks if a target is inside the UFO's radar range.
	bool insideRadarRange(Target *target) const;
};

}
