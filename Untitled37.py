
# coding: utf-8

# In[1]:


import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


# In[4]:


df=pd.read_csv("G:\\downloads\\covid-19-26.csv")
df.head()


# In[6]:


df.isnull().sum()


# In[21]:


from IPython.core.interactiveshell import InteractiveShell
InteractiveShell.ast_node_interactivity = "all"
X=df.iloc[:,3:7]
y=df["Health_Status"]
X.head()
y.head()


# In[22]:


from sklearn.model_selection import train_test_split ##Splitting train and test, fitting the model

from sklearn.ensemble import RandomForestClassifier
dcf= RandomForestClassifier()
from IPython.core.interactiveshell import InteractiveShell
InteractiveShell.ast_node_interactivity = "all"


# In[23]:


X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.2, random_state = 0)
X_train.shape

y_train.shape

X_test.shape

y_test.shape


# In[24]:


dcf.fit(X_train,y_train)
y_predict = dcf.predict(X_test)


# In[25]:


from sklearn.metrics import confusion_matrix,accuracy_score  #Accuracy Check
accuracy_score(y_test,y_predict)

