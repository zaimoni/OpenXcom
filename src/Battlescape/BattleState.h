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
#include "BattlescapeGame.h"

namespace OpenXcom
{

/**
 * This class sets the battlescape in a certain sub-state.
 * These states can be triggered by the player or the AI.
 */
class BattleState
{
protected:
	BattlescapeGame *_parent; /// Pointer to the parent state.
	BattleAction _action; /// Struct containing info about the action.

	/// Creates a new BattleState linked to the game.
	BattleState(BattlescapeGame* parent, BattleAction action) : _parent(parent), _action(action) {}
	/// Creates a new BattleState linked to the game.
	BattleState(BattlescapeGame* parent) noexcept : _parent(parent) {}

	// disallow public slicing copy
	BattleState(const BattleState &src) = default;
	BattleState(BattleState &&src) = default;
	BattleState& operator=(const BattleState& src) = default;
	BattleState& operator=(BattleState && src) = default;
public:
	/// Cleans up the BattleState.
	virtual ~BattleState() = default;
	/// Initializes the state.
	virtual void init();
	/// Called when the state gets popped out.
	virtual void deinit();
	/// Handles a cancel request.
	virtual void cancel();
	/// Runs state functionality every cycle.
	virtual void think();
	/// Gets a copy of the action.
	const BattleAction& getAction() const { return _action; }
};

}
