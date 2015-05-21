/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

#ifndef _PMIC_ACT_8945A_H_
#define _PMIC_ACT_8945A_H_

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#define ACT8945A_RET_OK  0
#define ACT8945A_RET_NOK 1

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

enum TWI_CMD
{
    TWI_RD   = 0,
    TWI_WR	 = 1
};

enum TWI_STATUS
{
  TWI_STATUS_RESET  = 0,
  TWI_STATUS_HANDLE = 1u<<0,
  TWI_STATUS_RFU2   = 1u<<1,
  TWI_STATUS_RFU3   = 1u<<2,
  TWI_STATUS_RFU4   = 1u<<3,
  TWI_STATUS_READY  = 1u<<7,
};

enum TWI_RESULT
{
    TWI_SUCCES   = 0,
    TWI_FAIL	 = 1
} ;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/// Slave address
#define ACT8945A_ADDRESS   0x5B

#define ADD_SYSTEM0 0x00
#define ADD_SYSTEM1 0x01

#define ADD_REG1_0  0x20
#define V_OUT1      ADD_REG1_0
#define ADD_REG1_1  ADD_REG1_0+1
#define ADD_REG1_2  ADD_REG1_0+2

#define ADD_REG2_0  0x30
#define V_OUT2      ADD_REG2_0
#define ADD_REG2_1  ADD_REG2_0+1
#define ADD_REG2_2  ADD_REG2_0+2

#define ADD_REG3_0  0x40
#define V_OUT3      ADD_REG3_0
#define ADD_REG3_1  ADD_REG3_0+1
#define ADD_REG3_2  ADD_REG3_0+2

#define ADD_REG4_0  0x50
#define V_OUT4      ADD_REG4_0
#define VDD_FUSE    V_OUT4
#define ADD_REG4_1  ADD_REG4_0+1

#define ADD_REG5_0  0x54
#define V_OUT5      ADD_REG5_0
#define VDD_ANA     V_OUT5
#define ADD_REG5_1  ADD_REG5_0+1

#define ADD_REG6_0  0x60
#define V_OUT6      ADD_REG6_0
#define ADD_REG6_1  ADD_REG6_0+1

#define ADD_REG7_0  0x64
#define V_OUT7      ADD_REG7_0
#define ADD_REG7_1  ADD_REG7_0+1

#define ADD_APCH_70   0x70
#define ADD_APCH_71   0x71
#define ADD_APCH_78   0x78
#define ADD_APCH_79   0x79
#define ADD_APCH_7A   0x7A

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

typedef enum
{
  ACT8945A_REG_OFF = 0,
  ACT8945A_REG_ON = 1,
} REG_ON_OFF_enum;

typedef enum
{
  ACT8945A_INT_OFF = 0,
  ACT8945A_INT_ON = 1,
} INT_ON_OFF_enum;

typedef enum
{
  ACT8945A_USB_MODE_100mA = 0,
  ACT8945A_USB_MODE_450mA = 1,
} CHG_LEVEL_enum;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

typedef struct
{
  char  RegName[16];
  uint8_t   Address;
} sActReg, psActReg;

// SYSTEM @0x00
typedef struct
{
  uint8_t
    trst : 1,           // Reset time out 0->260 1->65ms
    nsysmode : 1,       // response of SYSLEV voltage detector, 1->int 0>shutdown
    nsyslevmsk : 1,     // 1->unmask int
    nsysstat : 1,       // 1 if vsys < syslev voltage threshold
    syslev : 4;         // defines SYSLEV voltage threshold
} BITFIELD_SYS0;

// SYSTEM @0x01
typedef struct
{
  uint8_t
    scratch : 4,        // maybe be used by user to store system status information
    ruf4 : 1,           //
    mstroff : 1,        // Set bit to 1 to turn off all regulators
    ruf67 : 2;          //
} BITFIELD_SYS1;

// REG1 @0x20, REG2 @0x30, REG3 @0x40
typedef struct
{
  uint8_t
    vset1 : 6,
    ruf_67 : 2;
} BITFIELD_VSET1;

// REG1 @0x21, REG2 @0x31, REG3 @0x41
typedef struct
{
  uint8_t
    vset2 : 6,
    ruf_67 : 2;
} BITFIELD_VSET2;

// REG1 @0x22, REG2 @0x32, REG3 @0x42
typedef struct
{
  uint8_t
    ok : 1,
    nfltmsk : 1,
    delay : 3,
    mode : 1,
    phase : 1,
    on : 1;
} BITFIELD_CTRL1;

