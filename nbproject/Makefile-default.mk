#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/lcd_2x16_interfacing.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/lcd_2x16_interfacing.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=lcd_control_main.c atemga32a.c interfacing_connection_logic.c phone_keypad.c interrupt_configuration.c adc_interfacing.c timer0_interface.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/lcd_control_main.o ${OBJECTDIR}/atemga32a.o ${OBJECTDIR}/interfacing_connection_logic.o ${OBJECTDIR}/phone_keypad.o ${OBJECTDIR}/interrupt_configuration.o ${OBJECTDIR}/adc_interfacing.o ${OBJECTDIR}/timer0_interface.o
POSSIBLE_DEPFILES=${OBJECTDIR}/lcd_control_main.o.d ${OBJECTDIR}/atemga32a.o.d ${OBJECTDIR}/interfacing_connection_logic.o.d ${OBJECTDIR}/phone_keypad.o.d ${OBJECTDIR}/interrupt_configuration.o.d ${OBJECTDIR}/adc_interfacing.o.d ${OBJECTDIR}/timer0_interface.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/lcd_control_main.o ${OBJECTDIR}/atemga32a.o ${OBJECTDIR}/interfacing_connection_logic.o ${OBJECTDIR}/phone_keypad.o ${OBJECTDIR}/interrupt_configuration.o ${OBJECTDIR}/adc_interfacing.o ${OBJECTDIR}/timer0_interface.o

# Source Files
SOURCEFILES=lcd_control_main.c atemga32a.c interfacing_connection_logic.c phone_keypad.c interrupt_configuration.c adc_interfacing.c timer0_interface.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/lcd_2x16_interfacing.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATmega32A
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/lcd_control_main.o: lcd_control_main.c  .generated_files/flags/default/ce1f55f4bc9ff976aa29845fc4e0b28899088836 .generated_files/flags/default/2f9e58fd8ce1a2611b0e0fd33168db129b9285f3
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lcd_control_main.o.d 
	@${RM} ${OBJECTDIR}/lcd_control_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/lcd_control_main.o.d" -MT "${OBJECTDIR}/lcd_control_main.o.d" -MT ${OBJECTDIR}/lcd_control_main.o -o ${OBJECTDIR}/lcd_control_main.o lcd_control_main.c 
	
${OBJECTDIR}/atemga32a.o: atemga32a.c  .generated_files/flags/default/646d5d44ea84b6c6ccf3ee77fc5e9e7804383949 .generated_files/flags/default/2f9e58fd8ce1a2611b0e0fd33168db129b9285f3
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/atemga32a.o.d 
	@${RM} ${OBJECTDIR}/atemga32a.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/atemga32a.o.d" -MT "${OBJECTDIR}/atemga32a.o.d" -MT ${OBJECTDIR}/atemga32a.o -o ${OBJECTDIR}/atemga32a.o atemga32a.c 
	
${OBJECTDIR}/interfacing_connection_logic.o: interfacing_connection_logic.c  .generated_files/flags/default/3683d5127fcd3345138e6f23b5df9b4cb3cf29d2 .generated_files/flags/default/2f9e58fd8ce1a2611b0e0fd33168db129b9285f3
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interfacing_connection_logic.o.d 
	@${RM} ${OBJECTDIR}/interfacing_connection_logic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/interfacing_connection_logic.o.d" -MT "${OBJECTDIR}/interfacing_connection_logic.o.d" -MT ${OBJECTDIR}/interfacing_connection_logic.o -o ${OBJECTDIR}/interfacing_connection_logic.o interfacing_connection_logic.c 
	
${OBJECTDIR}/phone_keypad.o: phone_keypad.c  .generated_files/flags/default/7368fe313790a8d90158923aecd4f24f80084096 .generated_files/flags/default/2f9e58fd8ce1a2611b0e0fd33168db129b9285f3
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/phone_keypad.o.d 
	@${RM} ${OBJECTDIR}/phone_keypad.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/phone_keypad.o.d" -MT "${OBJECTDIR}/phone_keypad.o.d" -MT ${OBJECTDIR}/phone_keypad.o -o ${OBJECTDIR}/phone_keypad.o phone_keypad.c 
	
${OBJECTDIR}/interrupt_configuration.o: interrupt_configuration.c  .generated_files/flags/default/f1592b2330a2dffb6fa8420df3afb3f117cf9b42 .generated_files/flags/default/2f9e58fd8ce1a2611b0e0fd33168db129b9285f3
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupt_configuration.o.d 
	@${RM} ${OBJECTDIR}/interrupt_configuration.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/interrupt_configuration.o.d" -MT "${OBJECTDIR}/interrupt_configuration.o.d" -MT ${OBJECTDIR}/interrupt_configuration.o -o ${OBJECTDIR}/interrupt_configuration.o interrupt_configuration.c 
	
${OBJECTDIR}/adc_interfacing.o: adc_interfacing.c  .generated_files/flags/default/3303f327c68f3b38b06461fd9d0c5c1c2378cf39 .generated_files/flags/default/2f9e58fd8ce1a2611b0e0fd33168db129b9285f3
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/adc_interfacing.o.d 
	@${RM} ${OBJECTDIR}/adc_interfacing.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/adc_interfacing.o.d" -MT "${OBJECTDIR}/adc_interfacing.o.d" -MT ${OBJECTDIR}/adc_interfacing.o -o ${OBJECTDIR}/adc_interfacing.o adc_interfacing.c 
	
