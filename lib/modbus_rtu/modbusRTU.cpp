#include "modbusRTU.h"

#if defined (CORE_TEENSY)
WORD CRC16 (const uint8_t *nData, WORD wLength)
{
    static const WORD wCRCTable[] = {
       0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
       0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
       0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
       0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
       0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
       0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
       0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
       0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
       0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
       0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
       0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
       0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
       0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
       0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
       0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
       0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
       0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
       0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
       0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
       0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
       0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
       0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
       0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
       0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
       0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
       0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
       0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
       0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
       0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
       0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
       0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
       0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040 };

    uint8_t nTemp;
    WORD wCRCWord = 0xFFFF;

    while (wLength--)
    {
        nTemp = *nData++ ^ wCRCWord;
        wCRCWord >>= 8;
        wCRCWord  ^= wCRCTable[nTemp];
    }
    return wCRCWord;
} // End: CRC16

#else

WORD CRC16 (const uint8_t *nData, WORD wLength)
{
    static const WORD wCRCTable[] PROGMEM = {
       0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
       0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
       0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
       0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
       0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
       0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
       0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
       0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
       0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
       0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
       0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
       0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
       0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
       0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
       0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
       0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
       0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
       0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
       0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
       0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
       0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
       0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
       0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
       0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
       0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
       0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
       0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
       0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
       0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
       0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
       0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
       0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040 };

    uint8_t nTemp;
    WORD wCRCWord = 0xFFFF;

    while (wLength--)
    {
        nTemp = *nData++ ^ wCRCWord;
        wCRCWord >>= 8;
        WORD wCRCTableVal = pgm_read_word_near(&(wCRCTable[nTemp]));
        //wCRCWord  ^= wCRCTable[nTemp];
        wCRCWord  ^= wCRCTableVal;
    }
    return wCRCWord;
} // End: CRC16

#endif

int encodeRTUFrame(const uint8_t *data, uint8_t dlen, uint8_t *frame, uint8_t slave_addr, uint8_t function_code)
{
    // Check address for rule violations
    if ((slave_addr >= 248)) return EINVADDR;

    // Address and function codes and data length
    frame[0] = slave_addr;
    frame[1] = function_code;

    // Fill up data
    WORD i;
    for (i=2; i<dlen+2; i++)
        frame[i] = data[i-2];

    // Generate CRC
    WORD crc_val = CRC16(frame, dlen+2);
    //cout << "Generated CRC: " << crc_val << endl;
    frame[i] = crc_val & 0xFF;
    frame[i+1] = (crc_val >> 8) & 0xFF;

    return 0;
}

int decodeRTUFrame(const uint8_t *frame, WORD flen, uint8_t *data, uint8_t *slave_addr, uint8_t *function_code)
{
    // First check CRC
    WORD crc_val = CRC16(frame, flen-2);
    WORD crc_incoming = (frame[flen-1] << 8) | (frame[flen-2]);

    // Serial.print("Frame: ");
    // for(int j=0; j<flen; j++)
    // {
    //     Serial.print(frame[j], HEX);
    //     Serial.print(" ");
    // }
    // Serial.println();
    // Serial.print("CRC (old): ");
    // Serial.print(crc_incoming, HEX);
    // Serial.print("  CRC (new): ");
    // Serial.println(crc_val, HEX);

    //cout << "CRC (old): " << crc_val << "; CRC (new): " << crc_incoming << endl;

    if(crc_incoming != crc_val) return ECRCFAIL;

    // Then check for valid address
    if (((*slave_addr) >= 248)) return EINVADDR;

    //cout << "CRC Pass." << endl;

    // If CRC check passed
    *slave_addr = frame[0];
    *function_code = frame[1];

    WORD i;
    for(i=2; i<flen-2; i++)
        data[i-2] = frame[i];

    return 0;
}

