#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

#define SAFE_BLOCK_DAY 16
#define SAFE_URL_LEN   128
#define SAFE_MAC_LEN   18


struct block_time_s {
    list_head_t list;
    char days[SAFE_BLOCK_DAY];
    unsigned char start_hour;
    unsigned char start_minute;
    unsigned char end_hour;
    unsigned char end_minute;
};
typedef struct block_time_s block_time_t;


struct block_config_s {
    list_head_t list;
    char url[SAFE_URL_LEN];
    char mac[SAFE_MAC_LEN];
    int time_state;
    list_head_t block_time; // Danh sách các block_time_t
};
typedef struct block_config_s block_config_t;

// Khai báo danh sách chính
LIST_HEAD(l_block_config);

void add_block_config(const char *url, const char *mac) {
    block_config_t *cfg = malloc(sizeof(block_config_t));
    if (cfg) {
        INIT_LIST_HEAD(&cfg->block_time);
        strncpy(cfg->url, url, SAFE_URL_LEN);
        strncpy(cfg->mac, mac, SAFE_MAC_LEN);
        cfg->time_state = 1;
        list_add_tail(&cfg->list, &l_block_config);
    }
}

void add_block_time(block_config_t *cfg, const char *days, int sh, int sm, int eh, int em) {
    block_time_t *bt = malloc(sizeof(block_time_t));
    if (bt) {
        strncpy(bt->days, days, SAFE_BLOCK_DAY);
        bt->start_hour = sh;
        bt->start_minute = sm;
        bt->end_hour = eh;
        bt->end_minute = em;
        list_add_tail(&bt->list, &cfg->block_time);
    }
}

void print_all_configs() {
    block_config_t *cfg;
    block_time_t *bt;

    LIST_FOR_EACH_ENTRY(cfg, &l_block_config, list) {
        printf("Config: URL=%s, MAC=%s, TimeState=%d\n", cfg->url, cfg->mac, cfg->time_state);

        LIST_FOR_EACH_ENTRY(bt, &cfg->block_time, list) {
            printf("  BlockTime: %s %02d:%02d -> %02d:%02d\n",
                   bt->days, bt->start_hour, bt->start_minute,
                   bt->end_hour, bt->end_minute);
        }
    }
}

void free_all_configs() {
    block_config_t *cfg;
    list_head_t *p, *n;

    LIST_FOR_EACH_SAFE(p, n, &l_block_config) {
        cfg = LIST_ENTRY(p, block_config_t, list);

        list_head_t *tp, *tn;
        LIST_FOR_EACH_SAFE(tp, tn, &cfg->block_time) {
            block_time_t *bt = LIST_ENTRY(tp, block_time_t, list);
            list_del(tp);
            free(bt);
        }

        list_del(p);
        free(cfg);
    }
}

int main() {
    add_block_config("http://example.com", "00:11:22:33:44:55");
    add_block_config("http://another.com", "AA:BB:CC:DD:EE:FF");

    block_config_t *cfg;
    LIST_FOR_EACH_ENTRY(cfg, &l_block_config, list) {
        add_block_time(cfg, "Mon-Fri", 8, 0, 17, 0);
        add_block_time(cfg, "Sat", 9, 0, 12, 0);
    }

    print_all_configs();

    free_all_configs();
    return 0;
}
