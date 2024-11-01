import pandas as pd
import os
import shutil
import time
import matplotlib.pyplot as plt
import numpy as np

path = 'result'
path_statics = 'statics'

# 读取文件内容
problems = pd.read_excel(path + '\\selected_problems.xlsx')
rcompile = pd.read_excel(path + '\\compile.xlsx')
rresult = pd.read_excel(path + '\\result.xlsx')
rscore = pd.read_excel(path + '\\score.xlsx')
rtime = pd.read_excel(path + '\\time.xlsx')

# 创建文件夹path_statics
if os.path.exists(path_statics):
    shutil.rmtree(path_statics)
os.mkdir(path_statics)

# 统计selected_problems.xlsx下的难度数据
difficulty_counts = problems['难度'].unique().tolist()
print(difficulty_counts)

interested_tags = ['模拟', '数学', '枚举', '字符串', '贪心', '搜索', '二分', '动态规划', '图论', '线段树']
interested_tags_en = ['Simulation', 'Mathematics', 'Enumeration', 'String', 'Greedy', 'Search', 'Binary Search', 'Dynamic Programming', 'Graph Theory', 'Segment Tree']
difficulties = ['入门', '普及−', '普及/提高−', '普及+/提高', '提高+/省选−', '省选/NOI−', 'NOI/NOI+/CTSC']
dificulties_en = ['Entry-level', 'Generalization-', 'Generalization/Improvement-', 'Generalization+/Improvement', 'Improvement+/Provincial\_selection-', 'Provincial\_selection/NOI-', 'NOI/NOI+/CTSC']

valid_scores = []
correct_scores = []
score_scores = []

# 统计有效率
def compile_statics():
    global valid_scores
    #提取compile的列的信息
    models = rcompile.columns.tolist()[1:]

    # 初始化validate_cnt
    validate_cnt = {}
    for model in models:
        validate_cnt[model] = {}
        for difficulty in difficulty_counts:
            validate_cnt[model][difficulty] = 0

    # problems里面包含PID和难度两列数据，rcompile里面包含PID和各模型的编译结果数据，结合两个数据统计不同模型不同难度下的编译通过率，存放在validate_cnt中
    for index, row in problems.iterrows():
        pid = row['PID']
        difficulty = row['难度']
        for model in models:
            # 根据pid和model找到对应的编译结果
            value = rcompile.loc[rcompile['PID'] == pid, model].values[0]
            if not pd.isnull(value) and int(value) == 1:
                validate_cnt[model][difficulty] += 1

    #将validate_cnt写入excel
    compile_statics = {'难度': difficulty_counts.copy()}
    for model in models:
        compile_statics[model] = [validate_cnt[model][difficulty] for difficulty in difficulty_counts]
    # 添加一行数据"总计"
    compile_statics['难度'].append('总计')
    for model in models:
        total = sum(compile_statics[model])
        compile_statics[model].append(total)
        valid_scores.append(round(total/1050 * 100, 1))

    df = pd.DataFrame(compile_statics)
    df.to_excel(path_statics + '\\compile_statics.xlsx', index=False)

    print(valid_scores)

# 生成tex表格段落
def generate_tex_difficulty(result_statics, type, models):
    data = '\\hline\n'
    for model in models:
        rmodel = model.replace('_', '\_')
        data += ' & ' + rmodel
    data += '\\\\\\hline\n'

    for difficulty in dificulties_en:
        data += difficulty
        for model in models:
            data += ' & '
            diff_cn = difficulties[dificulties_en.index(difficulty)]
            if diff_cn in difficulty_counts:
                value = result_statics[model][result_statics['难度'].index(diff_cn)]
                data += str(value) + '\%'
            else:
                data += '-'
        data += '\\\\\n '
    data += '\\hline\n'

    data += 'Total'
    for model in models:
        data += ' & '
        value = result_statics[model][result_statics['难度'].index('总计')]
        data += str(value) + '\%'
    data += '\\\\ \\hline'

    with open(path_statics + '\\' + type + '_statics_difficulty.txt', 'w', encoding='utf-8') as f:
        f.write(data)

