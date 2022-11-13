import boto3
from boto3 import resource
import config

AWS_ACCESS_KEY_ID = 'AKIA5BSW6IQXVWMBIH6D' # config.AWS_ACCESS_KEY_ID
AWS_SECRET_ACCESS_KEY = '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' # config.AWS_SECRET_ACCESS_KEY
REGION_NAME = 'us-east-1' # config.REGION_NAME



client = boto3.client(
    'dynamodb',
    aws_access_key_id     = AWS_ACCESS_KEY_ID,
    aws_secret_access_key = AWS_SECRET_ACCESS_KEY,
    region_name           = REGION_NAME
)

resource = resource('dynamodb',
    aws_access_key_id     = AWS_ACCESS_KEY_ID,
    aws_secret_access_key = AWS_SECRET_ACCESS_KEY,
    region_name           = REGION_NAME
)

def create_occupancy_table():   
    table = client.create_table(
        TableName = 'Occupancy_data', # Name of the table
        KeySchema = [
            {
                'AttributeName': 'id',
                'KeyType'      : 'HASH' #RANGE = sort key, HASH = partition key
            }
        ],
        AttributeDefinitions = [
            {
                'AttributeName': 'id', # Name of the attribute
                'AttributeType': 'N'   # N = Number (B= Binary, S = String)
            }
        ],
        ProvisionedThroughput={
            'ReadCapacityUnits'  : 10,
            'WriteCapacityUnits': 10
        }
   )
    return table

Occupancy_table = resource.Table('Occupancy_data')

def addItem(id, title, author):
    response = Occupancy_table.put_item(
        Item = {
            'id'     : id,
            'title'  : title,
            'author' : author,
            'likes'  : 0
        }
    )
    return response

def ReadItem(id):
    response = Occupancy_table.get_item(
        Key = {
            'id'     : id
        },
        AttributesToGet=[
            'title', 'author'
        ]
    )
    return response

def UpdateItem(id, data:dict):
    response = Occupancy_table.update_item(
        Key = {
            'id': id
        },
        AttributeUpdates={
            'title': {
                'Value'  : data['title'],
                'Action' : 'PUT' # available options -> DELETE(delete), PUT(set), ADD(increment)
            },
            'author': {
                'Value'  : data['author'],
                'Action' : 'PUT'
            }
        },
        ReturnValues = "UPDATED_NEW" # returns the new updated values
    )
    return response

def DeleteAnItem(id):
    response = Occupancy_table.delete_item(
        Key = {
            'id': id
        }
    )
    return response
# table.get_time()

# dynamo_client = boto3.client('dynamodb')

# occ_table = resource.Table('Occupancy_data')

# def get_items():
#     return dynamo_client.scan(
#         TableName='Occupancy_data'
#     )
#     # table = dynamodb.Table('Ocuupancy_data')
#     # print(table)
#     # return table
# response = Occupancy_table.get_items()
# data = response['Items']

# while 'LastEvaluatedKey' in response:
#     response = Occupancy_table.scan(ExclusiveStartKey=response['LastEvaluatedKey'])
#     data.extend(response['Items'])

#https://dynobase.dev/dynamodb-python-with-boto3/

#https://www.youtube.com/watch?v=UuX2AFq_OkU&list=PLz8JBMMd7yjUHKAimoaN2A3aEr20Hq9yB&index=3
