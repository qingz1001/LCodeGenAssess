import pandas as pd

filename = "info_problems.xlsx"
df = pd.read_excel(filename)

#interested_tags = ['动态规划', '数学', '模拟', '贪心', '枚举', '线段树', '搜索', '字符串', '二分', '图论', '排序', '前缀和', '构造', '递推', '最短路', '深度优先搜索', '交互题', '树状数组', '并查集', '组合数学']

interested_tags = ['动态规划', '数学', '模拟', '贪心', '枚举', '线段树', '搜索', '字符串', '二分', '图论']

# 统计题目数量
count = df.shape[0]
print('题目总数:', count, '\n')

# 统计不同难度题目数量
difficulty_count = df['难度'].value_counts()
#print(difficulty_count)

# 统计不同难度下的题目PIDs
#difficulty_pids = df.groupby('难度')['PID'].apply(list)
#print(difficulty_pids)

# 统计不同难度和分类题目数量，并按难度和分类排序
# 遍历df里的内容
'''
tag_problems = {}
for index, row in df.iterrows():
    tags = row['标签'].strip("[]").split(',')
    for tag in tags:
        tag = tag.strip()
        if tag not in tag_problems:
            tag_problems[tag] = [row['PID']]
        else:
            tag_problems[tag].append(row['PID'])

# 统计不同标签下的题目数量
tag_count = {}
dataT = {'标签': [], '数量': []}
for tag in tag_problems:
    tag_count[tag] = len(tag_problems[tag])
    dataT['标签'].append(tag)
    dataT['数量'].append(tag_count[tag])
    print(tag, tag_count[tag])
dfT = pd.DataFrame(dataT)
dfT.to_excel('tags.xlsx', index=False)
'''

# 提取出仅与关心的难度和标签对应的数据放在data_simple中
data_simple = {'PID': [], '难度': [], '标签': []}
for index, row in df.iterrows():
#    print(row['PID'], row['难度'], row['标签'])
    difficulty = row['难度']
    if difficulty != '暂无评定':
        tags = row['标签'].strip("[]").split(',')
        
        new_tags = []
        for tag in tags:
            tag = tag.strip().strip('\'').strip('\"')
            if tag in interested_tags:             
                new_tags.append(tag)
        if len(new_tags) > 0:
            data_simple['标签'].append(new_tags)
            data_simple['难度'].append(difficulty)
            data_simple['PID'].append(row['PID'])

# 将data_simple先按难度排序，难度相同的情况按标签排序
#data_simple = sorted(data_simple, key=lambda x: (x[1], x[2]))

# 在data_simple里面统计每种难度下每种标签有多少个题目
difficulty_tag_count = {}
for i in range(len(data_simple['难度'])):
    difficulty = data_simple['难度'][i]
    tag = data_simple['标签'][i]
    if difficulty not in difficulty_tag_count:
        difficulty_tag_count[difficulty] = {}
    for t in tag:
        if t not in difficulty_tag_count[difficulty]:
            difficulty_tag_count[difficulty][t] = [data_simple['PID'][i]]
        else:
            difficulty_tag_count[difficulty][t].append(data_simple['PID'][i])

        # 输出每种难度下每种标签有多少个题目
for difficulty in difficulty_tag_count:
    print('============',difficulty,'=============')
    for tag in difficulty_tag_count[difficulty]:
        print(tag, len(difficulty_tag_count[difficulty][tag]))

# 从data_simple里面提取出700道题目，使得每种难度下每种标签都有至少10道题目
selected_problems = []
for difficulty in difficulty_tag_count:
    for tag in difficulty_tag_count[difficulty]:
        max_num = 10
        if difficulty == '入门':
            if tag in ['数学', '模拟', '枚举', '字符串']:
                max_num = 25
            else:
                max_num = 0
        elif difficulty == '普及−':
            if tag in ['数学', '模拟', '枚举', '字符串']:
                max_num = 10
            elif tag in ['动态规划', '贪心', '搜索', '二分']:
                max_num = 15
            else:
                max_num = 0
        else:
            max_num = 10

        num = 0
        for i in range(len(difficulty_tag_count[difficulty][tag])):
            if num == max_num:
                break
            if difficulty_tag_count[difficulty][tag][i] not in selected_problems:
                selected_problems.append(difficulty_tag_count[difficulty][tag][i])
                num += 1

# 输出选出的题目PID
# print(selected_problems)

# 统计selected_problems中题目对应的不同难度不同标签下的问题数量
selected_problems_count = {}
for i in range(len(data_simple['PID'])):
    if data_simple['PID'][i] in selected_problems:
        difficulty = data_simple['难度'][i]
        tag = data_simple['标签'][i]
        if difficulty not in selected_problems_count:
            selected_problems_count[difficulty] = {}
        for t in tag:
            if t not in selected_problems_count[difficulty]:
                selected_problems_count[difficulty][t] = 1
            else:
                selected_problems_count[difficulty][t] += 1

# 输出selected_problems_count
for difficulty in selected_problems_count:
    print('============',difficulty,'=============')
    for tag in selected_problems_count[difficulty]:
        print(tag, selected_problems_count[difficulty][tag])



df_simple = pd.DataFrame(data_simple)
df_simple.to_excel('simple_problems.xlsx', index=False)

print(len(selected_problems))

print('Success')


    