'''===========================================================
0, Waiting, 任务等待执行
1, Judging, 评测中
2, Compile Error, 编译失败
3, Output Limit Exceeded, 输出超限
4, Memory Limit Exceeded, 内存超限
5, Time Limit Exceeded, 运行时间超限
6, Wrong Answer, 答案错误
7, Runtime Error, 运行时错误
11, Invalid, 结果非法（一般是内部错误等，可以反馈）
12, Accepted, 结果正确、评测通过
14, Overall Unaccepted, 评测不通过（评测结果、子任务中使用，根据计分方式返回的评测失败）
=============================================================='''
import requests
import json
import time
import re
import os
import pandas as pd
from openai import OpenAI
from zhipuai import ZhipuAI
import qianfan
import shutil
from concurrent.futures import ThreadPoolExecutor, as_completed

problem_path = "problems\\selected_C"               # 问题描述文件路径
result_path = "result"                    # 结果文件路径
generated_code_path = "generated_code"    # 生成代码文件路径
post_url = "https://open-v1.lgapi.cn/judge/problem"
get_url = "https://open-v1.lgapi.cn/judge/result"
start_time = 0

EXEC_MODEL = 2  # model = 1表示每次运行时都会先清除掉之前的数据，model = 2表示每次运行时都会接着使用之前的数据
start_problem = 'P1001'  # 开始评测的题目编号，若model = 2则从该题目开始评测 

# 获取problem_path目录下的题目列表
def get_problems(problem_path):
    problems = []
    for file in os.listdir(problem_path):
        with open(os.path.join(problem_path, file), 'r', encoding='utf-8') as f:
            content = f.read()
            problems.append((file, content))
    return problems

# 代码生成客户端
def code_generation_client(problem, client, model_name):
    print(f"--{model_name} start code generation")

    # 若生成失败，重新生成，最多重试5次
    for i in range(5):
        try:
            response = client.chat.completions.create(
                model=model_name,
                messages=[
                    # {"role": "system", "content": "你是一位智能编程助手，你可以根据用户提供的问题描述准确生成代码"},
                    {"role": "user", "content": problem},
                ],
                stream=False
            )
            
            content = response.choices[0].message.content
            pattern = r'```c(.*?)```'
            match = re.search(pattern, content, re.DOTALL)

            print(f"##{model_name} finished code generation")

            if match:
                return match.group(1).strip()
            else:
                print(f"在 {model_name} 的响应中未找到有效代码段。")
                print(content)
                return None

        except Exception as e:
            print(f"{model_name} 代码生成失败，错误信息: {e}")
            print(f"等待2秒后重新生成")
            time.sleep(2)

def code_generation_Llama(problem):
    print('--Llama start code generation')
    os.environ["QIANFAN_ACCESS_KEY"] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
    os.environ["QIANFAN_SECRET_KEY"] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"

    chat_comp = qianfan.ChatCompletion()

    # 指定特定模型
    resp = chat_comp.do(
        model="Meta-Llama-3-70B", 
        messages=[
            {"role": "user", "content": problem}
        ],
        stream=False
    )

    #print(resp["body"]['result'])
    
    content = resp["body"]['result']
    pattern = r'```(.*?)```'
    match = re.search(pattern, content, re.DOTALL)

    print(f"##Llama finished code generation")

    if match:
        code = match.group(1).strip()
        if code[0] == 'c':
            code = code[1:]
        return code
    else:
        print(f"在 Llama 的响应中未找到有效代码段。")
        print(resp["body"])
        return None

# 调用DeepSeek进行代码生成
def code_generation_deepseek(problem):
    client = OpenAI(api_key="XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", base_url="XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX")
    return code_generation_client(problem, client, "deepseek-chat")

# 调用CodeGeeX进行代码生成
def code_generation_codegeex(problem):
    client = ZhipuAI(api_key="XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX")
    return code_generation_client(problem, client, "codegeex-4")

# 调用qwen进行代码生成
def code_generation_qwen(problem):
    client = OpenAI(
        api_key="XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", 
        base_url="XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
    )
    return code_generation_client(problem, client, "qwen-coder-turbo-latest")

# 调用kimi进行代码生成
def code_generation_kimi(problem):
    client = OpenAI(
        api_key="XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", 
        base_url="XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
    )
    return code_generation_client(problem, client, "moonshot-v1-8k")

