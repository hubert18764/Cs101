#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GROUPS 5
#define PICKS  7
#define MAXNUM 69

// 找出第一個尚未存在的編號：lotto[00001].txt, lotto[00002].txt, ...
static unsigned next_ticket_no(void) {
    char name[64];
    for (unsigned i = 1; ; i++) {
        snprintf(name, sizeof(name), "lotto[%05u].txt", i);
        FILE *f = fopen(name, "r");
        if (!f) return i;        // 沒有這張 → 下一張就是它
        fclose(f);               // 已存在 → 繼續找下一個
    }
}

// 印一行現在時間：= Mon Mar  7 10:11:14 2022 =
static void print_datetime(FILE *fp) {
    time_t now = time(NULL);
    struct tm *tm = localtime(&now);
    char buf[64];
    strftime(buf, sizeof(buf), "= %a %b %e %T %Y =", tm);
    fprintf(fp, "%s\n", buf);
}

// 產生一組 7 個 (1..69) 不重複號碼
static void print_one_group(FILE *fp) {
    int used[70] = {0}, n = 0;
    while (n < PICKS) {
        int x = rand() % MAXNUM + 1;
        if (!used[x]) {
            used[x] = 1;
            fprintf(fp, "%02d", x);
            if (++n < PICKS) fprintf(fp, " ");
        }
    }
    fprintf(fp, "\n");
}

int main(void) {
    unsigned no = next_ticket_no();             // 1) 找下一張單號
    char fname[64];
    snprintf(fname, sizeof(fname), "lotto[%05u].txt", no);

    FILE *fp = fopen(fname, "w");               // 2) 開檔
    if (!fp) return 0;

    srand((unsigned)time(NULL) ^ no);           // 3) 亂數（要固定就改成 srand(1);）

    fprintf(fp, "========= lotto649 =========\n");      // 4) 標題
    fprintf(fp, "========+ No.%05u +========\n", no);   //    單號
    print_datetime(fp);                                   //    時間

    for (int g = 1; g <= GROUPS; g++) {                  // 5) 五組號碼
        fprintf(fp, "[%d]: ", g);
        print_one_group(fp);
    }

    fprintf(fp, "========= csie@CGU =========\n");      // 6) 結尾
    fclose(fp);
    return 0;
}
