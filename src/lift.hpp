#pragma once
// https://www.codewars.com/kata/58905bfa1decb981da00009e/
#include <algorithm>
#include <iostream>
#include <vector>

using Floor = int;
using Queue = std::vector<Floor>;
using Queues = std::vector<Queue>;
class Lift {
public:
  Queue work(Queues queues, size_t capacity) {
    print(queues, capacity);
    top_floor_ = static_cast<Floor>(queues.size() - 1);
    while (true) {
      bool did_stop = unload();
      change_dir_at_end();
      did_stop |= load(queues[floor_], capacity);
      bool finished = is_finished(queues);
      log_floor(did_stop || finished);
      move_to_next();
      if (finished)
        break;
    }
    return log_;
  }

private:
  void print(Queues queues, size_t capacity) {
    std::cout << "capacity: " << capacity << std::endl;
    for (auto q : queues) {
      std::cout << "{";
      for (auto e : q) {
        std::cout << e << ",";
      }
      std::cout << "}" << std::endl;
    }
  }
  bool unload() {
    const auto old_end = cargo_.end();
    return old_end !=
           cargo_.erase(std::remove(cargo_.begin(), cargo_.end(), floor_),
                        old_end);
  }
  void change_dir_at_end() {
    if ((dir_ > 0 && floor_ == top_floor_) ||
        (dir_ < 0 && floor_ == bottom_floor_))
      dir_ *= -1;
  }
  bool load(Queue &queue, size_t capacity) {
    bool did_stop = false;
    for (auto it = queue.begin(); it != queue.end();) {
      if ((dir_ > 0 && *it > floor_) || (dir_ < 0 && *it < floor_)) {
        did_stop = true;
        if (cargo_.size() < capacity) {
          cargo_.push_back(*it);
          it = queue.erase(it);
          continue;
        }
      }
      ++it;
    }
    return did_stop;
  }
  bool is_finished(Queues queues) {
    return (floor_ == 0 && cargo_.empty() &&
            std::all_of(queues.begin(), queues.end(),
                        [](const auto &q) { return q.empty(); }));
  }
  void log_floor(bool should_log) {
    if (should_log && log_.back() != floor_)
      log_.push_back(floor_);
  }
  void move_to_next() { floor_ += 1 * dir_; }
  const Floor bottom_floor_ = 0;
  Floor top_floor_ = 0;
  Queue log_{bottom_floor_};
  Queue cargo_{};
  Floor floor_{bottom_floor_};
  Floor dir_{+1};
};

Queue the_lift(Queues queues, size_t capacity) {
  return Lift().work(queues, capacity);
}
