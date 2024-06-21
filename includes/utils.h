#define _chkBit(REG, bit) ((REG&(1<<bit)) > 0) ? 1 : 0
#define _setBit(REG, bit) (REG|(1<<bit))
#define _invBit(REG, bit) (REG^(1<<bit))
#define _clrBit(REG, bit) (REG&(~(1<<bit)))
#define _bit(bit) (1<<bit)


#define SRAM_BB_BASE 0x22000000
#define SRAM_BASE 0x20000000

#define PERI_BB_BASE 0x42000000
#define PERI_BASE 0x40000000

/*Bit Banding operations*/
#define SRAM_BB_ADDRESS_FROM_ABS_ADDRESS(var, bit) (SRAM_BB_BASE + (((var) ^ SRAM_BASE) << 5) + (bit << 2))
#define SRAM_BB_ADDRESS_FROM_VAR(var, bit) (SRAM_BB_BASE + (((uint32_t)&(var)) ^ SRAM_BASE << 5) + (bit << 2))
#define PERI_BB_ADDRESS_FROM_ABS_ADDRESS(var, bit) (PERI_BB_BASE + (((var) ^ PERI_BASE) << 5) + (bit << 2))
