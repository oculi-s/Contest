# -*- coding: utf-8 -*-
"""190720 Sweather without map data

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1qVJeyucyQRHYlh59YfzgLpKzxV14Zx_v
"""

import os
os.listdir()

"""##1. 데이터, 환경 구축

###1-1. 데이터 업로드
"""

from google.colab import files
uploaded = files.upload()
uploaded = files.upload()

"""###1-2. 데이터 압축 풀기"""

!unzip data.xlsx
#!unzip data_labelless.xlsx

"""###1-3. 라이브러리 선언"""

import numpy as np
import tensorflow as tf
import xlrd as xr
import xlwt as xw
import math

np.set_printoptions(suppress = True)

"""##2. 데이터 전처리 (1)

###2-1. 데이터 읽기, 할당
 - data.xlsx는 file에 저장함
 - data_labelless.xlsx는 file_prediction의 준말인 file_p에 저장함
"""

file = xr.open_workbook('data.xlsx')
file = file.sheet_by_index(0)

row = file.row
col = file.col
size_row = np.size(col(0))
size_col = np.size(row(0))

data = np.empty([size_row, size_col])
for i in range(1,size_row):
  for j in range(size_col):
    data[i][j] = row(i)[j].value

file_p = xr.open_workbook('data_labelless.xlsx')
file_p = file_p.sheet_by_index(0)

row_p = file_p.row
col_p = file_p.col
size_row_p = np.size(col_p(0))
size_col_p = np.size(row_p(0))

data_p = np.empty([size_row_p, size_col_p])
for i in range(1,size_row_p):
  for j in range(size_col_p):
    data_p[i][j] = row_p(i)[j].value

"""###2-2. floating_bit 설정
 - floating_bit : 2진수 변환 전체 비트 수
 - integer_bit : 정수에 할당할 비트 수
"""

floating_bit = 16
integer_bit = 5

"""###2-3. ftob, btof 함수 선언
 - ftob : float to binary
 - btof : binary to float
"""

def ftob(val_f):
  list = []
  for i in np.arange(integer_bit-1, integer_bit-floating_bit-1, -1):
    if val_f >= math.pow(2,i):
      list.append(1)
      val_f -= math.pow(2,i)
    else:
      list.append(0)
  return list

def btof(list):
  value = 0
  for i in range(floating_bit):
    value += list[i]*math.pow(2,integer_bit-i-1)
  return value

print(ftob(5.2))

print(btof(ftob(5.2)))

"""##3. 데이터 전처리 (2)

###3-1. nan, 0 데이터 제거
"""

epsilon = 1e-4

data = np.nan_to_num(data)
data += (data==0) * epsilon

#data_p = np.nan_to_num(data_p)
#data_p += (data_p==0) * epsilon

"""###3-2. input 정규화, upscaling, 비트화"""

tempdata = data[1:size_row, 1:size_col]
data_norm = np.float32(data)
data_norm[1:, 1:] = tempdata

# normalization
x_data = data_norm[1:size_row, 1:size_col-3]
x_mean = np.mean(x_data, axis=0, keepdims=True)
x_std = np.std(x_data, axis=0, keepdims=True)

# upscaling
x_data = (x_data-x_mean)/x_std *10 +15
tempdata = x_data

# binarization
x_data = np.empty([x_data.shape[0], x_data.shape[1]*floating_bit])
for i in range(tempdata.shape[0]):
  list = []
  for j in range(tempdata.shape[1]):
    list.append(ftob(tempdata[i][j]))
  x_data[i] = np.concatenate(list)

tempdata = data_p[1:size_row_p, 1:size_col_p]
data_norm_p = np.float32(data_p)
data_norm_p[1:, 1:] = tempdata

# normalization & upscaling
x_data_p = data_norm_p[1:size_row_p, 1:size_col_p-1]
x_data_p = (x_data_p-x_mean)/x_std*10+15
tempdata = x_data_p

# binarization
x_data_p = np.empty([x_data_p.shape[0], x_data_p.shape[1]*floating_bit])
for i in range(tempdata.shape[0]):
  list = []
  for j in range(tempdata.shape[1]):
    list.append(ftob(tempdata[i][j]))
  x_data_p[i] = np.concatenate(list)

"""###3-3. output, weight 분리"""

y_data = data_norm[1:size_row, size_col-2:size_col]
weight_data = data_norm[1:size_row, size_col-3]

#weight_data_p = data_norm_p[1:size_row_p, size_col_p-1]

"""##4. 모델 구축

- X, Y : input, output을 받을 placeholder
 - layers : layer size를 initialize 해주는 list
"""

