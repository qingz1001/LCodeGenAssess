import os
import shutil

# 复制Original文件夹中的所有文件到C文件夹中
original_path = "LCodeGenBench\\selected_problems" # 原始文件夹路径
c_path = "LCodeGenBench\\selected_problems_C" # 目标文件夹路径

# 如果目标文件夹存在，则删除
if os.path.exists(c_path):
    shutil.rmtree(c_path)
os.makedirs(c_path)

for file in os.listdir(original_path): # 遍历Original文件夹中的所有文件
    shutil.copy(os.path.join(original_path, file), c_path) # 将文件复制到目标文件夹中

# 在每个文件中添加一句话
for file in os.listdir(c_path): # 遍历目标文件夹中的所有文件
    with open(os.path.join(c_path, file), "r+", encoding="utf-8") as f: # 打开文件
        content = f.read() # 读取文件内容
        f.seek(0, 0) # 移动文件指针到开头
        f.write("请针对下面问题生成对应的C代码，生成代码之后不需要再给出后面的代码解释：\n\n" + content) # 在文件开头写入一句话
        f.truncate() # 截断文件，使写入的内容生效
# 关闭文件


