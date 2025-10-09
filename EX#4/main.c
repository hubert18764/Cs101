#include <stdio.h>

int main() {
    // 資料
    int   nums[3]    = {0,1,2};
    char  letters[3] = {'A','B','C'};
    float floats[3]  = {1.1f,1.2f,1.3f};

    FILE *fb = fopen("a.bin", "wb+");
    fwrite(nums,    sizeof(nums),    1, fb);
    fwrite(letters, sizeof(letters), 1, fb);
    fwrite(floats,  sizeof(floats),  1, fb);
    fseek(fb, 0, SEEK_SET); 
    fclose(fb);

    for (int i=0;i<3;i++) printf("%d%s", nums[i],    i<2?" ":""); puts("");
    for (int i=0;i<3;i++) printf("%c%s", letters[i], i<2?" ":""); puts("");
    for (int i=0;i<3;i++) printf("%.6f%s", floats[i], i<2?" ":""); puts("");

    return 0;
}
