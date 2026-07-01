#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_CITIES   20          /* 最多支持城市数 */
#define MAX_NAME_LEN 32          /* 城市名最大长度 */
#define INF          INT_MAX     /* 表示不可达 */
#define COST_PER_KM  10          /* 每公里费用（元）*/

typedef struct {
    int  n;                                  /* 城市数量 */
    char name[MAX_CITIES][MAX_NAME_LEN];     /* 城市名称 */
    int  dist[MAX_CITIES][MAX_CITIES];       /* 邻接矩阵（公里）*/
} Graph;

typedef struct {
    int  dist[MAX_CITIES];   /* 源点到各城市最短距离 */
    int  prev[MAX_CITIES];   /* 路径前驱 */
} DijkResult;

static void print_line(char c, int len) {
    for (int i = 0; i < len; i++) putchar(c);
    putchar('\n');
}

/* 安全读取整数，带范围校验；返回0表示成功 */
static int read_int(const char *prompt, int lo, int hi, int *out) {
    int v; char buf[64];
    while (1) {
        printf("%s", prompt);
        if (!fgets(buf, sizeof(buf), stdin)) return -1;
        if (sscanf(buf, "%d", &v) != 1 || v < lo || v > hi) {
            printf("  [!] 请输入 %d ~ %d 之间的整数\n", lo, hi);
            continue;
        }
        *out = v; return 0;
    }
}

static void dijkstra(const Graph *g, int src, DijkResult *res) {
    int visited[MAX_CITIES] = {0};
    for (int i = 0; i < g->n; i++) {
        res->dist[i] = INF;
        res->prev[i] = -1;
    }
    res->dist[src] = 0;

    for (int iter = 0; iter < g->n; iter++) {
        /* 找未访问中距离最小的节点 */
        int u = -1;
        for (int i = 0; i < g->n; i++) {
            if (!visited[i] && (u == -1 || res->dist[i] < res->dist[u]))
                u = i;
        }
        if (u == -1 || res->dist[u] == INF) break;
        visited[u] = 1;

        for (int v = 0; v < g->n; v++) {
            if (g->dist[u][v] == INF) continue;
            long long nd = (long long)res->dist[u] + g->dist[u][v];
            if (nd < res->dist[v]) {
                res->dist[v] = (int)nd;
                res->prev[v] = u;
            }
        }
    }
}

/* 递归打印路径 */
static void print_path(const Graph *g, const int *prev, int v) {
    if (prev[v] == -1) { printf("%s", g->name[v]); return; }
    print_path(g, prev, prev[v]);
    printf(" → %s", g->name[v]);
}


/* 模块1：初始化图（输入城市与距离）*/
static void module_init(Graph *g) {
    print_line('=', 56);
    printf("  【模块一】城市与道路数据录入\n");
    print_line('=', 56);

    read_int("  请输入城市数量 (2~20): ", 2, MAX_CITIES, &g->n);

    printf("\n  --- 输入城市名称 ---\n");
    for (int i = 0; i < g->n; i++) {
        char buf[64];
        printf("  城市 %d 名称: ", i + 1);
        if (!fgets(buf, sizeof(buf), stdin)) buf[0] = '\0';
        /* 去掉换行 */
        buf[strcspn(buf, "\n")] = '\0';
        if (strlen(buf) == 0) snprintf(buf, sizeof(buf), "城市%d", i + 1);
        strncpy(g->name[i], buf, MAX_NAME_LEN - 1);
    }

    /* 初始化为不可达 */
    for (int i = 0; i < g->n; i++)
        for (int j = 0; j < g->n; j++)
            g->dist[i][j] = (i == j) ? 0 : INF;

    printf("\n  --- 输入城市间公路距离（公里）---\n");
    printf("  提示：若两城市无直达公路，请输入 0（表示不可达）\n\n");

    for (int i = 0; i < g->n; i++) {
        for (int j = i + 1; j < g->n; j++) {
            int d;
            char prompt[128];
            snprintf(prompt, sizeof(prompt),
                     "  %s ↔ %s 距离 (0=不可达, 最大99999): ",
                     g->name[i], g->name[j]);
            read_int(prompt, 0, 99999, &d);
            if (d > 0) {
                g->dist[i][j] = d;
                g->dist[j][i] = d;  /* 无向图 */
            }
        }
    }

    printf("\n  ✔ 数据录入完成！共 %d 座城市。\n\n", g->n);
}

