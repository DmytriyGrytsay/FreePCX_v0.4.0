cd /home/kruger/FreePCX_v0.4.0/ise/mb
if { [ catch { xload xmp mb.xmp } result ] } {
  exit 10
}

if { [catch {run init_bram} result] } {
  exit -1
}

exit 0