X = tf.placeholder(np.float32, [None, x_data.shape[1]])
Y = tf.placeholder(np.float32, [None, y_data.shape[1]])

layers = [int(X.shape[1]), 64, 32, int(Y.shape[1])]
n = len(layers)
W = {}
L = X

for i in range(n-2):
    W[str(i+1)] = tf.Variable(tf.random_normal([layers[i],layers[i+1]]))
    L = tf.nn.leaky_relu(tf.matmul(L,W[str(i+1)]), 0.3)
    #L = tf.layers.dropout(L, 0.9)
    
W[str(n-1)] = tf.Variable(tf.random_normal([layers[n-2],layers[n-1]]))
L = tf.matmul(L,W[str(n-1)])

cost = tf.reduce_mean(tf.square(L-Y))
optimizer = tf.train.AdamOptimizer(0.01).minimize(cost)
is_correct = tf.less(tf.round(L-Y)*10, 1)
accuracy = tf.reduce_mean(tf.cast(is_correct, np.float32))

sess = tf.Session()
sess.run(tf.global_variables_initializer())

"""##5. 모델 학습

- valid_rate : 학습에 사용할 데이터의 비율
- 1-valid_rate 만큼의 데이터를 validation에 이용하였음
- cost_stop : 반복 학습을 멈출 cost
"""

valid_rate = 0.7
cost_stop = 0.5
epoch = 0

D = {X:x_data[0:int(size_row*valid_rate)], Y:y_data[0:int(size_row*valid_rate)]}
while(1):
  _, cost_val = sess.run([optimizer,cost], feed_dict = D)
  if epoch % 1000 == 0:
    print('%4d' % epoch, 'cost : {:.3f}'.format(cost_val))
  if cost_val <= cost_stop:
    print("cost is less than ",cost_stop)
    break
  epoch += 1

print("\noptimization finished")

"""##6. 검증 및 예측

###6-1. 함수 선언
"""

def print_accuracy_with_valid_rate(valid_rate):
  D_valid = {X:x_data[int(size_row*valid_rate):size_row], Y:y_data[int(size_row*valid_rate):size_row]}
  valid_set_accuracy = np.round(sess.run(accuracy*100, feed_dict = D_valid),2)
  print(valid_rate*100, "% validation set accuracy :", valid_set_accuracy, "%")
  
def print_label_with_input_data(input_data):
  D_label = {X:input_data}
  output = np.round(sess.run(L, feed_dict = D_label),1)
  return output

"""###6-2. 30%, 20%, 10%, 5%, 1%의 validation set에 대한 정확도 산출"""

print_accuracy_with_valid_rate(valid_rate = 0.7)
print_accuracy_with_valid_rate(valid_rate = 0.8)
print_accuracy_with_valid_rate(valid_rate = 0.9)
print_accuracy_with_valid_rate(valid_rate = 0.95)
print_accuracy_with_valid_rate(valid_rate = 0.99)

x_data

print(print_label_with_input_data(x_data[0:10]))
print(y_data[0:10])

"""###6-3. Unsupervised 데이터의 증발량 예측
 - 증발량 데이터를 label 이라는 numpy 행렬에 저장함
 - output.xls 파일에 label 데이터를 저장함
"""

label = print_label_with_input_data(x_data_p)
label *= label>0

file_w = xw.Workbook()
sheet = file_w.add_sheet('Sheet1')

for i in range(label.shape[0]):
  for j in range(label.shape[1]):
    sheet.write(i, j, round(float(label[i][j]),1))

from google.colab import files
file_w.save('output.xls')
files.download('output.xls')

"""###6-4. 총 증발량 산출"""

total_surface = math.pow(4000,2)
evaporator_surface = np.array([math.pow(0.1,2),math.pow(0.6,2)]).reshape(-1,2)*math.pi
total_source_surface = total_surface * weight_data_p.reshape(-1,1) / 100
unit_evaporation = label

total_evaporation =  np.round(unit_evaporation * total_source_surface / evaporator_surface)
total_evaporation *= total_evaporation>0
total_evaporation = np.mean(total_evaporation, axis = 1, keepdims = True)

file_w = xw.Workbook()
sheet = file_w.add_sheet('Sheet1')

for i in range(total_evaporation.shape[0]):
  for j in range(total_evaporation.shape[1]):
    sheet.write(i, j, total_evaporation[i][j])

from google.colab import files
file_w.save('total.xls')
files.download('total.xls')

total_evaporation /= np.max(total_evaporation)