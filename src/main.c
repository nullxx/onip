#include "lib/cloudflare.h"
#include "lib/curl_utils.h"
#include "lib/environment.h"
#include "lib/filesystem.h"
#include "lib/logger.h"
#include "lib/network.h"
#include "lib/notifier.h"
#include "lib/utils.h"

int main(int argc, char *argv[]) {
    log_info("======= STARTING =======");
    struct environment_st environment = load_environment();

    log_debug("FULL_FILE_NAME: %s", environment.FULL_FILE_NAME);

    char lastIp[16];
    int ret_saved_ip = get_saved_ip(environment.FULL_FILE_NAME, lastIp, sizeof(lastIp) / sizeof(char));
    if (ret_saved_ip != 0) {
        if (ret_saved_ip == -1) log_debug("File not found");
    }

    if (strlen(lastIp) > 0) {
        log_debug("Last IP (saved): %s", lastIp);
    }

    while (1) {
        get_saved_ip(environment.FULL_FILE_NAME, lastIp, sizeof(lastIp) / sizeof(char));

        char ip[16];
        int ret_get_ip = get_ip(ip);

        if (ret_get_ip != 0) {
            log_error("An error had ocurred retrieving public IP");
            continue;
        }

        if (strcmp(lastIp, ip) != 0) {
            log_debug(">>>> New IP %s <<<<", ip);

            int success_updated_cloudflare;
            do {
                success_updated_cloudflare = update_at_cloudflare(ip);
                log_debug("Cloudflare response %d", success_updated_cloudflare);
            } while (success_updated_cloudflare != 0);
            
            struct notify_response_st notify_response;

            do {
                notify_response = notify(ip);
                log_debug("=> Code %d, msg: %s, error: %d", notify_response.code, notify_response.msg, notify_response.error);

                if (notify_response.code != 1) {
                    log_error("An error ocurred notifying");
                }
            } while (notify_response.code != 1);

      

            log_debug("Saving IP to file");
            int ret_save_ip = save_ip(environment.DIRECTORY, environment.FILE_NAME, ip);

            if (ret_save_ip != 0) {
                log_debug("Failed to write ip");
                return ret_save_ip;
            }
            strcpy(lastIp, ip);
        }
        sleep(1);
    }

    return 0;
}