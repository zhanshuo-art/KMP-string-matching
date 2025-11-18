#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// KMP算法 - 构建next数组
vector<int> buildNext(const string& pattern) {
    int m = pattern.length();
    vector<int> next(m, 0);

    int j = 0;
    for (int i = 1; i < m; i++) {
        // 当字符不匹配时，回退j
        while (j > 0 && pattern[i] != pattern[j]) {
            j = next[j - 1];
        }
        // 字符匹配，j前进
        if (pattern[i] == pattern[j]) {
            j++;
        }
        next[i] = j;
    }
    return next;
}

// KMP算法 - 在文本中搜索模式串，判断是否存在（不区分大小写）
bool kmpSearch(string text, string pattern) {
    // 转换为小写进行不区分大小写的搜索
    transform(text.begin(), text.end(), text.begin(), ::tolower);
    transform(pattern.begin(), pattern.end(), pattern.begin(), ::tolower);

    int n = text.length();
    int m = pattern.length();

    if (m == 0) return true;
    if (n < m) return false;

    vector<int> next = buildNext(pattern);

    int j = 0; // pattern的索引
    for (int i = 0; i < n; i++) {
        // 字符不匹配时，根据next数组回退
        while (j > 0 && text[i] != pattern[j]) {
            j = next[j - 1];
        }
        // 字符匹配，pattern索引前进
        if (text[i] == pattern[j]) {
            j++;
        }
        // 找到完整匹配
        if (j == m) {
            return true;
        }
    }
    return false;
}

// 解析CSV行，返回各列数据
vector<string> parseCSVLine(const string& line) {
    vector<string> fields;
    string field;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (c == '"') {
            // 判断是否是转义引号 "" -> 一个 "
            if (inQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                field += '"';
                ++i; // 跳过下一个引号
            } else {
                inQuotes = !inQuotes; // 切换引号状态
            }
        } else if (c == ',' && !inQuotes) {
            fields.push_back(field);
            field.clear();
        } else {
            field += c;
        }
    }
    fields.push_back(field);

    // 去掉首尾可能存在的引号
    for (string& f : fields) {
        if (!f.empty() && f.front() == '"' && f.back() == '"') {
            f = f.substr(1, f.size() - 2);
        }
    }

    return fields;
}


// 搜索DeepDiveAI.csv文件
void searchDeepDiveAI(const string& filepath, const string& keyword) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cout << "无法打开文件: " << filepath << endl;
        return;
    }

    string line;
    getline(file, line); // 跳过表头

    cout << "\n=== DeepDiveAI 搜索结果 ===" << endl;
    int count = 0;

    while (getline(file, line)) {
        vector<string> fields = parseCSVLine(line);

        if (fields.size() >= 3) {
            string title = fields[1];      // 第2列
            string abstract = fields[2];   // 第3列

            // 使用KMP算法搜索
            if (kmpSearch(title, keyword) || kmpSearch(abstract, keyword)) {
                count++;
                cout << count << ". " << title << endl;
            }
        }
    }

    if (count == 0) {
        cout << "未找到匹配结果" << endl;
    } else {
        cout << "共找到 " << count << " 条结果" << endl;
    }

    file.close();
}

// 搜索DeepPatentAI.csv文件
void searchDeepPatentAI(const string& filepath, const string& keyword) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cout << "无法打开文件: " << filepath << endl;
        return;
    }

    string line;
    getline(file, line); // 跳过表头

    cout << "\n=== DeepPatentAI 搜索结果 ===" << endl;
    int count = 0;

    while (getline(file, line)) {
        vector<string> fields = parseCSVLine(line);

        if (fields.size() >= 6) {
            string title = fields[4];      // 第5列
            string abstract = fields[5];   // 第6列

            // 使用KMP算法搜索
            if (kmpSearch(title, keyword) || kmpSearch(abstract, keyword)) {
                count++;
                cout << count << ". " << title << endl;
            }
        }
    }

    if (count == 0) {
        cout << "未找到匹配结果" << endl;
    } else {
        cout << "共找到 " << count << " 条结果" << endl;
    }

    file.close();
}

int main() {
    // ========== 在此处填写CSV文件路径 ==========
    string deepDiveAI_path = "E:\\InnovationDataset\\DeepInnovationAI\\DeepDiveAI_Title_Abstract.csv";      // 修改为实际路径
    string deepPatentAI_path = "E:\\InnovationDataset\\DeepInnovationAI\\DeepPatentAI_1000.csv";  // 修改为实际路径
    // ==========================================

    string keyword;

    cout << "======================================" << endl;
    cout << "    专利/论文关键词检索系统 (KMP)" << endl;
    cout << "======================================" << endl;
    cout << "\n请输入要检索的关键词: ";
    getline(cin, keyword);

    if (keyword.empty()) {
        cout << "关键词不能为空！" << endl;
        return 1;
    }

    cout << "\n正在搜索关键词: \"" << keyword << "\" ..." << endl;

    // 搜索两个数据库
    searchDeepDiveAI(deepDiveAI_path, keyword);
    searchDeepPatentAI(deepPatentAI_path, keyword);

    cout << "\n搜索完成！" << endl;

    return 0;
}
