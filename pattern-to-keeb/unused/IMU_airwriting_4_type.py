import serial
import time
import csv
from datetime import datetime
import fastdtw as fastdtw
from fastdtw import fastdtw
import keyboard 
#################################################################################   
import os
import pandas as pd
import numpy as np
#################################################################################   
# Configure serial port
port = 'COM7'
baud_rate = 9600
timeout = 0.25  # seconds
#################################################################################   
# Directory containing the CSV files
folder_path = r'C:\Users\username\Desktop\Project\python_code_motion_to_csv\HLG'

# Get a list of all CSV files in the folder
csv_files = [f for f in os.listdir(folder_path) if f.endswith('.csv')]

# Dictionary to store the numpy arrays
HLG_dict = {}

for csv_file in csv_files:
    # Create a variable name based on the file name (without extension)
    variable_name = os.path.splitext(csv_file)[0]
    
    # Read the CSV file into a pandas DataFrame
    df = pd.read_csv(os.path.join(folder_path, csv_file))
    
    # Convert the DataFrame to a numpy array
    numpy_array = df.to_numpy()
    
    # Store the numpy array in the dictionary with the variable name as the key
    HLG_dict[variable_name] = numpy_array 
#################################################################################    
# create an dictionary to store alignment values
def Test_FastDTW_0(sample,choosen_template_dict):
  alignment_dict = {}
  for template in choosen_template_dict:
    alignment_val = fastdtw(choosen_template_dict[template], sample)
    # save alignment value in dictionary with key = template
    alignment_dict[template] = alignment_val[0]
  # return the key with lowest alignment value
  closest_template = min(alignment_dict, key=alignment_dict.get)

  keyboard.write(closest_template[-1])
  return closest_template
#################################################################################   


def read_from_serial(port, baud_rate, timeout):
    ser = serial.Serial(port, baud_rate, timeout=timeout)
    ser.flush()
    return ser

def write_to_csv(data, filename='imu_data.csv'):
    with open(filename, mode='w', newline='') as file:
        writer = csv.writer(file)
        # Write the header
        writer.writerow(["AX", "AY", "AZ", "GX", "GY", "GZ"])
        # Write the data rows
        writer.writerows(data)

def main():
        ser = read_from_serial(port, baud_rate, timeout)
        data_buffer = []
        recording = False
        last_received_time = time.time()

        while True:
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8').rstrip()
                current_time = time.time()
                timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
                # Split the line into individual sensor readings
                sensor_values = line.split(',')
                if len(sensor_values) == 6:
                    data_buffer.append( sensor_values)
                last_received_time = current_time
                recording = True
                print(f"Data received: {line}")

            if recording and (time.time() - last_received_time) > 0.25:
                write_to_csv(data_buffer)
                Test_FastDTW_0(data_buffer,HLG_dict)
                print("Data written to CSV. Waiting for new data...")
                data_buffer = []
                recording = False

if __name__ == '__main__':
    main()
