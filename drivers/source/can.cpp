#include "mbed.h"

#define CAN_RD (PD_0)
#define CAN_TD (PD_1)
#define CAN_RX_INT_FLAG (1UL << 0)
#define CAN_STOP (1UL << 1)
#define CAN_FREQ (115200)

// Locks a mutex when constructed, unlocks when out of scope
// https://os.mbed.com/docs/mbed-os/v6.5/feature-i2c-doxy/_lock_guard_8h_source.html#l00028
class LockGuard {
    Mutex& _mutex;
    // make non-copyable
    LockGuard(const LockGuard&) = delete;
    LockGuard& operator=(const LockGuard&) = delete;

    public:
    LockGuard(Mutex& mutex) : _mutex(mutex) {
        _mutex.lock();
    }
    ~LockGuard() {
        _mutex.unlock();
    }
};

class Can {
  CAN canBus;
  Can() : canBus(CAN_RD, CAN_TD), isInit(false), t(osPriorityHigh) {};
  EventFlags eventFlags;
  bool isInit;
  Thread t;
  Mutex mu;

  void interrupt() {
      eventFlags.set(CAN_RX_INT_FLAG);
  }

  void canThread() {
    CANMessage msg;
    while (isInit) {
      if (canBus.tderror() || canBus.rderror()) {
          isInit = 0;
          init();
      }
      eventFlags.wait_any(CAN_RX_INT_FLAG | CAN_STOP);
      CANMessage msg;
      if (read(msg) < 0)
        break;
      // TODO execute callbacks passed in
    }
    isInit = 0;
  }

  int init() {
    if (isInit)
        return 1;
    eventFlags.set(CAN_STOP);
    t.join();

    canBus.reset();
    canBus.attach(callback(this, &Can::interrupt), CAN::RxIrq);
    if (canBus.frequency(CAN_FREQ) != 1 || t.start(callback(this, &Can::canThread)) != osOK)
        return -1;
    isInit = 1;

    return 0;
  }

  template<typename T>
  int send(const T& data) {
      CANMessage msg;
      if (init() < 0 || sizeof(T) > sizeof(msg.data))
        return -1;
    LockGuard l(mu);
    msg.data = data;
    return canBus.write(msg) == 1; // returns 1 on sucess
  }

  int read(CANMessage& msg) {
      LockGuard l(mu);
      canBus.read(msg);
      return 0;
  }
};
