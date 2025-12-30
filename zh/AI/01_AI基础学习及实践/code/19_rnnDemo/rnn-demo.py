import numpy
# 我是学生 -> [[1, 0, 2, 3, 6], [1, 2, 0, 2, 4], [2, 4, 1, 2, 5], [4, 3, 2, 4, 0]]
# 我爱学习 -> [[1, 0, 2, 3, 6], [2, 1, 2, 0, 3], [2, 4, 1, 2, 5], [0, 2, 3, 0, 1]]
# 我是男生 -> [[1, 0, 2, 3, 6], [1, 2, 0, 2, 4], [2, 4, 5, 1, 2], [4, 3, 2, 4, 0]]

input = [[[1, 0, 2, 3, 6], [1, 2, 0, 2, 4], [2, 4, 1, 2, 5], [4, 3, 2, 4, 0]],
         [[1, 0, 2, 3, 6], [2, 1, 2, 0, 3], [2, 4, 1, 2, 5], [0, 2, 3, 0, 1]],
         [[1, 0, 2, 3, 6], [1, 2, 0, 2, 4], [2, 4, 5, 1, 2], [4, 3, 2, 4, 0]]]
input = numpy.array(input)
# print(input.shape)     #批量大小, 矩阵长度, 词嵌入大小 
# 3是表示3句话，4表示每一句4个字，5表示每个字用5维（5个数）表示。

# 把第0轴和第1轴交换，也就是把句子长度放在前面。因为为了，RNN是一字一个字的输入。
# 这样交换后，for x in input：x就是每个句子的第一个字。
# 批量大小, 句子长度, 词嵌入大小 --> 句子长度，批量大小, 词嵌入大小 
input = input.transpose((1, 0, 2))
print("input shape:")
print(input.shape)

batch = input.shape[1]           # =3  每个批次里有3句话
embedding_len = input.shape[2]   # =5  每个字用5个数字表示
hidden_size = 6                  # 一层6个神经元

# W_xh：隐藏层可学习权重参数
W_xh = numpy.random.random((embedding_len, hidden_size))  #(5, 6)
# W_hh：用于上一个时刻隐藏层变量对当前隐藏层变量影响的可学习参数
W_hh = numpy.random.random((hidden_size, hidden_size))    #(6, 6)
# W_hq：输出层可学习权重参数
W_hq = numpy.random.random((hidden_size, embedding_len))  #(6, 5)
# H：隐藏变量
H = numpy.random.random((batch, hidden_size))             #(3, 6)

params = (W_xh, W_hh, W_hq)

# rnn模型定义
def rnn(inputs, H, params):
    # `inputs`的形状：(句子长度，批量大小, 词嵌入大小)
    W_xh, W_hh, W_hq  = params
    outputs = []
    # `X`的形状：(批量大小, 词嵌入大小) 句子长度为4，循环4次。
    for X in inputs:
        # 第i循环，同时输入每个句子的第i个字的词嵌入。
        H = numpy.maximum(numpy.matmul(X, W_xh) + numpy.matmul(H, W_hh), 0)
        Y = numpy.matmul(H, W_hq)
        outputs.append(Y)
    return numpy.array(outputs), H

# 运行模型
outputs, H = rnn(input, H, params)
print("outputs:")
print(outputs)
print("outputs shape:")
print(outputs.shape)
print("hidden states shape:")
print(H.shape)