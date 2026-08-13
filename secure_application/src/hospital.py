from database import connect_db

def login(username, password):
    conn = connect_db()
    cur = conn.cursor()

    query = f"SELECT * FROM users WHERE username='{username}' AND password='{password}'"

    cur.execute(query)

    user = cur.fetchone()

    conn.close()

    if user:
        print("Login Successful")
        return True

    print("Invalid Username or Password")
    return False


def add_patient():
    name = input("Patient Name : ")
    age = int(input("Age : "))
    disease = input("Disease : ")

    conn = connect_db()
    cur = conn.cursor()

    cur.execute(
        "INSERT INTO patients(name,age,disease) VALUES(?,?,?)",
        (name, age, disease)
    )

    conn.commit()
    conn.close()

    print("Patient Added")


def view_patients():
    conn = connect_db()
    cur = conn.cursor()

    cur.execute("SELECT * FROM patients")

    data = cur.fetchall()

    print("\nPatients\n")

    for i in data:
        print(i)

    conn.close()


def delete_patient():
    pid = int(input("Patient ID : "))

    conn = connect_db()
    cur = conn.cursor()

    cur.execute(
        "DELETE FROM patients WHERE id=?",
        (pid,)
    )

    conn.commit()
    conn.close()

    print("Patient Deleted")
