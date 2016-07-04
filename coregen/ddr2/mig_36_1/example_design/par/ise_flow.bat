call rem_files.bat



echo Synthesis Tool: XST

mkdir "../synth/__projnav" > ise_flow_results.txt
mkdir "../synth/xst" >> ise_flow_results.txt
mkdir "../synth/xst/work" >> ise_flow_results.txt

xst -ifn ise_run.txt -ofn mem_interface_top.syr -intstyle ise >> ise_flow_results.txt
ngdbuild -intstyle ise -dd ../synth/_ngo -uc mig_36_1.ucf -p xc3sd3400afg676-5 mig_36_1.ngc mig_36_1.ngd >> ise_flow_results.txt

map -intstyle ise -detail -cm speed -pr off -c 100 -o mig_36_1_map.ncd mig_36_1.ngd mig_36_1.pcf >> ise_flow_results.txt
par -w -intstyle ise -ol std -t 1 mig_36_1_map.ncd mig_36_1.ncd mig_36_1.pcf >> ise_flow_results.txt
trce -e 100 mig_36_1.ncd mig_36_1.pcf >> ise_flow_results.txt
bitgen -intstyle ise -f mem_interface_top.ut mig_36_1.ncd >> ise_flow_results.txt

echo done!