/* 模块2：显示邻接矩阵 */
static void module_show_matrix(const Graph *g) {
    if (g->n == 0) { printf("  [!] 请先录入数据。\n\n"); return; }

    print_line('=', 56);
    printf("  【模块二】城市距离邻接矩阵（公里）\n");
    print_line('=', 56);

    /* 表头 */
    printf("  %-12s", "");
    for (int j = 0; j < g->n; j++)
        printf("%-12s", g->name[j]);
    printf("\n");
    print_line('-', 12 + 12 * g->n + 2);

    for (int i = 0; i < g->n; i++) {
        printf("  %-12s", g->name[i]);
        for (int j = 0; j < g->n; j++) {
            if (g->dist[i][j] == INF) printf("%-12s", "∞");
            else                       printf("%-12d", g->dist[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* 模块3：单源最短路径查询 */
static void module_single_source(const Graph *g) {
    if (g->n == 0) { printf("  [!] 请先录入数据。\n\n"); return; }

    print_line('=', 56);
    printf("  【模块三】单源最短路径（Dijkstra）\n");
    print_line('=', 56);

    printf("  城市编号列表：\n");
    for (int i = 0; i < g->n; i++)
        printf("    [%d] %s\n", i + 1, g->name[i]);

    int src;
    read_int("\n  请选择出发城市编号: ", 1, g->n, &src);
    src--;  /* 转为0-based */

    DijkResult res;
    dijkstra(g, src, &res);

    printf("\n  从【%s】出发到各城市的最短路径：\n\n", g->name[src]);
    print_line('-', 56);
    printf("  %-14s %-10s %-10s %s\n", "目标城市", "距离(km)", "费用(元)", "路径");
    print_line('-', 56);

    for (int i = 0; i < g->n; i++) {
        if (i == src) continue;
        printf("  %-14s ", g->name[i]);
        if (res.dist[i] == INF) {
            printf("%-10s %-10s %s\n", "不可达", "---", "---");
        } else {
            printf("%-10d %-10d ", res.dist[i], res.dist[i] * COST_PER_KM);
            print_path(g, res.prev, i);
            printf("\n");
        }
    }
    printf("\n");
}

/* 模块4：任意两城市查询 */
static void module_pair_query(const Graph *g) {
    if (g->n == 0) { printf("  [!] 请先录入数据。\n\n"); return; }

    print_line('=', 56);
    printf("  【模块四】指定两城市最优路径查询\n");
    print_line('=', 56);

    printf("  城市编号列表：\n");
    for (int i = 0; i < g->n; i++)
        printf("    [%d] %s\n", i + 1, g->name[i]);

    int src, dst;
    read_int("\n  请选择出发城市编号: ", 1, g->n, &src);
    read_int("  请选择目标城市编号: ", 1, g->n, &dst);
    src--; dst--;

    if (src == dst) {
        printf("  出发城市与目标城市相同，费用为 0 元。\n\n");
        return;
    }

    DijkResult res;
    dijkstra(g, src, &res);

    printf("\n");
    print_line('-', 56);
    if (res.dist[dst] == INF) {
        printf("  结论：%s → %s 无公路连通，无法到达。\n",
               g->name[src], g->name[dst]);
    } else {
        printf("  出发城市 : %s\n", g->name[src]);
        printf("  目标城市 : %s\n", g->name[dst]);
        printf("  最短距离 : %d 公里\n", res.dist[dst]);
        printf("  交通费用 : %d 元（按 %d 元/公里）\n",
               res.dist[dst] * COST_PER_KM, COST_PER_KM);
        printf("  最优路径 : ");
        print_path(g, res.prev, dst);
        printf("\n");
    }
    print_line('-', 56);
    printf("\n");
}

/* 模块5：全源最短路径费用汇总表（Floyd-Warshall 辅助展示）*/
static void module_all_pairs(const Graph *g) {
    if (g->n == 0) { printf("  [!] 请先录入数据。\n\n"); return; }

    print_line('=', 56);
    printf("  【模块五】全城市两两最优费用汇总表\n");
    print_line('=', 56);

    /* Floyd-Warshall */
    int fw[MAX_CITIES][MAX_CITIES];
    for (int i = 0; i < g->n; i++)
        for (int j = 0; j < g->n; j++)
            fw[i][j] = g->dist[i][j];

    for (int k = 0; k < g->n; k++)
        for (int i = 0; i < g->n; i++)
            for (int j = 0; j < g->n; j++)
                if (fw[i][k] != INF && fw[k][j] != INF)
                    if (fw[i][k] + fw[k][j] < fw[i][j])
                        fw[i][j] = fw[i][k] + fw[k][j];

    /* 打印费用表 */
    printf("\n  单位：元（距离×%d元/km）\n\n", COST_PER_KM);
    printf("  %-14s", "");
    for (int j = 0; j < g->n; j++) printf("%-12s", g->name[j]);
    printf("\n");
    print_line('-', 14 + 12 * g->n + 2);

    for (int i = 0; i < g->n; i++) {
        printf("  %-14s", g->name[i]);
        for (int j = 0; j < g->n; j++) {
            if (i == j)              printf("%-12s", "0");
            else if (fw[i][j]==INF)  printf("%-12s", "不可达");
            else                     printf("%-12d", fw[i][j] * COST_PER_KM);
        }
        printf("\n");
    }
    printf("\n");
}

/*  主菜单  */
static void show_menu(void) {
    print_line('=', 56);
    printf("     A公司工厂路径规划与费用计算系统\n");
    print_line('=', 56);
    printf("  [1] 录入 / 重新录入城市与道路数据\n");
    printf("  [2] 查看城市距离邻接矩阵\n");
    printf("  [3] 单源最短路径（从某城市出发到所有城市）\n");
    printf("  [4] 两城市间最优路径与费用查询\n");
    printf("  [5] 全城市两两最优费用汇总表\n");
    printf("  [0] 退出程序\n");
    print_line('-', 56);
}

static void load_sample(Graph *g) {
    /*
     * 6个工厂城市：武汉、重庆、桂林、长沙、兰州、深圳
     * 距离数据参考公路里程（近似值，单位km）
     */
    const char *cities[] = {"武汉","重庆","桂林","长沙","兰州","深圳"};
    /* 邻接矩阵（0=INF）*/
    int d[6][6] = {
      /*         武汉  重庆  桂林  长沙  兰州  深圳 */
      /* 武汉 */ {  0, 1040,  940,  340, 1660,  1100},
      /* 重庆 */ {1040,   0,  790,  770, 1200,  1490},
      /* 桂林 */ { 940, 790,    0,  540, 1960,   570},
      /* 长沙 */ { 340, 770,  540,    0, 1920,   760},
      /* 兰州 */ {1660,1200, 1960, 1920,    0,  2600},
      /* 深圳 */ {1100,1490,  570,  760, 2600,     0},
    };
    g->n = 6;
    for (int i = 0; i < 6; i++) {
        strncpy(g->name[i], cities[i], MAX_NAME_LEN - 1);
        for (int j = 0; j < 6; j++)
            g->dist[i][j] = (d[i][j] == 0 && i != j) ? INF : d[i][j];
    }
    printf("  ✔ 已加载内置样例（6城市）\n\n");
}

/*  程序入口  */
int main(void) {
    Graph g;
    memset(&g, 0, sizeof(g));
    g.n = 0;

    printf("\n");
    print_line('*', 56);
    printf("  欢迎使用 A公司工厂路径规划与费用计算系统\n");
    printf("  费率：%d 元/公里 \n",
           COST_PER_KM);
    print_line('*', 56);

    /* 询问是否加载样例 */
    printf("\n  是否加载内置样例数据（武汉/重庆/桂林/长沙/兰州/深圳）？\n");
    printf("  [1] 是   [2] 否，我自己输入\n  选择: ");
    char buf[8];
    fgets(buf, sizeof(buf), stdin);
    if (buf[0] == '1') load_sample(&g);

    int choice;
    do {
        show_menu();
        read_int("  请选择功能: ", 0, 5, &choice);
        printf("\n");
        switch (choice) {
            case 1: module_init(&g);          break;
            case 2: module_show_matrix(&g);   break;
            case 3: module_single_source(&g); break;
            case 4: module_pair_query(&g);    break;
            case 5: module_all_pairs(&g);     break;
            case 0:
                printf("  感谢使用，再见！\n\n");
                break;
            default:
                printf("  [!] 无效选项，请重试。\n\n");
        }
    } while (choice != 0);

    return 0;
}