# 调用chatGPT进行代码生成
def code_generation_chatgpt4o_mini(problem):
    client = OpenAI(
        api_key="XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", 
        base_url="XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
    )    
    return code_generation_client(problem, client, "gpt-4o-mini")

def code_generation_o1_mini(problem):    
    key='XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX'
    client = OpenAI(       
        base_url="XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
        api_key=key
    )    
    return code_generation_client(problem, client, "o1-mini")

# 调用claude进行代码生成
def code_generation_claude_3_5_sonnet(problem):    
    key='XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX'
    client = OpenAI(       
        base_url="XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
        api_key=key
    )    
    return code_generation_client(problem, client, "claude-3-5-sonnet-20240620")
    # return code_generation_client(problem, client, "claude-3-sonnet-20240229")

# 代码生成入口函数
def code_generation(problem, model_name):
    if model_name == "deepseek":
        return code_generation_deepseek(problem)
    elif model_name == "codegeex":
        return code_generation_codegeex(problem)
    elif model_name == "qwen":
        return code_generation_qwen(problem)
    elif model_name == "kimi":
        return code_generation_kimi(problem)
    elif model_name == "chatgpt4o_mini":
        return code_generation_chatgpt4o_mini(problem)
    elif model_name == 'Llama':
        return code_generation_Llama(problem)
    elif model_name == 'o1_mini':
        return code_generation_o1_mini(problem)
    elif model_name == 'claude_3_5_sonnet':
        return code_generation_claude_3_5_sonnet(problem)
    else:
        print(f"未知的模型名称: {model_name}")
        return None

# 提交洛谷平台进行代码评测
def evaluate(pid, code):
    global post_url, get_url, start_time

    # 请求头
    headers = {
        "Authorization": "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
        "Content-Type": "application/json; charset=UTF-8",
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/128.0.0.0 Safari/537.36 Edg/128.0.0.0"
    }

    # POST请求体
    data = {
        "pid": pid,
        "lang": "cxx/14/gcc",
        "o2": True,
        "code": code,
        "trackId": "string"
    }
    
    success_get = False
    response = None
    while not success_get:
        # 发送 POST 请求
        response = requests.post(post_url, json=data, headers=headers)

        # 获取 requestId
        requestId = response.json().get('requestId')

        # GET请求参数
        params = {
        "id": requestId
        }

        is_waiting = True

        while is_waiting:
            # 等待评测
            time.sleep(1)

            # 发送 GET 请求
            response = requests.get(get_url, params=params, headers=headers)

            # 检查请求是否成功
            if response.status_code == 200:
                result = response.json()
            
                # 检查 'data' 是否存在
                if 'data' in result and result['data'] is not None:
                    success_get = True
                else:
                    print("返回数据中没有 'data' 键或 'data' 为 None, 重新提交评测...")
                is_waiting = False
            elif response.status_code == 204:
                is_waiting = True
            else:
                print(f"请求失败，状态码: {response.status_code}, 等待2秒后重新提交评测...")
                time.sleep(1)
                is_waiting = False
    
    # 获取评判结果
    judge = response.json().get('data').get('judge')

    # 解析输出评判结果
    statuses = {0: 'Waiting', 1: 'Judging', 2: 'CompilError', 3: 'OutputLimitExceeded', 4: 'MemoryLimitExceeded', 5: 'TimeLimitExceeded', 6: 'WrongAnswer', 7: 'RuntimeError', 11: 'Invalid', 12: 'Accepted', 14: 'OverallUnaccepted'}
 
    return judge.get('status')!=2, statuses[judge.get('status')], judge.get('score'), judge.get('time'), judge.get('memory')

# 追加数据到excel文件
def append_to_excel(file_name, data):
    df = pd.read_excel(file_name)
    df = df.append(data, ignore_index=True)
    df.to_excel(file_name, index=False)

# 初始化结果文件夹和生成代码文件夹
def init_result_folders(models): 
    # 删除已有的代码目录
    if os.path.exists(generated_code_path):
        shutil.rmtree(generated_code_path)
    os.makedirs(generated_code_path)

    # 针对各模型在generated_code目录下创建子目录
    for model in models:
        os.makedirs(os.path.join(generated_code_path, model))

    # 删除已有的结果目录并创建新目录
    if os.path.exists(result_path):
        shutil.rmtree(result_path)
    os.makedirs(result_path)

    # 初始化各结果文件
    data = {'PID': []}
    for model in models:
        data[model] = []
    
    df = pd.DataFrame(data)
    df.to_excel(os.path.join(result_path, 'compile.xlsx'), index=False)
    df.to_excel(os.path.join(result_path, 'result.xlsx'), index=False)
    df.to_excel(os.path.join(result_path, 'score.xlsx'), index=False)
    df.to_excel(os.path.join(result_path, 'time.xlsx'), index=False)
    df.to_excel(os.path.join(result_path, 'memory.xlsx'), index=False)
    
