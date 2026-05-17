# Survey Parser (C)

A high-performance C-based data parser that processes raw survey data and converts it into structured, analysis-ready datasets using Likert scale normalization.

## Overview

This project was built to simulate real-world data ingestion challenges, where input data is often inconsistent, incomplete, or unstructured.

The Survey Parser reads raw survey files, validates and cleans the data, and transforms responses into a standardized format suitable for downstream analysis.

It emphasizes:
- Data integrity
- Efficient memory usage
- Robust error handling
- Structured data transformation

## Key Features

- Custom File Parser  
  Processes raw text-based survey files using efficient file I/O in C.

- Likert Scale Normalization  
  Converts qualitative survey responses (e.g., "Strongly Agree") into consistent numerical representations.

- Data Validation & Cleaning  
  Handles:
  - Missing values  
  - Invalid inputs  
  - Inconsistent formatting  

- Error Handling  
  Detects and safely handles malformed data without crashing.

- Memory-Efficient Design  
  Uses manual memory management to ensure performance and reliability.

## How It Works

1. Input  
   Raw survey data is read from a text file.

2. Parsing  
   The program tokenizes each line and extracts structured fields.

3. Validation  
   Each response is checked for correctness and completeness.

4. Transformation  
   Responses are mapped to a normalized Likert scale (e.g., 1–5).

5. Output  
   Cleaned data is written to a structured format (e.g., CSV).

## Installation & Usage

Compile:
make

Run:
./test_scripts.sh

## Skills Demonstrated

- Low-level programming in C
- File I/O and string parsing
- Data cleaning and normalization
- Memory management (malloc/free)
- Error handling and edge case coverage
- Data pipeline thinking (raw → processed → structured)

## Real-World Relevance

This project mirrors real-world data workflows where:
- Raw inputs are inconsistent and require cleaning
- Data must be normalized before analysis
- Reliability and correctness are critical

These concepts directly apply to:
- Data analysis pipelines
- Risk analysis systems
- Business intelligence workflows

## Future Improvements

- Add support for JSON/CSV input formats
- Implement multi-threaded parsing for large datasets
- Export results to database systems (SQLite/PostgreSQL)
- Add statistical summaries (mean, distribution, etc.)
- Build a simple visualization layer

## Author

Samuel Echefu  
GitHub: https://github.com/samnne  
LinkedIn: https://linkedin.com/in/samuel-echefu-251a21336