# 统计不同难度下的正确率
def result_statics_difficulty():
    global correct_scores

    #提取result的列的信息
    models = rresult.columns.tolist()[1:]

    # 初始化validate_cnt
    validate_cnt = {}
    for model in models:
        correct_scores.append(0)
        validate_cnt[model] = {}
        for difficulty in difficulty_counts:
            validate_cnt[model][difficulty] = 0

    # problems里面包含PID和难度两列数据，rresult里面包含PID和各模型的编译结果数据，结合两个数据统计不同模型不同难度下的编译通过率，存放在validate_cnt中
    for index, row in problems.iterrows():
        pid = row['PID']
        difficulty = row['难度']
        for model in models:
            # 根据pid和model找到对应的编译结果
            value = rresult.loc[rresult['PID'] == pid, model].values[0]
            if not pd.isnull(value) and value == 'Accepted':
                validate_cnt[model][difficulty] += 1
                correct_scores[models.index(model)] += 1

    #将validate_cnt写入excel
    result_statics = {'难度': difficulty_counts.copy()}
    for model in models:
        result_statics[model] = [round(validate_cnt[model][difficulty]/150*100,1) for difficulty in difficulty_counts]

    # 添加一行数据"总计"
    result_statics['难度'].append('总计')
    for model in models:
        result_statics[model].append(round(np.mean(result_statics[model]),1))
    
    df = pd.DataFrame(result_statics)
    df.to_excel(path_statics + '\\result_statics_difficulty.xlsx', index=False)

    # 生成tex表格段落
    generate_tex_difficulty(result_statics, 'correct', models)

    for i in range(len(models)):
        correct_scores[i] = round(correct_scores[i]/1050 * 100, 1)
    print(correct_scores)   


# 统计不同难度下的得分率
def score_statics_difficulty():
    global score_scores
    #提取result的列的信息
    models = rscore.columns.tolist()[1:]

    # 初始化scores_total
    scores_total = {}
    for model in models:
        score_scores.append(0)
        scores_total[model] = {}
        for difficulty in difficulty_counts:
            scores_total[model][difficulty] = 0

    # problems里面包含PID和难度两列数据，rscore里面包含PID和各模型的编译结果数据，结合两个数据统计不同模型不同难度下的编译通过率，存放在scores_total中
    for index, row in problems.iterrows():
        pid = row['PID']
        difficulty = row['难度']
        for model in models:
            # 根据pid和model找到对应的编译结果
            value = rscore.loc[rscore['PID'] == pid, model].values[0]
            if not pd.isnull(value):
                scores_total[model][difficulty] += int(value)
                score_scores[models.index(model)] += int(value)

    #将scores_total写入excel
    score_statics = {'难度': difficulty_counts.copy()}
    for model in models:
        score_statics[model] = [round(scores_total[model][difficulty]/150,1) for difficulty in difficulty_counts]

    # 添加一行数据"总计"
    score_statics['难度'].append('总计')
    for model in models:
        score_statics[model].append(round(np.mean(score_statics[model]),1))

    df = pd.DataFrame(score_statics)
    df.to_excel(path_statics + '\\score_statics_difficulty.xlsx', index=False)

    for i in range(len(models)):
        score_scores[i] = round(score_scores[i]/1050, 1)
    print(score_scores)

    # 生成tex表格段落
    generate_tex_difficulty(score_statics, 'score', models)

