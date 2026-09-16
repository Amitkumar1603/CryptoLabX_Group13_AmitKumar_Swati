# CryptoLabX

CryptoLabX is our Cryptography Lab  Repository
This repository contains the implementation, experiments, test cases, reports, and screenshots for all  laboratory assignments.


## Team Members

Group No.:- 13

1. Amit Kumar (2024UCP1597)
2. Swati (2024UCP1644)



## Assignments

# Assignment 1 – Build Your CryptoLabX Toolkit

In the first assignment, we created the basic structure of the CryptoLabX project.

Main work included:

- Creating the GitHub repository
- Creating the required folder structure
- Making a menu-driven command-line interface
- Adding options like Encrypt, Decrypt, Attack, Analyze and Exit
- Reading text files from the datasets folder
- Finding number of characters, words and lines
- Finding unique characters and letter frequency
- Creating datasets for future assignments
- Adding basic logging

---

### Lab 2 – Static Application Security Testing (SAST)

In Lab 2, we studied **Static Application Security Testing (SAST)** and learned how SAST tools can detect security problems in source code without running the program.

Our assigned tool is **Bandit**.

During this lab, we:

- Installed Bandit
- Checked the Bandit version
- Learned how Bandit works
- Tested Bandit on small Python programs
- Created Python code containing common security issues
- Ran Bandit and studied the warnings
- Observed the rule ID, severity, confidence and line number of reported issues

### Lab 3 – Hospital Management System using Bandit


 the assigned application is Hospital Management System.

The application includes basic functionality related to:

- Patient registration
- Appointments
- Prescriptions
- Billing
- Medical records

We intentionally added some insecure coding practices to the application so that Bandit could identify them.

The main security issues demonstrated include:

- SQL Injection
- Broken Access Control
- File Upload Vulnerability
- Missing Authorization
- Path Traversal

We then ran Bandit on the application and analyzed the security findings.

-----

### Assignment 4 – Shift Cipher Cryptanalysis

In this assignment, we worked with the **Shift Cipher** and its cryptanalysis.

The main techniques used were:

- Brute Force
- Dictionary Scoring
- Chi-Square Analysis

The program tries different keys and compares the generated plaintexts to determine the possible correct key.

We also compare the key predicted using dictionary scoring with the key predicted using Chi-Square analysis.

The results, observations and failure analysis are included in the corresponding assignment folder.

---

### Assignment 5 – Monoalphabetic Substitution Cipher

This assignment focuses on the **Monoalphabetic Substitution Cipher** and its cryptanalysis.

We first generate ciphertext using a substitution key and then try to recover the plaintext.

The main techniques used are:

- Letter Frequency Analysis
- Word Frequency Analysis
- Pattern Analysis
- Repeated word analysis
- Iterative substitution

The cryptanalysis is performed by observing the frequency of ciphertext letters, word patterns and repeated characters and then testing possible substitutions.

The recovered key is finally verified by re-encrypting the plaintext.

---

### Assignment 6 – Vigenère Cipher Cryptanalysis

In this assignment, we worked on **Vigenère Cipher cryptanalysis** using **Kasiski Examination and Frequency Analysis**.

The main steps are:

1. Clean the ciphertext
2. Find repeated patterns
3. Calculate distances between repeated patterns
4. Find factors of those distances
5. Estimate the key length
6. Divide the ciphertext into groups
7. Perform frequency analysis
8. Find the probable key
9. Decrypt the ciphertext
10. Re-encrypt the plaintext for verification

The program also calculates the Index of Coincidence and uses it as part of the key-length analysis.

---