# 检查结果文件夹和文件是否存在
def check_result_directories(models):
    flag = True
    if not os.path.exists(generated_code_path):
        flag = False
    for model in models:
        if not os.path.exists(os.path.join(generated_code_path, model)):
            flag = False
    if not os.path.exists(result_path):
        flag = False
    if not os.path.exists(os.path.join(result_path, 'compile.xlsx')):
        flag = False
    if not os.path.exists(os.path.join(result_path, 'result.xlsx')):
        flag = False
    if not os.path.exists(os.path.join(result_path,'score.xlsx')):
        flag = False
    if not os.path.exists(os.path.join(result_path, 'time.xlsx')):
        flag = False
    if not os.path.exists(os.path.join(result_path,'memory.xlsx')):
        flag = False
    return flag
    

# 调用模型model对问题problem进行代码生成，并对生成的代码进行评测
def process_model(model, problem):
    code = code_generation(problem[1], model)
    #print("------------")
    #print(code)
    if code is not None:
        # 保存生成的代码
        with open(os.path.join(generated_code_path, model, problem[0] + '.cpp'), 'w', encoding='utf-8') as f:
            f.write(code)

        # 评测代码    
        compile, result, score, time, memory = evaluate(problem[0], code)

        # 打印评测结果
        print(f"\n{model} evaluation result:")
        print('result: ', result)
        print('score: ', score)        

        return model, (compile, result, score, time, memory)
    else:
        print(f"{model} did not generate valid code, skipping evaluation...")
        return model, ('None', 'None', 'None', 'None', 'None')
    
def main():
    global start_problem    
    # models = ['deepseek', 'codegeex', 'qwen', 'o1_mini', 'claude_3_5_sonnet']
    models = ['o1_mini']

    # models = ['deepseek', 'codegeex', 'qwen', 'kimi', 'chatgpt4o_mini', 'Llama', 'o1_mini', 'claude_3_5_sonnet']

    if EXEC_MODEL == 1:
        # 初始化结果文件夹和生成代码文件夹
        init_result_folders(models)
    elif EXEC_MODEL == 2:
        # 检查结果文件夹和文件是否存在
        flag = check_result_directories(models)
        if not flag:
            print("结果文件夹和文件不存在，删除已有目录，重新创建...")
            init_result_folders(models)
            start_problem = None
    
    # 获取题目列表
    problems = get_problems(problem_path)
    
    start_flag = False
#    if start_problem is None:
#        start_flag = True
        
    for problem in problems:
        if EXEC_MODEL == 2:
            if not start_flag and problem[0] != start_problem:
                continue
            elif problem[0] == start_problem:
                start_flag = True
        
        # 获取题目ID
        print('\n======= problem:', problem[0], '=======')
        
        new_compile = {'PID': problem[0]}        
        new_result = {'PID': problem[0]}
        new_score = {'PID': problem[0]}
        new_time = {'PID': problem[0]}
        new_memory = {'PID': problem[0]}
        
        # 并行调用各模型进行代码生成和评测
        with ThreadPoolExecutor() as executor:
            futures = {executor.submit(process_model, model, problem): model for model in models}
            for future in as_completed(futures):
                model, results = future.result()
                new_compile[model], new_result[model], new_score[model], new_time[model], new_memory[model] = results

        # 保存结果
        append_to_excel(os.path.join(result_path, 'compile.xlsx'), new_compile)
        append_to_excel(os.path.join(result_path, 'result.xlsx'), new_result)
        append_to_excel(os.path.join(result_path, 'score.xlsx'), new_score)
        append_to_excel(os.path.join(result_path, 'time.xlsx'), new_time)
        append_to_excel(os.path.join(result_path, 'memory.xlsx'), new_memory)

        print('elapsed time: ', round(time.time() - start_time, 2), 's')     

if __name__ == "__main__":
    start_time = time.time() 
    main()
    print("\nTotal time: ", time.time() - start_time, "s")
