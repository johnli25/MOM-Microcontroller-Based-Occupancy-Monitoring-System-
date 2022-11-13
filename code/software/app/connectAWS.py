import boto3
from boto3 import resource
import config

AWS_ACCESS_KEY_ID = config.AWS_ACCESS_KEY_ID
AWS_SECRET_ACCESS_KEY = config.AWS_SECRET_ACCESS_KEY
REGION_NAME = config.REGION_NAME
 
resource = resource('dynamodb',
   aws_access_key_id     = AWS_ACCESS_KEY_ID,
   aws_secret_access_key = AWS_SECRET_ACCESS_KEY,
   region_name           = REGION_NAME
)

# client = boto3.client('dynamodb',
#   aws_access_key_id='AKIA5BSW6IQX6DQ35V5T',
#   aws_secret_access_key='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',
#   region_name='us-east-1')

# dynamodb = boto3.resource('dynamodb')
# table = dynamodb.Table('Occupancy_data')

# table.get_time(


# )

# dynamo_client = boto3.client('dynamodb')

# # dynamodb = boto3.resource('dynamodb', region_name='us-east-1', aws_access_key)
# # AWS_ACCESS_KEY_ID = config.AWS_ACCESS_KEY_ID
# # AWS_SECRET_ACCESS_KEY = config.AWS_SECRET_ACCESS_KEY
# # REGION_NAME = config.REGION_NAME
 
# resource = boto3.resource(
#    'dynamodb',
#    aws_access_key_id     = "AKIA5BSW6IQX6DQ35V5T",
#    aws_secret_access_key = "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",
#    region_name           = "us-east-1"
# )

# occ_table = resource.Table('Occupancy_data')

# def get_items():
#     return dynamo_client.scan(
#         TableName='Occupancy_data'
#     )
#     # table = dynamodb.Table('Ocuupancy_data')
#     # print(table)
#     # return table
import boto3
dynamodb = boto3.resource('dynamodb', region_name='us-east-1')

table = dynamodb.Table('Occupancy_data')

response = table.scan()
data = response['Items']

while 'LastEvaluatedKey' in response:
    response = table.scan(ExclusiveStartKey=response['LastEvaluatedKey'])
    data.extend(response['Items'])

#https://dynobase.dev/dynamodb-python-with-boto3/

#https://www.youtube.com/watch?v=UuX2AFq_OkU&list=PLz8JBMMd7yjUHKAimoaN2A3aEr20Hq9yB&index=3
