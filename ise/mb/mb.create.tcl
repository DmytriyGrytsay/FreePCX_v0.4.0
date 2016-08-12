cd D:/FreePCX_v0.4.0/ise/mb
if { [xload new mb.xmp] != 0 } {
  exit -1
}
xset arch spartan3adsp
xset dev xc3sd3400a
xset package fg676
xset speedgrade -5
xset simulator isim
if { [xset hier sub] != 0 } {
  exit -1
}
set bMisMatch false
set xpsArch [xget arch]
if { ! [ string equal -nocase $xpsArch "spartan3adsp" ] } {
   set bMisMatch true
}
set xpsDev [xget dev]
if { ! [ string equal -nocase $xpsDev "xc3sd3400a" ] } {
   set bMisMatch true
}
set xpsPkg [xget package]
if { ! [ string equal -nocase $xpsPkg "fg676" ] } {
   set bMisMatch true
}
set xpsSpd [xget speedgrade]
if { ! [ string equal -nocase $xpsSpd "-5" ] } {
   set bMisMatch true
}
if { $bMisMatch == true } {
   puts "Settings Mismatch:"
   puts "Current Project:"
   puts "	Family: spartan3adsp"
   puts "	Device: xc3sd3400a"
   puts "	Package: fg676"
   puts "	Speed: -5"
   puts "XPS File: "
   puts "	Family: $xpsArch"
   puts "	Device: $xpsDev"
   puts "	Package: $xpsPkg"
   puts "	Speed: $xpsSpd"
   exit 11
}
#default language
xset hdl vhdl
xset intstyle ise
save proj
exit
