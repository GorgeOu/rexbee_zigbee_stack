3.0.0 - sdk 3.0.0a

<<<<<<< HEAD
Unpublished
2.4.1 - sdk 2.0.xx
- Added zdo lqi rsp & rgt rsp
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

2.4.1 - sdk 2.0.24
- Added fast join v3 apis(commmon)
- Added fast join v3 encryption mechanim(commmon)

2.4.1 - sdk 2.0.23
- Optimized rx cca failure when received a strong signal(common)

2.4.0 - sdk 2.0.22
- Fixed a mt plugin issue(end device)

2.4.0 - sdk 2.0.21
- Fixed an zero detect plugin issue(common)

*(Important update) 2.4.0 - sdk 2.0.20
Feb 22, 2023 (end device 2.4.0 | router 2.4.0 | coordinator 2.4.0) with sdk 2.0.20
- Optimized the broadcast & multicast retransmission capability(common)
- Fixed an aps message buffer issue(router)
- Optimized the routing algorithm when nodes are dense(router)
- Added custom zcl command register api(common)
- Once an ota notify command is received, next image request must be sent(common)
- Added app event v3 api, support register event with args(common)
- Added wireless flow control maintainer(coordinator)
- Fixed an add scene with color cluster extension field filter issue(common)
- Optimized error gpio interrupt filter decision(common)

*(Important update) 2.3.0 - sdk 2.0.14
Sep 12, 2022 (end device 2.3.0 | router 2.3.0 | coordinator 2.3.0) with sdk 2.0.14

Nov 22, 2022 - stack 2.3.0 / sdk 2.0.19
- Modified flash enable safety threshold 1800 -> 2200(common)
- Added printf function type 'a'(common)
- Added ota plugin invoke wait for data callback(common) 

Nov 18, 2022 - stack 2.3.0 / sdk 2.0.18
- Added ota timeout plugin timeout callback register(common)

Nov 1, 2022 - stack 2.3.0 / sdk 2.0.17
- Added time server plugin(common)
- Added zero cross detect edge select api(common)
- Optimized no debug version code size(common)

Sep 30, 2022 - stack 2.3.0 / sdk 2.0.16
- Optimized color bulb state handler(common)
- Optimized coo device discovery(coordinator)

Sep 15, 2022 - stack 2.3.0 / sdk 2.0.15
- Added ota plugin timeout protection api(common)
- Fixed an issue where the move to level with onoff command was executed incorrectly(common)

Sep 12, 2022 - stack 2.3.0 / sdk 2.0.14
- Optimized poll event schedule(end device)
- Added rwp ota command handler(common) 
- Added network update request command handler(router & coordinator)
- Optimized timer event switch(common)
- Added zbck enhanced discovery & resp(common)  
- Added zbck identify(common)
- Added uart at command app handle register(common)
- Added sub gateway plugin(coordinator)
- Added interpan message register(common)
- Added uart rx keep wakeup maintain, keep awake if uart rx state busy(end device)
- Optimized color bulb pwm handler(common)
- Fixed a parent send rejoin resp issue(router)
- Added scan network with channel mask & scan duration api(common)
- Added fast attribute server read & write api(common)
- Fixed an child message broker issue that will not relay child broadcast message(router)
- Added neighbor leaved, remove them from NTB(router)
- Added joined network, reconfig frame counter(common)
- Optimized app event handler(common)
- Modified vain network network start callback(common)
- Fixed a pwm task event finished callback issue(common)
- Added move color temperature move stop callback(common)
- Modified recover & backup network api, added network state check(common)
- Modified default resp - disable default resp mask set to 1(common)
- Added ota plugin apis timed image block req / notify condition trigger req(common)
- Fixed a network start callback issue(common)
- Added rexense main infomation attribute(common)
- Fixed an ota issue(end device) 
- Added end device timeout request config(end device)
- Fixed some door lock plugin issues(common) 

May 21, 2022 (end device 2.2.4 | router 2.2.4 | coordinator 2.2.4)
- Fixed a network frame counter issue(common) 
- Added scan network v2 result callback & next scan interval config(common)
- Added reporting plugin reported callback(common)
- Added reporting plugin update record data - api app_reporting_plugin_update_data(common)
- Added network start callback(common)
- Modified stop pwm, pwm stop invoking after gpio config(common) 

April 13, 2022 (end device 2.2.3 | router 2.2.3 | coordinator 2.2.3)
- Added get last comm time api
- Added backup/recover network api
- Added scan network random backoff api
- Fixed a vain network issue