${OBJECTDIR}/timer0_interface.o: timer0_interface.c  .generated_files/flags/default/15831b047748bf2a48052cb0fedb5e21f83de69b .generated_files/flags/default/2f9e58fd8ce1a2611b0e0fd33168db129b9285f3
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timer0_interface.o.d 
	@${RM} ${OBJECTDIR}/timer0_interface.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/timer0_interface.o.d" -MT "${OBJECTDIR}/timer0_interface.o.d" -MT ${OBJECTDIR}/timer0_interface.o -o ${OBJECTDIR}/timer0_interface.o timer0_interface.c 
	
else
${OBJECTDIR}/lcd_control_main.o: lcd_control_main.c  .generated_files/flags/default/3ef04d583ab9c3611a9a6b68e2cdd42abc7d8430 .generated_files/flags/default/2f9e58fd8ce1a2611b0e0fd33168db129b9285f3
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lcd_control_main.o.d 
	@${RM} ${OBJECTDIR}/lcd_control_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/lcd_control_main.o.d" -MT "${OBJECTDIR}/lcd_control_main.o.d" -MT ${OBJECTDIR}/lcd_control_main.o -o ${OBJECTDIR}/lcd_control_main.o lcd_control_main.c 
	
${OBJECTDIR}/atemga32a.o: atemga32a.c  .generated_files/flags/default/a3bedfdc4035899907a3aee1c4666bf679402d43 .generated_files/flags/default/2f9e58fd8ce1a2611b0e0fd33168db129b9285f3
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/atemga32a.o.d 
	@${RM} ${OBJECTDIR}/atemga32a.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/atemga32a.o.d" -MT "${OBJECTDIR}/atemga32a.o.d" -MT ${OBJECTDIR}/atemga32a.o -o ${OBJECTDIR}/atemga32a.o atemga32a.c 
	
${OBJECTDIR}/interfacing_connection_logic.o: interfacing_connection_logic.c  .generated_files/flags/default/da44f4dc6573d7378fec2d3c725eddc2f0b88f38 .generated_files/flags/default/2f9e58fd8ce1a2611b0e0fd33168db129b9285f3
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interfacing_connection_logic.o.d 
	@${RM} ${OBJECTDIR}/interfacing_connection_logic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/interfacing_connection_logic.o.d" -MT "${OBJECTDIR}/interfacing_connection_logic.o.d" -MT ${OBJECTDIR}/interfacing_connection_logic.o -o ${OBJECTDIR}/interfacing_connection_logic.o interfacing_connection_logic.c 
	
${OBJECTDIR}/phone_keypad.o: phone_keypad.c  .generated_files/flags/default/acf5a040e7525c17ae1c9611a3b95f110ef8cc73 .generated_files/flags/default/2f9e58fd8ce1a2611b0e0fd33168db129b9285f3
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/phone_keypad.o.d 
	@${RM} ${OBJECTDIR}/phone_keypad.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/phone_keypad.o.d" -MT "${OBJECTDIR}/phone_keypad.o.d" -MT ${OBJECTDIR}/phone_keypad.o -o ${OBJECTDIR}/phone_keypad.o phone_keypad.c 
	
${OBJECTDIR}/interrupt_configuration.o: interrupt_configuration.c  .generated_files/flags/default/2c37786fa368d167ecb91f6c33f1d3a7126b4581 .generated_files/flags/default/2f9e58fd8ce1a2611b0e0fd33168db129b9285f3
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupt_configuration.o.d 
	@${RM} ${OBJECTDIR}/interrupt_configuration.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/interrupt_configuration.o.d" -MT "${OBJECTDIR}/interrupt_configuration.o.d" -MT ${OBJECTDIR}/interrupt_configuration.o -o ${OBJECTDIR}/interrupt_configuration.o interrupt_configuration.c 
	
${OBJECTDIR}/adc_interfacing.o: adc_interfacing.c  .generated_files/flags/default/efd5c7c1dda8af31fe84adb0fc00b91ced551b1d .generated_files/flags/default/2f9e58fd8ce1a2611b0e0fd33168db129b9285f3
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/adc_interfacing.o.d 
	@${RM} ${OBJECTDIR}/adc_interfacing.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/adc_interfacing.o.d" -MT "${OBJECTDIR}/adc_interfacing.o.d" -MT ${OBJECTDIR}/adc_interfacing.o -o ${OBJECTDIR}/adc_interfacing.o adc_interfacing.c 
	
${OBJECTDIR}/timer0_interface.o: timer0_interface.c  .generated_files/flags/default/467cc9a229eabd4a60e56bb27ce2df38be8d6946 .generated_files/flags/default/2f9e58fd8ce1a2611b0e0fd33168db129b9285f3
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timer0_interface.o.d 
	@${RM} ${OBJECTDIR}/timer0_interface.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/timer0_interface.o.d" -MT "${OBJECTDIR}/timer0_interface.o.d" -MT ${OBJECTDIR}/timer0_interface.o -o ${OBJECTDIR}/timer0_interface.o timer0_interface.c 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/lcd_2x16_interfacing.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/lcd_2x16_interfacing.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"   -gdwarf-2 -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -gdwarf-3     $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/lcd_2x16_interfacing.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o dist/${CND_CONF}/${IMAGE_TYPE}/lcd_2x16_interfacing.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group  -Wl,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/lcd_2x16_interfacing.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/lcd_2x16_interfacing.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/lcd_2x16_interfacing.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -gdwarf-3     $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/lcd_2x16_interfacing.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o dist/${CND_CONF}/${IMAGE_TYPE}/lcd_2x16_interfacing.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}\\avr-objcopy -O ihex "dist/${CND_CONF}/${IMAGE_TYPE}/lcd_2x16_interfacing.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/lcd_2x16_interfacing.${IMAGE_TYPE}.hex"
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
