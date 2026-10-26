import os
import pandas as pd
import matplotlib.pyplot as plt

# Path to your YOLO results.csv file
file_path = 'D:/whateveraboutit/Photo_Masher_Preprocessing/csv_files/results (2).csv'

# --- SET YOUR SPECIFIC SAVE ADDRESS HERE ---
# Examples:
# Windows: output_dir = r"C:\Users\YourName\Documents\YOLO_Plots"
# Mac/Linux: output_dir = "/home/username/Documents/YOLO_Plots"
output_dir = "D:/whateveraboutit/Photo_Masher_Preprocessing/output"

# Automatically create the folder (and any parent folders) if they don't exist
os.makedirs(output_dir, exist_ok=True)

# Read the CSV and strip spaces from headers
df = pd.read_csv(file_path)
df.columns = df.columns.str.strip()

epochs = df['epoch']

# Define the metrics you want to plot separately
metrics = {
    'precision': {'col': 'metrics/precision(B)', 'label': 'Precision', 'color': 'blue'},
    'recall': {'col': 'metrics/recall(B)', 'label': 'Recall', 'color': 'orange'},
    'map50': {'col': 'metrics/mAP50(B)', 'label': 'mAP50', 'color': 'green'},
    'map50_95': {'col': 'metrics/mAP50-95(B)', 'label': 'mAP50-95', 'color': 'red'}
}

# Loop through each metric, create a plot, and save it to the specific address
for key, info in metrics.items():
    plt.figure(figsize=(8, 5))
    
    plt.plot(epochs, df[info['col']], label=info['label'], color=info['color'], linewidth=1.5)
    
    plt.title(f'YOLO Training Performance - {info["label"]}', fontsize=14, fontweight='bold')
    plt.xlabel('Epoch', fontsize=12)
    plt.ylabel(info['label'], fontsize=12)
    plt.grid(True, linestyle='--', alpha=0.6)
    plt.legend(fontsize=11)
    
    # Combine the custom directory with the filename
    filename = os.path.join(output_dir, f'yolo_{key}.png')
    
    plt.savefig(filename, dpi=300, bbox_inches='tight')
    print(f"Saved to: {filename}")
    
    plt.close()

os.makedirs(output_dir, exist_ok=True)

# Read CSV and clean column headers
df = pd.read_csv(file_path)
df.columns = df.columns.str.strip()

epochs = df['epoch']

# Create a 2x2 grid layout for a combined dashboard view
fig, axes = plt.subplots(2, 2, figsize=(14, 10))

# 1. Precision Plot
axes[0, 0].plot(epochs, df['metrics/precision(B)'], color='blue', linewidth=1.5)
axes[0, 0].set_title('Precision over Epochs', fontsize=12, fontweight='bold')
axes[0, 0].set_xlabel('Epoch')
axes[0, 0].set_ylabel('Precision')
axes[0, 0].grid(True, linestyle='--', alpha=0.6)

# 2. Recall Plot
axes[0, 1].plot(epochs, df['metrics/recall(B)'], color='orange', linewidth=1.5)
axes[0, 1].set_title('Recall over Epochs', fontsize=12, fontweight='bold')
axes[0, 1].set_xlabel('Epoch')
axes[0, 1].set_ylabel('Recall')
axes[0, 1].grid(True, linestyle='--', alpha=0.6)

# 3. mAP50 Plot
axes[1, 0].plot(epochs, df['metrics/mAP50(B)'], color='green', linewidth=1.5)
axes[1, 0].set_title('mAP50 over Epochs', fontsize=12, fontweight='bold')
axes[1, 0].set_xlabel('Epoch')
axes[1, 0].set_ylabel('mAP50')
axes[1, 0].grid(True, linestyle='--', alpha=0.6)

# 4. mAP50-95 Plot
axes[1, 1].plot(epochs, df['metrics/mAP50-95(B)'], color='red', linewidth=1.5)
axes[1, 1].set_title('mAP50-95 over Epochs', fontsize=12, fontweight='bold')
axes[1, 1].set_xlabel('Epoch')
axes[1, 1].set_ylabel('mAP50-95')
axes[1, 1].grid(True, linestyle='--', alpha=0.6)

# Adjust spacing and save the combined figure
plt.tight_layout()
save_path = os.path.join(output_dir, 'yolo_training_dashboard.png')
plt.savefig(save_path, dpi=300, bbox_inches='tight')
print(f"Combined dashboard saved to: {save_path}")

# ==========================================
# 1. Precision & Recall over Epochs
# ==========================================
plt.figure(figsize=(10, 5))
plt.plot(epochs, df['metrics/precision(B)'], label='Precision', color='blue', linewidth=1.5)
plt.plot(epochs, df['metrics/recall(B)'], label='Recall', color='orange', linewidth=1.5)
plt.title('Precision and Recall over Epochs', fontsize=14, fontweight='bold')
plt.xlabel('Epoch', fontsize=12)
plt.ylabel('Metric Value', fontsize=12)
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend(fontsize=11)

path1 = os.path.join(output_dir, 'precision_and_recall_epochs.png')
plt.savefig(path1, dpi=300, bbox_inches='tight')
plt.close()

# ==========================================
# 2. mAP Metrics over Epochs
# ==========================================
plt.figure(figsize=(10, 5))
plt.plot(epochs, df['metrics/mAP50(B)'], label='mAP50', color='green', linewidth=1.5)
plt.plot(epochs, df['metrics/mAP50-95(B)'], label='mAP50-95', color='red', linewidth=1.5)
plt.title('mAP Performance over Epochs', fontsize=14, fontweight='bold')
plt.xlabel('Epoch', fontsize=12)
plt.ylabel('mAP Value', fontsize=12)
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend(fontsize=11)

path2 = os.path.join(output_dir, 'map_metrics_epochs.png')
plt.savefig(path2, dpi=300, bbox_inches='tight')
plt.close()

# ==========================================
# 3. Training vs Validation Box Loss
# ==========================================
plt.figure(figsize=(10, 5))
plt.plot(epochs, df['train/box_loss'], label='Train Box Loss', color='purple', linewidth=1.5)
plt.plot(epochs, df['val/box_loss'], label='Validation Box Loss', color='brown', linewidth=1.5)
plt.title('Box Loss over Epochs', fontsize=14, fontweight='bold')
plt.xlabel('Epoch', fontsize=12)
plt.ylabel('Loss', fontsize=12)
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend(fontsize=11)

path3 = os.path.join(output_dir, 'box_loss_epochs.png')
plt.savefig(path3, dpi=300, bbox_inches='tight')
plt.close()

print(f"All available graphs successfully saved to: {output_dir}")

plt.show()