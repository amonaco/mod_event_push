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
 * mod_event_push.c -- Destiny Event Module
 *
 */
#include <switch.h>
#include <switch_curl.h>
#include "mod_event_push.h"

static const char *config_file = "mod_event_push.conf";

/* make json object for http post */
void encode_json_params(switch_event_t *event, char **data, char **filter)
{
    int j;
    char *json_text = NULL;
    switch_event_header_t *hp;
    cJSON *json = NULL;

    /* initializes the json object */
    json = cJSON_CreateObject();

    /* iterate headers and build json object */
    for (hp = event->headers; hp; hp = hp->next) {
        if (filter) {
            /* count filter elements */
            for (j = 0; j < 2; j++) {
                
                /* apply event header filter */
                if (strcmp(filter[j], hp->name ) == 0) {
                    cJSON_AddItemToObject(json, hp->name, cJSON_CreateString(hp->value));
                }
            }
        } else {
            /* add all elements */
            cJSON_AddItemToObject(json, hp->name, cJSON_CreateString(hp->value));
        }
    }

    /* extract json text */
    json_text = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);
    *data = json_text;
}
static void event_handler(switch_event_t *event)
{
    char *data = NULL;

    switch (event->event_id) {

        case SWITCH_EVENT_LOG:
            break;
        case SWITCH_EVENT_CHANNEL_CREATE:
            encode_json_params(event, &data, filter_channel_create);
            break;
        case SWITCH_EVENT_CHANNEL_BRIDGE:
            break;
        case SWITCH_EVENT_CHANNEL_UNBRIDGE:
            break;
        case SWITCH_EVENT_CHANNEL_DESTROY:
            // encode_json_params(event, &data, filter_channel_destroy);
            break;
        case SWITCH_EVENT_CHANNEL_HOLD:
            break;
        case SWITCH_EVENT_PRESENCE_IN:
            break;
        case SWITCH_EVENT_PRESENCE_OUT:
            break;
        case SWITCH_EVENT_PRESENCE_PROBE:
            break;
        case SWITCH_EVENT_API:
            encode_json_params(event, &data, filter_api);
            curl_post_json(data);
            break;
        case SWITCH_EVENT_HEARTBEAT:
            // encode_json_params(event, &data, filter_heartbeat);
            break;
        default:
            encode_json_params(event, &data, NULL);
            curl_post_json(data);
            switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_DEBUG, "EVENT: %s\n", data);
            break;
    }

    switch_safe_free(data) /* review pointer freeing */
    return;
}

/* curl post function, could be done better */
void curl_post_json(char *data) {

    // long http_res = 255;
    switch_CURL *curl_handle = NULL;

    /* init curl library, use FS version? */
    curl_handle = curl_easy_init();
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDSIZE, strlen(data));
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, (void *) data);
    switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_DEBUG, "Post data: %s\n", data);

    /* setting up curl's options */
    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1);
                                               /* soft code me! */
                                               /* to config file! */
    curl_easy_setopt(curl_handle, CURLOPT_URL, "http://localhost/pub?id=50c41fb8-d99f-46ef-b4e3-abf12d106059");
    curl_easy_setopt(curl_handle, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "Push/1.0");
    curl_easy_perform(curl_handle);
    curl_easy_cleanup(curl_handle);

    /* do something with this code */
    // switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_DEBUG, "CURL RETURNS %d\n", (int) http_res);
}

/* amonaco: remove this bit */
#define MY_EVENT_COOL "test::cool"

SWITCH_MODULE_LOAD_FUNCTION(mod_event_push_load)
{
    switch_xml_t cfg; //, x_profiles;

    /* connect my internal structure to the blank pointer passed to me */
    *module_interface = switch_loadable_module_create_module_interface(pool, modname);

    if (!(cfg = switch_xml_open_cfg(config_file, &cfg, NULL))) {
        switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_ERROR, "Configuration file: %s failed\n", config_file);
    }

    /*
    if (!(x_profiles = switch_xml_child(cfg, "settings"))) {
        switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_ERROR, "Tag \"settings\" not found in configuration file: %s \n", config_file);
        return SWITCH_STATUS_GENERR;
    }
    */

    // amonaco: review this subclass code
    if (switch_event_reserve_subclass(MY_EVENT_COOL) != SWITCH_STATUS_SUCCESS) {
        switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "Couldn't register subclass!");
        return SWITCH_STATUS_GENERR;
    }

    if (switch_event_bind(modname, SWITCH_EVENT_ALL, SWITCH_EVENT_SUBCLASS_ANY, event_handler, NULL) != SWITCH_STATUS_SUCCESS) {
        switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "Couldn't bind!\n");
        return SWITCH_STATUS_GENERR;
    }

    /* indicate that the module should continue to be loaded */
    return SWITCH_STATUS_SUCCESS;
}

/* For Emacs:
 * Local Variables:
 * mode:c
 * indent-tabs-mode:t
 * tab-width:4
 * c-basic-offset:4
 * End:
 * For VIM:
 * vim:set softtabstop=4 shiftwidth=4 tabstop=4:
 */
