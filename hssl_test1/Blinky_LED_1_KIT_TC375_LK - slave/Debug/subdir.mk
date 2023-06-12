################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Cpu0_Main.c \
../Cpu1_Main.c \
../Cpu2_Main.c \
../Dma.c \
../HSSL_TEST.c \
../HSSL_interrupt.c 

COMPILED_SRCS += \
./Cpu0_Main.src \
./Cpu1_Main.src \
./Cpu2_Main.src \
./Dma.src \
./HSSL_TEST.src \
./HSSL_interrupt.src 

C_DEPS += \
./Cpu0_Main.d \
./Cpu1_Main.d \
./Cpu2_Main.d \
./Dma.d \
./HSSL_TEST.d \
./HSSL_interrupt.d 

OBJS += \
./Cpu0_Main.o \
./Cpu1_Main.o \
./Cpu2_Main.o \
./Dma.o \
./HSSL_TEST.o \
./HSSL_interrupt.o 


# Each subdirectory must supply rules for building sources it contributes
%.src: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/hejzhu1/Desktop/hssl_test1/Blinky_LED_1_KIT_TC375_LK - slave/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

%.o: ./%.src subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

clean--2e-:
	-$(RM) ./Cpu0_Main.d ./Cpu0_Main.o ./Cpu0_Main.src ./Cpu1_Main.d ./Cpu1_Main.o ./Cpu1_Main.src ./Cpu2_Main.d ./Cpu2_Main.o ./Cpu2_Main.src ./Dma.d ./Dma.o ./Dma.src ./HSSL_TEST.d ./HSSL_TEST.o ./HSSL_TEST.src ./HSSL_interrupt.d ./HSSL_interrupt.o ./HSSL_interrupt.src

.PHONY: clean--2e-

