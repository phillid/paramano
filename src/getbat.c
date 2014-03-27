/************************************************************************
 * This file is part of trayfreq.                                       *
 *                                                                      *
 * trayfreq is free software; you can redistribute it and/or modify     *
 * it under the terms of the GNU General Public License as published    *
 * by the Free Software Foundation; either version 3 of the License, or *
 * (at your option) any later version.                                  *
 *                                                                      *
 * trayfreq is distributed in the hope that it will be useful,	        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with trayfreq. If not, see <http://www.gnu.org/licenses/>.     *
 ************************************************************************/

#include "getbat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

gint BAT_NUM;
gint MAX_CAPACITY;
gint WARN_CAPACITY;
gint LOW_CAPACITY;

//gchar INFO_PATH[30];
gchar CHARGE_VALUE_PATH[40];
gchar CHARGE_STATE_PATH[40];
gchar CURRENT_PATH[40];

static gint get_bat_num()
{
	FILE* fd;
	gchar file[40];
	gint i;
	for(i = 0; i < 3; i++)
	{
		memset(file, '\0', 40);
		sprintf(file, "/sys/class/power_supply/BAT%i/present", i);

		if((fd = fopen(file, "r")) != NULL)
		{
			if (fgetc(fd) == '1')
			{
				fclose(fd);
				return i;
			}
		}
	}
	return -1;
}

static gint get_int(char* line)
{
	char numbers[] = "1234567890";
	char* first_num;

	first_num = strpbrk (line, numbers);
	if(first_num)
		return atoi(first_num);
	return 1;
}

static gint get_int_value_from_file(const gchar* path)
{
	FILE* fd;
	gchar buff[100];
	gint value;

	if(!(fd = fopen(path, "r")))
		return -1;

	if (fgets(buff, 100, fd))
		value = get_int(buff);

	fclose(fd);
	return value;
}

static gboolean file_has_line(const gchar* path, const gchar* line)
{
	FILE* fd;
	gchar buff[100];

	if(!(fd = fopen(path, "r")))
		return FALSE;

	while(fgets(buff, 100, fd) != NULL)
	{
		if(strstr(buff, line) != NULL)
		{
			fclose(fd);
			return TRUE;
		}
	}
	fclose(fd);
	return FALSE;
}

gboolean gb_init()
{
	BAT_NUM = get_bat_num();
	//sprintf(INFO_PATH, "/proc/acpi/battery/BAT%i/info", gb_number());
	sprintf(CHARGE_VALUE_PATH, "/sys/class/power_supply/BAT%i/capacity", gb_number());
	sprintf(CHARGE_STATE_PATH, "/sys/class/power_supply/BAT%i/status", gb_number());
	sprintf(CURRENT_PATH, "/sys/class/power_supply/BAT%i/charge_now", gb_number());

	FILE* fd;
	gchar buff[100];

	/*if(!(fd = fopen(INFO_PATH, "r")))
		return FALSE;

	while(fgets(buff, 100, fd)!= NULL)
	{
		if(strncmp("last full capacity:", buff, 19) == 0)
			MAX_CAPACITY = get_int(buff);
		else if(strncmp("design capacity warning:", buff, 24) == 0)
			WARN_CAPACITY = get_int(buff);
		else if(strncmp("design capacity low:", buff, 20) == 0)
			LOW_CAPACITY = get_int(buff);
		else if(strncmp("present:                 no",buff, 27) == 0)
			return FALSE;
	}
	fclose(fd);*/
	return TRUE;
}

gint gb_current_rate()
{
	return get_int_value_from_file(CURRENT_PATH);
	return 0;
}

gboolean gb_discharging()
{
	return file_has_line(CHARGE_STATE_PATH, "Discharging");
}

gboolean gb_charged()
{
	return file_has_line(CHARGE_STATE_PATH, "Full");
}

gboolean gb_charging()
{
	return file_has_line(CHARGE_STATE_PATH, "Charging");
}

gint gb_number()
{
	return BAT_NUM;
}
/*
gint gb_max_capacity()
{
	return MAX_CAPACITY;
}

gint gb_warn_capacity()
{
	return WARN_CAPACITY;
}

gint gb_low_capacity()
{
	return LOW_CAPACITY;
}*/

gint gb_percent()
{
	return get_int_value_from_file(CHARGE_VALUE_PATH);
}
/*
void gb_time(gchar* time)
{
	float minutes = (float)gb_current_rate()/1000;

	//float minutes = ftime/60;

	//if(minutes < 10)
		sprintf(time, "%i", (int)minutes);
	//else
	//	sprintf(time, "%i:%i", (int)ftime, (int)minutes);
}

void gb_charge_time(gchar* time)
{
	float ftime = ((float)gb_max_capacity() - (float)gb_percent()) / (float)gb_current_rate();
	float minutes = ((float)ftime - (int)ftime) * (float)60;
	if(minutes < 10)
		sprintf(time, "%i:0%i", (int)ftime, (int)minutes);
	else
		sprintf(time, "%i:%i", (int)ftime, (int)minutes);
}*/