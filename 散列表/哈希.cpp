#include <stdio.h>
#include <string.h>

#define HASH_SIZE 60
#define NAME_SIZE 20

typedef struct {
    char name[NAME_SIZE];
    int score;
} Student;

// 哈希函数
int hash(const char* name) {
    unsigned int n = 0;
    for (int i = 0; i < strlen(name); i++) {
        n = (n << 3) | (n >> 29);
        n += name[i];
    }
    return n % HASH_SIZE;
}

int main() {
    char* inputLines[] = {
        "ZHAO,70",
        "QIAN,76",
        "UN,80",
        "LI,90",
        "ZHOU,75",
        "WU,82",
        "ZHENG,84",
        "WANG,90",
        "CHANG,91",
        "CHAO,73",
        "YANG,86",
        "JIN,",
        "SUN"
    };

    Student hash_table[HASH_SIZE] = { 0 };
    int count = 0;

    // 插入学生信息到哈希表中
    for (int i = 0; i < 12; i++) {
        char name[NAME_SIZE];
        int score;
        sscanf(inputLines[i], "%[^,],%d", name, &score);
        Student student;
        strcpy(student.name, name);
        student.score = score;

        int pos = hash(student.name);
        // 处理哈希冲突，采用线性探测法找到空闲位置插入
        while (hash_table[pos].name[0]!= '\0' && strcmp(hash_table[pos].name, student.name)!= 0) {
            pos = (pos + 1) % HASH_SIZE;
        }
        // 插入数据
        strcpy(hash_table[pos].name, student.name);
        hash_table[pos].score = student.score;
        count++;
    }

    // 查找学生
    char name[NAME_SIZE];
    strcpy(name, inputLines[12]);
    int pos = hash(name);
    int steps = 0;
    // 查找时考虑哈希冲突，一直查找直到找到相同名字或者遍历完整个哈希表
    while (strcmp(hash_table[pos].name, name)!= 0 && hash_table[pos].name[0]!= '\0') {
        pos = (pos + 1) % HASH_SIZE;
        steps++;
    }
    // 判断是否找到
    if (hash_table[pos].name[0]!= '\0') {
        printf("该关键字在哈希表中的位置是：%d\n", pos);
        printf("成绩是：%d\n", hash_table[pos].score);
    }
    else {
        printf("未找到该学生信息\n");
    }

    return 0;
}
