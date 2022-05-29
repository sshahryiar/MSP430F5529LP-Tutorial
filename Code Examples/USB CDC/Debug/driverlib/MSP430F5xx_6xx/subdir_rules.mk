################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
driverlib/MSP430F5xx_6xx/%.obj: ../driverlib/MSP430F5xx_6xx/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"" -vmspx --code_model=large --data_model=restricted --near_data=none --use_hw_mpy=F5 --include_path="D:/Current Works/MSP430F5529/MSP430F5529LP_Examples/USB CDC/My_Libraries" --include_path="H:/New Docs/MSP430F5529/MSP430F5529LP_Examples/USB CDC/USB_config" --include_path="C:/ti/ccs901/ccs/ccs_base/msp430/include" --include_path="H:/New Docs/MSP430F5529/MSP430F5529LP_Examples/USB CDC" --include_path="H:/New Docs/MSP430F5529/MSP430F5529LP_Examples/USB CDC/driverlib/MSP430F5xx_6xx" --include_path="/include" --advice:power=all --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="driverlib/MSP430F5xx_6xx/$(basename $(<F)).d_raw" --obj_directory="driverlib/MSP430F5xx_6xx" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


