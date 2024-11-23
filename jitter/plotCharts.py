import re
import pandas as pd
import matplotlib.pyplot as plt
from concurrent.futures import ProcessPoolExecutor

# Function to parse the text file
def parse_timer_file(file_path):
    # Regex pattern to match lines like "Timer 2: elapsed = 12345 us"
    pattern = r"Timer (\d+): elapsed = (\d+)l us"
    
    # Dictionary to store the parsed data
    data = {"Timer": [], "Elapsed Time (us)": []}
    
    with open(file_path, 'r') as file:
        for line in file:
            match = re.match(pattern, line)
            if match:
                timer_number = int(match.group(1))
                elapsed_time = int(match.group(2))
                data["Timer"].append(timer_number)
                data["Elapsed Time (us)"].append(elapsed_time)
    
    return pd.DataFrame(data)

# Function to create separate bar charts for each timer
def plot_bar_chart(timer, dataframe):
    """Function to create and save a plot for a specific timer."""
    timer_data = dataframe[dataframe['Timer'] == timer]
    
    plt.figure(figsize=(10, 6))
    plt.bar(timer_data.index, timer_data['Elapsed Time (us)'], color='skyblue')
    plt.xlabel("Index")
    plt.ylabel("Elapsed Time (us)")
    plt.title(f"Bar Chart for Timer {timer}")
    output_file = f"bar_chart_timer_{timer}.png"
    plt.savefig(output_file)
    plt.close()
    return f"Bar chart for Timer {timer} saved to {output_file}"

def create_histogram(timer, dataframe):
    """Function to create and save a histogram for a specific timer."""
    timer_data = dataframe[dataframe['Timer'] == timer]
    
    plt.figure(figsize=(10, 6))
    plt.hist(timer_data['Elapsed Time (us)'], bins=50, alpha=0.7, color='blue', edgecolor='black')
    plt.xlabel("Elapsed Time (us)")
    plt.ylabel("Frequency")
    plt.title(f"Histogram for Timer {timer}")
    output_file = f"histogram_timer_{timer}.png"
    plt.savefig(output_file)
    plt.close()
    return f"Histogram for Timer {timer} saved to {output_file}"

# Path to the input text file
file_path = "output.log"  # Replace with your file path

# Parse the file and create a dataframe
df = parse_timer_file(file_path)

# Plot separate bar charts
#print("Creating separate bar charts for each timer...")
#plot_separate_bar_charts(df)

# Plot separate histograms
# print("Creating separate histograms for each timer...")
# plot_separate_histograms(df)

unique_timers = df['Timer'].unique()

# Use ProcessPoolExecutor for parallel processing
with ProcessPoolExecutor() as executor:
    results = executor.map(create_histogram, unique_timers, [df] * len(unique_timers))

# Print results
for result in results:
    print(result)


# Use ProcessPoolExecutor for parallel processing
with ProcessPoolExecutor() as executor:
    results = executor.map(plot_bar_chart, unique_timers, [df] * len(unique_timers))

# Print results
for result in results:
    print(result)
