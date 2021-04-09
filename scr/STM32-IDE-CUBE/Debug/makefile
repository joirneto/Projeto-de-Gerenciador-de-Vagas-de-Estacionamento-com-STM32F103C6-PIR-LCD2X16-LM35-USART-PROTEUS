################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

BUILD_ARTIFACT_NAME := projeto_estacionamento_stm32f103c6_sensor_pir
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX := 
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME).$(BUILD_ARTIFACT_EXTENSION)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
projeto_estacionamento_stm32f103c6_sensor_pir.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
projeto_estacionamento_stm32f103c6_sensor_pir.list \

OBJCOPY_HEX += \
projeto_estacionamento_stm32f103c6_sensor_pir.hex \

OBJCOPY_BIN += \
projeto_estacionamento_stm32f103c6_sensor_pir.bin \


# All Target
all: main-build

# Main-build Target
main-build: projeto_estacionamento_stm32f103c6_sensor_pir.elf secondary-outputs

# Tool invocations
projeto_estacionamento_stm32f103c6_sensor_pir.elf: $(OBJS) $(USER_OBJS) C:\Users\joirw\Dropbox\ENGENHARIA\MICRO\Projeto-de-Gerenciador-de-Vagas-de-Estacionamento-com-STM32F103C6-SENSOR-PIR-PROTEUS\scr\STM32-IDE-CUBE\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -o "projeto_estacionamento_stm32f103c6_sensor_pir.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\joirw\Dropbox\ENGENHARIA\MICRO\Projeto-de-Gerenciador-de-Vagas-de-Estacionamento-com-STM32F103C6-SENSOR-PIR-PROTEUS\scr\STM32-IDE-CUBE\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="projeto_estacionamento_stm32f103c6_sensor_pir.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

projeto_estacionamento_stm32f103c6_sensor_pir.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "projeto_estacionamento_stm32f103c6_sensor_pir.list"
	@echo 'Finished building: $@'
	@echo ' '

projeto_estacionamento_stm32f103c6_sensor_pir.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "projeto_estacionamento_stm32f103c6_sensor_pir.hex"
	@echo 'Finished building: $@'
	@echo ' '

projeto_estacionamento_stm32f103c6_sensor_pir.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "projeto_estacionamento_stm32f103c6_sensor_pir.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified
.SECONDARY:

-include ../makefile.targets
