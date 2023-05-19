#!/bin/env python3
import pickle, gzip, uuid, sys
import numpy as np
import pandas as pd
from sklearn.impute import SimpleImputer
from sklearn.metrics import classification_report
from sklearn.neighbors import KNeighborsClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.naive_bayes import GaussianNB

data_path = "./data"
train_set_name = ["A","B","C","D","E"]
verify_set_name = ["X", "Y", "Z"]
classifiers = [
  ("决策树", DecisionTreeClassifier),
  ("高斯朴素贝叶斯", GaussianNB),
  ("K临近", KNeighborsClassifier),
]

def benchmark(model, trainX, trainY, testX, testY, arg = None):
  m = model() if arg == None else model(n_jobs=arg)
  m.fit(trainX, np.ravel(trainY))
  return m, classification_report(testY, m.predict(testX))

if __name__ == "__main__":
  training_size = int(sys.argv[1])
  test_size = int(sys.argv[2])
  # Load training dataset
  raw_features = []
  labels = []
  for name in train_set_name:
    feat = pd.read_table("{}/{}/{}.feature"
    .format(data_path, name, name), sep=',', low_memory=False)
    label = pd.read_table("{}/{}/{}.label"
    .format(data_path, name, name), sep=',')
    raw_features.append(feat)
    labels.append(label)
    print("dataset {} loaded".format(name))

  # Transform training dataset
  features = []
  for name, feat in zip(train_set_name, raw_features):
    feat = feat.replace('?', 0)
    imp_mean = SimpleImputer(missing_values=0, strategy='mean')
    imp_mean.fit(feat)
    feat = imp_mean.transform(feat)
    features.append(feat)
    print("feature {} tranformed {}".format(name, feat.shape))
  del raw_features

  train_setX = np.vstack(features[0:4])
  train_setY = np.vstack(labels[0:4])
  print("trainset feature {} label {}"
  .format(train_setX.shape, train_setY.shape))
  test_setX = np.array(features[-1])
  test_setY = np.array(labels[-1])
  print("testset feature {} label {}"
  .format(test_setX.shape, test_setY.shape))

  # Load verify dataset
  verify_set = []
  for name in verify_set_name:
    feat = pd.read_table("{}/{}/{}.feature"
    .format(data_path, name, name), sep=',', low_memory=False)
    verify_set.append(feat)
    print("verify set {} loaded".format(name))

  # Transform verify dataset
  verify_features = []
  for name, feat in zip(verify_set_name, verify_set):
    feat = feat.replace('?', 0)
    imp_mean = SimpleImputer(missing_values=0, strategy='mean')
    imp_mean.fit(feat)
    feat = imp_mean.transform(feat)
    verify_features.append(feat)
    print("feature {} tranformed {}".format(name, feat.shape))

  # Train models
  models = []
  reports = []
  for name, c in classifiers:
    print(name)
    if name == "K临近":
      model, report = benchmark(c, train_setX[:training_size],
      train_setY[:training_size], test_setX[:test_size],
      test_setY[:test_size], -1)
    else:
      model, report = benchmark(c, train_setX[:training_size],
      train_setY[:training_size], test_setX[:test_size],
      test_setY[:test_size])
    reports.append(report)
    models.append(model)

  for cf, rep in zip(classifiers, reports):
    print(cf[0])
    print(rep)

  # dump results
  with gzip.open("model{}.pkl.gz".format(str(uuid.uuid4())), 'wb') as f:
    pickle.dump(models, f)
  with gzip.open("report{}.pkl.gz".format(str(uuid.uuid4())), 'wb') as f:
    pickle.dump(reports, f)
