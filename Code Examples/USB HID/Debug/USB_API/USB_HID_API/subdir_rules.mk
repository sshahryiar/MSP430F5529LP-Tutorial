################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
USB_API/USB_HID_API/%.obj: ../USB_API/USB_HID_API/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs920/ccs/tools/compiler/ti-cgt-msp430_19.6.0.STS/bin/cl430" -vmspx --code_model=large --data_model=restricted --near_data=none --use_hw_mpy=F5 --include_path="D:/Current Works/MSP430F5529/MSP430F5529LP_Examples/USB HID/My_Libraries" --include_path="D:/Current Works/MSP430F5529/MSP430F5529LP_Examples/USB HID/USB_config" --include_path="C:/ti/ccs920/ccs/ccs_base/msp430/include" --include_path="D:/Current Works/MSP430F5529/MSP430F5529LP_Examples/USB HID" --include_path="D:/Current Works/MSP430F5529/MSP430F5529LP_Examples/USB HID/driverlib/MSP430F5xx_6xx" --include_path="C:/ti/ccs920/ccs/tools/compiler/ti-cgt-msp430_19.6.0.STS/include" --advice:power=all --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="USB_API/USB_HID_API/$(basename $(<F)).d_raw" --obj_directory="USB_API/USB_HID_API" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


