from flask import render_template, request, jsonify, redirect
from flask.helpers import url_for
from app import app
import pytz
from datetime import datetime
from app import connectAWS as dynamodb_aws_handler

# https://medium.com/featurepreneur/crud-operations-on-dynamodb-with-flask-apis-916f6cae992

room_idx = 1 # global static room index
items = dynamodb_aws_handler.Occupancy_table.scan()['Items'] # declare and initialize here just to set the global value maxNumOfRoomsInDB
maxNumOfRoomsInDB = len(items)
def parseLatestRoomData(itemsDB):
    roomToLatestOccupancy = {}
    roomToLatestBattery = {}
    print(itemsDB)
    for item in itemsDB:
        roomToLatestOccupancy[item['device_data']['location']] = item['device_data']['occupancy']
        roomToLatestBattery[item['device_data']['location']] = item['device_data']['battery']

    print(len(roomToLatestOccupancy))
    return roomToLatestOccupancy, roomToLatestBattery

@app.route("/")
def home_page():
    items = dynamodb_aws_handler.Occupancy_table.scan()['Items']

    global maxNumOfRoomsInDB 
    maxNumOfRoomsInDB = len(items)
    room_idx = 0

    not_full_count = 37 # has to be changed!
    full_count = int(items[room_idx]['device_data']['occupancy'])

    d = datetime.now()
    dt = pytz.timezone('America/Chicago').localize(d)
    d = d.strftime('%B %d, %Y ; %I:%M:%S %p')

    roomsToLatestOccupancy, roomsToLatestBattery = parseLatestRoomData(items)
    # battery = items[room_idx]['device_data']['battery']
    location = items[room_idx]['device_data']['location']
    battery = roomsToLatestBattery[location]
    full_count = int(roomsToLatestOccupancy[location])
    siebel4022_data = {'Task' : 'Hours per Day', 'Not Full' : not_full_count, 'Full' : full_count} 
    device_id = items[room_idx]['device_id']

    return render_template("pie_siebel.html",data=siebel4022_data, full_count=full_count, now_time=d, battery=battery, device_id=device_id,
    location = location)
    # return jsonify(connectAWS.get_items())

@app.route("/update")
def update_home_page():
    global room_idx
    room_idx = (room_idx + 1) % maxNumOfRoomsInDB

    items = dynamodb_aws_handler.Occupancy_table.scan()['Items']

    not_full_count = 37
    full_count = int(items[room_idx]['device_data']['occupancy'])
    d = datetime.now()
    dt = pytz.timezone('America/Chicago').localize(d)
    d = d.strftime('%B %d, %Y ; %I:%M:%S %p')

    battery = items[room_idx]['device_data']['battery']
    location = items[room_idx]['device_data']['location']
    siebel4022_data = {'Task' : 'Hours per Day', 'Not Full' : not_full_count, 'Full' : full_count} 
    device_id = items[room_idx]['device_id']

    return render_template("pie_siebel.html",data=siebel4022_data, full_count=full_count, now_time=d, battery=battery, device_id=device_id,
    location = location)

class DB:
    def retrieve_value(sensor, metric=None):
        return DB.retrieve_values(sensor, metric)[0]
