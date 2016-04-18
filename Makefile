# This file was automagically generated by mbed.org. For more information, 
# see http://mbed.org/handbook/Exporting-to-GCC-ARM-Embedded

GCC_BIN = 
PROJECT = simucube
OBJECTS = ./main.o ./Debug.o ./Command.o ./Effects.o ./USBDevice/USBAudio/USBAudio.o ./USBDevice/USBDevice/USBDevice.o ./USBDevice/USBDevice/USBHAL_KL25Z.o ./USBDevice/USBDevice/USBHAL_LPC11U.o ./USBDevice/USBDevice/USBHAL_LPC17.o ./USBDevice/USBDevice/USBHAL_EFM32.o ./USBDevice/USBDevice/USBHAL_LPC40.o ./USBDevice/USBDevice/USBHAL_Maxim.o ./USBDevice/USBDevice/USBHAL_RZ_A1H.o ./USBDevice/USBDevice/USBHAL_STM32F4.o ./USBDevice/USBHID/USBHID.o ./USBDevice/USBHID/USBKeyboard.o ./USBDevice/USBHID/USBMouse.o ./USBDevice/USBHID/USBMouseKeyboard.o ./USBDevice/USBMIDI/USBMIDI.o ./USBDevice/USBMSD/USBMSD.o ./USBDevice/USBSerial/USBCDC.o ./USBDevice/USBSerial/USBSerial.o \
	./SimpleMotion/busdevice.o \
	./SimpleMotion/simplemotion.o \
	./SimpleMotion/sm_consts.o \
	./USBDevice/USBGameController/USBGameController.o \
	./USBDevice/USBGameController/USBGameControllerDesc.o \
	./USBDevice/USBGameController/ffb.o \
	./USBDevice/USBGameController/ffb_pro.o	 

	#stm periph lib headers conflict with mbed headers. avoid using stm lib
	#./stm32_periph_lib/src/misc.o \
	#./stm32_periph_lib/src/stm32f4xx_adc.o \
	#./stm32_periph_lib/src/stm32f4xx_can.o \
	#./stm32_periph_lib/src/stm32f4xx_cec.o \
	#./stm32_periph_lib/src/stm32f4xx_crc.o \
	#./stm32_periph_lib/src/stm32f4xx_cryp.o \
	#./stm32_periph_lib/src/stm32f4xx_cryp_aes.o \
	#./stm32_periph_lib/src/stm32f4xx_cryp_des.o \
	#./stm32_periph_lib/src/stm32f4xx_cryp_tdes.o \
	#./stm32_periph_lib/src/stm32f4xx_dac.o \
	#./stm32_periph_lib/src/stm32f4xx_dbgmcu.o \
	#./stm32_periph_lib/src/stm32f4xx_dcmi.o \
	#./stm32_periph_lib/src/stm32f4xx_dma.o \
	#./stm32_periph_lib/src/stm32f4xx_dma2d.o \
	#./stm32_periph_lib/src/stm32f4xx_dsi.o \
	#./stm32_periph_lib/src/stm32f4xx_exti.o \
	#./stm32_periph_lib/src/stm32f4xx_flash.o \
	#./stm32_periph_lib/src/stm32f4xx_flash_ramfunc.o \
	#./stm32_periph_lib/src/stm32f4xx_fmc.o \
	#./stm32_periph_lib/src/stm32f4xx_fmpi2c.o \
	#./stm32_periph_lib/src/stm32f4xx_fsmc.o \
	#./stm32_periph_lib/src/stm32f4xx_gpio.o \
	#./stm32_periph_lib/src/stm32f4xx_hash.o \
	#./stm32_periph_lib/src/stm32f4xx_hash_md5.o \
	#./stm32_periph_lib/src/stm32f4xx_hash_sha1.o \
	#./stm32_periph_lib/src/stm32f4xx_i2c.o \
	#./stm32_periph_lib/src/stm32f4xx_iwdg.o \
	#./stm32_periph_lib/src/stm32f4xx_lptim.o \
	#./stm32_periph_lib/src/stm32f4xx_ltdc.o \
	#./stm32_periph_lib/src/stm32f4xx_pwr.o \
	#./stm32_periph_lib/src/stm32f4xx_qspi.o \
	#./stm32_periph_lib/src/stm32f4xx_rcc.o \
	#./stm32_periph_lib/src/stm32f4xx_rng.o \
	#./stm32_periph_lib/src/stm32f4xx_rtc.o \
	#./stm32_periph_lib/src/stm32f4xx_sai.o \
	#./stm32_periph_lib/src/stm32f4xx_sdio.o \
	#./stm32_periph_lib/src/stm32f4xx_spdifrx.o \
	#./stm32_periph_lib/src/stm32f4xx_spi.o \
	#./stm32_periph_lib/src/stm32f4xx_syscfg.o \
	#./stm32_periph_lib/src/stm32f4xx_tim.o \
	#./stm32_periph_lib/src/stm32f4xx_usart.o \
	#./stm32_periph_lib/src/stm32f4xx_wwdg.o 
	 
