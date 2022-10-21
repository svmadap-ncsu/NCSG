import boto3

client = boto3.client('groundstation')

list_satellite = client.list_satellites(
    maxResults=10,
    nextToken='string'
)
for x in list_satellite:
    print(list_satellite[x])



# list_ground = client.list_ground_stations(
#     maxResults=10,
#     nextToken='string',
#     satelliteId='string'
# )

# print(list_ground)