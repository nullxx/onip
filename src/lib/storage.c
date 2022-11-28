#include "storage.h"

#include "logger.h"
#include "utils.h"
#include "environment.h"
#include <mysql.h>
#include <string.h>

#ifdef _WIN32
#define PATH_SEP "\\"
#else
#define PATH_SEP "/"
#endif

char* get_saved_ip(void) {
    struct environment_st env = get_environment();

    // 1. connect to mysql
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        log_error("Failed to init mysql");
        return NULL;
    }

    if (mysql_real_connect(conn, env.MYSQL_HOST, env.MYSQL_USER, env.MYSQL_PWD, env.MYSQL_DB, env.MYSQL__PORT, NULL, 0) == NULL) {
        log_error("Failed to connect to mysql");
        return NULL;
    }

    // 2. query the last created_at
    char query[] = "SELECT ip FROM `ip` ORDER BY created_at DESC LIMIT 1";
    if (mysql_query(conn, query)) {
        log_error("Failed to query mysql");
        return NULL;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        log_error("Failed to store result");
        return NULL;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL) {
        log_error("Failed to fetch row");
        return NULL;
    }

    char *ip = malloc(strlen(row[0]) + 1);
    strcpy(ip, row[0]);

    mysql_free_result(result);
    mysql_close(conn);
    
    return ip;
}

int save_ip(char *contents) {
    struct environment_st environment = get_environment();

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = environment.MYSQL_HOST;
    char *user = environment.MYSQL_USER;
    char *password = environment.MYSQL_PWD;
    char *database = environment.MYSQL_DB;
    int port = environment.MYSQL__PORT;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, port, NULL, 0)) {
        log_error("Failed to connect to database: Error: %s", mysql_error(conn));
        return -1;
    }

    char *query = "CREATE TABLE IF NOT EXISTS `ip` ( `id` INT NOT NULL AUTO_INCREMENT , `ip` VARCHAR(15) NOT NULL , `created_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP , PRIMARY KEY (`id`)) ENGINE = InnoDB;";
    if (mysql_query(conn, query)) {
        log_error("Failed to create table: Error: %s", mysql_error(conn));
        return -1;
    }

    char *insert_query = malloc(sizeof(char) * 100);
    sprintf(insert_query, "INSERT INTO `ip` (`ip`) VALUES ('%s');", contents);
    if (mysql_query(conn, insert_query)) {
        log_error("Failed to insert ip: Error: %s", mysql_error(conn));
        return -1;
    }

    mysql_close(conn);
    return 0;
}