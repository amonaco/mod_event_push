/* 
 * This file is part of Destiny (name may change very soon)
 * 
 * Destiny is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Destiny is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Destiny. If not, see http://www.gnu.org/licenses/.
 * 
 * Author(s): Ariel Monaco <amonaco@gmail.com>
 *
 * The Original Code is FreeSWITCH Modular Media Switching Software Library / Soft-Switch Application
 * Version: MPL 1.1
 *
 * mod_event_test.h -- Push Event Module
 *
 */

SWITCH_MODULE_LOAD_FUNCTION(mod_event_push_load);
SWITCH_MODULE_DEFINITION(mod_event_push, mod_event_push_load, NULL, NULL);

void encode_json_params(switch_event_t *event, char **str, char **filter);
void curl_post_json(char *data);

/* event filter for EVENT_CHANNEL_CREATE */
char *filter_channel_create[] = {
    "Event-Name",
    "Core-UUID",
    "Event-Date-Timestamp",
    "Channel-Name",
    "Unique-ID",
    "Call-Direction",
    "Channel-Presence-ID",
    "Channel-Call-UUID",
    "Answer-State",
    "Caller-Username",
    "Caller-Caller-ID-Name",
    "Caller-Network-Addr",
    "Caller-ANI",
    "Caller-Destination-Number",
    "Caller-Unique-ID",
    "Caller-Channel-Name"
    /* 
    "Caller-Channel-Answered-Time",
    "Caller-Channel-Progress-Time",
    "Caller-Channel-Progress-Media-Time",
    "Caller-Channel-Hangup-Time",
    "Caller-Channel-Transfer-Time",
    "Caller-Channel-Resurrect-Time",
    "Caller-Channel-Bridged-Time",
    "Caller-Channel-Last-Hold"
    */
};

/* event filter for EVENT_CHANNEL_DESTROY */
char *filter_channel_destroy[] = {
    "Core-UUID",
    "Event-Date-Timestamp",
    "Channel-Name",
    "Unique-ID",
    "Call-Direction",
    "Channel-Presence-ID",
    "Channel-Call-UUID",
    "Answer-State",
    "Caller-Username",
    "Caller-Caller-ID-Name",
    "Caller-Network-Addr",
    "Caller-ANI",
    "Caller-Destination-Number",
    "Caller-Unique-ID",
    "Caller-Channel-Name"
    /*
    "Caller-Channel-Created-Time",
    "Caller-Channel-Answered-Time",
    "Caller-Channel-Progress-Time",
    "Caller-Channel-Progress-Media-Time",
    "Caller-Channel-Hangup-Time",
    "Caller-Channel-Transfer-Time",
    "Caller-Channel-Resurrect-Time",
    "Caller-Channel-Bridged-Time",
    "Caller-Channel-Last-Hold",
    "Caller-Channel-Hold-Accum",
    "Other-Type",
    "Other-Leg-Direction",
    "Other-Leg-Username",
    "Other-Leg-Dialplan",
    "Other-Leg-Caller-ID-Name",
    "Other-Leg-Caller-ID-Number",
    "Other-Leg-Callee-ID-Name",
    "Other-Leg-Callee-ID-Number",
    "Other-Leg-Network-Addr",
    "Other-Leg-ANI",
    "Other-Leg-Destination-Number",
    "Other-Leg-Unique-ID",
    "Other-Leg-Channel-Name"
    */
};

/* event filter for EVENT_API */
char *filter_api[] = {
    "API-Command",
    "Core-UUID",
    "Event-Date-GMT",
    "Event-Date-Local",
    "Event-Date-Timestamp"
};


/* event filter for EVENT_HEARTBEAT */
char *filter_heartbeat[] = {
    "Up-Time",
    "Event-Date-Local",
    "Session-Count"
};