# 生成tex表格段落
def generate_tex_algorithm(result_statics, type, models):
    data = '\\hline\n'
    for model in models:
        rmodel = model.replace('_', '\_')
        data += ' & ' + rmodel
    data += ' & average \\\\\\hline\n'

    for tag in interested_tags_en:
        data += tag
        sum_value = 0
        for model in models:
            data += ' & '
            tag_cn = interested_tags[interested_tags_en.index(tag)]
            value = result_statics[model][result_statics['算法'].index(tag_cn)]
            data += str(value) + '\%'

            sum_value += value
        data += ' & '
        data += str(round(sum_value/len(models),1)) + '\%'

        data += '\\\\\n '
    data += '\\hline\n'

    with open(path_statics + '\\' + type + '_statics_algorithm.txt', 'w', encoding='utf-8') as f:
        f.write(data)

# 统计不同算法下的正确率
def result_statics_algorithm():
    #提取result的列的信息
    models = rresult.columns.tolist()[1:]

    # 初始化validate_cnt
    validate_cnt = {}
    for model in models:
        validate_cnt[model] = {}
        for tag  in interested_tags:
            validate_cnt[model][tag] = 0

    # 初始化每种算法下的问题个数信息
    alg_problem_cnt = {}
    for tag in interested_tags:
        alg_problem_cnt[tag] = 0

    # problems里面包含PID和难度两列数据，rresult里面包含PID和各模型的编译结果数据，结合两个数据统计不同模型不同难度下的编译通过率，存放在validate_cnt中
    for index, row in problems.iterrows():
        pid = row['PID']
        tags = row['标签'].strip("[]").split(',')

        new_tags = []
        for tag in tags:
            tag = tag.strip().strip('\'').strip('\"')
            if tag in interested_tags:             
                new_tags.append(tag)
        tags = new_tags.copy()

        for tag in tags:
            if tag in interested_tags:
                alg_problem_cnt[tag] += 1

        for model in models:
            # 根据pid和model找到对应的编译结果
            value = rresult.loc[rresult['PID'] == pid, model].values[0]
            if not pd.isnull(value) and value == 'Accepted':
                for tag in tags:
                    validate_cnt[model][tag] += 1

    #将validate_cnt写入excel
    result_statics = {'算法': interested_tags.copy()}
    for model in models:
        result_statics[model] = [round(validate_cnt[model][tag]/alg_problem_cnt[tag]*100, 1) for tag in interested_tags]

    df = pd.DataFrame(result_statics)
    df.to_excel(path_statics + '\\result_statics_algorithm.xlsx', index=False)

    # 生成tex表格段落
    generate_tex_algorithm(result_statics, 'correct', models)

# 统计不同算法下的得分率
def score_statics_algorithm():
    #提取result的列的信息
    models = rscore.columns.tolist()[1:]

     # 初始化scores_total
    scores_total = {}
    for model in models:
        scores_total[model] = {}
        for tag in interested_tags:
            scores_total[model][tag] = 0

    # 初始化每种算法下的问题个数信息
    alg_problem_cnt = {}
    for tag in interested_tags:
        alg_problem_cnt[tag] = 0

    # problems里面包含PID和难度两列数据，rscore里面包含PID和各模型的编译结果数据，结合两个数据统计不同模型不同难度下的编译通过率，存放在validate_cnt中
    for index, row in problems.iterrows():
        pid = row['PID']
        tags = row['标签'].strip("[]").split(',')

        new_tags = []
        for tag in tags:
            tag = tag.strip().strip('\'').strip('\"')
            if tag in interested_tags:             
                new_tags.append(tag)
        tags = new_tags.copy()

        for tag in tags:
            if tag in interested_tags:
                alg_problem_cnt[tag] += 1

        for model in models:
            # 根据pid和model找到对应的编译结果
            value = rscore.loc[rscore['PID'] == pid, model].values[0]
            if not pd.isnull(value):
                for tag in tags:
                    scores_total[model][tag] += int(value)

    #将scores_total写入excel
    score_statics = {'算法': interested_tags.copy()}
    for model in models:
        score_statics[model] = [round(scores_total[model][tag]/alg_problem_cnt[tag], 2) for tag in interested_tags]

    df = pd.DataFrame(score_statics)
    df.to_excel(path_statics + '\\score_statics_algorithm.xlsx', index=False)

    # 生成tex表格段落
    generate_tex_algorithm(score_statics, 'score', models)