void modbusRTU::begin(unsigned long baud, uint8_t slaveAddress, uint8_t DEN_PIN)
{
    NHOLDING = 0;
    NINPUTS = 0;
    holdingRegs = NULL;
    inputRegs = NULL;
    _baud = baud;
    byte_time = (1.0e6)/baud;
    t15 = (unsigned long) (byte_time*2);
    t35 = (unsigned long) (byte_time*4);
    bytes_read = 0;
    saddr = slaveAddress;
    DEN_PIN_ = DEN_PIN;
    pinMode(DEN_PIN_, OUTPUT);
    digitalWrite(DEN_PIN_, LOW);
    // ser.print("Setting saddr to ");
    // ser.print(slaveAddress);
    // ser.print("New value is ");
    // ser.println(saddr);
}

void modbusRTU::checkMessages()
{ 
    static int8_t state = ST_IDLE;
    int ctr;
    
    // Bytes available to read
    if ( ser.available() > 0 )
    {
        state = ST_RECV;
        ctr = 0;
        sa_recv = 0;
        fcode = 0;
        bytes_read = 0;
        //ser.println("Serial ")
    }

    while (state == ST_RECV)
    {
        if(ser.available())
        {
            recv_buf[ctr++] = ser.read();
        }
        else
        {
            // Wait for a bit
            delayMicroseconds(t15+5);
            // If serial is still not available
            if( ser.available() == 0 )
            {
                //Transmission has ended
                state = ST_PROC;
                bytes_read = ctr;
                // ser.print("Finished reading frame. Bytes read: ");
                // ser.println(bytes_read);
                // ser.print("Frame: ");
                // for(int j=0; j<bytes_read; j++)
                // {
                //     Serial.print(recv_buf[j], HEX);
                //     Serial.print(" ");
                // }
                // Serial.println();
                // for(int j=0; j<bytes_read; j++)
                // {
                //     Serial.print(recv_buf[j], HEX);
                //     Serial.print(" ");
                // }
                // Serial.println();
            }
        }
        // ctr = Serial.readBytes((char *) recv_buf, 200);
        // state = ST_PROC;
    }

    if ( state == ST_PROC )
    {
        // Process the request in the incoming message.
        int ret = decodeRTUFrame(recv_buf, bytes_read, data_buf, &sa_recv, &fcode);
        uint16_t regs_read;
        WORD start;
        WORD count;
        int8_t nb;
        uint8_t resp_[4];

        // If frame decoding was successful
        if(ret >= 0)
        {
            // Serial.println("Frame decoding successful");
            // ser.println("Frame decoding successful.");
            // ser.print("Addr: "); ser.println(sa_recv);
            // ser.print("Function: "); ser.println(fcode);
            // ser.print("Data: ");
            // for(int j=0; j<(bytes_read - 4); j++)
            // {
            //     ser.print(data_buf[j], HEX); 
            //     ser.print(" ");
            // }
            // ser.println();

            if ( sa_recv == 0 )
            {
                // Broadcast address.
                // Handle broadcast specific stuff.
            }
            else if ( sa_recv != saddr )
            {
                // Ignore the message
                state = ST_IDLE;
                // ser.println("Message not addressed to slave.");
                // ser.print("Address of device: ");
                // ser.print(saddr);
                // ser.print("Address of message: ");
                // ser.print(sa_recv);
            }
            else
            {
                switch (fcode)
                {
                    case FUNC_READ_MULTIREG:
                        //ser.println("Reading multiple registers...");
                        //assert((bytes_read - 4) == 4);
                        start = data_buf[1] | (data_buf[0] << 8);
                        count = data_buf[3] | (data_buf[2] << 8);
                        //memcpy(&count, &(data_buf[2]), 2);

                        // ser.print("Reading "); ser.print(count);
                        // ser.print(" words  starting at "); ser.println(start);

                        regs_read = readHoldingRegs(start, count, recv_buf+1);
                        recv_buf[0] = regs_read*2;

                        // ser.print("Holding regs req: ");
                        // for(uint16_t j=0; j<count; j++)
                        // {
                        //     ser.print(recv_buf[2*j]);
                        //     ser.print(" ");
                        //     ser.print(recv_buf[2*j+1]);
                        //     ser.print(" ");
                        // }
                        // ser.println();

                        encodeRTUFrame(recv_buf, regs_read*2 + 1, send_buf, saddr, fcode);
                        digitalWrite(DEN_PIN_, HIGH);
                        for(uint16_t i=0; i<regs_read*2 + 5; i++)
                            ser.write(send_buf[i]);
                        digitalWrite(DEN_PIN_, LOW);
                        ser.flush();
                        break;

                    case FUNC_WRITE_MULTIREG:
                        start = data_buf[1] | (data_buf[0] << 8);
                        count = data_buf[3] | (data_buf[2] << 8);
                        nb = data_buf[4];
                        regs_read = writeHoldingRegs(start, count, data_buf+5);
                        //resp_[4] = {(start >> 8), start & 0xFF, (regs_read>>8), regs_read & 0xFF};
                        resp_[0] = (start >> 8);
                        resp_[1] = start & 0xFF;
                        resp_[2] = (regs_read>>8);
                        resp_[3] = regs_read & 0xFF;
                        encodeRTUFrame(resp_, 4, send_buf, saddr, fcode);

                        if(regs_read == count)
                        {
                            // Return response
                            digitalWrite(DEN_PIN_, HIGH);
                            for(uint16_t i=0; i<8; i++)
                            {
                                ser.write(send_buf[i]);
                            }
                            // for(int i =0; i<8; i++)
                            //     Serial.print(send_buf[i], HEX);
                            // Serial.write('\n');
                            digitalWrite(DEN_PIN_, LOW);
                            ser.flush();
                        }

                        break;

                    case FUNC_READ_ID:
                        break;
                }
                // Use flush to ensure that all the data is written immediately.
                //ser.flush();
                // Wait for after frame delay
                delayMicroseconds(t35);
                state = ST_IDLE;
            }
        }
        else
        {
            ser.print("Error decoding frame. Code: ");
            ser.println(ret);
            // for(int j=0; j<bytes_read; j++)
            // {
            //     ser.print(data_buf[j], HEX);
            //     ser.print(" ");
            // }
            state = ST_IDLE;
        }
    }
}

