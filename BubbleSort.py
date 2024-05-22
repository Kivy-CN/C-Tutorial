def bubble_sort(arr):
    # 使用Python的内置排序函数
    arr.sort(key=lambda x: x['score'])

def main():
    N = 3
    info_arr = []

    # 输入数据
    for i in range(N):
        subject = input("输入科目: ")
        score = int(input("输入分数: "))
        info_arr.append({'subject': subject, 'score': score})

    # 对分数进行排序
    bubble_sort(info_arr)

    # 打印排序后的结果
    for i in range(N):
        print(info_arr[i]['subject'], info_arr[i]['score'])

if __name__ == "__main__":
    main()