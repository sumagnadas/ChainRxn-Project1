# Chain Rxn - Build Your Own Blockchain

Welcome to Project 1 of **Chain Rxn** (BIB Summer Bootcamp)!

In this project, you’ll build a simple **blockchain from scratch** to understand how blocks, hashes, and chain validation work under the hood. You’re free to use **any programming language** you’re comfortable with (C, Python, JavaScript, etc.).

---

## Getting Started

Follow these steps carefully. This guide assumes **no prior experience with GitHub**, so take it slow and read everything.

### Step 1: Fork This Repository

1. Click the **Fork** button at the top-right of this page.
2. A copy of this repository will be created in your own GitHub account.
3. Clone it to your local system using this command (replace `your-username`):

```bash
git clone https://github.com/your-username/ChainRxn-Project1
```
## 🧩 Task Overview
This project involves writing code to simulate a basic blockchain.

### Requirements:
- Create a **Block** structure/class with the following:
  - Index (block number)
  - Timestamp
  - Data (message or transaction)
  - Previous block’s hash
  - Current block’s hash (can use a simple/fake hash)

- Create a **Blockchain** class or logic that:
  - Starts with a **Genesis block**
  - Adds new blocks
  - Validates the integrity of the chain (check for tampering)

### Optional:
- Add Proof of Work or mining mechanism for added complexity.

---

## 🚀 How to Run

### If using C:
```bash
gcc blockchain.c -o blockchain
./blockchain
```
If using another language:
- Follow the normal run commands for that language.
- You can submit you solution in ANY PROGRAMMING LANGUAGE
- Templates have been added for Python and C.

- Add instructions in your own `README.md`

# 🚀 Pushing Changes to GitHub

After completing your implementation:

```bash
git add .
git commit -m "Completed my blockchain implementation"
git push origin main
```

> Replace `main` with `master` if your branch is named differently.

✅ **Verify your changes** are visible on your GitHub repository.

---

# 📤 Submitting Your Solution

Once ready and pushed:

1. Fill out the submission [Google Form](https://forms.gle/psN24KRMsGUbGTGP6).
2. Provide your:

   * **Full Name**
   * **Email ID**
   * **GitHub repo link** (e.g., `https://github.com/your-username/ChainRxn-Project1`)
3. Click **Submit**.

---

# 🕒 Deadline

Submit your solution by: **15th June' 25 (EOD)**

---

# 🏁 Final Tips

* Keep your code **simple and clear**.
* Focus on **understanding blockchain concepts**, not just coding.
* Document your code with comments or add a small `README.md` inside your repo.
* Try not using AI.

We look forward to seeing your first blockchain! 🚀

