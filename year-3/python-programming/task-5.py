import pandas as pd
import matplotlib.pyplot as plt

parquet_file = 'yellow_tripdata_2023-01.parquet'

data = pd.read_parquet(parquet_file)

data['tpep_pickup_datetime'] = pd.to_datetime(data['tpep_pickup_datetime'])

data['pickup_hour'] = data['tpep_pickup_datetime'].dt.hour

payment_type_map = {
    0: 'Unknown',
    1: 'Credit Card',
    2: 'Cash',
    3: 'No Charge',
    4: 'Dispute',
    5: 'Unknown',
    6: 'Voided Trip'
}

data['payment_type'] = data['payment_type'].replace(payment_type_map)

hourly_payment_type_counts = data.groupby(
    ['pickup_hour', 'payment_type']).size().reset_index(name='count')

hourly_total_counts = hourly_payment_type_counts.groupby(
    'pickup_hour')['count'].sum().reset_index(name='total_count')

hourly_payment_type_counts = hourly_payment_type_counts.merge(
    hourly_total_counts, on='pickup_hour')
hourly_payment_type_counts['percentage'] = (
    hourly_payment_type_counts['count'] / hourly_payment_type_counts['total_count']) * 100

pivot_data = hourly_payment_type_counts.pivot_table(
    values='percentage', index='pickup_hour', columns='payment_type', fill_value=0)

ax = pivot_data.plot(kind='bar', stacked=True,
                     figsize=(15, 7), colormap='viridis')
plt.title('Hourly Percentage Distribution of Payment Types')
plt.xlabel('Hour of Day')
plt.ylabel('Percentage of Transactions')
plt.legend(title='Payment Type', loc='upper right')
plt.show()
