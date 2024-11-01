# LCodeGenAssess

#### Architecture

1. LCodeGenBench: A benchmark dataset, consisting of 1050 programming problems sourced from the Luogu platform
   (1) selected_problems: The problem set, which consists of 1050 files, each file corresponding to a problem, with the file name being the problem ID in Luogu.
   (2) selected_problems_C: The problem set, which consists of 1050 files, each file adding a sentence to require the CG-LLMs to generate C code for the problem.
   (3) selected_problems_C_no_io:The problem set, which consists of 1050 files, each file add a sentence to require the CG-LLMs to generate C code for the problem without test cases.
   (4) info_problems.xlsx: The problem info of 10079 problems crawled from the Luogu platform, including ProblemID, difficulty level, and algorithm flag.
   (5) selected_problems.xlsx: The problem info of 1050 selected problems,including ProblemID, difficulty level, and algorithm flag.
2. Scripts: python scripts to perform the experiments
   (1) ProblemCrawl.py: The script used to crawl the difficulty, algorithm tags and content of problems from the Luogu platform.
   (2) ProblemSlection.py: The script used to construct our benchmark, which consists of 1050 problems, and spans over seven difficulty levels and ten top algorithms.
   (3) ProblemGenerate.py: The script used to add a sentence to each problem to require the CG-LLMs generate C code for the problem. We can easily modify this script to require the CG-LLMs to generate code in other language.
   (4) CodeGenerateEvaluate_Parallel.py: The script used to employ the CG-LLMs to generate code for each problem, and submit the code to Luogu platform for evaluation.
   (5) data_statics.py: The script used to statistically analyze the evaluation results and provide the statistics data.
3. Experiments: The experimental results of this paper
   (1) result: the evaluation results of 5 CG-LLMs based on problem set "selected_problems_C"
   (2) result_no_io: the evaluation results of 5 CG-LLMs based on problem set "selected_problems_C_no_io"
   (3) statics: the statistic data of the evaluation results based on problem set "selected_problems_C".    
   (4) statics_no_io: the statistic data of the evaluation results based on problem set "selected_problems_C_no_io".  
4. README.md: This file.

#### Instructions
Our experiments can be performed on either windows or Linux.
1. Crawl the problem descriptions from the Luogu platform using the problem IDs. The platform comprises a total of 10079 problems. This step generates the file "info_problems.xlsx".

   ```
   > cd scripts
   > python ProblemCrawl.py
   ```
   
2. Select 1050 problems from the crawled problems, and save them in the folder "selected_problems".

```
> cd scripts
> python ProblemSlection.py
```

3. Add a sentence to each problem to require the CG-LLMs to generate C code for the problem.

```
> cd scripts
> python ProblemGenerate.py
```

4. Employ CG-LLMs to generate code for each problem, submit this code to Luogu platform for evaluation and obtain the evaluation results

```
> cd scripts
> python CodeGenerateEvaluate_Parallel.py
```

5. Analyze the evaluation results and save the statistical data.

```
> cd scripts
> python data_statics.py
```

#### Experimental Environment

    - System Requirements: This project can be run on any environment that supports Python.
    - Python Version: 3.8+
    - Python Packages:
      - `requests`
      - `pandas`
      - `openai`
      - `zhipuai` 


