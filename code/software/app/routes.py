from flask import render_template, request, jsonify, redirect
from flask.helpers import url_for
from app import app
import pytz
from datetime import datetime
from app import connectAWS as dynamodb_aws_handler

# https://medium.com/featurepreneur/crud-operations-on-dynamodb-with-flask-apis-916f6cae992

room_idx = 0 # global static room index
maxNumOfRoomsInDB = 0 # declare and initialize to filler value, 0

def parseLatestRoomData(itemsDB):
    roomToLatestOccupancy = {}
    roomToLatestBattery = {}
    # print(itemsDB)
    for item in itemsDB:
        roomToLatestOccupancy[item['device_data']['location']] = item['device_data']['occupancy']
        roomToLatestBattery[item['device_data']['location']] = item['device_data']['battery']

    print(len(roomToLatestOccupancy))
    return roomToLatestOccupancy, roomToLatestBattery

@app.route("/")
def home_page():
    items = dynamodb_aws_handler.Occupancy_table.scan()['Items']
    items = sorted(items, key=lambda x: int(x['sample_time']))
    print(items[len(items) - 1])
    # print(items)
    print(len(items))
    file1 = open("output.txt", "w") 
    # for c in items:
    file1.write(str(items))
    file1.close()
  
    # items.reverse()
    # print((items))
    room_idx = 0
    
    d = datetime.now()
    dt = pytz.timezone('America/Chicago').localize(d)
    d = d.strftime('%B %d, %Y ; %I:%M:%S %p')

    roomsToLatestOccupancy, roomsToLatestBattery = parseLatestRoomData(items)

    global maxNumOfRoomsInDB 
    # maxNumOfRoomsInDB = len(items) # deprecated-no longer the case. Instead...
    maxNumOfRoomsInDB = len(roomsToLatestBattery) # len of roomsToLatestData dictionary
    
    not_full_count = 37 # has to be changed!
    location = items[room_idx]['device_data']['location'] # initial location
    # battery = roomsToLatestBattery[location]
    # full_count = int(roomsToLatestOccupancy[location])
    battery = items[len(items) - 1]['device_data']['battery']
    full_count = items[len(items) - 1]['device_data']['occupancy']
    siebel4022_data = {'Task' : 'Hours per Day', 'Not Full' : not_full_count, 'Full' : full_count} 
    device_id = items[room_idx]['device_id']

    return render_template("pie_siebel.html",data=siebel4022_data, full_count=full_count, now_time=d, battery=battery, device_id=device_id,
    location = location)
    # return jsonify(connectAWS.get_items())

@app.route("/update")
def update_home_page():
    items = dynamodb_aws_handler.Occupancy_table.scan()['Items']
    sorted(items, key=lambda x: int(x['sample_time']))
    items.reverse()
    
    roomsToLatestOccupancy, roomsToLatestBattery = parseLatestRoomData(items)
    # maxNumOfRoomsInDB = len(items) # deprecated-no longer the case. Instead...
    maxNumOfRoomsInDB = len(roomsToLatestBattery) # len of roomsToLatestData dictionary
    # print("max # of rooms", maxNumOfRoomsInDB)
    
    global room_idx
    room_idx = (room_idx + 1) % maxNumOfRoomsInDB
    # print("room idx", room_idx)

    not_full_count = 37 # has to be changed!
    d = datetime.now()
    dt = pytz.timezone('America/Chicago').localize(d)
    d = d.strftime('%B %d, %Y ; %I:%M:%S %p')

    not_full_count = 37 # has to be changed!

    location_key_list = list(roomsToLatestBattery.keys())
    nextLocationKey = location_key_list[room_idx]
    print(location_key_list)
    location = nextLocationKey

    battery = roomsToLatestBattery[location]
    full_count = int(roomsToLatestOccupancy[location])
    siebel4022_data = {'Task' : 'Hours per Day', 'Not Full' : not_full_count, 'Full' : full_count} 
    device_id = items[room_idx]['device_id']

    return render_template("pie_siebel.html",data=siebel4022_data, full_count=full_count, now_time=d, battery=battery, device_id=device_id,
    location = location)

class DB:
    def retrieve_value(sensor, metric=None):
        return DB.retrieve_values(sensor, metric)[0]
