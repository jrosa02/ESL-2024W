import pandas as pd
import re
import matplotlib.pyplot as plt
import numpy as np
import os

def read_log_to_df(file_path):
    """
    Reads a log file with the format `C: <clock_number>, S: <sample_number>, D: <delta>`
    and returns a pandas DataFrame.

    Args:
        file_path (str): The path to the log file to be read.

    Returns:
        pd.DataFrame: DataFrame containing columns 'Clock', 'Sample', and 'Delta'.
    """
    # Regular expression to match lines like: C: 0, S: 623, D: 18589
    log_pattern = re.compile(r"C: (\d+), S: (\d+), D: (\d+)")

    # List to store the parsed data
    data = []

    # Read the log file
    with open(file_path, 'r') as f:
        for line in f:
            match = log_pattern.match(line.strip())  # Strip whitespace and match the pattern
            if match:
                clock_num, sample_num, delta = match.groups()
                data.append({
                    'Clock': int(clock_num),
                    'Sample': int(sample_num),
                    'Delta': int(delta)
                })

    # Convert the list of dictionaries into a pandas DataFrame
    df = pd.DataFrame(data)

    return df

def plot_df(df, bins=10, output_dir='plots'):
    """
    Plots a histogram for each 'Clock' in the DataFrame, showing the distribution of 'Delta'.
    Saves each plot as an individual file in the specified output directory.

    Args:
        df (pd.DataFrame): The DataFrame containing the data to plot.
        bins (int): The number of bins to use for the histogram (default is 50).
        output_dir (str): The directory where the plots will be saved (default is 'plots').
    """
    # Create output directory if it does not exist
    import os
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    # Get unique clock values
    clocks = df['Clock'].unique()

    # Plot for each clock separately
    for clock in clocks:
        # Filter the DataFrame for the current clock
        clock_data = df[df['Clock'] == clock]
        
        # Create a new figure for each clock
        plt.figure(figsize=(10, 6))

        # Plot Delta as a histogram
        plt.hist(clock_data['Delta'], bins=bins, color='b', edgecolor='black')

        # Set the title, labels, and limits for the axes
        plt.title(f'Clock {clock}')
        plt.xlabel('Delta')
        plt.ylabel('Frequency')

        # Set the limits for the axes based on the min and max of Delta values
        delta_min = clock_data['Delta'].min()
        delta_max = clock_data['Delta'].max()
        plt.xlim(delta_min, delta_max)

        # Optionally set the y-axis limit to ensure it shows all frequency counts
        delta_freq_max = clock_data['Delta'].value_counts().max()
        plt.ylim(0, delta_freq_max)

        # Save the plot as a file
        plot_filename = f'{output_dir}/clock_{clock}_histogram.png'
        plt.savefig(plot_filename)

        # Close the plot to free memory
        plt.close()

def plot_cumulative_probability(df, output_dir='cumulative_plots'):
    """
    Plots a cumulative probability curve for each 'Clock' in the DataFrame.
    Saves each plot as an individual file in the specified output directory.

    Args:
        df (pd.DataFrame): The DataFrame containing the data to plot.
        output_dir (str): The directory where the plots will be saved (default is 'cumulative_plots').
    """
    # Create output directory if it does not exist
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    # Get unique clock values
    clocks = df['Clock'].unique()

    # Plot for each clock separately
    for clock in clocks:
        # Filter the DataFrame for the current clock
        clock_data = df[df['Clock'] == clock]['Delta']

        # Sort the Delta values for cumulative probability calculation
        sorted_deltas = np.sort(clock_data)
        cumulative_prob = np.linspace(0, 1, len(sorted_deltas))

        # Create a new figure for each clock
        plt.figure(figsize=(10, 6))

        # Plot the cumulative probability curve
        plt.plot(sorted_deltas, cumulative_prob, marker='.', linestyle='-', color='b')

        # Set the title and labels
        plt.title(f'Cumulative Probability for Clock {clock}')
        plt.xlabel('Delta')
        plt.ylabel('Cumulative Probability')

        # Save the plot as a file
        plot_filename = f'{output_dir}/clock_{clock}_cumulative.png'
        plt.savefig(plot_filename)

        # Close the plot to free memory
        plt.close()


if __name__ == "__main__":
    # Set the log file path
    file_path = 'output.log'  # Replace with your actual file path

    # Read the log file into a DataFrame
    df = read_log_to_df(file_path)

    # Display the DataFrame
    plot_df(df)
    plot_cumulative_probability(df)

    # Optionally, save it to a CSV file
    df.to_csv('output.csv', index=False)
