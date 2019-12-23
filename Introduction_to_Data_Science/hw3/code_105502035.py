from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import sys

import math
import matplotlib.pyplot as plt
import numpy
import pandas
import sklearn.metrics
from sklearn import metrics
import sklearn.model_selection
import sklearn.linear_model
import sklearn.preprocessing


def load_train_test_data(train_ratio=.5):
    data = pandas.read_csv('./HTRU_2.csv', header=None, names=['x%i' % (i) for i in range(8)] + ['y'])
    X = numpy.asarray(data[['x%i' % (i) for i in range(8)]])
    X = numpy.hstack((numpy.ones((X.shape[0],1)), X))
    y = numpy.asarray(data['y'])

    return sklearn.model_selection.train_test_split(X, y, test_size = 1 - train_ratio, random_state=0)


def scale_features(X_train, X_test, low=0, upp=1):
    minmax_scaler = sklearn.preprocessing.MinMaxScaler(feature_range=(low, upp)).fit(numpy.vstack((X_train, X_test)))
    X_train_scale = minmax_scaler.transform(X_train)
    X_test_scale = minmax_scaler.transform(X_test)
    return X_train_scale, X_test_scale


def cross_entropy(y, y_hat):
    loss = 0
    for i in range(len(y)):
        loss += -(y[i]*math.log(y_hat[i]) + (1-y[i])*math.log(1-y_hat[i]))
    return loss


def logreg_sgd(X, y, alpha = .0001, iters = 50, eps=1e-4, lmbda=1): #alpha stand for Learning rate
    # X is numpy.ndarray
    n, d = X.shape    
    # random initialize theta value
    theta = numpy.zeros((d, 1))
    #gradient descent loop iters times, study scale = alpha, threshold = eps
    for i in range(iters):
        # calculate new theta, theta = theta - alpha * sum
        tmp = numpy.zeros((d, 1))
        for j in range(len(X)):
            tmp += (predict_prob(X[j], theta) - y[j]) * numpy.array([X[j]]).T
        theta = theta - (alpha * tmp)
        
    return theta
def untraining(X, y):
    # X is numpy.ndarray
    n, d = X.shape    
    # random initialize theta value
    theta = numpy.zeros((d, 1))
    
    return theta

def predict_prob(X, theta):
    return 1./(1+numpy.exp(-numpy.dot(X, theta)))


def plot_roc_curve(y_train,y_test, y_prob, y_prob_,y_prob__):
    # TODO: compute tpr and fpr of different thresholds
    #TPR=(TP/(TP+FP))
    #FPR =(FP/(FP+TN))
    tr = []
    fr = []
    t = []
    f = []
    T = [] 
    F = []
    tpr = [] 
    fpr = []
    F, T, thresholds = metrics.roc_curve(y_test, y_prob_)
    f, t, thresholds = metrics.roc_curve(y_test, y_prob__)
    fpr, tpr, thresholds = metrics.roc_curve(y_test, y_prob)
    fr, tr, thresholds = metrics.roc_curve(y_train, y_prob)
    plt.plot(f, t, label='training data before training')
    plt.plot(F, T, label='test data before training')
    plt.plot(fpr, tpr, label='test data after training')
    plt.plot(fr, tr, label='training data after training')
    plt.title('ROC curve')
    plt.xlabel("FPR")
    plt.ylabel("TPR")
    plt.xlim(0,1)
    plt.ylim(0,1)
    plt.gca().set_aspect('equal', adjustable='box')
    plt.legend(loc='best')
    plt.savefig("roc_curve.png")


def main(argv):
    X_train, X_test, y_train, y_test = load_train_test_data(train_ratio=.5)
    X_train_scale, X_test_scale = scale_features(X_train, X_test, 0, 1)
    
    theta = logreg_sgd(X_train_scale, y_train)
    t = untraining(X_train_scale, y_train)
    y_prob = predict_prob(X_train_scale, theta)
    y_prob_ = predict_prob(X_train_scale, t)
    print("Logreg train accuracy: %f" % (sklearn.metrics.accuracy_score(y_train, y_prob > .5)))
    print("Logreg train precision: %f" % (sklearn.metrics.precision_score(y_train, y_prob > .5)))
    print("Logreg train recall: %f" % (sklearn.metrics.recall_score(y_train, y_prob > .5)))
    
    y_prob = predict_prob(X_test_scale, theta)
    y_prob__ = predict_prob(X_test_scale, t)
    print("Logreg test accuracy: %f" % (sklearn.metrics.accuracy_score(y_test, y_prob > .5)))
    print("Logreg test precision: %f" % (sklearn.metrics.precision_score(y_test, y_prob > .5)))
    print("Logreg test recall: %f" % (sklearn.metrics.recall_score(y_test, y_prob > .5)))
    plot_roc_curve(y_train.flatten(), y_test.flatten(), y_prob.flatten(), y_prob_.flatten(), y_prob__.flatten())


if __name__ == "__main__":
    main(sys.argv)


