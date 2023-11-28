import time 
# 定义函数fibonacci，参数n
n = 100
# 定义变量t1,t2，分别赋值为0和1
t1, t2 = 0, 1
# 打印输出Fibonacci Series
print("Fibonacci Series: ", end=" ")
# 记录函数开始时间
start = time.perf_counter()
# 循环n次，每次打印输出t1，并将t1和t2的值进行交换
for i in range(n):
    print(t1, end=" ")
    nextTerm = t1 + t2
    t1 = t2
    t2 = nextTerm

# 记录函数结束时间
end = time.perf_counter()

# 计算函数运行时间
time_spent = end - start
# 打印输出函数运行时间
print("\nTime taken: ", time_spent, " seconds")
