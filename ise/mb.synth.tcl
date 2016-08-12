proc pnsynth {} {
  cd /home/kruger/FreePCX_v0.4.0/ise/mb
  if { [ catch { xload xmp mb.xmp } result ] } {
    exit 10
  }
  if { [catch {run netlist} result] } {
    return -1
  }
  return $result
}
if { [catch {pnsynth} result] } {
  exit -1
}
exit $result