void modbusRTU::setHoldingRegs(WORD *regs, WORD count)
{
    NHOLDING = count;
    holdingRegs = regs;
}

int modbusRTU::writeHoldingRegs(WORD first, WORD count, const uint8_t *src)
{
    WORD i, j;
    WORD last;

    if(first+count <= NHOLDING){
        last = first + count;
    }else{
        last = NHOLDING;
    }

    for(i=first, j=0; i<last; i++, j++)
    {
        holdingRegs[i] = (src[j*2] << 8) | (src[j*2 + 1]);
    }

    return last - first;
}

uint16_t modbusRTU::readHoldingRegs(WORD first, WORD count, uint8_t *dst)
{
    WORD i, j;

    WORD last;

    if((first + count) <= NHOLDING)
    {
        last = first + count;
    }else{
        last = NHOLDING;
    }

    // ser.print("Reading holding regs from ");
    // ser.print(first);
    // ser.print(" to ");
    // ser.println(last);

    // ser.println("Before reading: ");
    // for(int j=first; j < last; j++)
    // {
    //     ser.print(recv_buf[2*j]);
    //     ser.print(" ");
    //     ser.print(recv_buf[2*j + 1]);
    //     ser.print(" ");
    // }
    // ser.println();

    for(i=first, j=0; i<last; i++, j++)
    {
        dst[2*j] = (holdingRegs[i] >> 8) & 0xFF;
        dst[2*j + 1] = holdingRegs[i] & 0xFF;
    }

    // ser.println("After reading: ");
    // for(int j=first; j < last; j++)
    // {
    //     ser.print(recv_buf[2*j]);
    //     ser.print(" ");
    //     ser.print(recv_buf[2*j + 1]);
    //     ser.print(" ");
    // }
    // ser.println();

    // Return actual number of bytes read.
    return last-first;
}