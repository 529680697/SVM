import requests


def getdata():  # 收集数据
    url = 'https://archive.ics.uci.edu/ml/machine-learning-databases/cmc/cmc.data'
    data = requests.get(url).content
    with open('data1.txt', 'wb+') as fw:
        fw.write(data)


def data_feature():  # 数据处理
    fr = open('data1.txt')
    fw = open('data2.txt', 'w')
    datalist = []
    while True:
        line = fr.readline()
        if not line:
            break
        linelist = line.split(',')
        datalist.append(linelist)
    for i in datalist:
        for j in i:
            fw.write(j+' ')
        fw.write('\n')
    fr.close()
    fw.close()


if __name__ == '__main__':
    getdata()
    data_feature()

