#ifndef __can__h__
#define __can__h__

#include "mbed.h"
#include <vector>

#define CAN_RD (PD_0)
#define CAN_TD (PD_1)
#define CAN_RX_INT_FLAG (1UL << 0)
#define CAN_STOP (1UL << 1)
#define CAN_FREQ (125000)


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

  Can(CAN* canBus);
  ~Can();
  void add(device *d) { 
      devices.push_back(d); 
      printf("Device added\n");
      printf("%d\n", devices.size());
    }
  void interrupt();
  void canThread();
  void reset();
  int read(CANMessage &msg);
  int send(unsigned int id, char *data, unsigned int len);

private:
  EventFlags eventFlags;
  CAN* canBus;
  bool isInit;
  Thread t;
  vector<device *> devices;
};

#endif