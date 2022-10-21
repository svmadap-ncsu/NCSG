import requests
import json
import time
import schedule

# this function uses requests, allows user to type in a satellite id and then returns json value

def satellite_data(data_id):
    satellite = requests.get(
        f"https://api.spacexdata.com/v4/starlink/{str(data_id)}")
    store = satellite.json()
    wanted_values = ["CREATION_DATE", "OBJECT_NAME", "OBJECT_ID", "LAUNCH_DATE"]
    new_dict = dict(
        (x,y)
        for x,y in store['spaceTrack'].items() if x in wanted_values
    )
    store['spaceTrack'] = new_dict

    timestr = time.strftime("%a %B %d %Y-%H %M %S") # Day Month Day Year Hour Min Sec
    new = open('data/' + timestr + '.json', 'w')

    json.dump(store, new, indent= 1)
    new.close()



# main
schedule.every(2).minutes.do(satellite_data, '628ea116a8973c1694df189b')

while True:
    schedule.run_pending()
    time.sleep(1)