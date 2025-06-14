#THIS TEMPLATE IS FOR REFERENCE ONLY, YOU ARE FREE TO USE YOUR OWN LOGIC
#HAPPY LEARNING

import time

# TODO: Implement a simple hash function or use a real one
def simple_hash(input_str):
    # Simulate a hash by processing the input string
    pass

# Block class
class Block:
    def __init__(self, index, data, previous_hash):
        self.index = index
        self.timestamp = self.get_timestamp()
        self.data = data
        self.previous_hash = previous_hash
        self.hash = None  # To be set after hashing
        self.next = None

        # TODO: Create a string from block data to hash

        # TODO: Call simple_hash on the string and store in self.hash

    # TODO: Fill this to get current time in string format
    def get_timestamp(self):
        # Fill and return current date-time
        pass

# TODO: Implement logic to create a new block
def create_block(index, data, previous_hash):
    # Create a new Block object and set all required fields
    pass

# TODO: Implement logic to add a block to the chain
def add_block(head, data):
    # Traverse to the last block
    # Get index and previous_hash
    # Call create_block and link the new block
    pass

# TODO: Print all blocks in the blockchain
def print_chain(head):
    # Traverse the chain and print block details
    pass

if __name__ == "__main__":
    blockchain = None

    # TODO: Add a few blocks with sample data
    # blockchain = add_block(blockchain, "Genesis Block")
    # blockchain = add_block(blockchain, "Sample transaction")

    # TODO: Print the chain
    # print_chain(blockchain)

    # TODO: Free the chain (handled by garbage collector in Python)
