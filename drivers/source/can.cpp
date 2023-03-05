#include "can.h"
#include "greentea-client/test_env.h"

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
#if !MBED_TEST_MODE
  canBus.read(msg);
#else
  greentea_parse_kv((char*)msg.data, (char*)&msg.id, sizeof(msg.data), sizeof(msg.id));
#endif
  return 0;
}

int Can::send(unsigned int id, char *data, unsigned int len) {
  CANMessage msg;
  if (init() < 0 || len > sizeof(msg.data))
    return -1;
  LockGuard l(mu);
  msg.id = id;
  memcpy(msg.data, data, len);
#if !MBED_TEST_MODE
  return canBus.write(msg) == 1;
#else
  char* d = (char*)malloc(sizeof(msg.data)+1);
  memcpy(d, msg.data, sizeof(msg.data));
  d[sizeof(msg.data)] = '\0';
  char* i = (char*)malloc(sizeof(msg.data)+1);
  memcpy(i, (char*)&msg.id, sizeof(msg.id));
  i[sizeof(msg.id)] = '\0';
  greentea_send_kv(d, i);
#endif
  return 0;
}
