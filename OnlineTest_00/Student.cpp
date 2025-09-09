#include <iostream>
#include <cstring>   // 包含 strcmp

using namespace std;

// 数据结构格式，详见StudentSorter.h文件
struct Student {
 	int no;
 	char name[101];
 };


// 按学号升序排序
bool sortByNoAsc(const Student& s1, const Student& s2) {

    return s1.no<s2.no;
}

// 按学号降序排序
bool sortByNoDesc(const Student& s1, const Student& s2) {

    return s1.no>s2.no;
}

// 按姓名字典序升序排序，如果姓名相同，再按学号升序排序
bool sortByNameAsc(const Student& s1, const Student& s2) {
    // 使用 strcmp 比较字符串
    int cmpResult = std::strcmp(s1.name, s2.name);
    if (cmpResult < 0) {
        return true; // s1.name 字典序小于 s2.name
    } else if (cmpResult > 0) {
        return false; // s1.name 字典序大于 s2.name
    } else {
        // 姓名相同，按学号升序
        return s1.no < s2.no;
    }
}

// 通用排序函数
void sortStudents(Student st[], int num, bool (*comp)(const Student&, const Student&)) {
    // 使用冒泡排序实现（不使用 std::sort）
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            // 使用提供的比较函数判断是否需要交换
            if (!comp(st[j], st[j+1])) {
                // 交换元素
                Student temp = st[j];
                st[j] = st[j+1];
                st[j+1] = temp;
            }
        }
    }
}
// main函数无需修改
int main() {
    int N;
    cin >> N; // 同scanf("%d", &N);
    Student students[100];

    for (int i = 0; i < N; i++) {
        cin >> students[i].no >> students[i].name; // 类似于scanf("%d %s", &(students[i].no), students[i].name);
    }

    int M;
    cin >> M;

    // 根据输入选择不同的比较函数
    bool (*comp)(const Student&, const Student&);
    switch (M) {
        case 1:
            comp = sortByNoAsc;
        break;
        case 2:
            comp = sortByNoDesc;
        break;
        case 3:
            comp = sortByNameAsc;
        break;
        default:
            comp = sortByNoAsc;
        break;
    }

    sortStudents(students, N, comp);

    for (int i = 0; i < N; i++) {
        cout << students[i].no << " " << students[i].name << endl; // cout语句类似于C中的printf输出
    }

    return 0;
}