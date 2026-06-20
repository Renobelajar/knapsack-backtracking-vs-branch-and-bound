# 0/1 Knapsack Problem: Backtracking vs. Branch and Bound

This repository contains a C++ comparative implementation to solve the classic **0/1 Knapsack Problem**. The project demonstrates how the exact same optimization problem can be tackled using two distinct algorithmic paradigms: **Backtracking** and **Branch & Bound**.

## Problem Statement (Case Study)

A thief breaks into a luxury jewelry store. He finds **4 valuable items**, each with a specific weight and profit value. However, the thief only brought **one backpack** with a maximum weight capacity of **15 kg**. 

Since these are high-value discrete items, they **cannot be divided or cut** (hence the **0/1** property: either leave it `0` or take it as a whole `1`). 

### Available Items Data
| Item ID | Profit (Value) | Weight | Profit-to-Weight Ratio |
| :---: | :---: | :---: | :---: |
| Item 1 | Rp 10 Million | 2 kg | 5.0 |
| Item 2 | Rp 10 Million | 4 kg | 2.5 |
| Item 3 | Rp 12 Million | 6 kg | 2.0 |
| Item 4 | Rp 18 Million | 9 kg | 2.0 |

* **Maximum Knapsack Capacity ($W$):** 15 kg
* **Objective:** Find the optimal combination of items that maximizes the total profit without exceeding the 15 kg weight limit.

---

## Algorithmic Approaches

### 1. Backtracking (Depth-First Search)
* **Strategy:** It systematically explores the state space tree by going deep down a single path. 
* **Mechanism:** If the total weight exceeds 15 kg, the algorithm stops exploring further down that branch (dead end) and backtracks to the previous decision point to try another alternative.
* **Pros/Cons:** Highly memory-efficient ($O(n)$ space complexity) but can be slow for larger datasets since it explores many redundant nodes.

### 2. Branch and Bound (Best-First Search)
* **Strategy:** It utilizes a **Priority Queue** to explore the state space tree using a *Best-First* approach.
* **Mechanism:** Before expanding a node, it calculates a theoretical maximum upper bound using a fractional knapsack simulation. If a branch's upper bound is lower than the best profit found so far, the entire branch is **pruned** (discarded) from the memory.
* **Pros/Cons:** Extremely fast for large datasets because it aggressively cuts down unnecessary calculations. However, it requires more RAM to store active queue nodes.


## Optimal Solution

Both algorithms independently arrive at the exact same optimal solution:
* **Items Selected:** Item 1, Item 2, and Item 4.
* **Total Weight:** $2\text{ kg} + 4\text{ kg} + 9\text{ kg} = \mathbf{15\text{ kg}}$ (Perfect fit).
* **Maximum Profit:** $\text{Rp } 10\text{M} + \text{Rp } 10\text{M} + \text{Rp } 18\text{M} = \mathbf{\text{Rp } 38\text{ Million}}$.


## How to Run the Code

### Prerequisites
Make sure you have a C++ compiler installed (e.g., `g++` via GCC, Clang, or MSVC).

### Running the Backtracking Implementation
1. Navigate to the directory containing the files.
2. Compile the backtracking file:
   ```bash
   g++ -o backtracking backtracking.cpp