# 统计平均时间
def time_statics():
    # 提取time的列的信息
    models = rtime.columns.tolist()[1:]

    # 初始化time_total
    time_total = {}
    for model in models:
        time_total[model] = 0

    validate_cnt = 0
    for index, row in rresult.iterrows():
        pid = row['PID']

        flag = True
        for model in models:
            if row[model] != 'Accepted':
                flag = False
                break
        if flag:
            validate_cnt += 1
            for model in models:
                time_total[model] += rtime.loc[rtime['PID'] == pid, model].values[0]

    # 将time_total写入excel
    time_statics = {'模型': models.copy()}
    time_statics['平均时间'] = [round(time_total[model]/validate_cnt, 2) for model in models]

    print('全部通过的题目数：', validate_cnt)

    df = pd.DataFrame(time_statics)
    df.to_excel(path_statics + '\\time_statics.xlsx', index=False)

# 绘制性能对比图
def plot_compare_fig():
    global valid_scores, correct_scores, score_scores
    models = rscore.columns.tolist()[1:]
    data = {}
    for model in models:
        data[model] = [valid_scores[models.index(model)], correct_scores[models.index(model)], score_scores[models.index(model)]]

    x = np.arange(3) * 1.4  # x轴刻度标签位置
    width = 0.2  # 条形的宽度

    fig, ax = plt.subplots(figsize=(10, 5))

    rects = {}
    for model in models:
        xnp = x - 3 * width / 2 + width * models.index(model)
        rects[model] = ax.bar(xnp, data[model], width, label=model)

    # 添加一些文本标签
    ax.set_xlabel('models')
    ax.set_ylabel('Scores')
    ax.set_title('Performance Comparison')
    ax.set_xticks(x)
    ax.set_xticklabels(['valid rate', 'correct rate', 'scoring rate'])
    ax.legend()

    # 在每个条形上添加数值标签
    def autolabel(rects):
        for rect in rects:
            height = rect.get_height()
            ax.annotate(f'{height}',
                        xy=(rect.get_x() + rect.get_width() / 2, height),
                        xytext=(0, 3),  # 3 points vertical offset
                        textcoords="offset points",
                        ha='center', va='bottom')
            
    for model in models:
        autolabel(rects[model])

    fig.tight_layout()

    plt.savefig(path_statics + '\\compare.png')

    plt.show()

# 统计每个模型独立解出来的题目个数
def independent_solve_statics():
    models = rresult.columns.tolist()[1:]

    total_solved = {}
    independent_solved = {}
    for model in models:
        total_solved[model] = 0
        independent_solved[model] = 0
    total = 0

    for index, row in rresult.iterrows():
        pid = row['PID']

        num = 0
        smodel = ''

        for model in models:
            if row[model] == 'Accepted':
                total_solved[model] += 1
                num += 1
                smodel = model

        if num > 0:
            total += 1

        if num == 1:
            independent_solved[smodel] += 1 

    print(f'total solved: {total}')
    for model in models:
        print(f'{model}: {total_solved[model]}  {independent_solved[model]}')

def main(): 
    # 统计有效率   
    compile_statics()

    # 统计正确率   
    result_statics_difficulty()

    # 统计不同难度下的得分率
    score_statics_difficulty()

    # 统计不同算法下的正确率
    result_statics_algorithm()

    # 统计不同算法下的得分率
    score_statics_algorithm()

    # 统计平均时间
    time_statics()

    # 绘制性能对比图
    plot_compare_fig()

    # 统计每个模型独立解出来的题目个数
    independent_solve_statics()

if __name__ == "__main__":
    start_time = time.time() 
    main()
    print("\nTotal time: ", time.time() - start_time, "s")
