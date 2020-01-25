
//=========================================
// ds1307.c -- Functions for the Dallas Semiconductor DS1307
// real time clock and NVRAM chip.
//
// The DS1307 uses BCD as its internal format, but we use it
// in binary format, outside of this module. So we have code
// to convert to/from BCD to binary in the functions below.                         

//----------------------------------------------------------------------
// Set the date and time.

/*
The registers inside the ds1307 are in this format. The values are in BCD.

DS1307_SECONDS_REG 0
DS1307_MINUTES_REG 1
DS1307_HOURS_REG 2
DS1307_DAY_OF_WEEK_REG 3 // We don't use this register. Set it to 0.
DS1307_DATE_REG 4
DS1307_MONTH_REG 5
DS1307_YEAR_REG 6
*/

#define DS1307_I2C_WRITE_ADDR 0xd0
#define DS1307_I2C_READ_ADDR 0xd1

// DS1307 register offsets
#define DS1307_SECONDS_REG 0
#define DS1307_MINUTES_REG 1
#define DS1307_HOURS_REG 2
#define DS1307_DAY_OF_WEEK_REG 3
#define DS1307_DATE_REG 4
#define DS1307_MONTH_REG 5
#define DS1307_YEAR_REG 6
#define DS1307_CONTROL_REG 7


#define DS1307_DATE_TIME_BYTE_COUNT 7 // Includes bytes 0-6

#define DS1307_NVRAM_START_ADDR 8

// We disable the SQWV output, because it uses
// a lot of battery current when it's enabled.
// Disable it by setting Out = Open Collector.

#define DS1307_CONTROL_REG_INIT_VALUE 0x80


char gca_ds1307_regs[DS1307_DATE_TIME_BYTE_COUNT];

void ds1307_set_date_time(void);
void ds1307_read_date_time(void);
char ds1307_read_byte(char addr);
char bcd2bin(char bcd_value);
char bin2bcd(char bin_value);
void ds1307_write_byte(char addr, char value);


void ds1307_set_date_time(void)
{
char i;
// Convert the binary ds1307 data, which is passed in a global array,
// into bcd data. Store it in the same array.

for(i = 0; i < 7; i++)
{
gca_ds1307_regs[i] = bin2bcd(gca_ds1307_regs[i]);
}

// There are two control bits embedded in the following data.
// The Clock Halt bit is in bit 7 of the DS1307 Seconds register.
// We need to make sure that it's = 0, to make the clock run.
// The other bit is the 24/12 hour clock format bit, in bit 6 of
// the DS1307 Hours register. We need 24 hour mode, so set it = 0.

gca_ds1307_regs[DS1307_SECONDS_REG] &= 0x7f;
gca_ds1307_regs[DS1307_HOURS_REG] &= 0x3f;

// Now write the 7 bytes of BCD data to the ds1307,
// using inline code for speed.
disable_interrupts(GLOBAL);

i2c_start();
i2c_write(DS1307_I2C_WRITE_ADDR);
// Start reading at the Seconds register.
i2c_write(DS1307_SECONDS_REG);

// Write 7 bytes, to registers 0 to 6.

for(i = 0; i < 7; i++)
{
i2c_write(gca_ds1307_regs[i]);
}

// After setting the time in registers 0-6, also set the
// Control register. (index = 7)

// This just turns off the squarewave output pin.
// Doing it here, every time we set the clock registers,
// seems less risky than setting it near the
// start of the program, every time the unit powers-up.
i2c_write(DS1307_CONTROL_REG_INIT_VALUE);

i2c_stop();

enable_interrupts(GLOBAL);
}

//----------------------------------------------------------------------
// Read the date and time.

// The registers inside the ds1307 are in this order.
// The values inside the registers are in BCD.

// DS1307_SECONDS_REG_ADDR 0
// DS1307_MINUTES_REG_ADDR 1
// DS1307_HOURS_REG_ADDR 2
// DS1307_DAY_OF_WEEK_REG_ADDR 3
// DS1307_DATE_REG_ADDR 4
// DS1307_MONTH_REG_ADDR 5
// DS1307_YEAR_REG_ADDR 6

