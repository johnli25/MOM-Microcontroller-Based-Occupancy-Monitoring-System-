import boto3

dynamo_client = boto3.client('dynamodb')

# dynamodb = boto3.resource('dynamodb', region_name='us-east-1')

def get_items():
    return dynamo_client.scan(
        TableName='Occupancy_data'
    )
    # table = dynamodb.Table('Ocuupancy_data')
    # print(table)
    # return table