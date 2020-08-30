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
#include <utility>
#include "../Mod/RuleCraft.h"

namespace OpenXcom
{

typedef std::pair<std::string, int> CraftId;

class RuleItem;
class Base;
class Soldier;
class CraftWeapon;
class ItemContainer;
class Mod;
class SavedGame;
class Vehicle;
class RuleStartingCondition;

enum UfoDetection : int;

/**
 * Represents a craft stored in a base.
 * Contains variable info about a craft like
 * position, fuel, damage, etc.
 * @sa RuleCraft
 */
class Craft final : public MovingTarget
{
private:
	const RuleCraft *_rules;
	Base *_base;
	int _fuel, _damage, _shield, _interceptionOrder, _takeoff;
	std::vector<CraftWeapon*> _weapons;
	ItemContainer *_items;
	std::vector<Vehicle*> _vehicles;
	std::string _status;
	bool _lowFuel, _mission, _inBattlescape, _inDogfight;
	double _speedMaxRadian;
	RuleCraftStats _stats;
	bool _isAutoPatrolling;
	double _lonAuto, _latAuto;
	std::vector<int> _pilots;

	void recalcSpeedMaxRadian();

	using MovingTarget::load;
public:
	/// Creates a craft of the specified type.
	Craft(const RuleCraft *rules, Base *base, int id = 0);
	/// Cleans up the craft.
	~Craft();
	/// Loads the craft from YAML.
	void load(const YAML::Node& node, const Mod *mod, SavedGame *save);
	/// Finishes loading the craft from YAML (called after all other XCOM craft are loaded too).
	void finishLoading(const YAML::Node& node, SavedGame *save);
	/// Saves the craft to YAML.
	YAML::Node save() const override;
	/// Loads a craft ID from YAML.
	static CraftId loadId(const YAML::Node &node);
	/// Gets the craft's type.
	std::string getType() const override;
	const RuleCraft *getRules() const { return _rules; } /// @return Pointer to the ruleset for the craft's type.
	/// Sets the craft's ruleset.
	void changeRules(RuleCraft *rules);
	/// Gets the craft's default name.
	std::string getDefaultName(Language *lang) const override;
	/// Gets the craft's marker sprite.
	int getMarker() const override;
	Base *getBase() const { return _base; } /// @return Pointer to the base the craft belongs to.
	/// Sets the craft's base.
	void setBase(Base *base, bool move = true);
	/// Gets the craft's status.
	std::string getStatus() const;
	/// Sets the craft's status.
	void setStatus(const std::string &status);
	/// Gets the craft's altitude.
	std::string getAltitude() const;
	/// Sets the craft's destination.
	void setDestination(Target *dest) override;
	bool getIsAutoPatrolling() const { return _isAutoPatrolling; } /// @return whether craft is on auto patrol
	void setIsAutoPatrolling(bool isAuto) { _isAutoPatrolling = isAuto; } /// @param isAuto whether craft is on auto patrol
	double getLongitudeAuto() const { return _lonAuto; } /// @return auto patrol longitude.
	void setLongitudeAuto(double lon) { _lonAuto = lon; } /// @param lon auto patrol longitude. 
	double getLatitudeAuto() const { return _latAuto; } /// @return auto patrol latitude.
	void setLatitudeAuto(double lat) { _latAuto = lat; } /// @param lat auto patrol latitude.
	/// Gets the craft's amount of weapons.
	int getNumWeapons(bool onlyLoaded = false) const;
	/// Gets the craft's amount of soldiers.
	int getNumSoldiers() const;
	/// Gets the craft's amount of equipment.
	int getNumEquipment() const;
	/// Gets the craft's amount of vehicles.
	int getNumVehicles() const;
	/// Gets the craft's weapons.
	std::vector<CraftWeapon*> *getWeapons();
	/// Gets the craft's items.
	ItemContainer *getItems();
	/// Gets the craft's vehicles.
	std::vector<Vehicle*> *getVehicles();

	/// Gets the total storage size of all items in the craft. Including vehicles+ammo and craft weapons+ammo.
	double getTotalItemStorageSize(const Mod* mod) const;
	/// Gets the total number of items of a given type in the craft. Including vehicles+ammo and craft weapons+ammo.
	int getTotalItemCount(const RuleItem* item) const;

