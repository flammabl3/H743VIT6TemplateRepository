################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AltitudePredictionFilter/Data.cpp \
../AltitudePredictionFilter/EverestTask.cpp \
../AltitudePredictionFilter/HALO.cpp \
../AltitudePredictionFilter/Infusion.cpp \
../AltitudePredictionFilter/KDTree.cpp \
../AltitudePredictionFilter/gpsData.cpp \
../AltitudePredictionFilter/input_data.cpp \
../AltitudePredictionFilter/pre_flight_data.cpp 

OBJS += \
./AltitudePredictionFilter/Data.o \
./AltitudePredictionFilter/EverestTask.o \
./AltitudePredictionFilter/HALO.o \
./AltitudePredictionFilter/Infusion.o \
./AltitudePredictionFilter/KDTree.o \
./AltitudePredictionFilter/gpsData.o \
./AltitudePredictionFilter/input_data.o \
./AltitudePredictionFilter/pre_flight_data.o 

CPP_DEPS += \
./AltitudePredictionFilter/Data.d \
./AltitudePredictionFilter/EverestTask.d \
./AltitudePredictionFilter/HALO.d \
./AltitudePredictionFilter/Infusion.d \
./AltitudePredictionFilter/KDTree.d \
./AltitudePredictionFilter/gpsData.d \
./AltitudePredictionFilter/input_data.d \
./AltitudePredictionFilter/pre_flight_data.d 


# Each subdirectory must supply rules for building sources it contributes
AltitudePredictionFilter/%.o AltitudePredictionFilter/%.su AltitudePredictionFilter/%.cyclo: ../AltitudePredictionFilter/%.cpp AltitudePredictionFilter/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++20 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -DUSE_PWR_LDO_SUPPLY -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/harry/Desktop/soar/H743VIT6TemplateRepository/SoarOS/Core" -I"C:/Users/harry/Desktop/soar/H743VIT6TemplateRepository/SoarOS/Drivers" -I"C:/Users/harry/Desktop/soar/H743VIT6TemplateRepository/SoarOS/Core/Inc" -I"C:/Users/harry/Desktop/soar/H743VIT6TemplateRepository/SoarOS/Drivers/Inc" -I"C:/Users/harry/Desktop/soar/H743VIT6TemplateRepository/SoarOS/Libraries" -I"C:/Users/harry/Desktop/soar/H743VIT6TemplateRepository/SoarOS/Libraries/embedded-template-library" -I"C:/Users/harry/Desktop/soar/H743VIT6TemplateRepository/SoarOS/Libraries/embedded-template-library/include" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/harry/Desktop/soar/H743VIT6TemplateRepository/Components" -I"C:/Users/harry/Desktop/soar/H743VIT6TemplateRepository/SoarOS" -I"C:/Users/harry/Desktop/soar/H743VIT6TemplateRepository/Debug" -I"C:/Users/harry/Desktop/soar/H743VIT6TemplateRepository/Middlewares" -I"C:/Users/harry/Desktop/soar/H743VIT6TemplateRepository/Components/SOARDebug" -I"C:/Users/harry/Desktop/soar/H743VIT6TemplateRepository/AltitudePredictionFilter" -I"C:/Users/harry/Desktop/soar/H743VIT6TemplateRepository/SoarOS/Components/DataBroker/Inc" -I"C:/Users/harry/Desktop/soar/H743VIT6TemplateRepository/SoarOS/Components/DataBroker" -I"C:/Users/harry/Desktop/soar/H743VIT6TemplateRepository/SoarOS/Components/SystemTypes" -I"C:/Users/harry/Desktop/soar/H743VIT6TemplateRepository/Components/AltitudeTask" -I"C:/Users/harry/Desktop/soar/H743VIT6TemplateRepository/Components/Communication" -I"C:/Users/harry/Desktop/soar/H743VIT6TemplateRepository/Components/Communication/Inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-AltitudePredictionFilter

clean-AltitudePredictionFilter:
	-$(RM) ./AltitudePredictionFilter/Data.cyclo ./AltitudePredictionFilter/Data.d ./AltitudePredictionFilter/Data.o ./AltitudePredictionFilter/Data.su ./AltitudePredictionFilter/EverestTask.cyclo ./AltitudePredictionFilter/EverestTask.d ./AltitudePredictionFilter/EverestTask.o ./AltitudePredictionFilter/EverestTask.su ./AltitudePredictionFilter/HALO.cyclo ./AltitudePredictionFilter/HALO.d ./AltitudePredictionFilter/HALO.o ./AltitudePredictionFilter/HALO.su ./AltitudePredictionFilter/Infusion.cyclo ./AltitudePredictionFilter/Infusion.d ./AltitudePredictionFilter/Infusion.o ./AltitudePredictionFilter/Infusion.su ./AltitudePredictionFilter/KDTree.cyclo ./AltitudePredictionFilter/KDTree.d ./AltitudePredictionFilter/KDTree.o ./AltitudePredictionFilter/KDTree.su ./AltitudePredictionFilter/gpsData.cyclo ./AltitudePredictionFilter/gpsData.d ./AltitudePredictionFilter/gpsData.o ./AltitudePredictionFilter/gpsData.su ./AltitudePredictionFilter/input_data.cyclo ./AltitudePredictionFilter/input_data.d ./AltitudePredictionFilter/input_data.o ./AltitudePredictionFilter/input_data.su ./AltitudePredictionFilter/pre_flight_data.cyclo ./AltitudePredictionFilter/pre_flight_data.d ./AltitudePredictionFilter/pre_flight_data.o ./AltitudePredictionFilter/pre_flight_data.su

.PHONY: clean-AltitudePredictionFilter

