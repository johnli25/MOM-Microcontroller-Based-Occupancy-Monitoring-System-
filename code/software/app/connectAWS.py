import flask as fl
import boto3

class DB:
   # Query db for the last 20 measures of a sensor
   def retrieve_values(sensor, metric=None):       table = db.Table('Measurements')       response = table.query(
           KeyConditionExpression=Key('sensor').eq(sensor),
           ScanIndexForward=False,
           Limit=2)       items = []
​
       for i in response[u'Items']:           # Transforming timestamp to readable hour and minutes
           # in one line
           i['message']['timestamp'] = datetime.fromtimestamp(int(i['timestamp'][:-3])).strftime('%H:%M')
​
           if metric is not None:               #if metric is set return only that value
               i = i['message'][metric]           else:
               # otherwise return all metrics for this sensor
               i = i['message']
​
           items.append(i)
       return items

client = boto3.client('iot')

def countDevices():
    pass    

def measureOccupancy():
    pass

if __name__ == '__main__':
    countDevices()
    measureOccupancy()

