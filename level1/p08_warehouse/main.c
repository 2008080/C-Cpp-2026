#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义最大货物种类数
#define MAX_ITEMS 100
// 定义文件名
#define FILE_NAME "inventory.txt"

// 定义货物结构体
typedef struct {
    char id[50];    // 货物型号
    int quantity;   // 数量
} Item;

// 全局变量
Item inventory[MAX_ITEMS];
int itemCount = 0;

// --- 函数声明 ---
void loadData();
void saveData();
void showMenu();
void displayInventory();
void stockIn();
void stockOut();
int findItemIndex(char *id);

int main() {
    int choice;

    // 1. 程序启动时读取数据
    loadData();

    while (1) {
        showMenu();
        printf("请选择功能 (1-4): ");
        if (scanf("%d", &choice) != 1) {
            // 处理非数字输入防止死循环
            while(getchar() != '\n'); 
            printf("输入无效，请重新输入。\n");
            continue;
        }

        switch (choice) {
            case 1:
                displayInventory();
                break;
            case 2:
                stockIn();
                break;
            case 3:
                stockOut();
                break;
            case 4:
                // 3. 退出时保存数据
                saveData();
                printf("数据已保存，程序退出。\n");
                return 0;
            default:
                printf("无效的选择，请重试。\n");
        }
    }
    return 0;
}

// 显示菜单
void showMenu() {
    printf("\n========= 简单进销存系统 =========\n");
    printf("1. 显示存货列表\n");
    printf("2. 入库\n");
    printf("3. 出库\n");
    printf("4. 退出程序\n");
    printf("==================================\n");
}

// 读取文件数据
void loadData() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        // 文件不存在则初始化为空，不报错
        printf("未找到库存文件，将新建库存。\n");
        return;
    }

    itemCount = 0;
    // 读取格式：型号 数量
    while (fscanf(fp, "%s %d", inventory[itemCount].id, &inventory[itemCount].quantity) != EOF) {
        itemCount++;
        if (itemCount >= MAX_ITEMS) break;
    }
    fclose(fp);
    printf("已成功加载 %d 条库存数据。\n", itemCount);
}

// 保存文件数据
void saveData() {
    FILE *fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("错误：无法保存文件！\n");
        return;
    }

    for (int i = 0; i < itemCount; i++) {
        fprintf(fp, "%s %d\n", inventory[i].id, inventory[i].quantity);
    }
    fclose(fp);
}

// 显示库存列表
void displayInventory() {
    printf("\n--- 当前存货列表 ---\n");
    if (itemCount == 0) {
        printf("库存为空。\n");
        return;
    }
    printf("%-20s %-10s\n", "货物型号", "数量");
    printf("------------------------------\n");
    for (int i = 0; i < itemCount; i++) {
        printf("%-20s %-10d\n", inventory[i].id, inventory[i].quantity);
    }
    printf("------------------------------\n");
}

// 查找货物索引，找不到返回-1
int findItemIndex(char *id) {
    for (int i = 0; i < itemCount; i++) {
        if (strcmp(inventory[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

// 入库功能
void stockIn() {
    char id[50];
    int amount;
    
    printf("\n请输入入库货物型号: ");
    scanf("%s", id);
    printf("请输入入库数量: ");
    scanf("%d", &amount);

    if (amount <= 0) {
        printf("入库数量必须大于0。\n");
        return;
    }

    int index = findItemIndex(id);
    if (index != -1) {
        // 已存在，增加数量
        inventory[index].quantity += amount;
        printf("入库成功！型号 %s 当前库存: %d\n", id, inventory[index].quantity);
    } else {
        // 不存在，添加新货物
        if (itemCount < MAX_ITEMS) {
            strcpy(inventory[itemCount].id, id);
            inventory[itemCount].quantity = amount;
            itemCount++;
            printf("新货物入库成功！\n");
        } else {
            printf("库存已满，无法添加新货物。\n");
        }
    }
}

// 出库功能
void stockOut() {
    char id[50];
    int amount;
    
    printf("\n请输入出库货物型号: ");
    scanf("%s", id);
    
    int index = findItemIndex(id);
    if (index == -1) {
        printf("错误：未找到型号为 %s 的货物。\n", id);
        return;
    }

    printf("当前库存: %d，请输入出库数量: ", inventory[index].quantity);
    scanf("%d", &amount);

    if (amount <= 0) {
        printf("出库数量必须大于0。\n");
        return;
    }

    if (amount > inventory[index].quantity) {
        printf("错误：库存不足！\n");
    } else {
        inventory[index].quantity -= amount;
        printf("出库成功！型号 %s 剩余库存: %d\n", id, inventory[index].quantity);
    }
}
