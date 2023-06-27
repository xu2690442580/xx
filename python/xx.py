import pandas as pd

# Sample data
data = {
    'id': [1, 2, 3, 4, 5],
    'orderTime': ['2020-01-01', '2020-02-15', '2020-03-10', '2020-04-20', '2020-12-31'],
    'payTime': ['2020-01-02', '2020-02-16', '2020-03-11', '2020-04-21', '2021-01-01'],
    'orderAmount': [100, 200, 150, 300, 250],
    'payment': [90, 180, 140, 270, 220],
    'orderID': ['OD001', 'OD002', 'OD003', 'OD004', 'OD005'],
    'goodsID': ['PR001', 'PR002', 'PR003', 'PR004', 'PR005'],
    'chanelID': ['CH001', 'CH002', 'CH003', 'CH004', 'CH005'],
    'platformType': ['Platform A', 'Platform B', 'Platform A', 'Platform C', 'Platform B'],
    'chargeback': ['No', 'No', 'Yes', 'No', 'Yes'],
    'userID': ['User001', 'User002', 'User003', 'User004', 'User005']
}

# Create DataFrame
df = pd.DataFrame(data)

# Save DataFrame to Excel file
df.to_excel('order2020.xlsx', index=False)
import pandas as pd
import datetime

# Read the data file
df = pd.read_excel('order2020.xlsx', index_col='id')

# Convert 'orderTime' column to datetime type
df['orderTime'] = pd.to_datetime(df['orderTime'])

# Define the start and end time points
startTime = datetime.datetime(2020, 1, 1)
endTime = datetime.datetime(2020, 12, 31, 23, 59, 59)

# Remove data before the start time point
df = df[df['orderTime'] >= startTime]

# Remove data after the end time point
df = df[df['orderTime'] <= endTime]

# Continue with the rest of the code...