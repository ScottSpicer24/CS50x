import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

MONTHS = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
DAYMIN = 1

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        name = request.form.get("name")

        month = request.form.get("month")
        if int(month) not in MONTHS:
            return render_template("error.html", message = "Invalid Month.")
        elif int(month) == 2:
            DAYMAX = 29
        elif int(month) == 4 or int(month) == 6 or int(month) == 9 or int(month) == 11:
            DAYMAX = 30
        else:
            DAYMAX = 31

        day = request.form.get("day")
        if DAYMIN > int(day) or int(day) > DAYMAX:
            return render_template("error.html", message = "Invalid day")

        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)

        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays;")
        return render_template("index.html", birthdays=birthdays)

@app.route("/remove", methods=["POST"])
def remove():
    id = request.form.get("id")
    if id:
        db.execute("DELETE FROM birthdays WHERE id = ?;", id)
    return redirect("/")

