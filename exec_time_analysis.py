import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sys


if len(sys.argv) < 2:
    print("Usage: python script.py <csv_filename>")
    sys.exit(1)

# Function to calculate jitter (standard deviation of differences between execution times)
def calculate_jitter(execution_times):
    return np.std(execution_times)

# Load the CSV file containing execution times
csv_filename = sys.argv[1]

# Load the CSV file
try:
    df = pd.read_csv(csv_filename)
except FileNotFoundError:
    print(f"Error: File '{csv_filename}' not found.")
    sys.exit(1)

# Assuming the CSV has a single column 'execution_time'
df.columns = ['execution_time']

# Calculate jitter
jitter = calculate_jitter(df['execution_time'])

# Calculate other statistics
mean_execution_time = df['execution_time'].mean()
min_execution_time = df['execution_time'].min()
max_execution_time = df['execution_time'].max()
variance_execution_time = df['execution_time'].var()

# Print out the statistics
print(f"Mean Execution Time: {mean_execution_time:.10f} seconds")
print(f"Min Execution Time: {min_execution_time:.10f} seconds")
print(f"Max Execution Time: {max_execution_time:.10f} seconds")
print(f"Variance: {variance_execution_time:.10f} seconds^2")
print(f"Jitter (Standard Deviation): {jitter:.10f} seconds")

# Plot the execution times
plt.figure(figsize=(10,6))
plt.plot(df['execution_time'], label='Execution Times')
plt.title('Execution Times of Each Iteration')
plt.xlabel('Iteration')
plt.ylabel('Execution Time (seconds)')
plt.legend()
plt.show()
