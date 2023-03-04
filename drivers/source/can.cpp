#include "can.h"

Can::Can() : canBus(CAN_RD, CAN_TD), isInit(false), t(osPriorityHigh) {}

Can::~Can() {
  isInit = 0;
  eventFlags.set(CAN_STOP);
  t.join();
}

void Can::interrupt() { eventFlags.set(CAN_RX_INT_FLAG); }

void Can::canThread() {
  CANMessage msg;
  while (isInit) {
    if (canBus.tderror() || canBus.rderror()) {
      isInit = 0;
      eventFlags.set(CAN_STOP);
      t.join();
      init();
    }
    eventFlags.wait_any(CAN_RX_INT_FLAG | CAN_STOP);
    CANMessage msg;
    if (read(msg) < 0)
      break;
    for (auto d : devices)
      if (!d->callback(msg))
        break;
  }
  isInit = 0;
}

int Can::init() {
  if (isInit)
    return 1;

  canBus.reset();
  canBus.attach(callback(this, &Can::interrupt), CAN::RxIrq);
  if (canBus.frequency(CAN_FREQ) != 1 ||
      t.start(callback(this, &Can::canThread)) != osOK)
    return -1;
  isInit = 1;

  return 0;
}

int Can::read(CANMessage &msg) {
  LockGuard l(mu);
  canBus.read(msg);
  return 0;
}

int Can::send(unsigned int id, char *data, unsigned int len) {
  CANMessage msg;
  if (init() < 0 || len > sizeof(msg.data))
    return -1;
  LockGuard l(mu);
  msg.id = id;
  memcpy(msg.data, data, len);
  return canBus.write(msg) == 1; // returns 1 on success
                                 // we return 0 on success
}