// We return the data in a global array. The data in is binary.

// seconds // 0-59 seconds
// minutes // 0-59 minutes
// hours // 0-23 hours
// day_of_week // 1-7
// date // 1-31 date
// month // 1-12 month
// year // 00-99 year (based on year 2000)

void ds1307_read_date_time(void) 
{                                   
char i;

disable_interrupts(GLOBAL);

i2c_start();
i2c_write(DS1307_I2C_WRITE_ADDR);
// Start reading at the Seconds register.
i2c_write(DS1307_SECONDS_REG);
                                        
i2c_start();                           
i2c_write(DS1307_I2C_READ_ADDR);     
                                    
// Read the 7 bytes from the ds1307. Mask off the unused bits.
gca_ds1307_regs[DS1307_SECONDS_REG] = i2c_read() & 0x7f;
gca_ds1307_regs[DS1307_MINUTES_REG] = i2c_read() & 0x7f;
gca_ds1307_regs[DS1307_HOURS_REG] = i2c_read() & 0x3f;
gca_ds1307_regs[DS1307_DAY_OF_WEEK_REG] = i2c_read() & 0x07;
gca_ds1307_regs[DS1307_DATE_REG] = i2c_read() & 0x3f;
gca_ds1307_regs[DS1307_MONTH_REG] = i2c_read() & 0x1f;
gca_ds1307_regs[DS1307_YEAR_REG] = i2c_read(0);
                           
i2c_stop();                            
                           
enable_interrupts(GLOBAL);                              

// Now convert the data from BCD to binary.
// Do it after reading the bytes, so that
// the i2c reads can be done quickly.
                                               
for(i = 0; i < 7; i++)
{                     
gca_ds1307_regs[i] = bcd2bin(gca_ds1307_regs[i]);
}

}

//------------------------------------------------------------------------
// Read one byte at the specified address.
// This function is used to access the control byte
// or the NVRAM bytes.                   

char ds1307_read_byte(char addr)
{                                   
char retval;

disable_interrupts(GLOBAL);
i2c_start();
i2c_write(DS1307_I2C_WRITE_ADDR); 
i2c_write(addr);

i2c_start();
i2c_write(DS1307_I2C_READ_ADDR); 
retval = i2c_read(0); // Don't ACK the last byte read
i2c_stop();
enable_interrupts(GLOBAL);

return(retval);
}

//----------------------------------------------------------------------
// Write one byte to the DS1307.
// This function is used to access the control byte
// or the NVRAM bytes.

void ds1307_write_byte(char addr, char value)
{
disable_interrupts(GLOBAL);
i2c_start();
i2c_write(DS1307_I2C_WRITE_ADDR);
i2c_write(addr);
i2c_write(value);
i2c_stop();
enable_interrupts(GLOBAL);
}
//-------------------------------------------------------------
// This function converts an 8 bit binary value
// to an 8 bit BCD value.
// The input range must be from 0 to 99.

char bin2bcd(char binary_value)
{
char temp;
char retval;

temp = binary_value;
retval = 0;

while(1)
{
// Get the tens digit by doing multiple subtraction
// of 10 from the binary value.
if(temp >= 10)
{
temp -= 10;
retval += 0x10;
}
else // Get the ones digit by adding the remainder.
{
retval += temp;
break;
}
}

return(retval);
}

//--------------------------------------------------------------
// This function converts an 8 bit BCD value to
// an 8 bit binary value.
// The input range must be from 00 to 99.

char bcd2bin(char bcd_value)
{
char temp;

temp = bcd_value;
// Shifting upper digit right by 1 is same as multiplying by 8.
temp >>= 1;
// Isolate the bits for the upper digit.
temp &= 0x78;

// Now return: (Tens * 8) + (Tens * 2) + Ones

return(temp + (temp >> 2) + (bcd_value & 0x0f));

}