March 20, 2022 (end device 2.2.2 | router 2.2.2 | coordinator 2.2.2)
- Optimized neighbor link alg(common)
- Added sim eeprom protect(common)
- Added flash write & erase vdd voltage limit(common)
- Added zbck mac direct raw message handle(common)
- Fixed a pwm driver issue(common)

March 1, 2022 (end device 2.2.1 | router 2.2.1 | coordinator 2.2.1)
- Fixed a uart driver issue that uart data will lost when the frame interval less than 5ms(common)
- Optimized route discovery alg(common)
- Added coordinator library support(coordinator)

February 14, 2022 (end device version 2.2.0 and router version 2.2.0)
- Modified mac layer transmit queue handler(common)
- Optimized routing alg(common)
- Added complementary pwm driver(common)

January 24, 2022 (end device version 2.1.6 and router version 2.1.6)
- Added mass production test api(common)
- Fixed a issue that zll scan resp use wrong mac address(common)

December 22, 2021 (end device version 2.1.5 and router version 2.1.5)
- Modified lqi map table(common)
- Fixed an ota notify command issue(common)

December 17, 2021 (end device version 2.1.4 and router version 2.1.4)
- Added network address request parser(router)
- Added 2M virtual serial(common)
- Added separate virtual serial buffer, prevent conflicts between serial ports and virtual serial ports(common)
- Fixed message packet errors(common)
- Modified irq stk size to 0x600(re support need update)(common)

December 8, 2021 (end device version 2.1.3 and router version 2.1.3)
- Sync reporting configuration response & read reporting configuration response zcl sequence(common)
- Added door lock plugin(common)
- Optimized wakeup time(end device)

December 4, 2021 (end device version 2.1.3b and router version 2.1.3b)
- Added re support plugin(common)

November 30, 2021 (end device version 2.1.3a and router version 2.1.3a)
- Optimized code size(common)
- Added model id & mfg name cib configuration, support AT command & api(common)
- Added uart token configuration api(common)

*(Important update)
November 26, 2021 (end device version 2.1.2 and router version 2.1.2)
- Added zdo update network parse(change channel support)(router)
- Router node packet buffer increase(router)
- Fixed an issue that pwm second mode no output(common)
- Added battery plugin external measure pin support(common)

November 16, 2021 (end device version 2.1.2c and router version 2.1.2c)
- Added zdo update network parse(change channel support)(router)
- Router node packet buffer increase(router)
- Added virtual gpio PORTM & N(common)
- Zdo & zcl message size up to 82, if length > 74, network layer source mac will be remove(common)
- Added aps message filter plugin, default register in universal plugin init(common)
- Added basic cluster command reset factory new callback register(common)
- Optimized router build alg(router)
- Added i2c driver api(common)
- Fixed an issue that pwm gradual change will be faster than setting

November 1, 2021 (end device version 2.1.1 and router version 2.1.1)
- Added zigbee light link(ZLL) support, initiator(remote) & target(light) (common)
- Optimized pwm graient function(common)
- Added log10 & log function support(common)
- Added printf %f support(common)
- Added debug printf, use AT+DEBUG(common)
- Fixed a irq stack overflow issue

*(Important update)
September 28, 2021 (end device version 2.1.0 and router version 2.1.0)
- Optimized scene table remove all speed(common)
- Fixed an issue that fast join commission will drop network key when reboot(common)
- Optimized phy&mac layer performance(common)
- Fixed an issue that scene table will be erased after ota(common)
- Fixed an issue that command list out of memory errors
- Update boot link file & cstartup

September 16, 2021 (end device version 2.0.9 and router version 2.0.9)
- Optimized scene table erase speed(common)
- Optimized zero detect plugin detect trigger occasion(common) 

*(Important update) 
September 15, 2021 (end device version 2.0.8 and router version 2.0.8)
- Fixed a eeprom issue that flash will erase 0x78000 address when filp over(common)
- Fixed an issue that message will send failure in post attribute change(common)
- Fixed an issue that zone plugin enroll request fill wrong zone type & mfg code(common)
- Added reporting plugin reporting table data sent callback register(common)

*(Important update) 
September 1, 2021 (end device version 2.0.7 and router version 2.0.7)
- Added zcl scene v2 plugin support, max support entry count(dynamic adjust by single scene entry size, max 100)(common)
- Added zcl window covering plugin support(common)
- Fixed pa module tx power max limit & default value(common)
- Fixed a color control cluster scene handle & view scene issue(common)
- Added ota process callback(common)
- Added pa module config select, need update common_implements.c(common)

August 26, 2021 (end device version 2.0.6 and router version 2.0.6)
- Added zcl color plugin support(common)

August 19, 2021 (end device version 2.0.5 and router version 2.0.5)
- Fixed an issue that group message will be dropped(common)
- Optimized binding table read & write rate, added binding table fetch in ram api(common)

