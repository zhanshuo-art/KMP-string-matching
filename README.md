# 专利/论文关键词检索系统（KMP算法）

## 项目简介
这是一个基于 KMP（Knuth-Morris-Pratt）算法的高效文本检索系统，用于在大规模论文和专利数据集中快速搜索关键词。

## 功能特点
- 🔍 **高效搜索**：使用 KMP 算法实现 O(n+m) 时间复杂度的字符串匹配
- 📚 **双数据库**：同时检索论文（DeepDiveAI）和专利（DeepPatentAI）数据
- 🔤 **不区分大小写**：自动转换为小写进行匹配
- 📄 **多字段搜索**：在标题和摘要字段中查找关键词
- 📊 **结果统计**：显示匹配数量和标题列表

## 核心技术

### KMP 算法原理
KMP 算法是一种高效的字符串匹配算法，相比暴力匹配有显著性能提升：

**传统暴力匹配**：
- 时间复杂度：O(n × m)，其中 n 为文本长度，m 为模式串长度
- 每次不匹配时，模式串回退到起点重新匹配

**KMP 算法优化**：
- 时间复杂度：O(n + m)
- 核心思想：利用已匹配的信息，避免重复比较
- 关键数据结构：**next 数组**（也叫部分匹配表）

### next 数组的作用
next 数组记录了模式串的"最长相等前后缀"长度：
- 当匹配失败时，模式串不需要从头开始，而是跳到 next 值指定的位置
- 避免了已匹配字符的重复比较

**示例**：
```
模式串: "ABABC"
next数组: [0, 0, 1, 2, 0]

匹配过程：
文本: "ABABABABC"
模式: "ABABC"
      ↑ 不匹配时，利用 next[3]=2，模式串跳到索引2继续匹配
```

### 工作流程
```
1. 构建 next 数组
   ↓
2. 文本与模式串逐字符比较
   ↓
3. 匹配成功 → 继续
   不匹配 → 根据 next 数组跳转
   ↓
4. 找到完整匹配 → 返回 true
   文本扫描完 → 返回 false
```

## 使用方法

### 1. 准备数据文件
需要两个 CSV 文件：
- **DeepDiveAI_Title_Abstract.csv**（论文数据）
  - 第2列：论文标题
  - 第3列：论文摘要

- **DeepPatentAI.csv**（专利数据）
  - 第5列：专利标题
  - 第6列：专利摘要

### 2. 修改文件路径
在代码第176-177行修改为你的文件路径：
```cpp
string deepDiveAI_path = "your_path/DeepDiveAI_Title_Abstract.csv";
string deepPatentAI_path = "your_path/DeepPatentAI.csv";
```

### 3. 编译运行
```bash
g++ experiment_2_2nd.cpp -o keyword_search
./keyword_search
```

### 4. 输入关键词
```
======================================
    专利/论文关键词检索系统 (KMP)
======================================

请输入要检索的关键词: artificial intelligence
```

## 输出示例
```
正在搜索关键词: "artificial intelligence" ...

=== DeepDiveAI 搜索结果 ===
1. Deep Learning for Artificial Intelligence Applications
2. Artificial Intelligence in Healthcare Systems
3. Neural Networks and Artificial Intelligence
...
共找到 127 条结果

=== DeepPatentAI 搜索结果 ===
1. Method and System for Artificial Intelligence Processing
2. Artificial Intelligence Based Image Recognition
3. Machine Learning Algorithm for AI Applications
...
共找到 89 条结果

搜索完成！
```

## CSV 解析特性
- 支持引号包裹的字段（如 `"title, with comma"`）
- 处理转义引号（`""` 表示字面引号 `"`）
- 自动去除字段首尾的引号
- 正确处理包含逗号的字段内容

## 应用场景
- 学术文献检索（快速查找相关论文）
- 专利信息查询（技术主题检索）
- 大规模文本数据挖掘
- 字符串匹配算法学习与实践
- 信息检索系统开发

## 算法复杂度
- **时间复杂度**：O(n + m)
  - n：文本总长度
  - m：模式串（关键词）长度
- **空间复杂度**：O(m)（next 数组）

## 性能对比
假设文本长度为 1,000,000 字符，关键词长度为 10：
- **暴力匹配**：最坏情况需要 10,000,000 次比较
- **KMP 算法**：最多 1,000,010 次比较（约快100倍）

## 扩展功能建议
- 支持正则表达式匹配
- 添加结果导出功能（保存为 CSV）
- 支持多关键词同时搜索
- 添加相关性评分排序
- 实现高亮显示匹配位置
