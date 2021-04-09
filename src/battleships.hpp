#pragma once
// https://www.codewars.com/kata/52bb6539a4cf1b12d90005b7/
#include <algorithm>
#include <vector>

using Field = std::vector<std::vector<int>>;
using Ship = std::vector<std::pair<size_t, size_t>>;

bool identify_ships(const Field &field, std::vector<Ship> &ships) {
  Field cluster_ids{}; // wil get initialized with all -1's

  // Perform a region-growing clustering. Left to right, top to bottom
  for (size_t rowIdx = 0; rowIdx < field.size(); ++rowIdx) {
    cluster_ids.emplace_back(std::vector<int>(field[rowIdx].size(), -1));
    for (size_t colIdx = 0; colIdx < field[rowIdx].size(); ++colIdx) {
      // We are interested in checked cells
      if (!field[rowIdx][colIdx])
        continue;

      // Check neighbors for existing id
      const auto left_id = colIdx > 0 ? cluster_ids[rowIdx][colIdx - 1] : -1;
      const auto upper_id = rowIdx > 0 ? cluster_ids[rowIdx - 1][colIdx] : -1;
      const auto upper_left_id =
          rowIdx > 0 && colIdx > 0 ? cluster_ids[rowIdx - 1][colIdx - 1] : -1;
      const auto upper_right_id =
          rowIdx > 0 && colIdx < field[rowIdx].size() - 1
              ? cluster_ids[rowIdx - 1][colIdx + 1]
              : -1;
      const auto neighbors = {left_id, upper_id, upper_left_id, upper_right_id};
      const auto num_neighbors_alive =
          std::count_if(neighbors.begin(), neighbors.end(),
                        [](const auto &i) { return i != -1; });
      if (num_neighbors_alive > 1)
        return false; // This can only happen if ships are touching. Not ok.
      int cluster_id = std::max(neighbors);

      // If neighbors are not part of cluster yet, create new cluster
      if (cluster_id == -1) {
        ships.emplace_back(Ship());
        cluster_id = ships.size() - 1;
      }

      // Remember
      cluster_ids[rowIdx][colIdx] = cluster_id;
      ships[cluster_id].emplace_back(std::make_pair(rowIdx, colIdx));
    }
  }
  return true;
}

bool is_ship_straight(const Ship &ship) {
  // Ships must be straight, running either along x or y axis
  bool all_x_same = std::all_of(ship.begin(), ship.end(), [&](const auto &p) {
    return p.first == ship[0].first;
  });
  bool all_y_same = std::all_of(ship.begin(), ship.end(), [&](const auto &p) {
    return p.second == ship[0].second;
  });
  return all_x_same || all_y_same;
}

bool are_ships_straight(const std::vector<Ship> &ships) {
  // Are all ships valid in them selfs?
  return std::all_of(ships.begin(), ships.end(), is_ship_straight);
}

bool are_ship_lengths_valid(const std::vector<Ship> &ships) {
  // There must be
  // - 1 battleship (size of 4 cells)
  // - 2 cruisers (size 3)
  // - 3 destroyers (size 2)
  // - 4 submarines (size 1)
  // Any additional ships are not allowed, nor are missing ships.
  std::vector<size_t> ship_lengths(5, 0);
  for (const Ship &ship : ships) {
    ++ship_lengths[ship.size()];
  }
  return ship_lengths == std::vector<size_t>{0, 4, 3, 2, 1};
}

bool validate_battlefield(const Field &field) {
  std::vector<Ship> ships{};
  bool are_ships_valid = identify_ships(field, ships);
  return are_ships_valid && are_ships_straight(ships) &&
         are_ship_lengths_valid(ships);
}