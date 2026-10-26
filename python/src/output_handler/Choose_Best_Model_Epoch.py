import pandas as pd

# Path to your CSV file
file_path = 'c:/Users/Uokbr/Downloads/results (2).csv'

column1 = 'metrics/precision(B)'
column2 = 'metrics/recall(B)'
column3 = 'metrics/mAP50-95(B)'

# Specify the columns you want to read
target_columns = [column1, column2, column3]

# Read the CSV
df = pd.read_csv(file_path, usecols=target_columns)

# Convert columns to float
df[column1] = df[column1].astype(float)
df[column2] = df[column2].astype(float)
df[column3] = df[column3].astype(float)

# Print max and min for each column properly using the variable names
print(f"Precision - Max: {df[column1].max()}, Min: {df[column1].min()}")
print(f"Recall    - Max: {df[column2].max()}, Min: {df[column2].min()}")
print(f"mAP50-95  - Max: {df[column3].max()}, Min: {df[column3].min()}\n")

# Initialize tracking variables for your custom score calculation
best_score = 0
best_epoch = 0

current_P = 0
current_R = 0
current_mAP = 0

# Iterate through each row using zip for clean and fast access
for i, (v1, v2, v3) in enumerate(zip(df[column1], df[column2], df[column3])):
    # Calculate your custom weighted score
    current_score = (v1 * 35) + (v2 * 45) + (v3 * 20)
    
    if current_score > best_score:
        current_P = v1
        current_R = v2
        current_mAP = v3

        best_score = current_score
        best_epoch = i + 1  # i starts at 0, so epoch starts at 1

print(f"Best Combined Score: {best_score}\n")
print(f"Precision: {current_P}")
print(f"Recall: {current_R}")
print(f"mAP: {current_mAP}")
print(f"Best Epoch: {best_epoch}")