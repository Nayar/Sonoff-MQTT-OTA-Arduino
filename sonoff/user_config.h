/*********************************************************************************************\
 * User specific configuration parameters
 * 
 * Select hardware MODULE:
 *  SONOFF          = Sonoff, Sonoff SV, Sonoff Dual, Sonoff TH 10A/16A, S20 Smart Socket
 *  SONOFF_POW      = Sonoff Pow (Experimental until tested)
 *  ELECTRO_DRAGON  = Electro Dragon (Relay 2 only)
 * 
\*********************************************************************************************/

#define MODULE                 SONOFF       // Hardware module type (SONOFF, SONOFF_POW or ELECTRO_DRAGON)

#define PROJECT                "sonoff"     // PROJECT is used as the default topic delimiter and OTA file name
                                            // As an IDE restriction it needs to be the same as the main .ino file
                                            
#define CFG_HOLDER             0x20160520   // Change this value to load default configuration parameters
#define SAVE_DATA              1            // Save changed parameters to Flash (0 = disable, 1 - 3600 seconds)
#define SAVE_STATE             1            // Save changed power state to Flash (0 = disable, 1 = enable)

// Wifi
#define STA_SSID               "indebuurt3"      // Wifi SSID
#define STA_PASS               "VnsqrtnrsddbrN"  // Wifi password
#define WIFI_HOSTNAME          "%s-%04d"         // Expands to <MQTT_TOPIC>-<last 4 decimal chars of MAC address>
#define WIFI_CONFIG_TOOL       WIFI_WPSCONFIG    // Default tool if wifi fails to connect (WIFI_SMARTCONFIG, WIFI_MANAGER or WIFI_WPSCONFIG)

// Syslog
#define SYS_LOG_HOST           "domus1"
#define SYS_LOG_PORT           514
#define SYS_LOG_LEVEL          LOG_LEVEL_NONE
#define SERIAL_LOG_LEVEL       LOG_LEVEL_INFO
#define WEB_LOG_LEVEL          LOG_LEVEL_INFO

// Ota
#if (ARDUINO >= 168)
  #define OTA_URL              "http://domus1:80/api/arduino/" PROJECT ".ino.bin"
#else
  #define OTA_URL              "http://domus1:80/api/arduino/" PROJECT ".cpp.bin"
#endif

// MQTT
#define MQTT_HOST              "domus1"
#define MQTT_PORT              1883

#define MQTT_CLIENT_ID         "DVES_%06X"  // Also fall back topic using Chip Id = last 6 characters of MAC address
#define MQTT_USER              "DVES_USER"
#define MQTT_PASS              "DVES_PASS"

#define SUB_PREFIX             "cmnd"       // Sonoff devices subscribe to:- cmnd/MQTT_TOPIC and cmnd/MQTT_GRPTOPIC
#define PUB_PREFIX             "stat"       // Sonoff devices publish to:- stat/MQTT_TOPIC
#define PUB_PREFIX2            "tele"       // Sonoff devices publish telemetry data to:- tele/MQTT_TOPIC/UPTIME, POWER/LIGHT and TIME
                                            // May be named the same as PUB_PREFIX
#define MQTT_TOPIC             PROJECT
#define MQTT_GRPTOPIC          PROJECT"s"   // Group topic
#define MQTT_BUTTON_RETAIN     0            // Button may send retain flag (0 = off, 1 = on)

// Domoticz  
#define DOMOTICZ_IN_TOPIC      "domoticz/in"
#define DOMOTICZ_OUT_TOPIC     "domoticz/out"
#define DOMOTICZ_RELAY_IDX1    0            // Sonoff Relay 1 (0 = disable domoticz)
#define DOMOTICZ_RELAY_IDX2    0            // Sonoff Dual Relay 2
#define DOMOTICZ_KEY_IDX1      0            // Button single press (0 = disable)
#define DOMOTICZ_KEY_IDX2      0            // Button double press (0 = disable)
#define DOMOTICZ_UPDATE_TIMER  0            // Send relay status (0 = disable, 1 - 3600 seconds) (Optional)

// MQTT - Telemetry
#define TELE_PERIOD            300          // Telemetry (0 = disable, 2 - 3600 seconds)
#define SEND_TELEMETRY_UPTIME               // Enable sending uptime telemetry (if disabled will still send hourly message)
#define SEND_TELEMETRY_RSSI                 // Enable sending wifi RSSI telemetry
#define SEND_TELEMETRY_POWER                // Enable sending power telemetry

// HTTP
#define WEB_SERVER             2            // Web server (0 = Off, 1 = Start as User, 2 = Start as Admin)

// Time - Up to three NTP servers in your region
#define NTP_SERVER1            "pool.ntp.org"
#define NTP_SERVER2            "nl.pool.ntp.org"
#define NTP_SERVER3            "0.nl.pool.ntp.org"

// Time - Start Daylight Saving Time and timezone offset from UTC in minutes
#define TIME_DST               Last, Sun, Mar, 2, +120  // Last sunday in march at 02:00 +120 minutes

// Time - Start Standard Time and timezone offset from UTC in minutes
#define TIME_STD               Last, Sun, Oct, 3, +60   // Last sunday in october 02:00 +60 minutes

