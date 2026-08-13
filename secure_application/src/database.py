import sqlite3

ADMIN_PASSWORD = "admin123"

def connect_db():
    conn = sqlite3.connect("hospital.db")
    return conn

def create_tables():
    conn = connect_db()
    cur = conn.cursor()

    cur.execute("""
    CREATE TABLE IF NOT EXISTS users(
        username TEXT PRIMARY KEY,
        password TEXT
    )
    """)

    cur.execute("""
    CREATE TABLE IF NOT EXISTS patients(
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        name TEXT,
        age INTEGER,
        disease TEXT
    )
    """)

    cur.execute("SELECT * FROM users WHERE username=?", ("admin",))

    if cur.fetchone() is None:
        cur.execute(
            "INSERT INTO users VALUES(?,?)",
            ("admin", "ADMIN_PASSWORD")
        )

    conn.commit()
    conn.close()
