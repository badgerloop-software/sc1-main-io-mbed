#include "mbed.h"
#include <vector>

#define CAN_RD (PD_0)
#define CAN_TD (PD_1)
#define CAN_RX_INT_FLAG (1UL << 0)
#define CAN_STOP (1UL << 1)
#define CAN_FREQ (115200)

// Locks a mutex when constructed, unlocks when out of scope
// https://os.mbed.com/docs/mbed-os/v6.5/feature-i2c-doxy/_lock_guard_8h_source.html#l00028
class LockGuard {
  Mutex &_mutex;
  // make non-copyable
  LockGuard(const LockGuard &) = delete;
  LockGuard &operator=(const LockGuard &) = delete;

public:
  LockGuard(Mutex &mutex) : _mutex(mutex) { _mutex.lock(); }
  ~LockGuard() { _mutex.unlock(); }
};

class Can {
public:
  class device {
  private:
    Can &_c;

  public:
    device(Can &c) : _c(c) { _c.add(this); }

    /*
      Must return 0 on success and nonzero on failure.
      If 0 is returned, no other devices see this message.
    */
    virtual int callback(CANMessage &msg) = 0;
  };

  Can();
  void add(device *d) { devices.push_back(d); }
  void interrupt();
  void canThread();
  int init();
  int read(CANMessage &msg);
  int send(unsigned int id, char *data, unsigned int len);

private:
  CAN canBus;
  EventFlags eventFlags;
  bool isInit;
  Thread t;
  Mutex mu;
  vector<device *> devices;
};
