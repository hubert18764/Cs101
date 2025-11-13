#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINEBUF 256

// 從像 "=====  March 13 2025  =====" 的行抓出中間日期（抓不到就空字串）
static void extract_date(const char *line, char *date_out, size_t cap) {
    int n = (int)strlen(line), L = 0, R = n - 1;
    while (L < n && !isalpha((unsigned char)line[L])) L++;
    while (R >= 0 && !(isalnum((unsigned char)line[R]) || line[R] == ')')) R--;
    if (L <= R && (size_t)(R - L + 1) < cap) {
        memcpy(date_out, line + L, (size_t)(R - L + 1));
        date_out[R - L + 1] = '\0';
    } else {
        date_out[0] = '\0';
    }
}

// 從一行中把「第一個整數當成索引，其後連續 7 個整數當號碼」抓出來
static int parse_line_numbers(const char *line, int *idx_out, int nums[7]) {
    int idx = -1, cnt = 0;
    const char *p = line;
    while (*p) {
        while (*p && !isdigit((unsigned char)*p)) p++; // 跳過非數字
        if (!*p) break;
        long v = strtol(p, (char **)&p, 10);           // 讀一個整數
        if (idx < 0) idx = (int)v;                     // 第一個數字是 [idx]
        else if (cnt < 7) nums[cnt++] = (int)v;        // 之後的七個是號碼
        if (cnt == 7) break;
    }
    if (idx >= 0 && cnt == 7) { *idx_out = idx; return 1; }
    return 0;
}

int main(void) {
    int a, b, c;
    printf("請輸入中獎號碼三個：");
    if (scanf("%d %d %d", &a, &b, &c) != 3) return 0;
    printf("輸入中獎號碼為：%02d %02d %02d\n", a, b, c);
    printf("以下為中獎彩卷：\n");

    FILE *fp = fopen("lotto.txt", "r");
    if (!fp) { printf("(找不到 lotto.txt)\n"); return 0; }

    char line[LINEBUF], date[LINEBUF] = {0};
    int found_any = 0;

    // 讀標題行
    if (!fgets(line, sizeof(line), fp)) { fclose(fp); return 0; }

    // 嘗試讀日期行（可能沒有）
    long pos = ftell(fp);
    if (fgets(line, sizeof(line), fp)) {
        if (strchr(line, '[') == NULL) {
            // 沒有 '['，多半是日期行
            extract_date(line, date, sizeof(date));
        } else {
            // 不是日期，回退讓後面處理
            fseek(fp, pos, SEEK_SET);
        }
    } else { fclose(fp); return 0; }

    // 掃描直到尾巴 "========="
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "=========") != NULL) break;
        if (strstr(line, "__") != NULL || strstr(line, "--") != NULL) continue; // 補空白行略過

        int idx, x[7];
        if (!parse_line_numbers(line, &idx, x)) continue; // 不是有效號碼行

        // 命中任一號碼就印出該行
        int hit = 0;
        for (int i = 0; i < 7; i++) {
            if (x[i] == a || x[i] == b || x[i] == c) { hit = 1; break; }
        }
        if (hit) {
            found_any = 1;
            if (date[0])
                printf("售出時間： %s: [%d]: %02d %02d %02d %02d %02d %02d %02d\n",
                       date, idx, x[0], x[1], x[2], x[3], x[4], x[5], x[6]);
            else
                printf("售出時間： [%d]: %02d %02d %02d %02d %02d %02d %02d\n",
                       idx, x[0], x[1], x[2], x[3], x[4], x[5], x[6]);
        }
    }

    if (!found_any) printf("(無)\n");

    fclose(fp);
    return 0;
}
