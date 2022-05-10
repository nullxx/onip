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

    while (1) {
        char * lastIp = get_saved_ip(environment.FULL_FILE_NAME);
        if (lastIp == NULL) {
            log_error("Could not get last IP");
            continue;
        }

        char *ip = get_ip();

        if (ip == NULL) {
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
        free(lastIp);
        free(ip);
        sleep(1);
    }

    return 0;
}