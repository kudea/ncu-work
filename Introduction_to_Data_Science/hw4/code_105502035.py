import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


def mf_sgd(R, K=64, alpha=1e-4, beta=1e-2, iterations=50):
    """
    :param R: user-item rating matrix
    :param K: number of latent dimensions
    :param alpha: learning rate
    :param beta: regularization parameter
    """
    num_users, num_items = R.shape

    # Initialize user and item latent feature matrice
    P = np.random.normal(scale=1. / K, size=(num_users, K))
    Q = np.random.normal(scale=1. / K, size=(num_items, K))

    # Initialize the biases
    b_u = np.zeros(num_users)
    b_i = np.zeros(num_items)
    b = np.mean(R[np.where(R != 0)])

    # Create a list of training samples
    samples = [
        (i, j, R[i, j])
        for i in range(num_users)
        for j in range(num_items)
        if R[i, j] > 0
    ]

    # Perform stochastic gradient descent for number of iterations
    training_loss = []
    for iters in range(iterations):
        np.random.shuffle(samples)
        for i, j, r in samples:
            '''
            rheadij = u(mean) + bi + cj + piqj 
            dij = rhead - rheadij
            
            del bi = -dij + lambda bi ----user
            del cj = -dij + lambda cj ----item
            del pi = -dijqj + lambda pi ----P
            del qj = -dijpi + lambda qj ----Q
            
            theta^(k+1) = theta^(k) - eta del theta^(k)
            
            param beta: regularization parameter ---> lambda
            
            '''
            rheadij = b + b_u[i] + b_i[j] + np.dot(P[i],Q[j]) 
            dij = r - rheadij
            
            del_b_u = -dij + beta * b_u[i]
            del_b_i = -dij + beta * b_i[i]
            del_p_i = -dij * Q[j] + beta * P[i]
            del_q_j = -dij * P[i] + beta * Q[j]
            
            b_u[i] = b_u[i] - alpha * del_b_u   
            b_i[j] = b_i[j] - alpha * del_b_i
            P[i] = P[i] - alpha * del_p_i
            Q[j] = Q[j] - alpha * del_q_j    
            
            
            """
            TODO: 
            In this for-loop scope, 
            you need to (1)update "b_u"(vector of rating bias for users) and "b_i"(vector of rating bias for items)
            and (2)update user and item latent feature matrices "P", "Q"
            """

        # Using RMSE to compute training_loss
        xs, ys = R.nonzero()
        pred = b + b_u[:, np.newaxis] + b_i[np.newaxis:, ] + P.dot(Q.T)
        error = 0
        for x, y in zip(xs, ys):
            error += pow(R[x, y] - pred[x, y], 2)
        rmse = np.sqrt(error / len(xs))
        training_loss.append((iters, rmse))
        if (iters + 1) % 10 == 0:
            print("Iteration: %d ; error = %.4f" % (iters + 1, rmse))

    return pred, b, b_u, b_i, training_loss


def plot_training_loss(training_loss):
    x = [x for x, y in training_loss]
    y = [y for x, y in training_loss]
    plt.figure(figsize=(16, 4))
    plt.plot(x, y)
    plt.xticks(x, x)
    plt.xlabel("Iterations")
    plt.ylabel("Root Mean Square Error")
    plt.grid(axis="y")
    plt.savefig("training_loss.png")
    plt.show()


if __name__ == "__main__":
    data = pd.read_csv('ratings.csv')
    table = pd.pivot_table(data, values='rating', index='userId', columns='movieId', fill_value=0)
    R = table.values
    pred, b, b_u, b_i, loss = mf_sgd(R)
    
    print("P x Q:")
    print(pred)
    print("Global bias:")
    print(b)
    print("User bias:")
    print(b_u)
    print("Item bias:")
    print(b_i)
    plot_training_loss(loss)
    