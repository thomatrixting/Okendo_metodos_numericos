import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

def scatter_plot(x1, y1, x2, y2, title=None, xlabel=None, ylabel=None, label1='Category 1', label2='Category 2'):
    """
    Creates a scatter plot with two categories.
    
    Parameters:
        x1, y1 (list): Data points for category 1.
        x2, y2 (list): Data points for category 2.
        title (str, optional): Title of the plot.
        xlabel (str, optional): Label for the x-axis.
        ylabel (str, optional): Label for the y-axis.
        label1 (str, optional): Label for category 1.
        label2 (str, optional): Label for category 2.
    """
    plt.figure(figsize=(8, 6))
    plt.scatter(x1, y1, color='blue', label=label1, edgecolor='black')
    plt.scatter(x2, y2, color='red', label=label2, edgecolor='black')
    
    if title:
        plt.title(title, fontsize=14)
    if xlabel:
        plt.xlabel(xlabel, fontsize=12)
    if ylabel:
        plt.ylabel(ylabel, fontsize=12)
    
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.legend()
    plt.show()

def histogram_plot(x1, x2, title=None, xlabel=None, label1='Category 1', label2='Category 2'):
    """
    Creates a histogram with two categories.
    
    Parameters:
        x1 (list): Data points for category 1.
        x2 (list): Data points for category 2.
        title (str, optional): Title of the plot.
        xlabel (str, optional): Label for the x-axis.
        label1 (str, optional): Label for category 1.
        label2 (str, optional): Label for category 2.
    """
    plt.figure(figsize=(8, 6))
    sns.histplot(x1, color='blue', label=label1, kde=True, bins=20, alpha=0.6)
    sns.histplot(x2, color='red', label=label2, kde=True, bins=20, alpha=0.6)
    
    if title:
        plt.title(title, fontsize=14)
    if xlabel:
        plt.xlabel(xlabel, fontsize=12)
    
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.legend()
    plt.show()

# Example Usage
data_category_1 = {
    'X_values': [1, 3, 5, 7, 9],
    'Y_values': [2, 5, 11, 17, 23]
}
data_category_2 = {
    'X_values': [2, 4, 6, 8, 10],
    'Y_values': [3, 7, 13, 19, 29]
}

# Create a scatter plot
scatter_plot(
    x1=data_category_1['X_values'], y1=data_category_1['Y_values'],
    x2=data_category_2['X_values'], y2=data_category_2['Y_values'],
    title='Scatter Plot Example', xlabel='X Axis', ylabel='Y Axis'
)

# Create a histogram
histogram_plot(
    x1=data_category_1['X_values'], x2=data_category_2['X_values'],
    title='Histogram Example', xlabel='X Axis'
)

