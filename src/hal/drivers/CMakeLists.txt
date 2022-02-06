include(buildcomponent)

if(${BUILD_PARPORT})
	build_component(NAME hal_parport SOURCES hal_parport.c)
endif()

# drivers (not working on FreeBSD)
if(${CMAKE_SYSTEM} MATCHES "Linux")
	build_component(NAME pci_8255 SOURCES pci_8255.c)
	build_component(NAME hal_tiro SOURCES hal_tiro.c)
	build_component(NAME hal_stg SOURCES hal_stg.c)
	#todo fix vti
	#build_component(NAME hal_vti SOURCES hal_vti.c)
	#todo fix evoreg
	#build_component(hal_evoreg ../drivers/hal_evoreg.c ON)
	#todo fix motenc
	#build_component(hal_motenc ../drivers/hal_motenc.c ON)
	build_component(NAME hal_ax5214h SOURCES hal_ax5214h.c)
	build_component(NAME hal_speaker SOURCES hal_speaker.c)
	build_component(NAME hal_skeleton SOURCES hal_skeleton.c)
	#todo fix opto ac5 driver
	#build_component(opto_ac5 ../drivers/opto_ac5.c ON)
endif()
build_component(NAME hal_gm SOURCES hal_gm.c)
build_component(NAME hal_ppmc SOURCES hal_ppmc.c)

build_component(NAME hal_bb_gpio SOURCES hal_bb_gpio.c)
build_component(NAME hal_pi_gpio SOURCES hal_pi_gpio.c cpuinfo.c)

set(HOSTMOT2_SOURCES
		mesa-hostmot2/hostmot2.c
		mesa-hostmot2/abs_encoder.c
		mesa-hostmot2/bitfile.c
		mesa-hostmot2/bspi.c
		mesa-hostmot2/dpll.c
		mesa-hostmot2/encoder.c
		mesa-hostmot2/inm.c
		mesa-hostmot2/inmux.c
		mesa-hostmot2/ioport.c
		mesa-hostmot2/led.c
		mesa-hostmot2/pins.c
		mesa-hostmot2/pktuart.c
		mesa-hostmot2/pwmgen.c
		mesa-hostmot2/raw.c
		mesa-hostmot2/rcpwmgen.c
		mesa-hostmot2/resolver.c
		mesa-hostmot2/sserial.c
		mesa-hostmot2/ssr.c
		mesa-hostmot2/stepgen.c
		mesa-hostmot2/tp_pwmgen.c
		mesa-hostmot2/tram.c
		mesa-hostmot2/uart.c
		mesa-hostmot2/watchdog.c
		mesa-hostmot2/xy2mod.c
		)
build_component(NAME hostmot2 SOURCES ${HOSTMOT2_SOURCES})

build_component(NAME hm2_test SOURCES mesa-hostmot2/hm2_test.c mesa-hostmot2/bitfile.c)
#obj-$(CONFIG_HOSTMOT2) += hostmot2.o hm2_test.o hm2_pci.o hm2_7i43.o hm2_7i90.o setsserial.o
#ifeq ($(BUILD_SYS),uspace)
#obj-$(CONFIG_HOSTMOT2) += hm2_eth.o hm2_spi.o hm2_rpspi.o
#endif
#hm2_7i90-objs :=                          \
#    hal/drivers/mesa-hostmot2/hm2_7i90.o  \
#    hal/drivers/mesa-hostmot2/bitfile.o   \
#    $(MATHSTUB)
#hm2_7i43-objs :=                          \
#    hal/drivers/mesa-hostmot2/hm2_7i43.o  \
#    hal/drivers/mesa-hostmot2/bitfile.o   \
#    $(MATHSTUB)
#hm2_pci-objs  :=                          \
#    hal/drivers/mesa-hostmot2/hm2_pci.o   \
#    hal/drivers/mesa-hostmot2/bitfile.o   \
#    $(MATHSTUB)
#hm2_eth-objs  :=                          \
#    hal/drivers/mesa-hostmot2/hm2_eth.o   \
#    $(MATHSTUB)
#hm2_spi-objs  :=                          \
#    hal/drivers/mesa-hostmot2/hm2_spi.o   \
#    $(MATHSTUB)
#hm2_rpspi-objs  :=                        \
#    hal/drivers/mesa-hostmot2/hm2_rpspi.o   \
#    $(MATHSTUB)
#hm2_test-objs :=                          \
#    hal/drivers/mesa-hostmot2/hm2_test.o  \
#    hal/drivers/mesa-hostmot2/bitfile.o   \
#    $(MATHSTUB)
#setsserial-objs :=                        \
#    hal/drivers/mesa-hostmot2/setsserial.o  \
#    $(MATHSTUB)
