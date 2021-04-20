#pragma once
// https://www.codewars.com/kata/58905bfa1decb981da00009e/
#include <algorithm>
#include <iostream>
#include <vector>

using Floor = int;
using Passenger = int;
using Queue = std::vector<Passenger>;
enum class Direction : int { UP = 1, DOWN = -1 };

class Lift {
public:
  Lift() = delete;
  Lift(std::vector<Queue> &queues, size_t capacity)
      : m_queues(queues), m_capacity(capacity){};

  bool work() {
    goto_and_log(m_next);
    unload();
    load();
    determine_next_floor();
    return has_work_todo();
  }

  std::vector<Queue> &m_queues;
  size_t m_capacity{};
  std::vector<Passenger> m_passengers{};
  Direction m_direction{Direction::UP};
  Floor m_floor{};
  Floor m_next{0};
  std::vector<Floor> m_log{};

private:
  bool has_work_todo() {
    bool clients_left = std::any_of(m_queues.begin(), m_queues.end(),
                                    [](const auto &q) { return !q.empty(); });
    bool passengers_left = !m_passengers.empty();
    bool has_returned_home = m_log.back() == 0;
    return clients_left || passengers_left || !has_returned_home;
  }

  void goto_and_log(Floor next) {
    m_floor = next;
    if (m_log.empty() || m_log.back() != m_floor)
      m_log.push_back(m_floor);
  }

  void unload() {
    const auto old_end = m_passengers.end();
    const auto new_end =
        std::remove(m_passengers.begin(), m_passengers.end(), m_floor);
    m_passengers.erase(new_end, old_end);
  }

  void load() {
    Queue &queue = m_queues[m_floor];

    bool load_another = true;
    while (is_capacity_left() && load_another) {
      load_another = false;
      const auto passenger =
          std::find_if(queue.begin(), queue.end(), [&](auto desired_floor) {
            if (m_direction == Direction::UP)
              return desired_floor > m_floor;
            else
              return desired_floor < m_floor;
          });
      if (passenger != queue.end()) {
        m_passengers.push_back(*passenger);
        queue.erase(passenger);
        load_another = true;
      }
    }
  }

  bool is_capacity_left() { return m_capacity > m_passengers.size(); }

  bool determine_next_up() {
    Floor passenger_wish = m_queues.size();
    for (auto p : m_passengers)
      if (p < passenger_wish)
        passenger_wish = p;

    Floor client_request = m_queues.size();
    Floor floor = is_capacity_left() ? m_floor : m_floor + 1;
    for (; floor < m_queues.size(); ++floor) {
      if (m_queues[floor].empty())
        continue;
      else if (std::any_of(m_queues[floor].begin(), m_queues[floor].end(),
                           [&](auto f) { return f > floor; })) {
        client_request = floor;
        break;
      }
    }

    m_next = std::min(passenger_wish, client_request);
    return m_next != m_queues.size();
  }

  bool determine_next_down() {
    Floor passenger_wish = -1;
    for (auto p : m_passengers)
      if (p > passenger_wish)
        passenger_wish = p;

    Floor client_request = -1;
    Floor floor = is_capacity_left() ? m_floor : m_floor - 1;
    for (; floor > -1; --floor) {
      if (m_queues[floor].empty())
        continue;
      else if (std::any_of(m_queues[floor].begin(), m_queues[floor].end(),
                           [&](auto f) { return f < floor; })) {
        client_request = floor;
        break;
      }
    }

    m_next = std::max(passenger_wish, client_request);
    return m_next != -1;
  }

  void determine_next_floor() {
    bool has_work = false;

    // Work left in the same direction?
    if (m_direction == Direction::UP) {
      has_work = determine_next_up();
    } else {
      has_work = determine_next_down();
    }

    if (!has_work) {
      // Work left in the other direction?
      if (m_direction == Direction::UP) {
        m_direction = Direction::DOWN;
        m_floor = m_queues.size() - 1;
        has_work = determine_next_down();
      } else {
        m_direction = Direction::UP;
        m_floor = 0;
        has_work = determine_next_up();
      }
    }

    if (!has_work) {
      // Work left in the other direction?
      if (m_direction == Direction::UP) {
        m_direction = Direction::DOWN;
        m_floor = m_queues.size() - 1;
        has_work = determine_next_down();
      } else {
        m_direction = Direction::UP;
        m_floor = 0;
        has_work = determine_next_up();
      }
    }

    if (!has_work) {
      // Go home
      m_direction = Direction::DOWN;
      m_next = 0;
    }
  }
};

std::vector<int> the_lift(std::vector<Queue> queues, int capacity) {
  std::cout << "capacity: " << capacity << std::endl;
  for (auto q : queues) {
    std::cout << "{";
    for (auto e : q) {
      std::cout << e << ",";
    }
    std::cout << "}" << std::endl;
  }
  Lift lift(queues, capacity);
  while (lift.work()) {
  }
  return lift.m_log;
}
