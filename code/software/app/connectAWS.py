import boto3

dynamo_client = boto3.client('dynamodb')

# dynamodb = boto3.resource('dynamodb', region_name='us-east-1', aws_access_key)
# AWS_ACCESS_KEY_ID = config.AWS_ACCESS_KEY_ID
# AWS_SECRET_ACCESS_KEY = config.AWS_SECRET_ACCESS_KEY
# REGION_NAME = config.REGION_NAME
 
resource = boto3.resource(
   'dynamodb',
   aws_access_key_id     = "AKIA5BSW6IQX6DQ35V5T",
   aws_secret_access_key = "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",
   region_name           = "us-east-1"
)

occ_table = resource.Table('Occupancy_data')

def get_items():
    return dynamo_client.scan(
        TableName='Occupancy_data'
    )
    # table = dynamodb.Table('Ocuupancy_data')
    # print(table)
    # return table