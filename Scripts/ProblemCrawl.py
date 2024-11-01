from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time
import pandas as pd
import shutil
import os

startID = 1001   #起始问题ID
endID   = 100079   #结束问题ID
info_file = 'info_problems.xlsx'   # 问题信息文件
problem_path = 'problems' # 问题内容文件保存路径

# 获取问题内容
def get_problem_content(driver):
    button = driver.find_element(By.XPATH, '//a[contains(text(), "复制Markdown")]')
    button.click()
    time.sleep(2)

    textarea = driver.find_element(By.XPATH, '//textarea[@class="copy-input"]')
    content = textarea.get_attribute('value')
    return content

# 获取问题难度
def get_problem_difficulty(driver):
    difficulty_label = driver.find_element(By.XPATH, '//span[contains(text(), "难度")]')
    difficulty_container = difficulty_label.find_element(By.XPATH, '../..')  
    #print(difficulty_container.get_attribute('innerHTML'))  # 打印父元素的HTML内容
    difficulty_link = difficulty_container.find_element(By.XPATH, './span/a/span')
    difficulty = difficulty_link.text.strip()
    return difficulty

# 获取问题标签
def get_problem_tags(driver):
    button = driver.find_element(By.XPATH, '//span[contains(text(), "查看算法标签")]')
    button.click()
    time.sleep(2)
    
    tags_container = driver.find_element(By.XPATH, '//div[@class="tags-wrap multiline"]')
    tags_items = tags_container.find_elements(By.XPATH, './/a[@class="tag color-none"]')
    tags = [tag.find_element(By.XPATH, './/span').text for tag in tags_items]
    return tags

# 追加数据到excel文件
def append_to_excel(file_name, data):
    df = pd.read_excel(file_name)
    df = df._append(data, ignore_index=True)
    df.to_excel(file_name, index=False)

# 创建必要的文件夹和结果文件
def create_folders_and_info_file(problem_path, info_file):
    data = {'PID': [], '难度': [], '标签': []}
    df = pd.DataFrame(data)
    df.to_excel(info_file, index=False)

    if os.path.exists(problem_path):
        shutil.rmtree(problem_path)
    os.makedirs(problem_path)

# 主函数
def main():
    # 创建必要的文件夹和结果文件
    global problem_path, info_file
    create_folders_and_info_file(problem_path, info_file)

    # 设置Chrome选项
    chrome_options = webdriver.ChromeOptions()
    chrome_options.add_argument('--headless')  # 无头模式，若需要显示浏览器则移除此行
    chrome_options.add_argument("--window-position=-2400,-2400")

    # 创建WebDriver对象
    service = Service('C:\Program Files\chromedriver\chromedriver.exe')
    driver = webdriver.Chrome(service=service, options=chrome_options)

    for i in range(startID, endID + 1):
        # 生成问题ID
        pid = "P" + str(i)
        info = {'PID': pid}
        print('\n## 爬取问题 ' + pid)

        # 访问网页
        url = 'https://www.luogu.com.cn/problem/' + pid
        driver.get(url)

        # 等待页面加载
        WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.XPATH, '//a[contains(text(), "复制Markdown")]')))

        try:
            # 获取问题内容
            content = get_problem_content(driver)

            # 获取问题难度
            difficulty = get_problem_difficulty(driver)

            # 获取问题标签
            tags = get_problem_tags(driver)

            # 将问题内容、难度、标签写入文件
            with open("problems/" + pid, "w", encoding="utf-8") as f:
                f.write(content)
            print("内容已写入文件" + pid)

            info['难度'] = difficulty
            info['标签'] = tags
            append_to_excel('info.xlsx', info)            

            print("难度:", difficulty)
            print("标签:", tags)

        except Exception as e:
            print("出错:", e)

    # 关闭浏览器
    driver.quit()

if __name__ == "__main__":
    main()