// Application
#define APP_TIMEZONE           1            // +1 hour (Amsterdam) (-12 .. 12 = hours from UTC, 99 = use TIME_DST/TIME_STD)
#define APP_LEDSTATE           1            // Do not show power state (1 = Show power state)

/*********************************************************************************************\
 * Enable feature by removing leading // or disable feature by adding leading //
\*********************************************************************************************/

//#define USE_SPIFFS                          // Switch persistent configuration from flash to spiffs (+24k code, +0.6k mem)
#define USE_WEBSERVER                       // Enable web server and wifi manager (+37k code, +2k mem)
#define USE_DOMOTICZ                        // Enable Domoticz (+3k code, +0.2k mem)

/*********************************************************************************************\
 * Sonoff specific paremeters
\*********************************************************************************************/

#if MODULE == SONOFF                        // programming header 1:3.3V 2:rx 3:tx 4:gnd
  #define APP_NAME             "Sonoff module"
  #define LED_PIN              13           // GPIO 13 = Green/Blue Led (0 = On, 1 = Off) - Sonoff
  #define LED_INVERTED         1            // 0 = (1 = On, 0 = Off), 1 = (0 = On, 1 = Off)
  #define REL_PIN              12           // GPIO 12 = Red Led and Relay (0 = Off, 1 = On)
  #define KEY_PIN              0            // GPIO 00 = Button
/*-------------------------------------------------------------------------------------------*/
  #define DSB_PIN              14           // GPIO 14 = DS18B20 (Sonoff_TH10A(16A), Sonoff SV)
//  #define SEND_TELEMETRY_DS18B20            // Enable sending temperature telemetry
/*-------------------------------------------------------------------------------------------*/
  #define DHT_PIN              14           // GPIO 14 = AM2301 (Sonoff_TH10A(16A), Sonoff SV)
  #define DHT_TYPE             AM2301       // DHT module type (DHT11, DHT21, DHT22, AM2301, AM2302 or AM2321)
//  #define SEND_TELEMETRY_DHT                // Enable sending temperature and humidity telemetry

/*********************************************************************************************\
 * Sonoff Pow specific parameters
\*********************************************************************************************/

#elif MODULE == SONOFF_POW                  // programming header 1:3.3V 2:rx 3:tx 4:gnd
  #define APP_NAME             "Sonoff Pow module"
  #define LED_PIN              15           // GPIO 15 = Green Led (0 = On, 1 = Off) - Sonoff
  #define LED_INVERTED         0            // 0 = (1 = On, 0 = Off), 1 = (0 = On, 1 = Off)
  #define REL_PIN              12           // GPIO 12 = Red Led and Relay (0 = Off, 1 = On)
  #define KEY_PIN              0            // GPIO 00 = Button
/*-------------------------------------------------------------------------------------------*/
  #define HLW_SEL              5            // GPIO 05 = HLW8012 Sel input (Sonoff Pow)
  #define HLW_CF1              13           // GPIO 13 = HLW8012 CF1 voltage / current (Sonoff Pow)
  #define HLW_CF               14           // GPIO 14 = HLW8012 CF power (Sonoff Pow)
  #define SEND_TELEMETRY_ENERGY             // Enable sending energy telemetry
  
/*********************************************************************************************\
 * Electrodragon specific paremeters
\*********************************************************************************************/

#elif MODULE == ELECTRO_DRAGON              // programming header 5V/3V/gnd/
  #define APP_NAME             "ElectroDragon module"
  #define LED_PIN              16           // GPIO 16 = Led (0 = Off, 1 = On)
  #define LED_INVERTED         0            // 0 = (1 = On, 0 = Off), 1 = (0 = On, 1 = Off)
  #define REL_PIN              13           // GPIO 13 = Red Led and Relay 1 (0 = Off, 1 = On)
  #define KEY_PIN              2            // GPIO 02 = Button 1
  #define REL2_PIN             12           // GPIO 12 = Red Led and Relay 2 (0 = Off, 1 = On)
  #define KEY2_PIN             0            // GPIO 00 = Button 2
/*-------------------------------------------------------------------------------------------*/
  #define DSB_PIN              4            // GPIO 04 = DS18B20
//  #define SEND_TELEMETRY_DS18B20            // Enable sending temperature telemetry
/*-------------------------------------------------------------------------------------------*/
  #define DHT_PIN              14           // GPIO 14 = DHT22
  #define DHT_TYPE             DHT22        // DHT module type (DHT11, DHT21, DHT22, AM2301, AM2302 or AM2321)
//  #define SEND_TELEMETRY_DHT                // Enable sending temperature and humidity telemetry

/*********************************************************************************************\
 * No user configurable items below
\*********************************************************************************************/
 
#else
  #error "Select either module SONOFF, SONOFF_POW or ELECTRO_DRAGON"
#endif

#ifdef SEND_TELEMETRY_DS18B20 && SEND_TELEMETRY_DHT
#if DSB_PIN == DHT_PIN
  #error "Select either SEND_TELEMETRY_DS18B20 or SEND_TELEMETRY_DHT or use different GPIOs"
#endif
#endif

