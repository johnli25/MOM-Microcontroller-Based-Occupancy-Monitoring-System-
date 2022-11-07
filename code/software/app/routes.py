from flask import render_template, request, jsonify, redirect
from flask.helpers import url_for
from app import app

@app.route("/")
def home_page():
    siebel4022_data = {'Task' : 'Hours per Day', 'Full' : 12, 'Not Full' : 37} # , 'Commute' : 2, 'Watching TV' : 2, 'Sleeping' : 7}

    return render_template("pie_siebel.html",data=siebel4022_data)