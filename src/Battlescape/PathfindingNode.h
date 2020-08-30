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
#include "Position.h"

namespace OpenXcom
{

class PathfindingOpenSet;
struct OpenSetEntry;

/**
 * A class that holds pathfinding info for a certain node on the map.
 */
class PathfindingNode
{
private:
	Position _pos;
	bool _checked;
	int _tuCost;
	PathfindingNode* _prevNode; /// owner is Pathfinding class
	int _prevDir;
	/// Approximate cost to reach goal position.
	int _tuGuess;
	// Invasive field needed by PathfindingOpenSet
	OpenSetEntry *_openentry; /// owner is PathfindingOpenSet
	friend class PathfindingOpenSet;
public:
	/// Creates a new PathfindingNode class.
	PathfindingNode(Position pos) noexcept;
	/// Cleans up the PathfindingNode.
	~PathfindingNode() = default;
	Position getPosition() const { return _pos; } /// @return Node position.
	/// Resets the node.
	void reset();
	bool isChecked() const { return _checked; } /// @return True, if and only if this node was checked.
	/// Marks the node as checked.
	void setChecked() { _checked = true; }
	/// Gets the TU cost.
	int getTUCost(bool missile) const;
	PathfindingNode* getPrevNode() const { return _prevNode; } /// @return Pointer to the previous node.
	int getPrevDir() const { return _prevDir; } /// @return the previous walking direction, i.e. how we got on this node.
	/// Is this node already in a PathfindingOpenSet?
	bool inOpenSet() const { return (_openentry != 0); }
	/// Gets the approximate cost to reach the target position.
	int getTUGuess() const { return _tuGuess; }

	#ifdef __MORPHOS__
	#undef connect
	#endif

	/// Connects to previous node along the path.
	void connect(int tuCost, PathfindingNode* prevNode, int prevDir, Position target);
	/// Connects to previous node along a visit.
	void connect(int tuCost, PathfindingNode* prevNode, int prevDir);
};

/**
 * Compares PathfindingNode pointers based on TU cost.
 */
class MinNodeCosts
{
public:
	/**
	 * Compares nodes @a *a and @a *b.
	 * @param a Pointer to first node.
	 * @param b Pointer to second node.
	 * @return True if node @a *a must come before @a *b.
	 */
	bool operator()(const PathfindingNode *a, const PathfindingNode *b) const
	{
		return a->getTUCost(false) < b->getTUCost(false);
	}
};

}
