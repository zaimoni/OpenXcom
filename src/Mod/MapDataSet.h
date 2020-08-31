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
#include <string>
#include <vector>
#include <SDL.h>
#include <yaml-cpp/yaml.h>
#include "../Mod/MCDPatch.h"

namespace OpenXcom
{

class MapData;
class SurfaceSet;

/**
 * Represents a Terrain Map Datafile.
 * Which corresponds to an XCom MCD & PCK file.
 * The list of map datafiles is stored in RuleSet, but referenced in RuleTerrain.
 * @sa http://www.ufopaedia.org/index.php?title=MCD
 */
class MapDataSet
{
private:
	std::string _name;
	std::vector<MapData*> _objects;
	SurfaceSet *_surfaceSet;
	bool _loaded;
	static MapData *_blankTile;
	static MapData *_scorchedTile;
public:
	MapDataSet(const std::string &name);
	~MapDataSet();
	/// Loads voxeldata from a DAT file.
	static void loadLOFTEMPS(const std::string &filename, std::vector<Uint16> *voxelData);
	const std::string& getName() const { return _name; } /// @return The dataset name (used for MAP generation).
	/// Gets the dataset size.
	size_t getSize() const;
	/// Gets the objects in this dataset.
	std::vector<MapData*> *getObjectsRaw();
	/// Gets an object in this dataset.
	MapData *getObject(size_t i);
	SurfaceSet *getSurfaceset() const { return _surfaceSet; } /// @return Pointer to the surfaceset, i.e. surfaces in this dataset.
	/// Loads the objects from an MCD file.
	void loadData(MCDPatch *patch, bool validate = true);
	///	Unloads to free memory.
	void unloadData();
	static MapData *getBlankFloorTile() { return _blankTile; } /// @return Pointer to a blank tile.
	static MapData *getScorchedEarthTile() { return _scorchedTile; } /// @return @return Pointer to a scorched earth tile.
};

}
