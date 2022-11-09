from flask import render_template, request, jsonify, redirect
from flask.helpers import url_for
from app import app
import pytz
from datetime import datetime
from app import connectAWS

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

# @app.route('/get-items')
# def get_items():
#     return jsonify(connectAWS.get_items())