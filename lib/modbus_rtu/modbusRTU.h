#ifndef MODBUSRTU_H
#define MODBUSRTU_H

#include <Arduino.h>
//#include <assert.h>

#if defined (CORE_TEENSY)
#else
#include <avr/pgmspace.h>
#endif

#define MAX_BUF_SIZE 32

#define ST_IDLE 20
#define ST_RECV 30
#define ST_PROC 40

typedef uint16_t WORD;
// typedef uint8_t BYTE;

// Address defines
#define ADDR_BCAST 0x00

// Function codes
#define FUNC_READ_DISCRETE 2
#define FUNC_READ_COIL 1
#define FUNC_WRITE_COIL 5
#define FUNC_WRITE_MULTICOIL 15
#define FUNC_READ_INPUT 4
#define FUNC_READ_MULTIREG 3
#define FUNC_WRITE_REG 6
#define FUNC_WRITE_MULTIREG 16
#define FUNC_READ_ID 17

// Define some errors
#define EINVADDR -1
#define ECRCFAIL -2

// Define dev types
#define DEV_MASTER
#define DEV_SLAVE

#define DEFAULT_SADDR 1

WORD CRC16 (const uint8_t *nData, WORD wLength);
int encodeRTUFrame(const uint8_t *data, uint8_t dlen, uint8_t *frame, uint8_t slave_addr, uint8_t function_code);
int decodeRTUFrame(const uint8_t *frame, WORD flen, uint8_t *data, uint8_t *slave_addr, uint8_t *function_code);

class modbusRTU
{
    public:
    modbusRTU(Stream &s=Serial):ser(s){}
    void begin(unsigned long baud, uint8_t slaveAddress, uint8_t DEN_PIN);
    void checkMessages();
    WORD readDiscrete(WORD first, WORD count);
    int readInputRegs(WORD first, WORD count, WORD *dst);
    void setInputRegs(WORD *regs, WORD count);
    uint16_t readHoldingRegs(WORD first, WORD count, uint8_t *dst);
    int writeHoldingRegs(WORD first, WORD count, const uint8_t *src);
    void setHoldingRegs(WORD *regs, WORD count);
    
    Stream &ser;
    WORD *inputRegs;
    WORD *holdingRegs;
    WORD NHOLDING;
    WORD NINPUTS;
    uint8_t recv_buf[MAX_BUF_SIZE];
    uint8_t send_buf[MAX_BUF_SIZE];
    uint8_t data_buf[MAX_BUF_SIZE];
    uint8_t sa_recv;
    uint8_t fcode;
    uint8_t saddr;
    uint8_t DEN_PIN_;
    WORD bytes_read;
    unsigned long _baud;
    float byte_time;
    unsigned long t15;
    unsigned long t35;
};


#endif