// REG4 @0x51, REG5 @0x55, REG6 @0x61, REG7 @0x65
typedef struct
{
  uint8_t
    ok : 1,
    nfltmsk : 1,
    delay : 3,
    lowiq : 1,
    dis : 1,
    on : 1;
} BITFIELD_CTRL2;

//#pragma bitfields=reverse_disjoint_types

typedef struct
{
  uint8_t
    ruf_0 : 1,
    ruf_1 : 1,
    ruf_2 : 1,
    ruf_3 : 1,
    ruf_45 : 2,
    ruf_67 : 2;
} BITFIELD_APCH70;

typedef struct
{
  uint8_t
    ovpset : 2,
    pretimo : 2,
    tottimo : 2,
    ruf6 : 1,
    suschg : 1;
} BITFIELD_APCH71;

typedef struct
{
  uint8_t
    chgdat : 1,
    indat : 1,
    tempdat : 1,
    timrdat : 1,
    chgstat : 1,
    instat : 1,
    tempstat : 1,
    timrstat : 1;
} BITFIELD_APCH78;

typedef struct
{
  uint8_t
    chgeocout : 1,
    indis : 1,
    tempout : 1,
    timrpre : 1,
    chgeocin : 1,
    incon : 1,
    tempin : 1,
    timrtot : 1;
} BITFIELD_APCH79;

typedef struct
{
  uint8_t
    ruf0 : 1,
    acinstat : 1,
    ruf32 : 2,
    cstate : 2,
    ruf76 : 2;
} BITFIELD_APCH7A;

#pragma bitfields=default

typedef enum
{
    CHARGE_STATE_OUT_EOC_STATE_INT_CTRL, // bit[0]
    INPUT_VOLTAGE_OUT_VALID_RANGE_INT_CTRL,
    BATTERY_TEMPERATURE_OUT_RANGE_INT_CTRL,
    PRECHARGE_TIME_OUT_INT_CTRL,
    CHARGE_STATE_INTO_EOC_STATE_INT_CTRL,
    INPUT_VOLTAGE_INTO_VALID_RANGE_INT_CTRL,
    BATTERY_TEMPERATURE_INTO_RANGE_INT_CTRL,
    TOTAL_CHARGE_TIME_OUT_INT_CTRL,
} INT_APCH_enum ;


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void _ACT8945A_twi_error (void);
void _ACT8945A_delay_ms (uint32_t delay);
float _ACT8945A_convert_voltage_setting (uint8_t Reg);
void _ACT8945A_display_system_setting (void);
void _ACT8945A_display_voltage_setting (void);
void _ACT8945A_registers_dump (void);
void _ACT8945A_registers_dump_apch (void);

uint8_t _ACT8945A_display_active_path_charger (void);
uint8_t _ACT8945A_display_syslev_failing_threshold (void);

extern void ACT8945A_active_interrupt (void);
extern void ACT8945A_disable_twi (void);

extern uint8_t ACT8945A_set_regulator_state_out1to3 (uint8_t RegVout, REG_ON_OFF_enum ON_OFF);
extern uint8_t ACT8945A_set_regulator_state_out4to7 (uint8_t RegVout, REG_ON_OFF_enum ON_OFF);
extern uint8_t ACT8945A_set_regulator_voltage_out4to7 (uint8_t RegVout, uint16_t VOut);
extern uint8_t ACT8945A_set_system_voltage_level_interrupt (INT_ON_OFF_enum ON_OFF);
extern uint8_t ACT8945A_set_regulator_fault_interrupt (uint8_t RegVout, INT_ON_OFF_enum ON_OFF);
extern uint8_t ACT8945A_set_APCH_interrupt (INT_APCH_enum IntType, INT_ON_OFF_enum ON_OFF);
extern uint8_t ACT8945A_disable_all_APCH_interrupt (void);
extern uint8_t ACT8945A_system_voltage_level (uint16_t Value);
extern uint8_t ACT8945A_set_state_CHGLEV_pin (CHG_LEVEL_enum State);
extern uint8_t ACT8945A_get_state_LBO_pin (void);
extern uint8_t ACT8945A_begin(void);
extern uint8_t ACT8945A_test (void);

extern void ACT8945A_irq_handler(void);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#endif /* _PMIC_ACT_8945A_H_ */
