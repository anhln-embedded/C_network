// #include <stdio.h>
// #include "wan_infor.h"
// #include "parser_json_file.h"
// #include "wan_testcase.h"


// int main(){
//     log_config_t config = {
//         .log_config_level = LOG_LVL_DEBUG,
//         .log_config_type = LOG_STDOUT,
//         .log_config_file = "application.log"
//     };
//     log_init(&config);
//     cJSON *json_input = NULL;
//     wan_config_t output;
//     error_t err = parser_json_file("wan_config.json", &json_input);
//     if (err != ERROR_NONE)
//     {
//         log_error("Failed to parse JSON file: %s", error_to_string(err));
//         return -1;
//     }

//     err = wan_infor_parser_json(json_input, &output);
//     if (err != ERROR_NONE)
//     {
//         log_error("Failed to parse WAN config: %s", error_to_string(err));
//         cJSON_Delete(json_input);
//         return -1;
//     }
//     log_debug("WAN Config Parsed Successfully");
//     wan_create(NULL);
//     return 0;
// }

#include <uci.h>
#include <stdio.h>

void create_wan_interface(struct uci_context *ctx) {
    struct uci_ptr ptr;

    // Tạo một giao diện WAN mới
    if (uci_lookup_ptr(ctx, &ptr, "network.wan", true) != UCI_OK) {
        printf("Không thể tìm thấy cấu hình WAN\n");
        return;
    }
    ptr.value = "interface";
    uci_set(ctx, &ptr);

    // Cấu hình WAN sử dụng DHCP
    if (uci_lookup_ptr(ctx, &ptr, "network.wan.proto", true) == UCI_OK) {
        ptr.value = "dhcp";
        uci_set(ctx, &ptr);
    }

    if (uci_lookup_ptr(ctx, &ptr, "network.wan.ifname", true) == UCI_OK) {
        ptr.value = "eth0";
        uci_set(ctx, &ptr);
    }

    // Lưu cấu hình
    uci_commit(ctx, &ptr.p, false);
}

int main() {
    struct uci_context *ctx;

    // Khởi tạo UCI
    ctx = uci_alloc_context();
    if (!ctx) {
        printf("Không thể khởi tạo UCI\n");
        return -1;
    }

    // Tạo giao diện WAN
    create_wan_interface(ctx);

    // Giải phóng tài nguyên
    uci_free_context(ctx);

    printf("Giao diện WAN đã được tạo thành công!\n");
    return 0;
}

