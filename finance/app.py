import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    PORTFOLIO = db.execute("SELECT symbol, shares FROM portfolio WHERE person_id=(?)", session["user_id"])
    x = len(PORTFOLIO)
    runningTotal = 0
    for i in range(x):
        otherInfo = lookup(PORTFOLIO[i]['symbol'])
        PORTFOLIO[i]['name'] = otherInfo['name']
        PORTFOLIO[i]['price'] = otherInfo['price']
        totalValue = otherInfo['price'] * PORTFOLIO[i]['shares']
        PORTFOLIO[i]['value'] = totalValue
        runningTotal += totalValue
    cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
    if len(cash) > 0:
        netWorth = cash[0]["cash"] + runningTotal
        return render_template("portfolio.html", portfolio = PORTFOLIO, x=x, runningTotal=runningTotal, cash=cash, netWorth=netWorth)
    else:
        return render_template("login.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not str(symbol.strip()):
            return apology("Blank Symbol.")
        elif lookup(symbol) == None:
            return apology("Symbol not found.")
        shares = request.form.get("shares")
        try:
            val = int(shares)
        except ValueError:
            try:
                val = float(shares)
            except ValueError:
                return apology("invalid number of shares")
        if float(shares) <= 0:
            return apology("invalid number of shares")
        symbol_Dict = lookup(symbol)
        share_price = float(symbol_Dict['price'])
        cost = share_price * float(shares)
        cash_list = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash1 = float(cash_list[0]['cash'])
        if cost > cash1:
            return apology("You're too poor")
        else:
            db.execute("UPDATE users SET cash = ? WHERE id = ?", float(cash1 - cost), session["user_id"])
            db.execute("INSERT INTO transactions (shares, symbol, total_cost, person_id, type, datetime) VALUES (?, ?, ?, ?, ?, datetime('now'))", float(shares), symbol.upper(), float(cost), session["user_id"], "Buy")
            check = db.execute("SELECT symbol FROM portfolio WHERE symbol=? AND person_id=?", symbol.upper(), session["user_id"])
            if len(check) == 0:
                db.execute("INSERT INTO portfolio (person_id, symbol, shares) VALUES (?, ?, ?)", session["user_id"], symbol.upper(), float(shares))
            else:
                oldShares = db.execute("SELECT shares FROM portfolio WHERE person_id = ? AND symbol = ?", session["user_id"], symbol.upper())
                newShares = float(shares) + float(oldShares[0]['shares'])
                db.execute("UPDATE portfolio SET shares = ? WHERE person_id = ? AND symbol = ?", float(newShares), session["user_id"], symbol.upper())
            return render_template("success.html")
    else:
        return render_template("buy.html")



@app.route("/history")
@login_required
def history():
    transactions = db.execute("SELECT symbol, total_cost, type, datetime FROM transactions WHERE person_id=?", session["user_id"])
    x = len(transactions)
    for i in range(x):
        otherInfo = lookup(transactions[i]['symbol'])
        transactions[i]['name'] = otherInfo['name']
        transactions[i]['price'] = float(otherInfo['price'])
    return render_template("history.html", transactions=transactions, x=x)




@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == 'POST':
        symbol = request.form.get("symbol")
        if not str(symbol.strip()):
            return apology("Blank Symbol.")
        elif lookup(symbol) == None:
            return apology("Symbol not found.")
        QUOTE = lookup(symbol)
        return render_template("quoted.html", quote=QUOTE)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """TODO: Register user COMPLETE"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if not username.strip():
            return apology("Username is blank")
        elif int(len(db.execute("SELECT * FROM users WHERE username = ? ", username))) > 0:
            return apology("Username is taken")
        elif password != confirmation:
            return apology("Passwords don't match")
        elif not password.strip():
            return apology("Password is blank")
        else:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))
            return redirect("/login")
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    portfolio = db.execute("SELECT symbol, shares FROM portfolio WHERE person_id=?", session["user_id"])
    x = len(portfolio)
    if request.method == "POST":
        soldSymbol = request.form.get('symbol')
        soldShares = request.form.get('shares')
        try:
            val = int(shares)
        except ValueError:
            try:
                val = float(shares)
            except ValueError:
                return apology("invalid number of shares")
        for i in range(x):
            if portfolio[i]['symbol'] == soldSymbol.upper():
                dict = lookup( portfolio[i]['symbol'])
                portfolio[i]['price'] = dict['price']
                if portfolio[i]['shares'] >= float(soldShares) and float(soldShares) > 0:
                    newShares = float(portfolio[i]['shares']) - float(soldShares)
                    db.execute("UPDATE portfolio SET shares = ? WHERE person_id = ? AND symbol = ?", float(newShares), session["user_id"], soldSymbol.upper())
                    newCash = float(portfolio[i]['price']) * float(soldShares)
                    db.execute("INSERT INTO transactions (shares, symbol, total_cost, person_id, type, datetime) VALUES (?, ?, ?, ?, ?, datetime('now'))",float(soldShares), soldSymbol.upper(), float(newCash), session["user_id"], 'Sold')
                    cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
                    newWorth = float(cash[0]["cash"]) + float(newCash)
                    db.execute("UPDATE users SET cash = ? WHERE id = ?", float(newWorth), session["user_id"])
                    db.execute("DELETE FROM portfolio WHERE shares=0")
                    return render_template("success.html")
                else:
                    return apology("invalid number of shares")
    else:
        return render_template("sold.html", x=x, portfolio=portfolio)
