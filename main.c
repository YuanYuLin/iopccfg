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
        cmd_opt = getopt(argc, argv, "f:k:alvt");

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
        case 'a': // show all json
            func |= SHOW_JSON;
        break;
        case 'l': // show json array len
            func |= SHOW_ARRAY_LEN;
        break;
        caes 's': // show json array string
            func |= SHOW_ARRAY_STRING;
        break;
        case 'v': // show json value
            func |= SHOW_VALUE;
        break;
        case 't': // show json type
            func |= SHOW_TYPE;
        break;
        }
    }

    return func;
}

static void show_usage()
{
    printf("-f: input json file\n");
    printf("-k: json key string\n");
    printf("-a: show all elements of file\n");
    printf("-v: show value of element\n");
    printf("-t: show type of element\n");
    printf("-l: show length of array element\n");
    printf("-s: show array strings\n");
    printf("example : \n");
    printf("    utils -f vmcfg.json -a\n");
    printf("    utils -f vmcfg.json -k type -v\n");
}

int main(int argc, char** argv)
{
    char* path;
    struct json_object *json_obj;
    struct query_json_obj_t query_json_obj;
    char json_file[STR_LEN];
    unsigned long func = 0x0;
    int array_len = 0;
    int isError = 0;

    if(argc < 2) {
        show_usage();
        return 1;
    }

    func = parse_paramegers(argc, argv, &json_file[0], &query_json_obj.cmp_key[0]);
    json_obj = json_object_from_file(json_file);
    query_json_obj.isFound = 0;

    switch(func) {
    case SHOW_JSON:
        show_json(json_obj);
    break;
    case SHOW_TYPE:
        get_json_obj_by_query_obj(&query_json_obj, json_obj);
        switch(query_json_obj.type){
        case json_type_null:
            printf("%s", "NULL");
        break;
        case json_type_boolean:
            printf("%s", "BOOLEAN");
        break;
        case json_type_double:
            printf("%s", "DOUBLE");
        break;
        case json_type_int:
            printf("%s", "INTEGER");
        break;
        case json_type_string:
            printf("%s", "STRING");
        break;
        case json_type_object:
            printf("%s", "OBJECT");
        break;
        case json_type_array:
            printf("%s", "ARRAY");
        break;
        default:
            isError = 1;
        break;
    break;
    case SHOW_ARRAY_LEN:
        get_json_obj_by_query_obj(&query_json_obj, json_obj);
        isError = 1;
        if(query_json_obj.type == json_type_array) {
            printf("%d", json_object_array_length(query_json_obj.obj));
            isError = 0;
        }
    break;
    case SHOW_ARRAY_STRING:
        get_json_obj_by_query_obj(&query_json_obj, json_obj);
        isError = 1;
        if(query_json_obj.type == json_type_array) {
            isError = 0;
        }
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
        case json_type_string:
            printf("%s", json_object_get_string(query_json_obj.obj));
        break;
        case json_type_object:
        case json_type_array:
        default:
            isError = 1;
        break;
        }
    break;
    }

    if(isError)
        printf("%s", ERROR_STRING);

    return 0;
}