SYS_OBJECTS = ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_flash_ramfunc.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/board.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/cmsis_nvic.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/hal_tick.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/mbed_overrides.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/retarget.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/startup_stm32f407xx.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_adc.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_adc_ex.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_can.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_cec.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_cortex.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_crc.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_cryp.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_cryp_ex.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_dac.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_dac_ex.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_dcmi.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_dcmi_ex.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_dma.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_dma2d.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_dma_ex.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_dsi.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_eth.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_flash.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_flash_ex.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_fmpi2c_ex.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_fmpi2c.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_msp_template.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_gpio.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_hash.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_hash_ex.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_hcd.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_i2c.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_i2c_ex.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_i2s.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_i2s_ex.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_irda.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_iwdg.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_lptim.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_ltdc.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_ltdc_ex.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_smartcard.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_nand.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_nor.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_pccard.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_pcd.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_pcd_ex.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_pwr.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_pwr_ex.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_qspi.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_rcc.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_rcc_ex.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_rng.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_rtc.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_rtc_ex.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_sai.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_sai_ex.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_sd.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_sdram.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_spdifrx.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_spi.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_sram.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_tim.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_tim_ex.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_uart.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_usart.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_hal_wwdg.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_ll_fmc.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_ll_fsmc.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_ll_sdmmc.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/stm32f4xx_ll_usb.o ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/system_stm32f4xx.o 
INCLUDE_PATHS = -I. -I./USBDevice -I./USBDevice/USBAudio -I./USBDevice/USBDevice -I./USBDevice/USBHID -I./USBDevice/USBMIDI -I./USBDevice/USBMSD -I./USBDevice/USBSerial -I./mbed -I./mbed/TARGET_ARCH_MAX -I./mbed/TARGET_ARCH_MAX/TARGET_STM -I./mbed/TARGET_ARCH_MAX/TARGET_STM/TARGET_STM32F4 -I./mbed/TARGET_ARCH_MAX/TARGET_STM/TARGET_STM32F4/TARGET_ARCH_MAX -I./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM -I./SimuCUBE -I./SimpleMotion -I./stm32_periph_lib/inc -I./USBDevice/USBGameController 
LIBRARY_PATHS = -L./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM 
LIBRARIES = -lmbed 
LINKER_SCRIPT = ./mbed/TARGET_ARCH_MAX/TOOLCHAIN_GCC_ARM/STM32F407XG.ld

############################################################################### 
AS      = $(GCC_BIN)arm-none-eabi-as
CC      = $(GCC_BIN)arm-none-eabi-gcc
CPP     = $(GCC_BIN)arm-none-eabi-g++
LD      = $(GCC_BIN)arm-none-eabi-gcc
OBJCOPY = $(GCC_BIN)arm-none-eabi-objcopy
OBJDUMP = $(GCC_BIN)arm-none-eabi-objdump
SIZE    = $(GCC_BIN)arm-none-eabi-size 

ifeq ($(HARDFP),1)
	FLOAT_ABI = hard
else
	FLOAT_ABI = softfp
endif


CPU = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=$(FLOAT_ABI) 
CC_FLAGS = $(CPU) -c -g -fno-common -fmessage-length=0 -Wall -Wextra -Wunused-parameter -fno-exceptions -ffunction-sections -fdata-sections -fomit-frame-pointer -MMD -MP
CC_SYMBOLS = -DTARGET_RTOS_M4_M7 -DTARGET_ARCH_MAX -DTOOLCHAIN_GCC_ARM -DTOOLCHAIN_GCC -D__CORTEX_M4 -DTARGET_LIKE_MBED -DTARGET_CORTEX_M -DLSI_VALUE=32000 -D__FPU_PRESENT=1 -DTARGET_FF_ARDUINO -DTARGET_LIKE_CORTEX_M4 -DTARGET_M4 -D__MBED__=1 -DTARGET_STM -DTARGET_STM32F407 -DTARGET_STM32F4 -DTARGET_STM32F407VG -DARM_MATH_CM4 -DMBED_BUILD_TIMESTAMP=1458485789.96 

LD_FLAGS = $(CPU) -Wl,--gc-sections --specs=nano.specs -u _printf_float -u _scanf_float -Wl,--wrap,main -Wl,-Map=$(PROJECT).map,--cref
LD_SYS_LIBS = -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys


ifeq ($(DEBUG), 1)
  CC_FLAGS += -DDEBUG -O0
else
  CC_FLAGS += -DNDEBUG -Os
endif

.PHONY: all clean lst size

all: $(PROJECT).bin $(PROJECT).hex size


clean:
	rm -f $(PROJECT).bin $(PROJECT).elf $(PROJECT).hex $(PROJECT).map $(PROJECT).lst $(OBJECTS) $(DEPS)


.asm.o:
	$(CC) $(CPU) -c -x assembler-with-cpp -o $@ $<
.s.o:
	$(CC) $(CPU) -c -x assembler-with-cpp -o $@ $<
.S.o:
	$(CC) $(CPU) -c -x assembler-with-cpp -o $@ $<

.c.o:
	$(CC)  $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu99   $(INCLUDE_PATHS) -o $@ $<

.cpp.o:
	$(CPP) $(CC_FLAGS) $(CC_SYMBOLS) -std=c++11 -fno-rtti $(INCLUDE_PATHS) -o $@ $<

#	$(CPP) $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu++98 -fno-rtti $(INCLUDE_PATHS) -o $@ $<



$(PROJECT).elf: $(OBJECTS) $(SYS_OBJECTS)
	$(LD) $(LD_FLAGS) -T$(LINKER_SCRIPT) $(LIBRARY_PATHS) -o $@ $^ $(LIBRARIES) $(LD_SYS_LIBS) $(LIBRARIES) $(LD_SYS_LIBS)


$(PROJECT).bin: $(PROJECT).elf
	$(OBJCOPY) -O binary $< $@

$(PROJECT).hex: $(PROJECT).elf
	@$(OBJCOPY) -O ihex $< $@

$(PROJECT).lst: $(PROJECT).elf
	@$(OBJDUMP) -Sdh $< > $@

lst: $(PROJECT).lst

size: $(PROJECT).elf
	$(SIZE) $(PROJECT).elf

DEPS = $(OBJECTS:.o=.d) $(SYS_OBJECTS:.o=.d)
-include $(DEPS)


