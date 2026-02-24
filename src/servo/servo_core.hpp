#ifndef SERVO_CORE_HPP
#define SERVO_CORE_HPP

#include <can/can_interface.hpp>
#include <cstdint>
#include <cstring>

namespace servo {
/// @brief サーボ制御のコアロジック（プラットフォーム非依存）
/// @details CAN通信を含まない純粋なデータ処理クラス。
///          CAN送受信は使用者側で行う。
class ServoCore {
 public:
  ServoCore(uint8_t id) : id_(id) { std::memset(data_, 0, sizeof(data_)); }

  CANMessage to_can_message() const {
    CANMessage msg;
    msg.id = id_;
    std::memcpy(msg.data, (uint8_t*)data_, sizeof(data_));
    msg.len = sizeof(data_);
    return msg;
  }

 private:
  bool data_[8];
  uint8_t id_;
};
}  // namespace servo
#endif  // SERVO_CORE_HPP