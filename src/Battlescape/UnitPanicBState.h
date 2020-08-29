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
#include "BattleState.h"

namespace OpenXcom
{

class BattleUnit;

/**
 * State for panicking units.
 */
class UnitPanicBState final : public BattleState
{
private:
	BattleUnit *_unit;
	bool _berserking;
	int _shotsFired;
public:
	/// Creates a new UnitPanicBState class
	UnitPanicBState(BattlescapeGame *parent, BattleUnit *unit) noexcept;
	/// Cleans up the UnitPanicBState.
	~UnitPanicBState() = default;
//	void init() override; // no-op initialization
//	void cancel() override; // panic cannot be cancelled
	/// Runs state functionality every cycle.
	void think() override;
};

}
