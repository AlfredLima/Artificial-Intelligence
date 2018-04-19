

class Data:

    def __init__(self, values, classification=None):

        self.values = []
        for v in values[:-1]:
            self.values.append(float(v))
        if classification is None:
            self.classification = None
        else:
            self.classification = classification.replace('\n', '')

    def distance(self, data):

        sum = 0
        for i in range(len(self.values)):
            sum += abs(self.values[i] - data.values[i])
        return sum