*(Important update) 
* August 15, 2021 (end device version 2.0.4 and router version 2.0.4)
- Optimized children message queue distribute(router)
- Optimized cca detect & broadcast backoff(router)
 
July 29, 2021 (end device version 2.0.3 and router version 2.0.3)
- Added zcl level plugin support(common)

July 25, 2021 (end device version 2.0.2 and router version 2.0.2)
- Added mfg test gpio-test(common)
- Fixed an issue that caused child cache memory release failure(router)
- Fixed an issue that end device call leave_network_detect_callback when recevied leave with rejoin command(end device)

July 25, 2021 (end device version 2.0.1 and router version 2.0.1)
- Optimized RREQ broadcast reply handle(router)
- Optimized user interface callback function calls(common)

July 14, 2021 (end device version 2.0.0 and router version 2.0.0)
- Added router on off demo

July 7, 2021 (end device version 1.1.5 and router version 1.1.5)
- Optimized source route handle, device droped message when not find next hop and no source route list
- Fixed an issue leaving handle have not stop tc link update
- Optimized broadcast relay RREQ select
- Added beacon frame pending address field parse(incompatible with nxp gateway)

July 2, 2021 (end device version 1.1.4 and router version 1.1.4)
- Optimized two way link neighbor maintain
- Fixed an issue message table droped conflict aps counter aps ack & aps message
- Added special neighbor & child table request handler
- Added leave info record

June 21, 2021 (end device version 1.1.3 and router version 1.1.3)
- Added zbit and ut flash uid read support
- Fixed a route table maintian issue
- Optimized RREQ handle
- Optimized lqi and link cost alg

June 15, 2021 (end device version 1.1.2 and router version 1.1.2)
- Optimized router status maintain
- Fixed a reporting issue when configure unknow attribute
- Fixed a end device network info issue, clear parent frame counter when lost parent
- Added zero cross detection plugin implement
- Fixed an issue frame counter could not be cleared when switch parent, in this case, device will drop parent message

June 9, 2021 (end device version 1.1.1 and router version 1.1.1)
- Added led task implement
- Added rexense fast join implement
- Added new door sensor demo

June 1, 2021 (end device version 1.1.0 and router version 1.1.0)
Update end device 1.1.0 and router 1.1.0: 
- Fixed some reporting plugin issue
- Fixed some ota plugin issue
- Added hal timer event management implement
- Optimized router device child message handler
- Added more app_user_device_info_t member
- Added rejoin success callback
- Added battery monitor plugin implement
- Added diagnostic info plugin implement
- Added button & contact plugin implement
- Added identify plugin command register implement
- Added ias zone plugin implement

May 9, 2021 (end device version 1.0.5 and router version 1.0.5)
Update router 1.0.5: 
- Fixed leave announce and device announce release issue
- Fixed end device poll once behind leave announce
- Added child table frame counter filter
- Added router permit join handler
- Optimized joining and leaving processor
- Modified user config, use struct app_user_device_info_t now
- Added ota plugin implement
- Added reporting plugin implement

April 16, 2021 (router version 1.0.4)
Update router 1.0.4: 
- Fixed a issue when aps counter 0xff->0x00, a send failure may occur
- Added association server support 
- Added soure router enable message parse and relay support

April 9, 2021 (end device version 1.0.4 and router version 1.0.3)
Update end device 1.0.4 and router 1.0.3: 
- Added pwm driver support
- Added join network via install code generate link key support
- Modified rexense signature
- Added route record reply
- Optimized neighbor's interaction
- Peel plugin api, register in app_plugin_init_callback
- Added rf test command line support
- Added crystal calibration support

March 24, 2021 (end device version 1.0.3 and router version 1.0.2)
Update end device 1.0.3 and router 1.0.2: 
- Fixed sws pin wakeup issue
- Added rexense universal project callbacks register for compatibility
- Added adc measure api and battery monitor api.
- Fixed transport key sequence known compatibility issues.
- Added app sim eeprom api
- Fixed issues with ti zigbee stack interaction
- Use new code style, compatible with older version's api 

February 20, 2021 (end device version 1.0.2)
Update end device 1.0.2: 
- Added new event register api v2
- Improved poll controller
- Added app register layer callbacks

January 29, 2021 (end device version 1.0.1)
Update end device 1.0.1: 
- Fixed wakeup source handler
- Improved end device recover wakeup from deep sleep, speed up loading

January 28, 2021 (end device version 1.0.0)
Update end device 1.0.0: 
- Alpha, provide end device demo.

January 7, 2021 (router version 1.0.0)
Update router 1.0.0: 
- Alpha, provide router demo.