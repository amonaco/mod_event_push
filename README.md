mod_event_push
==============

* This module encondes FS events and posts them to a Comet server on a specified websocket channel. It can be used to get live FS events on broswers connected to this Comet server. 
* It has been partially tested with https://github.com/wandenberg/nginx-push-stream-module but should work with any Comet/websocket/long-pooling server
* This code is experimental

tasks
=====
* Read http parameters and other parameters from config file
* Add configuration file parsing
* Fix configuration loading issue:

---- BEGIN ----
freeswitch@internal> load mod_event_push 
+OK Reloading XML
-ERR [module load file routine returned an error]

2013-06-13 12:48:49.133335 [INFO] mod_enum.c:872 ENUM Reloaded
2013-06-13 12:48:49.133335 [INFO] switch_time.c:1173 Timezone reloaded 530 definitions
2013-06-13 12:48:49.133335 [ERR] mod_event_push.c:149 Tag "settings" not found in configuration file: mod_event_push.conf 
2013-06-13 12:48:49.133335 [CRIT] switch_loadable_module.c:1332 Error Loading module /usr/local/freeswitch/mod/mod_event_push.so
**Module load routine returned an error**
---- END ----

notes
=====
* Review functions for dialplan module (probably called from Lua?): All _ivr_ functions are here: /usr/local/src/freeswitch/src/include/switch_ivr.h
* FS Core JSON reference: FS cJSON parsing routines: /usr/local/src/freeswitch/src/include/switch_json.h
