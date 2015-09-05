commandArray = {}
vals = {8,8,9,16,25,36,49,64,81,100,121,144,169,196,225,256,289,324,361,400,441,484,529,576,625,676,729,841,900,961,1024,1024}

DomDevice = 'Wifi1'
IP = '10.100.1.50'
Port = '43333'

LEDtarget = 'LED2_Target='
Fadetimer = 'Fadetimer2='
Waittime = '2'
FadeTime1 = '2000'
 if devicechanged[DomDevice] then
	print("dev " .. devicechanged[DomDevice]);

	if(devicechanged[DomDevice]=='Off') then DomValue = 0;
	   print ("Turning off " .. DomDevice);
	   runcommand = "echo " .. (Fadetimer) .."" .. (FadeTime1) .. "," .. (LEDtarget) .. "-1  | nc -w " .. (Waittime) .. " " .. (IP) .. " " .. (Port) .. " ";
	   print (runcommand);
	   os.execute(runcommand);
	 return commandArray
	elseif(devicechanged[DomDevice]=='On') then
	   print ("Turning on " .. DomDevice);
           runcommand = "echo " .. (Fadetimer) .."" .. (FadeTime1) .. "," .. (LEDtarget) .. "-2  | nc -w " .. (Waittime) .. " " .. (IP) .. " " .. (Port) .. " ";
           print (runcommand);
           os.execute(runcommand);
         return commandArray
	else
    	DomValue = (otherdevices_svalues[DomDevice]);
   end

   CalcValue = vals[DomValue+1];
   print ("Value received from Domoticz was " .. (DomValue) .." ");
   print ("Calculated value for ESP is " .. (CalcValue) .." ");
   if(CalcValue<0) then CalcValue=0; end
   print ("Dimming "  .. (DomDevice) .. " to " .. (CalcValue) .. " ");
   runcommand = "echo " .. (Fadetimer) .."" .. (FadeTime1) .. "," .. (LEDtarget) .. "" .. (CalcValue) .. " | nc -w " .. (Waittime) .. " " .. (IP) .. " " .. (Port) .. " ";
   print (runcommand);
   os.execute(runcommand);
 end

return commandArray

