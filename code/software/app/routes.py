from flask import render_template, request, jsonify, redirect
from flask.helpers import url_for
from app import app
import pytz
from datetime import datetime
from app import connectAWS as dynamodb_aws_handler

# @app.route('/')
# def root_route():
#     dynamodb_aws_handler.create_occupancy_table()
#     return 'Hello World'

#  Route: http://localhost:5000/book
#  Method : POST
@app.route('/book', methods=['POST'])
def addItemFlask():

    data = request.get_json()
    # id, title, author = 1001, 'Angels and Demons', 'Dan Brown'

    response = dynamodb_aws_handler.addItem(data['id'], data['title'], data['author'])    
    
    if (response['ResponseMetadata']['HTTPStatusCode'] == 200):
        return {
            'msg': 'Added successfully',
        }

    return {  
        'msg': 'Some error occcured',
        'response': response
    }

#  Route: http://localhost:5000/book/<id>
#  Method : GET
@app.route('/book/<int:id>', methods=['GET'])
def ReadItemFlask(id):
    response = dynamodb_aws_handler.ReadItem(id)
    
    if (response['ResponseMetadata']['HTTPStatusCode'] == 200):
        
        if ('Item' in response):
            return { 'Item': response['Item'] }

        return { 'msg' : 'Item not found!' }

    return {
        'msg': 'Some error occured',
        'response': response
    }

#  Route: http://localhost:5000/book/<id>
#  Method : DELETE
@app.route('/book/<int:id>', methods=['DELETE'])
def DeleteAnItemFlask(id):

    response = dynamodb_aws_handler.DeleteAnItem(id)

    if (response['ResponseMetadata']['HTTPStatusCode'] == 200):
        return {
            'msg': 'Deleted successfully',
        }

    return {  
        'msg': 'Some error occcured',
        'response': response
    } 

#  Route: http://localhost:5000/book/<id>
#  Method : PUT
@app.route('/book/<int:id>', methods=['PUT'])
def UpdateItemFlask(id):

    data = request.get_json()
    # data = {
    #     'title': 'Angels And Demons',
    #     'author': 'Daniel Brown'
    # }
    response = dynamodb_aws_handler.UpdateItem(id, data)

    if (response['ResponseMetadata']['HTTPStatusCode'] == 200):
        return {
            'msg'                : 'Updated successfully',
            'ModifiedAttributes' : response['Attributes'],
            'response'           : response['ResponseMetadata']
        }

    return {
        'msg'      : 'Some error occured',
        'response' : response
    }   

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
