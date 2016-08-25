#define STATE_CHARGING		0
#define STATE_DISCHARGING	1
#define STATE_CHARGED		2
#define STATE_FULL			STATE_CHARGED
#define STATE_UNKNOWN		3

void bat_tray_init();
void bat_tray_show();
void bat_tray_hide();
int  get_battery_state();
int  get_bat_num();
