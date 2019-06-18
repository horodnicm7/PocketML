import numpy as np
from sklearn.linear_model import LogisticRegression

data_x = np.array([1, 2, 3, 5, 6, 7, 8, 10, 11, 14, 15, 16, 17])
data_y = np.array([0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1])
test_x = np.array([4, 9, 12, 13, 20])

data_x = data_x.reshape(-1, 1)
data_y = data_y.reshape(-1, 1)
test_x = test_x.reshape(-1, 1)

LogReg = LogisticRegression()
LogReg.fit(data_x, data_y.ravel())
y_pred = LogReg.predict(test_x)

print(LogReg.coef_)
print(LogReg.intercept_)
print(y_pred)