programmer=C:/Program\ Files/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin

CC = arm-none-eabi-gcc
CC_CPU = cortex-m4

CC_LD_COMMON_FLAGS = --coverage -std=gnu17
FPU_FLAGS = -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Wdouble-promotion -Wfloat-conversion -fsingle-precision-constant
OPTIMIZATION_FLAGS = -O0 --specs=nano.specs

CC_FLAGS = -mcpu=cortex-m4 -std=gnu17 -g3 -O0 -ffunction-sections -fdata-sections -Wall -Wswitch-default --coverage -fstack-usage \
			--specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb

LD_FLAGS = -mcpu=cortex-m4 --specs=nosys.specs -Wl,--gc-sections -static --coverage --specs=nano.specs -mfpu=fpv4-sp-d16 \
		   	-mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group

LINKER_SCRIPT = ./linker.ld

APP_DIRECTORY = ./build/binaries
APP_NAME = firmware


SRC_DIRECTORY = ./src
SRC = $(wildcard $(SRC_DIRECTORY)/*.c)

OBJ_DIRECTORY = ./build/src
OBJ = $(subst $(SRC_DIRECTORY),$(OBJ_DIRECTORY),$(SRC:.c=.o))

INC_DIRECTORY = ./includes

LIBS =

.PHONY: configure build
build: configure $(OBJ) 
	@echo Linking... 
	@$(CC) $(LD_FLAGS) $(OBJ) -o $(APP_DIRECTORY)/$(APP_NAME).elf -Wl,-T$(LINKER_SCRIPT) -Wl,-Map=$(APP_DIRECTORY)/$(APP_NAME).map -Wl,--print-memory-usage
	@arm-none-eabi-objcopy -O ihex $(APP_DIRECTORY)/$(APP_NAME).elf $(APP_DIRECTORY)/$(APP_NAME).hex
	@arm-none-eabi-objdump -D -S -C -h $(APP_DIRECTORY)/$(APP_NAME).elf > $(APP_DIRECTORY)/$(APP_NAME).lst

	@make mem_report --no-print-directory
	@printf "\e[1;96mBuild Successful  !!\e[0m\n"

$(OBJ_DIRECTORY)%.o:$(SRC_DIRECTORY)%.c
	$(CC) $(CC_FLAGS) $< -c -o $@ -I$(INC_DIRECTORY)

configure:
	@mkdir -p $(OBJ_DIRECTORY) $(APP_DIRECTORY)

flash: build
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "init; reset init; program $(APP_DIRECTORY)/$(APP_NAME).elf; reset; shutdown"

show_flash_info:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "init; reset init; flash info 0; reset; shutdown"
	
erase:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "init; reset init; stm32f4x mass_erase 0; reset; shutdown"

.PHONY: debug
debug: build
# Start OpenOCD in the background, redirecting output to null to keep the terminal clean
	@echo "Starting OpenOCD..."
	@openocd -s scripts -f interface/stlink.cfg -f target/stm32f4x.cfg 2>&1 >/dev/null & \
    echo $$! > openocd.pid
    # Give OpenOCD time to start
	@sleep 2
    # Start arm-none-eabi-gdb and connect to OpenOCD
	@echo "Starting GDB..."
	@gdb-multiarch $(APP_DIRECTORY)/$(APP_NAME).elf -x ./gdb-config.gdb
	@kill $$(cat openocd.pid) && rm -f openocd.pid
	
.PHONY: mem_report
mem_report:
	@echo "--------------------------------------------------------"
	@echo "| 	Section Name  	|    Address    |  Size (Bytes)|"
	@echo "--------------------------------------------------------"
	@arm-none-eabi-objdump -h $(APP_DIRECTORY)/$(APP_NAME).elf | \
    awk '/^\s+[0-9]+/ { if (strtonum($$(4)) > 0) printf("| %-21s | 0x%-10s 	| %-12d |\n", $$2, $$(4), strtonum("0x"$$3)); }'
	@echo "--------------------------------------------------------"

.PHONY: clean_build
clean_build:
	@make clean --no-print-directory
	@make build --no-print-directory


program: build
	$(programmer)/STM32_Programmer_CLI -c port=USB1 -w firmware.elf 0x08000000
# /cygdrive/c/Program\ Files/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32_Programmer_CLI -c port=USB1 -w firmware.elf 0x08000000

clean:
	rm -f $(OBJ_DIRECTORY)/* $(APP_DIRECTORY)/*