	/// Update the craft's stats.
	void addCraftStats(const RuleCraftStats& s);
	/// Gets the craft's stats.
	const RuleCraftStats& getCraftStats() const;
	/// Gets the craft's max amount of fuel.
	int getFuelMax() const;
	int getFuel() const { return _fuel; } /// @return the amount of fuel currently contained in this craft.
	/// Sets the craft's amount of fuel.
	void setFuel(int fuel);
	/// Gets the craft's percentage of fuel.
	int getFuelPercentage() const;
	/// Gets the craft's max amount of damage.
	int getDamageMax() const;
	int getDamage() const { return _damage; } /// @return the amount of damage this craft has taken.
	/// Sets the craft's amount of damage.
	void setDamage(int damage);
	/// Gets the craft's percentage of damage.
	int getDamagePercentage() const;
	/// Gets the craft's max shield capacity
	int getShieldCapacity () const;
	int getShield() const { return _shield; } /// @return shield points this craft has remaining.
	/// Sets the craft's shield remaining
	void setShield(int shield);
	/// Gets the percent shield remaining
	int getShieldPercentage() const;
	bool getLowFuel() const { return _lowFuel; } /// @return whether the craft is currently low on fuel (only has enough to head back to base).
	void setLowFuel(bool low) { _lowFuel = low; } /// @param low whether the craft is currently low on fuel (only has enough to head back to base).
	bool getMissionComplete() const { return _mission; } /// @return whether the craft has just done a ground mission, and is forced to return to base.
	void setMissionComplete(bool mission) { _mission = mission; } // @param mission whether the craft has just done a ground mission, and is forced to return to base.
	/// Gets the craft's distance from its base.
	double getDistanceFromBase() const;
	/// Gets the craft's fuel consumption at a certain speed.
	int getFuelConsumption(int speed, int escortSpeed) const;
	/// Gets the craft's minimum fuel limit.
	int getFuelLimit() const;
	/// Gets the craft's minimum fuel limit to go to a base.
	int getFuelLimit(Base *base) const;

	double getBaseRange() const;
	/// Returns the craft to its base.
	void returnToBase();
	/// Returns the crew to their base (using transfers).
	void evacuateCrew(const Mod *mod);
	/// Checks if a target is detected by the craft's radar.
	UfoDetection detect(const Ufo *target, bool alreadyTracked) const;
	/// Handles craft logic.
	bool think();
	/// Does a craft full checkup.
	void checkup();
	/// Consumes the craft's fuel.
	void consumeFuel(int escortSpeed);
	/// Calculates the time to repair
	unsigned int calcRepairTime();
	/// Calculates the time to refuel
	unsigned int calcRefuelTime();
	/// Calculates the time to rearm
	unsigned int calcRearmTime();
	/// Repairs the craft.
	void repair();
	/// Refuels the craft.
	void refuel();
	/// Rearms the craft.
	const RuleItem* rearm();
	/// Sets the craft's battlescape status.
	void setInBattlescape(bool inbattle);
	bool isInBattlescape() const { return _inBattlescape; } /// @return Is the craft currently in battle?
	/// Gets if craft is destroyed during dogfights.
	bool isDestroyed() const;
	/// Gets the amount of space available inside a craft.
	int getSpaceAvailable() const;
	/// Gets the amount of space used inside a craft.
	int getSpaceUsed() const;
	/// Checks if there are only permitted soldier types onboard.
	bool areOnlyPermittedSoldierTypesOnboard(const RuleStartingCondition* sc);
	/// Checks if there are enough required items onboard.
	bool areRequiredItemsOnboard(const std::map<std::string, int>& requiredItems);
	/// Destroys given required items.
	void destroyRequiredItems(const std::map<std::string, int>& requiredItems);
	/// Checks if there are enough pilots onboard.
	bool arePilotsOnboard();
	/// Checks if a pilot is already on the list.
	bool isPilot(int pilotId);
	/// Adds a pilot to the list.
	void addPilot(int pilotId);
	/// Removes all pilots from the list.
	void removeAllPilots();
	/// Gets the list of craft pilots.
	const std::vector<Soldier*> getPilotList(bool autoAdd);
	/// Calculates the accuracy bonus based on pilot skills.
	int getPilotAccuracyBonus(const std::vector<Soldier*> &pilots, const Mod *mod) const;
	/// Calculates the dodge bonus based on pilot skills.
	int getPilotDodgeBonus(const std::vector<Soldier*> &pilots, const Mod *mod) const;
	/// Calculates the approach speed modifier based on pilot skills.
	int getPilotApproachSpeedModifier(const std::vector<Soldier*> &pilots, const Mod *mod) const;
	/// Gets the craft's vehicles of a certain type.
	int getVehicleCount(const std::string &vehicle) const;
	bool isInDogfight() const { return _inDogfight; } /// @return Is the craft ion a dogfight?
	void setInDogfight(const bool inDogfight) { _inDogfight = inDogfight; } /// @param inDogFight Is the craft ion a dogfight?
	int getInterceptionOrder() const { return _interceptionOrder; } /// @return Interception order (first to leave base 1, second 2, ...)
	void setInterceptionOrder(const int order) { _interceptionOrder = order; } /// @param order Interception order (first to leave base 1, second 2, ...)
	/// Gets the craft's unique id.
	CraftId getUniqueId() const;
	/// Unloads the craft.
	void unload();
	/// Reuses a base item.
	void reuseItem(const RuleItem* item);
	/// Gets the attraction value of the craft for alien hunter-killers.
	int getHunterKillerAttraction(int huntMode) const;
};

}
