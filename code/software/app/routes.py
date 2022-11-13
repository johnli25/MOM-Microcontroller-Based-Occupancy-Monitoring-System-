from flask import render_template, request, jsonify, redirect
from flask.helpers import url_for
from app import app
import pytz
from datetime import datetime
from app import connectAWS

import connectAWS as dynamodb_aws_handler

@app.route('/')
def root_route():
    dynamodb_aws_handler.CreatATableBook()
    return 'Hello World'

#  Add a book entry
#  Route: http://localhost:5000/book
#  Method : POST
@app.route('/book', methods=['POST'])
def addABook():

    data = request.get_json()
    # id, title, author = 1001, 'Angels and Demons', 'Dan Brown'

    response = dynamodb_aws_handler.addItemToBook(data['id'], data['title'], data['author'])    
    
    if (response['ResponseMetadata']['HTTPStatusCode'] == 200):
        return {
            'msg': 'Added successfully',
        }

    return {  
        'msg': 'Some error occcured',
        'response': response
    }

#  Read a book entry
#  Route: http://localhost:5000/book/<id>
#  Method : GET
@app.route('/book/<int:id>', methods=['GET'])
def getBook(id):
    response = dynamodb_aws_handler.GetItemFromBook(id)
    
    if (response['ResponseMetadata']['HTTPStatusCode'] == 200):
        
        if ('Item' in response):
            return { 'Item': response['Item'] }

        return { 'msg' : 'Item not found!' }

    return {
        'msg': 'Some error occured',
        'response': response
    }


#  Delete a book entry
#  Route: http://localhost:5000/book/<id>
#  Method : DELETE
@app.route('/book/<int:id>', methods=['DELETE'])
def DeleteABook(id):

    response = dynamodb_aws_handler.DeleteAnItemFromBook(id)

    if (response['ResponseMetadata']['HTTPStatusCode'] == 200):
        return {
            'msg': 'Deleted successfully',
        }

    return {  
        'msg': 'Some error occcured',
        'response': response
    } 


#  Update a book entry
#  Route: http://localhost:5000/book/<id>
#  Method : PUT
@app.route('/book/<int:id>', methods=['PUT'])
def UpdateABook(id):

    data = request.get_json()

    # data = {
    #     'title': 'Angels And Demons',
    #     'author': 'Daniel Brown'
    # }

    response = dynamodb_aws_handler.UpdateItemInBook(id, data)

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

#  Like a book
#  Route: http://localhost:5000/like/book/<id>
#  Method : POST
@app.route('/like/book/<int:id>', methods=['POST'])
def LikeBook(id):

    response = dynamodb_aws_handler.LikeABook(id)

    if (response['ResponseMetadata']['HTTPStatusCode'] == 200):
        return {
            'msg'      : 'Likes the book successfully',
            'Likes'    : response['Attributes']['likes'],
            'response' : response['ResponseMetadata']
        }

    return {
        'msg'      : 'Some error occured',
        'response' : response
    }

# if __name__ == '__main__':
#     app.run(host='localhost', port=5000, debug=True)

@app.route("/")
def home_page():
    not_full_count = 37
    full_count = 12
    d = datetime.now()
    dt = pytz.timezone('America/Chicago').localize(d)
    d = d.strftime('%B %d, %Y ; %I:%M:%S %p')
    battery = 56
    print(d)
    siebel4022_data = {'Task' : 'Hours per Day', 'Not Full' : not_full_count, 'Full' : full_count} 
    print("test")
    return render_template("pie_siebel.html",data=siebel4022_data, full_count=full_count, now_time=d, battery=battery)
    # return jsonify(connectAWS.get_items())

class DB:
    def retrieve_value(sensor, metric=None):
        return DB.retrieve_values(sensor, metric)[0]

# @app.route('/get-items')
# def get_items():
#     return jsonify(connectAWS.get_items())