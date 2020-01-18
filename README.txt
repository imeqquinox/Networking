To launch the application:
- First launch the server exe.
- Then a minimum of 2 clients must be launched to run the game. 

For networking over 2 sperate devices the IP must be changed within the source file. 

To test packet loss there is a rand() within the game update which is commented out, uncomment out and the clients will then only send 60% of packets.

if testing from the same device be carefull not to open 2 clients one after the other quickly due to what was discussed within the powerpoint. 