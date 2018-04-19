import Data
import queue

DEBUG = 1

class Manager:

    base = []

    def __init__(self, file_base ):


        try:
            file = open(file_base, 'r')
            lines = file.readlines()
            for line in lines:
                line = line.replace(',', ' ')
                line = line.split()
                self.base.append(Data.Data(line, line[-1]))
        except Exception as e:
            print(e)


    def classification(self, file_classification, k):

        data_classification = []

        try:
            file = open(file_classification, 'r')
            lines = file.readlines()
            for line in lines:
                line = line.replace(',', ' ')
                line = line.split()
                data_classification.append(Data.Data(line))
        except Exception as e:
            print(e)

        data_nearest = []

        for i in range(len(data_classification)):
            data_nearest.append(queue.PriorityQueue())
            for base in self.base:
                data_nearest[i].put((base.distance(data_classification[i]), base.classification))

        for i in range(len(data_nearest)):
            qt = {}
            for j in range(k):
                node = data_nearest[i].get()
                if not node[1] in qt:
                    qt[node[1]] = 1
                else:
                    qt[node[1]] += 1
            answer = (0, '')
            for e in qt:
                if qt[e] > answer[0]:
                    answer = (qt[e], e)
            data_classification[i].classification = answer[1]

        '''
            Teste para K = 1 e como entrada o próprio dado
        '''
        if DEBUG:
            for i in range(len(data_classification)):
                if not data_classification[i].classification == self.base[i].classification:
                    print(i, "Erro ")


s = "lenses.data"
a = Manager(s)
a.classification(s, 1)