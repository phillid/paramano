#ifndef STRINGS_H
#define STRINGS_H
	#ifdef LANG_FR
		////////////////////////////////////////////////////////////////
		// FRANCAIS
		#define S_TRAYFREQ_SET_C_FILE_OPEN_ERROR			"ERREUR: Pouvais pas ecrit à %s\n"
		#define S_TRAYFREQ_SET_C_NO_ARGS					"Utiliser -g pour activer les profils or -f pour activer les fréquences\n"
		#define S_TRAYFREQ_SET_C_SET_FREQUENCY_ARG			"Indiquer la fréquence avec un -f\n"
		#define S_TRAYFREQ_SET_C_SET_GOVERNOR_ARG			"Indiquer le profil avec un -g\n"
		#define S_TRAYFREQ_SET_C_SET_CORE_ARG				"Indiquer le core avec un -c\n"

		#define S_TRAY_C_GOVERNOR							"Profil: %s\n"
		#define S_TRAY_C_CPU								"CPU%i: %s%s"

		#define S_TRAYFREQ_C_GTK_ERROR						"Erreur gtk: gtk_init_check est FALSE.\nJe partes."
		#define S_TRAYFREQ_C_CONFIG_FILE_ERROR				"[Translate me] Failed to open config files!\n"

		#define S_BAT_TRAY_C_BATTERY_FULL					"Complètement chargée"
		#define S_BAT_TRAY_C_BATTERY_CHARGING				"Charging (%i%%)"
		#define S_BAT_TRAY_C_BATTERY_DISCHARGING			"Discharging (%i%%)"
		#define S_BAT_TRAY_C_BATTERY_UNKNOWN				"?"
		////////////////////////////////////////////////////////////////

	#else /* ifdef LANG_FR */
		////////////////////////////////////////////////////////////////
		// ENGLISH
		#define S_TRAYFREQ_SET_C_FILE_OPEN_ERROR			"FAILED: Couldn't open %s for writing\n"
		#define S_TRAYFREQ_SET_C_NO_ARGS					"Use -g to set the governor or -f to set the frequency\n"
		#define S_TRAYFREQ_SET_C_SET_FREQUENCY_ARG			"Pass the frequency with -f\n"
		#define S_TRAYFREQ_SET_C_SET_GOVERNOR_ARG			"Pass the governor with -g\n"
		#define S_TRAYFREQ_SET_C_SET_CORE_ARG				"Pass the with -c\n"

		#define S_TRAY_C_GOVERNOR							"Governor: %s\n"
		#define S_TRAY_C_CPU								"CPU%i: %s%s"

		#define S_TRAYFREQ_C_GTK_ERROR						"Cannot initialize gtk: gtk_init_check returned FALSE.\nBailing."
		#define S_TRAYFREQ_C_CONFIG_FILE_ERROR				"Failed to open config files!\n"

		#define S_BAT_TRAY_C_BATTERY_FULL					"Fully charged"
		#define S_BAT_TRAY_C_BATTERY_CHARGING				"Charging (%i%%)"
		#define S_BAT_TRAY_C_BATTERY_DISCHARGING			"Discharging (%i%%)"
		#define S_BAT_TRAY_C_BATTERY_UNKNOWN				"Unknown status"
		////////////////////////////////////////////////////////////////
	#endif /* ifdef LANG_FR */
#endif /* ifdef STRINGS_H */