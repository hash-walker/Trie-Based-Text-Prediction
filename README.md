# Trie-Based Text Prediction System

This program implements a text prediction system using a Trie data structure. It reads an article, builds a Trie to store words and their frequencies, and provides suggestions for text completion based on user input.

## Features
- **Insert Sentences and Articles**: Populate the Trie with words and their frequencies from individual sentences or entire articles.
- **Text Prediction**: Provides up to four text suggestions based on user input, prioritizing frequently occurring words.
- **Display Trie Structure**: Visualize the stored Trie structure with word frequencies for debugging and analysis.

## How It Works
1. **Trie Structure**:
   - Each node stores:
     - A word (`string word`).
     - Its frequency (`int freq`).
     - A list of child nodes (`vector<node*> next`).

2. **Input and Prediction**:
   - The program reads an article (`article.txt`) to build the Trie.
   - Users can type text, and the system predicts the next possible words based on the Trie structure.
   - The user can select one of the suggested words to append to their input.

3. **Suggestions**:
   - The `suggest_four()` function selects the top 4 words with the highest frequencies from the current node's children.

## How to Run
1. **Compile the Program**:
   ```bash
   g++ -o text_predictor A3_2022661_2022204.cpp
   ```

2. **Run the Program**:
   ```bash
   ./text_predictor
   ```

3. **Provide Input**:
   - Type a sentence or press Enter to receive suggestions.
   - Choose a suggestion (1-4) to complete your sentence.
   - The process continues until no suggestions are available or the user decides to stop.

## File Requirements
- The program reads an article from a file named `article.txt`. Ensure this file exists in the same directory as the executable.

### Example `article.txt` Content:
```plaintext
The quick brown fox jumps over the lazy dog.
The quick brown fox is clever and fast.
The dog is lazy but friendly.
```

## Example Usage
### Input:
```text
Enter Sentence or Press Enter for suggestions: The quick
```

### Output:
```text
    1. brown
    2. fox
    3. is
    4. dog
Select a suggestion (1-4): 2

Enter Sentence or Press Enter for suggestions: The quick fox
    1. jumps
    2. is
    3. is clever
    4. over
Select a suggestion (1-4): 1

Final Sentence: The quick fox jumps
```

## Functions Overview
### **Trie Class**
1. `insert_sentence(string s)`: Splits a sentence into words and adds them to the Trie.
2. `predicted_text(string s)`: Predicts up to four next words based on the given input string.
3. `insert_article(string path)`: Reads an article file, splits it into sentences, and adds them to the Trie.
4. `print_elements(node* current, string space)`: Recursively prints the Trie structure for debugging.

### **Utility Functions**
1. `words_split(const string& s)`: Splits a string into words.
2. `lower(string upper)`: Converts a string to lowercase.
3. `suggest_four(vector<node*> current)`: Returns the top four suggestions based on word frequency.

## Limitations
- Assumes the input file `article.txt` exists and is formatted correctly.
- Limited to suggesting up to four words at a time.
- No advanced grammar or contextual analysis beyond word frequency.

## Author
Developed by **Hamza**, 2023.

## License
This project is free to use and modify under the MIT License.
