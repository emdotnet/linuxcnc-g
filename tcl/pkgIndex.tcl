package ifneeded "Linuxcnc" 1.0 \
 [list source [file join $dir linuxcnc.tcl]]
package ifneeded "Hal" 1.0 \
 [list load [file join $env(EMC2_LIB_DIR) libhalsh[info sharedlibextension]]]

# Support for inifile entry: [DISPLAY]TKPKG = Ngcgui
package ifneeded "Ngcgui" 1.0 \
  [list source [file join $dir ngcgui_app.tcl]]

# Support for inifile entry: [DISPLAY]TKPKG = Ngcguittt
package ifneeded "Ngcguittt" 1.0 \
  [list source [file join $dir ngcgui_ttt.tcl]]
