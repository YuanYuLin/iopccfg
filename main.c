#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "main.h"
#include "iopccfg.h"

unsigned long parse_paramegers(int argc, char** argv, char* json_file, char* json_key)
{
    unsigned long func = 0x0;
    int cmd_opt = 0;
    while(1) {
        cmd_opt = getopt(argc, argv, "f:k:slv");

        if(cmd_opt == -1) {
            return func;
        }

        switch(cmd_opt) {
        case 'k': // json key
            strcpy(json_key, optarg);
        break;
        case 'f': // json file
            strcpy(json_file, optarg);
        break;
        case 's': // show all json
            func |= SHOW_JSON;
        break;
        case 'l': // show json array len
            func |= SHOW_ARRAY_LEN;
        break;
        case 'v': // show json value
            func |= SHOW_VALUE;
        break;
        }
    }

    return func;
}

static void show_usage()
{
    printf("-f: input json file\n");
    printf("-k: json key string\n");
    printf("-s: show all elements of file\n");
    printf("-l: show length of array element\n");
    printf("-v: show vale of element\n");
    printf("example : \n");
    printf("    utils -f vmcfg.json -s\n");
}

int main(int argc, char** argv)
{
    char* path;
    struct json_object *json_obj;
    struct query_json_obj_t query_json_obj;
    char json_file[STR_LEN];
    unsigned long func = 0x0;

    if(argc < 2) {
        show_usage();
        return 1;
    }

    func = parse_paramegers(argc, argv, &json_file[0], &query_json_obj.cmp_key[0]);
    json_obj = json_object_from_file(json_file);
    query_json_obj.isFound = 0;

    switch(func) {
    case SHOW_JSON:
//        show_json(json_obj);
    break;
    case SHOW_ARRAY_LEN:
//        show_json_array_len(json_key, json_obj);
    break;
    case SHOW_VALUE:
        get_json_obj_by_query_obj(&query_json_obj, json_obj);
        switch(query_json_obj.type){
        case json_type_null:
            printf("%s", "NULL");
        break;
        case json_type_boolean:
            printf("%d", json_object_get_boolean(query_json_obj.obj));
        break;
        case json_type_double:
            printf("%f", json_object_get_double(query_json_obj.obj));
        break;
        case json_type_int:
            printf("%d", json_object_get_int(query_json_obj.obj));
        break;
        case json_type_object:
            printf("error");
        break;
        case json_type_array:
            printf("error");
        break;
        case json_type_string:
            printf("%s", json_object_get_string(query_json_obj.obj));
        break;
        default:
            printf("error");
        break;
        }
    break;
    }
    return 0;
}

