from flask import render_template, request, jsonify, redirect
from flask.helpers import url_for
from app import app
import pytz
from datetime import datetime
from app import connectAWS as dynamodb_aws_handler

# https://medium.com/featurepreneur/crud-operations-on-dynamodb-with-flask-apis-916f6cae992

room_idx = 1 # global static room index
maxNumOfRoomsInDB = 2 # global static max # of rooms in DB

@app.route("/")
def home_page():
    # global room_idx
    # room_idx = (room_idx + 1) % 2
    # dynamodb_aws_handler.create_occupancy_table()
    print(dynamodb_aws_handler.Occupancy_table)
    response = dynamodb_aws_handler.Occupancy_table.get_item(Key={
        "sample_time": 1667948705117,
        "device_id": 22
    })
    # data = response['Items']
    # while 'LastEvaluatedKey' in response:
    #     response = dynamodb_aws_handler.scan(ExclusiveStartKey=response['LastEvaluatedKey'])
    #     data.extend(response['Items'])
    items = dynamodb_aws_handler.Occupancy_table.scan()['Items']
    global maxNumOfRoomsInDB 
    maxNumOfRoomsInDB = len(items)
    print(maxNumOfRoomsInDB)
    not_full_count = 37
    full_count = int(items[room_idx]['device_data']['occupancy'])
    d = datetime.now()
    dt = pytz.timezone('America/Chicago').localize(d)
    d = d.strftime('%B %d, %Y ; %I:%M:%S %p')
    battery = items[room_idx]['device_data']['battery']
    print(battery)
    print(d)
    location = items[room_idx]['device_data']['location']
    siebel4022_data = {'Task' : 'Hours per Day', 'Not Full' : not_full_count, 'Full' : full_count} 
    device_id = items[room_idx]['device_id']
    return render_template("pie_siebel.html",data=siebel4022_data, full_count=full_count, now_time=d, battery=battery, device_id=device_id,
    location = location)
    # return jsonify(connectAWS.get_items())

@app.route("/update")
def update_home_page():
    global room_idx
    room_idx = (room_idx + 1) % maxNumOfRoomsInDB
    response = dynamodb_aws_handler.Occupancy_table.get_item(Key={
        "sample_time": 1667948705117,
        "device_id": 22
    })
    items = dynamodb_aws_handler.Occupancy_table.scan()['Items']
    not_full_count = 37
    full_count = int(items[room_idx]['device_data']['occupancy'])
    d = datetime.now()
    dt = pytz.timezone('America/Chicago').localize(d)
    d = d.strftime('%B %d, %Y ; %I:%M:%S %p')
    battery = items[room_idx]['device_data']['battery']
    print(battery)
    print(d)
    location = items[room_idx]['device_data']['location']
    siebel4022_data = {'Task' : 'Hours per Day', 'Not Full' : not_full_count, 'Full' : full_count} 
    device_id = items[room_idx]['device_id']
    return render_template("pie_siebel.html",data=siebel4022_data, full_count=full_count, now_time=d, battery=battery, device_id=device_id,
    location = location)

class DB:
    def retrieve_value(sensor, metric=None):
        return DB.retrieve_values(sensor, metric)[0]
