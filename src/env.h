

#define DEVELOPMENT
#ifdef DEVELOPMENT
#define DEVICE_NAME "analog-watch-dev"
#else
#define DEVICE_NAME "analog-watch"
#endif
#define BUTTON_PIN 0

#define DAT_PIN 14
#define CLK_PIN 13

#define DS1307_SDA 4
#define DS1307_CLK 5

#define RING_CLOCK_LEDS 60
#define MATRIX_PANEL_WIDTH 32
#define MATRIX_PANEL_HEIGHT 8
#define MATRIX_PANEL_LEDS (MATRIX_PANEL_WIDTH * MATRIX_PANEL_HEIGHT)
#define LED_COUNT (MATRIX_PANEL_LEDS + RING_CLOCK_LEDS) // number of LEDs on the strip

#define TICK_MS 25

#define DEFAULT_STASSID "Vong Cat 3"
#define DEFAULT_STAPSK "78787878"

#define DEFAULT_SETUP_WIFI "{\n\"APSSID\": \"led du go\",\n\"APPSK\": \"123123123\"\n}"
#define DEFAULT_SETUP_LED "{\n\"secondHandColor\": \"#ff0000\",\n\"hourHandColor\": \"#0000ff\",\n\"brightness\": 200,\n\"minuteHandColor\": \"#00ff00\"\n}"
